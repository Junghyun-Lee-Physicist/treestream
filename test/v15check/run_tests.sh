#!/bin/bash
# run_tests.sh -- eventBuffer/treestream checks on the real NanoAOD v15 2024 schema (synthetic values).
# Needs ROOT 6 (+PyROOT, numpy), a built treestream (TS) and an NtupleForge checkout (NF, for the inventories,
# the slim branch lists and script/check_branchlist.py).  Writes only under WORK.
#   TS=~/treestream NF=~/NtupleForge WORK=/tmp/$USER/tscheck /bin/bash run_tests.sh
set -u
K=$(cd "$(dirname "$0")" && pwd)
: "${TS:?set TS=<treestream checkout, built>}" "${NF:?set NF=<NtupleForge checkout>}"
WORK=${WORK:-/tmp/$USER/tscheck}; mkdir -p "$WORK" && cd "$WORK" || exit 2
export PYTHONWARNINGS=ignore NF
set +u; source "$TS/setup.sh" > /dev/null; set -u   # setup.sh reads unset variables
INV=$NF/script/inventory; BL=$NF/branches
CXX="g++ -O1 -std=c++17 -w -I. -I$TS/include"
SRC="$TS/src/treestream.cc $(root-config --cflags --libs)"
echo "== files (real 2024 v15 Events schema after the NtupleForge slim lists)"
python3 $K/mkfiles.py $INV/inv_Summer24_v15_MC.tsv $BL/branch_hadronic_2024_v15_MC.txt mc24.root 1 | tail -1
for e in C E F Iv2; do python3 $K/mkfiles.py $INV/inv_2024${e}_v15_Data.tsv $BL/branch_hadronic_2024_v15_Data.txt data24$e.root 2 | tail -1; done
python3 $K/mkfiles.py $INV/inv_2024C_v15_Data.tsv $BL/branch_hadronic_2024_v15_Data.txt data24C_noPNetReg.root 2 --drop Jet_PNetRegPtRawCorr | tail -1
echo "== generate (Super-Set of MC, C, Iv2)"
mkvariables.py --merge mc24.root data24C.root data24Iv2.root --tree Events -o variables_2024.txt | grep -E "Total unique|Type conflicts"
mkeventbuffer.py variables_2024.txt -o eventBuffer.h | tail -1
grep -E "^    \w+\.resize\(\w+\.size\(\)\);|nobj_ = 0" eventBuffer.h | head -2
python3 $K/mkharness.py eventBuffer.h harness.cc && $CXX harness.cc $SRC -o harness || exit 3
echo "== T1 single files: every member, every event"
for f in mc24 data24C data24E data24F data24Iv2; do ./harness d_$f.txt $f.root > l_$f.txt 2>&1; echo "-- $f exit=$?"; python3 $K/compare.py d_$f.txt eventBuffer.h $f.root | grep -E "^events|^struct|^counter"; grep -oE "PRE_STRUCT Jet [0-9]+|PRE_COUNTER nJet [-0-9]+" d_$f.txt | tr '\n' ' '; echo; done
echo "== T2 the field that sizes Jet is absent"
./harness d_t2.txt data24C_noPNetReg.root > l_t2.txt 2>&1; echo "exit=$?"; python3 $K/compare.py d_t2.txt eventBuffer.h data24C_noPNetReg.root | grep -E "^struct|STRUCT mismatch" | head -2
echo "== T3 chains (the first file decides)"
for ch in "data24C data24Iv2" "data24Iv2 data24C"; do set -- $ch; ./harness d_ch.txt $1.root $2.root > l_ch.txt 2>&1; echo "-- $1 -> $2 exit=$?"; grep -m1 "Error" l_ch.txt; python3 $K/compare.py d_ch.txt eventBuffer.h $1.root $2.root | grep -E "^events"; done
echo "== T4 corrupted basket"
mkdir -p t4 && (cd t4 && python3 $K/mkcorrupt.py && mkvariables.py c.root Events > /dev/null && mkeventbuffer.py variables.txt -o eventBuffer.h > /dev/null && $CXX $K/t10.cc $SRC -o t10 && ./t10 c_bad.root > t10.log 2>&1; echo "exit=$?"; grep -E "^entry|RESULT|\*\* Error" t10.log | head -3)
echo "== T5 varlist"
$CXX $K/t11.cc $SRC -o t11 && for v in "Jet_pt PuppiMET_pt run" "Events/Jet_pt Events/PuppiMET_pt Events/run"; do ./t11 data24C.root "$v" 2>&1 | grep -E "RESULT|\[OK\]" | tr '\n' ' '; echo; done
echo "== T6 single-mode tree name and header"
python3 $K/mkfiles.py $INV/inv_2024C_v15_Data.tsv $BL/branch_hadronic_2024_v15_Data.txt runsfirst.root 7 --runs-first > /dev/null
mkdir -p t6 && (cd t6 && mkvariables.py ../runsfirst.root Events > /dev/null 2>&1; head -1 variables.txt; grep -c "^[a-z]" variables.txt)
echo "== T7 varlist leaves out an object whose counter is absent in a later file"
mkdir -p t7 && (cd t7 && python3 $K/mkab.py && mkvariables.py --merge a.root b.root --tree Events -o v.txt > /dev/null && mkeventbuffer.py v.txt -o eventBuffer.h > /dev/null && $CXX $K/t7.cc $SRC -o t7 && ./t7 "Jet_ run" > t7.log 2>&1; echo "exit=$?"; grep -E "RESULT|\*\* Error" t7.log | head -2)
echo "== T8 a chain file becomes unreadable after the buffer is built"
(cd t7 && ./t7 "" gone > t8.log 2>&1; echo "exit=$?"; grep -E "RESULT|\*\* Error|\*\* eventBuffer" t8.log | head -2)
echo "== T9 skeleton tree when the manifest header lists Runs first (old mkvariables)"
mkdir -p t9 && (cd t9 && { printf 'Tree Runs\tx\nTree Events\nTree LuminosityBlocks\n\n'; grep "^[a-z]" ../variables_2024.txt; } > v_old.txt && rm -rf SK && mkanalyzer.py SK v_old.txt > /dev/null 2>&1; grep -h "itreestream stream" SK/SK.cc)
