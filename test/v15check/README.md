# test/v15check — eventBuffer checks on the real NanoAOD v15 schema

Two scripts. Both need ROOT 6 with PyROOT and numpy (`cmsenv` in CMSSW_14_2_1 is enough), a **built** treestream (`make lib`), and write
only under `WORK`. Each prints one block per test; the expected results are below.

## 1. Synthetic files with the real schema — `run_tests.sh`

Builds files with the exact `Events` schema of real 2024 NanoAOD v15 files (names, types, counters from the NtupleForge branch inventories,
after the NtupleForge 2024 slim branch lists), fills them with known values, generates `eventBuffer.h` from them and compares every
member of every event with what was written. Needs an NtupleForge checkout (`NF`: `script/inventory/*.tsv`, `branches/*.txt`,
`script/check_branchlist.py`).

```bash
TS=<this treestream> NF=<NtupleForge> WORK=/tmp/$USER/tscheck /bin/bash test/v15check/run_tests.sh
```

| block | checks | expected (with troubleshooting A11–A17 fixed) |
|---|---|---|
| T1 | single files MC, data C/E/F/Iv2: every value, struct sizes, counters, state before the first read | `wrong 0 … nonzero_for_absent 0`, `struct … mismatches 0`, `counter checks: ok 270, mismatches 0`, `PRE_STRUCT Jet 0`, `PRE_COUNTER nJet 0` |
| T2 | the field that used to size `Jet` (`Jet_PNetRegPtRawCorr`) is absent | `struct checks: 150, mismatches 0` |
| T3 | two-file chains: the first file decides (design §4 "Chains") | C→Iv2: `silent_zero 150` (era-only HLT branches), Iv2→C: exit 1 `update - pointer is zero` — by design |
| T4 | one corrupted basket | exit 1, `readbranch - I/O error … entry 200` |
| T5 | varlist with short and full names | 5 branches connected, values read |
| T6 | `mkvariables.py file.root Events` on a file whose first tree is `Runs` | header `Tree Events`, 481 branches |
| T7 | varlist that leaves out an object whose counter is absent in a later file | exit 0, `wrong=0` |
| T8 | a chain file becomes unreadable after the buffer is built | exit 1, `cannot load entry 20` |
| T9 | skeleton tree when an old manifest lists `Runs` first | `itreestream stream(filenames, "Events")` |

## 2. Real files — `run_realfiles.sh`

Generates the buffer from the given files, then compares, for the first `NMAX` entries of each file, every member with an independent
PyROOT read (`rootdump.py`). Give at least one MC and one Data file.

```bash
TS=<this treestream> WORK=/tmp/$USER/tsreal NMAX=50 /bin/bash test/v15check/run_realfiles.sh <mc.root> <data_C.root> <data_I.root>
```

Expected: per file `RESULT PASS` (`differ 0`, `absent-but-nonzero 0`, `struct problems 0`).
