#!/usr/bin/env python3
"""Independent read of a real file with PyROOT, in the format of the eventBuffer harness dump.
Usage: NMAX=50 rootdump.py eventBuffer.h file.root > rootdump.txt
Only members of eventBuffer.h whose branch exists in the file are printed (absent ones must be 0/empty in the harness)."""
import os, re, sys
import ROOT
ebh, fname = sys.argv[1], sys.argv[2]
src = open(ebh).read()
pairs = re.findall(r'input->present\("Events/(\w+)"\)\) \{ (?:\w+\.resize\(\d+\); )?input->select\("Events/\w+", (\w+)\)', src)
f = ROOT.TFile.Open(fname); t = f.Get("Events")
have = set(b.GetName() for b in t.GetListOfBranches())
counters = sorted(set(re.findall(r'usedCounters\.count\("(\w+)"\)', src)))
n = int(t.GetEntries()); nmax = int(os.environ.get("NMAX", n)); n = min(n, nmax)
def fmt(v, typ):
    if typ in ('Float_t', 'Double_t'): return '%.17g' % float(v)
    return '%d' % int(v)
types = {}
for b in t.GetListOfBranches():
    lf = b.GetListOfLeaves()[0]; types[b.GetName()] = (lf.GetTypeName(), bool(lf.GetLeafCount()))
out = sys.stdout
for e in range(n):
    t.GetEntry(e)
    out.write('EV %d 0\n' % e)
    for br, member in pairs:
        if br not in have: continue
        typ, isarr = types[br]
        v = getattr(t, br)
        if isarr:
            lf = t.GetBranch(br).GetLeaf(br); k = lf.GetLen()
            out.write('%s [%s]\n' % (member, ' '.join(fmt(lf.GetValue(i), typ) for i in range(k))))
        else:
            out.write('%s %s\n' % (member, fmt(t.GetBranch(br).GetLeaf(br).GetValue(), typ)))
    for c in counters:
        if c in have: out.write('COUNTER %s %d\n' % (c, int(t.GetBranch(c).GetLeaf(c).GetValue())))
