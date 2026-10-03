#!/usr/bin/env python3
"""Compare a harness dump with the values written (expect.json of each input file, in chain order).
Usage: compare.py dump.txt eventBuffer.h file1.root [file2.root ...]"""
import json, re, sys
dump, ebh, files = sys.argv[1], sys.argv[2], sys.argv[3:]
exp = [json.load(open(f + '.expect.json')) for f in files]
# member name -> branch name: generated buffer names members after the branch (Events/<b> -> <b>)
src = open(ebh).read()
members = dict((m.group(2), m.group(1)) for m in re.finditer(r'input->present\("Events/(\w+)"\)\) \{ (?:\w+\.resize\(\d+\); )?input->select\("Events/\w+", (\w+)\)', src))
member2branch = {v: k for k, v in members.items()}  # member -> branch
first = exp[0]['types']
evs = []
for fi, e in enumerate(exp):
    for ev in e['events']: evs.append((fi, ev))
cur = -1; stats = {'ok': 0, 'wrong': 0, 'silent_zero': 0, 'nonzero_absent': 0}
bad = []; structs = []; pre = []; counters = []
lines = open(dump).read().split('\n')
for l in lines:
    if not l: continue
    if l.startswith('PRE_'): pre.append(l); continue
    if l.startswith('EV '):
        _, e, num = l.split(); cur = int(e); fi, ev = evs[cur]; continue
    if l.startswith('STRUCT '): structs.append((cur, l)); continue
    if l.startswith('COUNTER '): counters.append((cur, l)); continue
    name, val = l.split(' ', 1)
    br = member2branch.get(name, name)
    fi, ev = evs[cur]
    is_vec = val.startswith('[')
    got = [float(x) if '.' in x or 'e' in x else int(x) for x in val.strip('[]').split()] if is_vec else (float(val) if ('.' in val or 'e' in val or 'n' in val) else int(val))
    if br in ev:
        want = ev[br]
        if got == want: stats['ok'] += 1
        else:
            zero = (got == [] or got == 0) and want not in ([], 0)
            # present in this file but never bound (absent in the chain's first file)
            if zero and br not in first: stats['silent_zero'] += 1; bad.append(('SILENT_ZERO', cur, br, want, got))
            else: stats['wrong'] += 1; bad.append(('WRONG', cur, br, want, got))
    else:
        if got in ([], 0): stats['ok'] += 1
        else: stats['nonzero_absent'] += 1; bad.append(('NONZERO_ABSENT', cur, br, None, got))
print('events %d  values ok %d  wrong %d  silent_zero %d  nonzero_for_absent %d' % (cur + 1, stats['ok'], stats['wrong'], stats['silent_zero'], stats['nonzero_absent']))
kinds = {}
for b in bad: kinds.setdefault((b[0], b[2]), []).append(b)
for (k, br), lst in sorted(kinds.items())[:40]:
    b = lst[0]
    print('  %-14s %-45s in %d events; e.g. event %d want %s got %s' % (k, br, len(lst), b[1], str(b[3])[:60], str(b[4])[:60]))
print('PRE:', ' | '.join(pre[:12]))
# struct size check vs the number of objects written (counter value in the file of that event)
sbad = 0
for cur, l in structs:
    _, o, size, nbad = l.split(); fi, ev = evs[cur]
    cn = 'n' + o
    want = ev.get(cn, 0)
    if int(size) != want or int(nbad) != 0:
        sbad += 1
        if sbad <= 8: print('  STRUCT mismatch event %d %s size %s want %s field-mismatches %s' % (cur, o, size, want, nbad))
print('struct checks: %d, mismatches %d' % (len(structs), sbad))
cbad = 0; cok = 0
for cur, l in counters:
    _, c, v = l.split(); fi, ev = evs[cur]
    want = ev.get(c, 0)
    if int(v) == want: cok += 1
    else:
        cbad += 1
        if cbad <= 3: print('  COUNTER mismatch event %d %s got %s want %s' % (cur, c, v, want))
print('counter checks: ok %d, mismatches %d' % (cok, cbad))
