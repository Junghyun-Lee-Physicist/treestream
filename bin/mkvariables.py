#!/usr/bin/env python3
# ----------------------------------------------------------------------------
#  File:        mkvariables.py
#
#  Description: Scan one or more ROOT ntuples and create the file variables.txt
#               that describes their branches and leaves.
#
#               Single-file mode (original):
#                 mkvariables.py <ntuple.root> [TreeName]
#
#               Multi-file mode (Super-Set):
#                 mkvariables.py --merge <file1.root> <file2.root> ... [--tree TreeName]
#                 Scans multiple samples, takes the union of all branches,
#                 and annotates which branches are common vs sample-specific.
#
#               Output format:
#                 type / branch[.leaf] / variable-name / maximum count [leafcounter]
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
#  Updated:     Junghyun Lee  <junghyun.lee@cern.ch>
#               02-Dec-2025 JhLee - Refactor for Python 3
#               15-Mar-2026 JhLee - Add --merge mode for multi-sample Super-Set
#                                   variables.txt generation with common/unique
#                                   branch annotation
# ----------------------------------------------------------------------------

import os, sys, re, argparse
from time import ctime
from collections import OrderedDict

# Check ROOT libraries existence
try:
    import ROOT
except ImportError:
    sys.exit("\n** Cannot import ROOT. Please set up ROOT environment.\n")

# ----------------------------------------------------------------------------
# Load treestream module
# ----------------------------------------------------------------------------
try:
    from PhysicsTools.TheNtupleMaker.AutoLoader import *
except ImportError:
    try:
        if ROOT.gSystem.Load("$TREESTREAM_PATH/lib/libtreestream") < 0:
            raise OSError("Load failed")
    except Exception as e:
        print(f"\t** libtreestream not found: {e}")
        sys.exit('''
    Try installing the treestream package:

    cd $HOME/external
    git clone http://github.com/hbprosper/treestream.git
    cd treestream
    make && make install
    ''')

# ----------------------------------------------------------------------------
# Regex Compilation
# ----------------------------------------------------------------------------
re_getvtype  = re.compile(r'(?<=vector[<]).+(?=[>])')
re_namespace = re.compile(r'^(edm|reco|pat)')
re_patname   = re.compile(r'(?<=pat)[a-z]+[1-9]*')
re_reconame  = re.compile(r'(?<=reco)[a-z]+[1-9]*')
re_genname   = re.compile(r'^(gen[a-z]+|edm[a-z]+)')
re_countname = re.compile(r'(?<=^n)(pat|reco)')
re_arraytype = re.compile(r'\[[0-9]+\]')

# ----------------------------------------------------------------------------
# Scan a single ROOT file and return a dict of branch records
# ----------------------------------------------------------------------------
def scan_file(filename, treenames=None, usetree=False):
    """
    Scan a ROOT file and return:
      branches: OrderedDict  varname -> (btype, branch, varname, maxcount, lc)
      tname:    list of tree names found
      skipped:  list of skipped branch descriptions
    """
    if not os.path.exists(filename):
        sys.exit(f"\t** file {filename} not found")

    if treenames:
        treename_str = ' '.join(treenames)
        stream = ROOT.itreestream(filename, treename_str)
        if not stream.good():
            sys.exit(f"\t** Cannot open stream for {filename}")
        tname = list(stream.treenames())
    else:
        stream = ROOT.itreestream(filename)
        if not stream.good():
            sys.exit(f"\t** Cannot open stream for {filename}")
        treename_str = stream.tree().GetName()
        tname = [treename_str]

    # Parse stream listing
    raw_stream = stream.str()
    if isinstance(raw_stream, bytes):
        raw_stream = raw_stream.decode('utf-8')

    lines = raw_stream.split('\n')
    records = [line.split() for line in lines if line.strip()]

    dupname = {}
    branches = OrderedDict()
    skipped = []

    for x in records:
        if not x or x[0] in ["File", "Tree", "Entries"]:
            continue

        is_counter = (x[-1] == "*")
        if is_counter:
            continue

        has_counter = False
        maxcount = 1
        lc = ""

        try:
            if len(x) == 4:
                _, branch, _, btype = x
            elif len(x) == 5:
                _, branch, _, btype, count_str = x
                maxcount = int(count_str[1:-1])
            elif len(x) == 7:
                has_counter = True
                _, branch, _, btype, count_str, _, countername = x
                maxcount = int(count_str[1:-1])
            else:
                continue
        except ValueError:
            continue

        if btype in ['TLorentzVector', 'TRefArray', 'TRef'] or re_arraytype.search(branch):
            skipped.append(f'{x[1]}\t{x[3]}')
            continue

        btype = btype.lower().replace("_t", "")

        vtype_match = re_getvtype.findall(btype)
        if len(vtype_match) == 1:
            inner_type = vtype_match[0]
            maxcount = 50
            btype = f"vector<{inner_type}>"

        if has_counter:
            lc = countername

        # Name processing
        t = branch.split('.')
        t[0] = t[0].split('/')[-1]
        bname = t[0]

        if len(t) > 1:
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
                t[0] = re_countname.sub("", t[0]).split('_')[0]

        key = t[0]
        if key not in dupname:
            dupname[key] = [bname, 0]
        if dupname[key][0] != bname:
            dupname[key][1] += 1
        if dupname[key][1] > 0:
            t[0] = f"{t[0]}{dupname[key][1]}"

        t[0] = re_namespace.sub("", t[0])
        name = '_'.join(t)

        if usetree:
            clean_treename = treename_str.split('/')[-1]
            name = f"{clean_treename}_{name}"

        branches[name] = (btype, branch, name, maxcount, lc)

    return branches, tname, skipped


# ----------------------------------------------------------------------------
# Single-file mode (original behavior)
# ----------------------------------------------------------------------------
def run_single(args):
    filename = args.filename[0]
    treenames = args.tree if args.tree else None
    branches, tname, skipped = scan_file(filename, treenames, args.usetree)

    print(f"\n==> file: {filename}")
    for name in tname:
        print(f"==> tree: {name}")
    print(f"==> output: variables.txt")
    print(f"==> branches found: {len(branches)}")

    with open("variables.txt", "w") as out:
        out.write(f"Tree {tname[0]}\t{ctime()}\n")
        for name in tname[1:]:
            out.write(f"Tree {name}\n")
        out.write("\n")

        for varname, (btype, branch, name, maxcount, lc) in branches.items():
            out.write(f"{btype}/{branch}/{name}/{maxcount} {lc}\n")

    if skipped:
        with open("variables_skipped.txt", "w") as f:
            for s in skipped:
                f.write(s + "\n")
    else:
        try:
            os.remove("variables_skipped.txt")
        except OSError:
            pass

    print(f"\n\tDone. {len(branches)} branches written to variables.txt")


# ----------------------------------------------------------------------------
# Multi-file merge mode (Super-Set Strategy)
# ----------------------------------------------------------------------------
def run_merge(args):
    filenames = args.filename
    treenames = args.tree if args.tree else None

    if len(filenames) < 2:
        sys.exit("--merge requires at least 2 input files")

    # Scan each file
    file_branches = OrderedDict()  # filename -> {varname -> record}
    common_tname = None

    print(f"\n{'='*60}")
    print(f"  Multi-Sample Super-Set Merge Mode")
    print(f"  Scanning {len(filenames)} files...")
    print(f"{'='*60}\n")

    for fname in filenames:
        label = os.path.basename(fname)
        branches, tname, skipped = scan_file(fname, treenames, args.usetree)
        file_branches[label] = branches
        if common_tname is None:
            common_tname = tname
        print(f"  [{label}] {len(branches)} branches")

    # Compute union, intersection, and per-file unique sets
    all_labels = list(file_branches.keys())
    all_varnames = OrderedDict()  # varname -> record (use first occurrence for type/count)
    presence = {}  # varname -> set of labels that contain it

    for label, branches in file_branches.items():
        for varname, record in branches.items():
            if varname not in all_varnames:
                all_varnames[varname] = record
            else:
                # Take max count across files
                existing = all_varnames[varname]
                if record[3] > existing[3]:
                    all_varnames[varname] = record
            if varname not in presence:
                presence[varname] = set()
            presence[varname].add(label)

    # ---- Unify counts for branches sharing the same leaf counter ----
    # When merging across files, the same object (e.g. Jet) may have
    # COMMON branches with count=77 and SAMPLE-SPECIFIC branches with
    # count=31 (because the specific file had fewer entries).
    # mkanalyzer.py requires all fields of a struct to share the same
    # count, so we must unify: for each leaf counter (nJet, nElectron, ...),
    # find the maximum count across ALL branches that use it, then set
    # every such branch to that maximum.
    lc_max_count = {}  # leaf_counter_name -> max count seen
    for varname, (btype, branch, name, maxcount, lc) in all_varnames.items():
        if lc and maxcount > 1:
            if lc not in lc_max_count or maxcount > lc_max_count[lc]:
                lc_max_count[lc] = maxcount

    unified_count = 0
    for varname in all_varnames:
        btype, branch, name, maxcount, lc = all_varnames[varname]
        if lc and lc in lc_max_count and maxcount < lc_max_count[lc]:
            all_varnames[varname] = (btype, branch, name, lc_max_count[lc], lc)
            unified_count += 1

    if unified_count > 0:
        print(f"  [Count unification] {unified_count} branches updated "
              f"to match max count per leaf counter")

    # Classify branches
    common_branches = []
    unique_branches = {}  # label -> list of varnames

    for label in all_labels:
        unique_branches[label] = []

    for varname in all_varnames:
        present_in = presence[varname]
        if len(present_in) == len(all_labels):
            common_branches.append(varname)
        else:
            for label in present_in:
                unique_branches[label].append(varname)

    # Print summary
    print(f"\n{'='*60}")
    print(f"  Merge Summary")
    print(f"{'='*60}")
    print(f"  Total unique branches (union): {len(all_varnames)}")
    print(f"  Common to ALL files:           {len(common_branches)}")
    for label in all_labels:
        n = len(unique_branches[label])
        if n > 0:
            print(f"  Unique to [{label}]:  {n}")
    print(f"{'='*60}\n")

    # Write annotated variables.txt
    output = args.output if args.output else "variables.txt"
    with open(output, "w") as out:
        out.write(f"Tree {common_tname[0]}\t{ctime()}\n")
        for name in common_tname[1:]:
            out.write(f"Tree {name}\n")
        out.write("\n")

        # Header comment
        out.write(f"# Super-Set variables.txt generated by mkvariables.py --merge\n")
        out.write(f"# Date: {ctime()}\n")
        out.write(f"# Input files: {', '.join(all_labels)}\n")
        out.write(f"# Total: {len(all_varnames)} branches "
                   f"({len(common_branches)} common, "
                   f"{len(all_varnames) - len(common_branches)} sample-specific)\n")
        out.write(f"#\n")
        out.write(f"# [COMMON]       = present in all input files\n")
        for label in all_labels:
            out.write(f"# [ONLY:{label}] = present only in this file\n")
        out.write(f"# [PARTIAL:...]  = present in some but not all files\n")
        out.write(f"#\n")
        out.write(f"# Note: Branches marked as non-COMMON may be absent at runtime.\n")
        out.write(f"#       eventBuffer uses present() to safely skip missing branches.\n")
        out.write(f"#\n\n")

        # Write common branches first
        out.write(f"# ---- COMMON branches ({len(common_branches)}) ----\n")
        for varname in sorted(common_branches):
            btype, branch, name, maxcount, lc = all_varnames[varname]
            out.write(f"{btype}/{branch}/{name}/{maxcount} {lc}\n")

        # Write sample-specific branches grouped by source
        has_unique = any(len(v) > 0 for v in unique_branches.values())
        if has_unique:
            out.write(f"\n# ---- SAMPLE-SPECIFIC branches ----\n")

            # Group by presence pattern
            pattern_groups = {}  # frozenset(labels) -> [varnames]
            for varname in all_varnames:
                present_in = presence[varname]
                if len(present_in) == len(all_labels):
                    continue  # already written
                key = frozenset(present_in)
                if key not in pattern_groups:
                    pattern_groups[key] = []
                pattern_groups[key].append(varname)

            for label_set, varnames in sorted(pattern_groups.items(),
                                                key=lambda x: (-len(x[0]), sorted(x[0]))):
                labels_str = ', '.join(sorted(label_set))
                missing_set = set(all_labels) - label_set
                missing_str = ', '.join(sorted(missing_set))

                if len(label_set) == 1:
                    tag = f"ONLY:{list(label_set)[0]}"
                else:
                    tag = f"PARTIAL:{labels_str}"

                out.write(f"\n# [{tag}]  (missing in: {missing_str})\n")
                for varname in sorted(varnames):
                    btype, branch, name, maxcount, lc = all_varnames[varname]
                    out.write(f"{btype}/{branch}/{name}/{maxcount} {lc}\n")

    print(f"  Output written to: {output}")
    print(f"  Use this file with mkanalyzer.py to generate a Super-Set analyzer.\n")


# ----------------------------------------------------------------------------
# Main
# ----------------------------------------------------------------------------
def main():
    parser = argparse.ArgumentParser(
        description="Scan ROOT ntuple(s) and create variables.txt",
        epilog="""
Examples:
  Single file:
    mkvariables.py data.root Events

  Multi-file merge (Super-Set):
    mkvariables.py --merge mc.root data_B.root data_C.root --tree Events
    mkvariables.py --merge mc.root data.root --tree Events -o variables_superset.txt
        """
    )
    parser.add_argument("filename", nargs="+",
                        help="Path to ntuple file(s). "
                             "With --merge, specify multiple files.")
    parser.add_argument("--tree", nargs="*",
                        help="Tree name(s) to scan (default: auto-detect)")
    parser.add_argument("--usetree", action="store_true",
                        help="Use treename as struct name prefix")
    parser.add_argument("--merge", action="store_true",
                        help="Merge multiple files into a Super-Set variables.txt "
                             "with common/unique branch annotations")
    parser.add_argument("-o", "--output", default=None,
                        help="Output filename (default: variables.txt)")

    args = parser.parse_args()

    if args.merge:
        run_merge(args)
    else:
        run_single(args)


if __name__ == "__main__":
    main()
