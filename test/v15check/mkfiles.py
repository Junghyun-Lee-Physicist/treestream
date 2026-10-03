#!/usr/bin/env python3
"""Synthetic NanoAOD-like ROOT files with the REAL v15 2024 Events schema (names, types, counters)
taken from NtupleForge script/inventory/*.tsv, after the NtupleForge 2024 slim branch list.
Values are deterministic (h()), so the read-back can be checked branch by branch.
Usage: mkfiles.py <inventory.tsv> <branchlist.txt> <out.root> <seed> [--drop B1,B2] [--nev N] [--runs-first]
Also writes <out.root>.expect.json with every value written."""
import os, sys, json, argparse
import numpy as np
sys.path.insert(0, os.path.join(os.environ.get('NF', '.'), 'script'))
import check_branchlist as cb
import ROOT

CODE = {'Float_t': ('F', np.float32), 'Double_t': ('D', np.float64), 'Int_t': ('I', np.int32),
        'UInt_t': ('i', np.uint32), 'Short_t': ('S', np.int16), 'UShort_t': ('s', np.uint16),
        'UChar_t': ('b', np.uint8), 'Char_t': ('B', np.int8), 'Bool_t': ('O', np.bool_),
        'Long64_t': ('L', np.int64), 'ULong64_t': ('l', np.uint64)}
CAP = {'nGenPart': 40, 'nLHEScaleWeight': 9, 'nPSWeight': 4, 'nLHEPdfWeight': 30}

def h(bi, ev, j, seed):
    return ((bi * 1000003 + ev * 7919 + j * 104729 + 12345 + seed * 15485863) * 2654435761) % (2 ** 64)

def value(typ, name, x):
    if typ == 'Bool_t': return int(x % 2)
    if typ == 'UChar_t': return int(x % 256)
    if typ == 'Char_t': return int(x % 256) - 128
    if typ == 'Short_t': return int(x % 65536) - 32768
    if typ == 'UShort_t': return int(x % 65536)
    if typ == 'Int_t': return int(x % 2 ** 32) - 2 ** 31
    if typ == 'UInt_t': return int(x % 2 ** 32)
    if typ == 'Long64_t': return int(x % 2 ** 63) - 2 ** 62
    if typ == 'ULong64_t':
        return int(x % 10 ** 10) if name == 'event' else int(x % 2 ** 64)
    if typ == 'Float_t': return float(np.float32((int(x % 2000001) - 1000000) / 64.0))
    if typ == 'Double_t': return float((x % 2 ** 40) / 1024.0)
    raise SystemExit('type? %s' % typ)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('inv'); ap.add_argument('blist'); ap.add_argument('out'); ap.add_argument('seed', type=int)
    ap.add_argument('--drop', default=''); ap.add_argument('--nev', type=int, default=30)
    ap.add_argument('--runs-first', action='store_true'); ap.add_argument('--autoflush', type=int, default=0)
    a = ap.parse_args()
    rows = []
    for line in open(a.inv):
        if line.startswith('#') or not line.strip(): continue
        f = line.rstrip('\n').split('\t')
        if f[0] == 'Events': rows.append((f[1], f[2], f[3] if len(f) > 3 else ''))
    rules = cb.read_rules(a.blist)
    kept, _ = cb.apply_rules([r[0] for r in rows], rules)
    drop = set(x for x in a.drop.split(',') if x)
    sel = [r for r in rows if r[0] in kept and r[0] not in drop]
    counters_needed = set(r[2] for r in sel if r[2])
    have = set(r[0] for r in sel)
    for r in rows:   # a kept array needs its counter
        if r[0] in counters_needed and r[0] not in have: sel.append(r)
    counters = set(r[0] for r in sel if r[0] in counters_needed)
    sel = [r for r in sel if r[0] in counters] + [r for r in sel if r[0] not in counters]   # counters first
    fo = ROOT.TFile(a.out, 'RECREATE')
    if a.runs_first:
        tr0 = ROOT.TTree('Runs', 'Runs'); rb = np.zeros(1, np.uint32); tr0.Branch('run', rb, 'run/i'); rb[0] = 1; tr0.Fill()
        tr0.Write()
    t = ROOT.TTree('Events', 'Events')
    if a.autoflush: t.SetAutoFlush(a.autoflush)
    bufs = {}
    for name, typ, lv in sel:
        code, dt = CODE[typ]
        if lv:
            cap = CAP.get(lv, 9)
            bufs[name] = np.zeros(cap, dt); t.Branch(name, bufs[name], '%s[%s]/%s' % (name, lv, code))
        else:
            bufs[name] = np.zeros(1, dt); t.Branch(name, bufs[name], '%s/%s' % (name, code))
    index = {n: i for i, (n, _, _) in enumerate(sorted(sel))}
    expect = []
    for ev in range(a.nev):
        e = {}
        for c in sorted(counters):
            cap = CAP.get(c, 9)
            n = int(h(index[c], ev, 99999, a.seed) % (cap + 1))
            if ev == 0: n = cap          # first event at full capacity
            bufs[c][0] = n; e[c] = n
        for name, typ, lv in sel:
            if name in counters: continue
            if lv:
                n = e[lv]; vals = [value(typ, name, h(index[name], ev, j, a.seed)) for j in range(n)]
                for j, v in enumerate(vals): bufs[name][j] = v
                e[name] = vals
            else:
                v = value(typ, name, h(index[name], ev, 0, a.seed)); bufs[name][0] = v; e[name] = v
        t.Fill(); expect.append(e)
    t.Write()
    if not a.runs_first:
        tr = ROOT.TTree('Runs', 'Runs'); rb = np.zeros(1, np.uint32); tr.Branch('run', rb, 'run/i'); rb[0] = 1; tr.Fill(); tr.Write()
    lb = ROOT.TTree('LuminosityBlocks', 'LuminosityBlocks'); lbb = np.zeros(1, np.uint32); lb.Branch('luminosityBlock', lbb, 'luminosityBlock/i'); lb.Fill(); lb.Write()
    fo.Close()
    json.dump({'types': {n: t_ for n, t_, _ in sel}, 'counters': sorted(counters),
               'lenvar': {n: lv for n, _, lv in sel if lv}, 'events': expect}, open(a.out + '.expect.json', 'w'))
    print('%s: %d branches (%d counters), %d events' % (a.out, len(sel), len(counters), a.nev))

main()
