#!/usr/bin/env python3
# ----------------------------------------------------------------------------
#  File:        mkvariables.py
#
#  Description: Scan a simple ntuple and create the file variables.txt that
#               describes its branches and leaves. The file variables.txt has
#               the following fields:
#              
#               type / branch[.leaf] / variable-name / maximum count
#
#               This file can then be used by mkanalyzer.py to create a
#               reasonably comprehensive (first) version of an analyzer.
#
#  Created:     Mon Oct  4, 2010
#  Author:      Harrison B. Prosper
#  Email:       harry@hep.fsu.edu, Harrison.Prosper@cern.ch
#  Fixes:       15-Nov-2010 HBP make sure buffers have a count of at least 1
#               22-Nov-2010 HBP allow multiple trees
#               11-Jan-2011 HBP shorten genparticlehelper variable
#               20-Jul-2011 HBP fix problem with basic type
#               09-Jul-2013 HBP re-order imports to avoid Error message from
#                           root. Also do not convert names to lower case.
#               21-Dec-2014 HBP get rid of xml module
#               03-Dec-2017 HBP add name of leaf counter
#               02-Feb-2018 HBP no need to write out leaf counters separately.
#               22-Feb-2018 HBP adapt to improved treestream listing
#               17-Jan-2020 HBP make compatible with Python 3
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# Rafactoring update for Python 3
# Edditor:      Junghyun Lee
# Email:        junghyun.lee@cern.ch
# Fixes:        02-Dec-2025 JhLee 
# ----------------------------------------------------------------------------              

import os, sys, re, argparse
from time import ctime

# Check ROOT libaraies existence
try:
    import ROOT
except ImportError:
    sys.exit("\n\033[91m**Can not [import ROOT]. Please make sure ROOT is installed or related environment variables.\033[0m\n")    

# ----------------------------------------------------------------------------
# Load treestream module
# ----------------------------------------------------------------------------
print("\t[mkvariables] : Will use \"treestream\" module. It will read the ntuple and help to extract TTree and it's branches type & name")
print("\t[mkvariables] : Module is searched in CMSSW PhysicsTools first. If CMSSW is not setted, then program search libaray path at \"$TREESTREAM_PATH/lib/libtreestream\". So If you did not set \"$TREESTREAM_PATH\", please execute \"setup.sh\" or \"setup.csh\".")
try:
    from PhysicsTools.TheNtupleMaker.AutoLoader import *
except ImportError:
    try:
        print("\tloading treestream...")
        # ROOT handles env vars in paths, but catching load errors is safer
        if ROOT.gSystem.Load("$TREESTREAM_PATH/lib/libtreestream") < 0:
            raise OSError("Load failed")
    except Exception as e:
        print(f"\t** libtreestream not found: {e}")
        sys.exit('''
    Try installing the treestream package:
    
    cd
    mkdir -p external/bin external/lib external/include
    cd external
    git clone http://github.com/hbprosper/treestream.git

    then
    cd treestream
    make
    make install
    ''')
print("\t[mkvariables] : Module is succesfully setted\n")


# ----------------------------------------------------------------------------
# Regex Compilation
# ----------------------------------------------------------------------------
# Using raw strings (r'') for regex patterns is best practice in Python
re_getvtype  = re.compile(r'(?<=vector[<]).+(?=[>])')
re_namespace = re.compile(r'^(edm|reco|pat)')
re_patname   = re.compile(r'(?<=pat)[a-z]+[1-9]*')
re_reconame  = re.compile(r'(?<=reco)[a-z]+[1-9]*')
re_genname   = re.compile(r'^(gen[a-z]+|edm[a-z]+)')
re_countname = re.compile(r'(?<=^n)(pat|reco)')
re_arraytype = re.compile(r'\[[0-9]+\]')

# ----------------------------------------------------------------------------
# Main Logic
# ----------------------------------------------------------------------------
def main():

    # 1. Argument Parsing (Replaces manual sys.argv)
    parser = argparse.ArgumentParser(
        description="Scan a simple ntuple and create variables.txt"
    )
    parser.add_argument("filename", help="Path to the ntuple file")
    parser.add_argument("treenames", nargs="*", help="Optional tree names")
    parser.add_argument("--usetree", action="store_true", help="Use the treename as struct names")
    
    args = parser.parse_args()
    
    filename = args.filename
    usetree = args.usetree
    
    print("\t[mkvariables] : Setted argument")


    if not os.path.exists(filename):
        sys.exit(f"\t** file {filename} not found")

    # 2. Setup ROOT treestream
    if args.treenames:
        # Join list of tree names into a single string
        treename_str = ' '.join(args.treenames)
        print("join 모듈을 통해 tree string들을 조합함. 근데 왜 굳이 여러 트리 이름을 받지? 이거 variables 목록의 tree 이름까지 반영해서 analyzer 만드나보다.")
        print(f"Trees: {treename_str}")
        stream = ROOT.itreestream(filename, treename_str)
        if not stream.good():
            sys.exit("\t** hmmmm...something amiss here (stream not good)!")
        
        # In Python 3, map returns an iterator, convert to list if needed immediately
        tname = list(stream.treenames())

        print("ROOT에서 itreestream으로 가져온 streaem 변수에 대해 treenames()를 사용하고 그걸 다시 list로 형변환함.")

    else:
        print("트리 이름 지정 안해줬을 때 분기. 이 경우 stream에서 모든 tree이름들을 tree().GetName()을 통해 반환할까?")

        stream = ROOT.itreestream(filename)
        if not stream.good():
            sys.exit("\t** hmmmm...something amiss here (stream not good)!")
        
        treename_str = stream.tree().GetName()
        tname = [treename_str]
        print(f"살펴보자 --> tname : {tname}")


    # 3. Prepare Output
    print(f"\n==> file: {filename}")
    for name in tname:
        print(f"==> tree: {name}")
    print("==> output: variables.txt")

    skipped_at_least_one = False
    
    # Use context managers (with open) for safe file handling
    with open("variables.txt", "w") as out, open("variables_skipped.txt", "w") as skipped:
        
        # Write Header
        out.write(f"Tree {tname[0]}\t{ctime()}\n")
        for name in tname[1:]:
            out.write(f"Tree {name}\n")
        out.write("\n")

        # 4. Process Ntuple Listing
        dupname = {} # Track duplicate names

        # Modern string splitting
        # Ensure we work with strings. If stream.str() returns bytes, decode it.
        raw_stream = stream.str()
        if isinstance(raw_stream, bytes):
            raw_stream = raw_stream.decode('utf-8')

        lines = raw_stream.split('\n')
        records = [line.split() for line in lines if line.strip()]

        for x in records:
            # Skip empty or header lines
            if not x or x[0] in ["File", "Tree", "Entries"]:
                continue

            # Fields logic: branch / type [maximum count [*]]
            
            # Skip leaf counters
            is_counter = (x[-1] == "*")
            if is_counter:
                continue

            # Parse fields based on length
            has_counter = False
            maxcount = 1
            lc = "" # leaf counter name
            
            try:
                if len(x) == 4:
                    _, branch, _, btype = x
                elif len(x) == 5:
                    _, branch, _, btype, count_str = x
                    maxcount = int(count_str[1:-1]) # Modern int() conversion
                elif len(x) == 7:
                    has_counter = True
                    _, branch, _, btype, count_str, _, countername = x
                    maxcount = int(count_str[1:-1])
                else:
                    sys.exit(f"\t**hmmm...not sure what to do with:\n\t{x}\n\tchoi!")
            except ValueError:
                print(f"Warning: Parsing error on line: {x}")
                continue

            # Check Types to Skip
            if btype in ['TLorentzVector', 'TRefArray', 'TRef'] or re_arraytype.search(branch):
                skipped.write(f'{x[1]}\t{x[3]}\t{x[4]}\n')
                skipped_at_least_one = True
                continue
            
            # Normalize Branch Type
            # Using method chaining for string manipulation
            btype = btype.lower().replace("_t", "")
            
            vtype_match = re_getvtype.findall(btype)
            if len(vtype_match) == 1:
                inner_type = vtype_match[0]
                maxcount = 50   # Default max for vectors
                btype = f"vector<{inner_type}>"
            
            if has_counter:
                lc = countername

            # 5. Name Processing Logic
            t = branch.split('.')
            t[0] = t[0].split('/')[-1]
            bname = t[0]

            if len(t) > 1:
                # Handle TNM branch names
                t[0] = t[0].split('_')[0]

                a = re_patname.findall(t[0])
                if not a:
                    a = re_reconame.findall(t[0])
                    if not a:
                        a = re_genname.findall(t[0])
                
                if a:
                    t[0] = a[0]
            else:
                if re_countname.findall(t[0]):
                    # re.sub returns string, split it
                    t[0] = re_countname.sub("", t[0]).split('_')[0]

            # Duplicate Name Handling
            key = t[0]
            if key not in dupname:
                dupname[key] = [bname, 0]
            
            # Check if the mapped name is different from original branch name
            if dupname[key][0] != bname:
                dupname[key][1] += 1
            
            if dupname[key][1] > 0:
                t[0] = f"{t[0]}{dupname[key][1]}"

            # Final Name Construction
            t[0] = re_namespace.sub("", t[0])
            name = '_'.join(t)

            if usetree:
                # The treename may include a directory, take last part
                clean_treename = treename_str.split('/')[-1]
                name = f"{clean_treename}_{name}"
            
            # Write Output
            out.write(f"{btype}/{branch}/{name}/{maxcount} {lc}\n")

    # Cleanup skipped file if empty
    if not skipped_at_least_one:
        try:
            os.remove("variables_skipped.txt")
        except OSError:
            pass

if __name__ == "__main__":
    main()
