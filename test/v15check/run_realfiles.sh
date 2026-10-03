#!/bin/bash
# run_realfiles.sh -- the same check on REAL ntuples: eventBuffer (generated from these files) versus an
# independent PyROOT read, first NMAX entries of each file. Read-only on the inputs; writes under WORK.
#   TS=<treestream, built> WORK=/tmp/$USER/tsreal NMAX=50 /bin/bash run_realfiles.sh f1.root f2.root ...
set -u
K=$(cd "$(dirname "$0")" && pwd)
: "${TS:?set TS=<treestream checkout, built>}"
[ $# -ge 2 ] || { echo "give at least two files (MC and Data)"; exit 2; }
WORK=${WORK:-/tmp/$USER/tsreal}; export NMAX=${NMAX:-50} PYTHONWARNINGS=ignore
mkdir -p "$WORK" && cd "$WORK" || exit 2
set +u; source "$TS/setup.sh" > /dev/null; set -u
mkvariables.py --merge "$@" --tree Events -o variables_real.txt | grep -E "Total unique|Common to ALL|Type conflicts|Unique to"
mkeventbuffer.py variables_real.txt -o eventBuffer.h | tail -1
python3 $K/mkharness.py eventBuffer.h harness.cc && g++ -O1 -std=c++17 -w -I. -I$TS/include harness.cc $TS/src/treestream.cc $(root-config --cflags --libs) -o harness || exit 3
rc=0
for f in "$@"; do b=$(basename "$f" .root)
  ./harness h_$b.txt "$f" > l_$b.txt 2>&1 || { echo "-- $f: harness exit $?"; tail -3 l_$b.txt; rc=1; continue; }
  python3 $K/rootdump.py eventBuffer.h "$f" > r_$b.txt || { echo "-- $f: rootdump failed"; rc=1; continue; }
  echo "-- $f"; grep -E "\[OK\]|\[MISSING\]" l_$b.txt | tr -s ' ' | tr '\n' ' '; echo
  python3 $K/compare_dumps.py h_$b.txt r_$b.txt > c_$b.txt; [ $? -eq 0 ] || rc=1; tail -9 c_$b.txt
done
exit $rc
