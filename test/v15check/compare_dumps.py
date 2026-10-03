#!/usr/bin/env python3
"""Compare the eventBuffer harness dump with rootdump.py of the same single file.
Usage: compare_dumps.py harness_dump.txt rootdump.txt"""
import sys
def load(p):
    ev = {}; cur = None
    for l in open(p):
        l = l.rstrip('\n')
        if not l or l.startswith('PRE_'): continue
        if l.startswith('EV '): cur = int(l.split()[1]); ev[cur] = {}; continue
        if l.startswith('STRUCT '):
            _, o, size, bad = l.split(); ev[cur]['STRUCT ' + o] = (int(size), int(bad)); continue
        k, v = l.split(' ', 1)
        if k == 'COUNTER': k, v = 'COUNTER ' + v.split()[0], v.split()[1]
        ev[cur][k] = v
    return ev
h, r = load(sys.argv[1]), load(sys.argv[2])
ok = bad = absent_nonzero = sbad = 0; shown = 0
for e in sorted(r):
    he, re_ = h.get(e, {}), r[e]
    for k, v in re_.items():
        hv = he.get(k)
        if hv == v: ok += 1
        else:
            bad += 1
            if shown < 8: print('  MISMATCH event %d %s: eventBuffer=%s  file=%s' % (e, k, str(hv)[:70], v[:70])); shown += 1
    for k, v in he.items():
        if k.startswith('STRUCT '):
            o = k.split()[1]; size, nb = v; c = re_.get('COUNTER n' + o)
            if nb != 0 or (c is not None and int(c) != size): sbad += 1
            continue
        if k in re_ or k.startswith('COUNTER '): continue
        if v not in ('0', '[]'): absent_nonzero += 1
print('events %d  values equal %d  differ %d  absent-but-nonzero %d  struct problems %d' % (len(r), ok, bad, absent_nonzero, sbad))
good = bad == 0 and absent_nonzero == 0 and sbad == 0 and ok > 0
print('RESULT', 'PASS' if good else 'FAIL')
sys.exit(0 if good else 1)
