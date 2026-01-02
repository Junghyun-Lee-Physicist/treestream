#!/usr/bin/env python3
# -----------------------------------------------------------------------------
# File:        mkdebug_ntuple.py
# Description: Create a small debug ntuple from a variables.txt-style file.
# -----------------------------------------------------------------------------
import argparse
import sys
from array import array

try:
    import ROOT as rt
except ImportError:
    sys.exit("\n\033[91m**Can not [import ROOT]. Please make sure ROOT is installed.\033[0m\n")

SCALAR_TYPE_MAP = {
    "bool": ("b", "O"),
    "double": ("d", "D"),
    "float": ("f", "F"),
    "int": ("i", "I"),
    "long": ("l", "L"),
    "long64": ("q", "L"),
    "short": ("h", "S"),
    "uchar": ("B", "b"),
    "uint": ("I", "i"),
    "ulong": ("L", "l"),
    "ulong64": ("Q", "l"),
    "ushort": ("H", "s"),
}

VECTOR_TYPE_MAP = {
    "bool": "bool",
    "double": "double",
    "float": "float",
    "int": "int",
    "long": "long",
    "long64": "long long",
    "short": "short",
    "uchar": "unsigned char",
    "uint": "unsigned int",
    "ulong": "unsigned long",
    "ulong64": "unsigned long long",
    "ushort": "unsigned short",
}


def parse_variables(filename):
    with open(filename, "r") as handle:
        lines = [line.strip() for line in handle.readlines()]

    treename = None
    records = []
    for line in lines:
        if not line:
            continue
        if line.startswith("Tree "):
            if treename is None:
                treename = line.split()[1]
            continue
        if line.startswith("Tree"):
            continue
        parts = line.split()
        if not parts:
            continue
        spec = parts[0]
        counter = parts[1] if len(parts) > 1 else None
        tokens = spec.split("/")
        if len(tokens) < 4:
            continue
        rtype = tokens[0]
        maxcount = int(tokens[-1])
        varname = tokens[-2]
        branchname = "/".join(tokens[1:-2])
        records.append((rtype, branchname, varname, maxcount, counter))

    if treename is None:
        treename = "Events"
    return treename, records


def scalar_value(rtype, entry, var_index):
    if rtype in ("float", "double"):
        value = (entry + 1) * 1.25 + var_index * 0.01
        if entry == 3 and var_index % 7 == 0:
            value = -999.0
        if entry == 7 and var_index % 11 == 0:
            value = float("nan")
        return value
    if rtype == "bool":
        return (entry + var_index) % 2 == 0
    value = (entry + 1) * 10 + var_index
    if rtype.startswith("u"):
        return abs(value)
    return value


def fill_vector(vec, rtype, entry, var_index, count):
    vec.clear()
    for i in range(count):
        vec.push_back(scalar_value(rtype, entry, var_index + i))


def main():
    parser = argparse.ArgumentParser(
        description="Create a small debug ntuple from a variables.txt file."
    )
    parser.add_argument(
        "variables",
        nargs="?",
        default="variables_Combine_with_Bperiod.txt",
        help="variables.txt-style input file",
    )
    parser.add_argument(
        "--output",
        default="debug_ntuple.root",
        help="output ROOT filename",
    )
    parser.add_argument(
        "--entries",
        type=int,
        default=10,
        help="number of events to write",
    )
    args = parser.parse_args()

    treename, records = parse_variables(args.variables)
    if not records:
        sys.exit("** No variables found to write.")

    root_file = rt.TFile(args.output, "RECREATE")
    tree = rt.TTree(treename, "debug ntuple")

    counter_max = {}
    for rtype, branchname, varname, maxcount, counter in records:
        if counter:
            counter_max[counter] = max(counter_max.get(counter, 0), maxcount)

    counters = {}
    for counter in sorted(counter_max):
        counters[counter] = array("i", [0])
        tree.Branch(counter, counters[counter], f"{counter}/I")

    scalars = {}
    vectors = {}

    for rtype, branchname, varname, maxcount, counter in records:
        branch_leaf = branchname
        if branchname.startswith(f"{treename}/"):
            branch_leaf = branchname.split("/", 1)[1]
        if maxcount == 1:
            scalar_info = SCALAR_TYPE_MAP.get(rtype)
            if scalar_info is None:
                raise ValueError(f"Unsupported scalar type: {rtype}")
            typecode, leafcode = scalar_info
            scalars[varname] = array(typecode, [0])
            tree.Branch(branch_leaf, scalars[varname], f"{branch_leaf}/{leafcode}")
        else:
            vector_type = VECTOR_TYPE_MAP.get(rtype)
            if vector_type is None:
                raise ValueError(f"Unsupported vector type: {rtype}")
            vectors[varname] = rt.std.vector(vector_type)()
            tree.Branch(branch_leaf, vectors[varname])

    for entry in range(args.entries):
        counter_values = {}
        for idx, counter in enumerate(sorted(counter_max)):
            maxcount = counter_max[counter]
            if entry == 0 and idx % 2 == 0:
                value = 0
            elif entry == 1 and idx % 3 == 0:
                value = maxcount
            else:
                value = min(maxcount, (entry % 3) + 1)
            counters[counter][0] = value
            counter_values[counter] = value

        var_index = 0
        for rtype, branchname, varname, maxcount, counter in records:
            if maxcount == 1:
                scalars[varname][0] = scalar_value(rtype, entry, var_index)
            else:
                size = counter_values.get(counter, min(maxcount, (entry % 3) + 1))
                fill_vector(vectors[varname], rtype, entry, var_index, size)
            var_index += 1

        tree.Fill()

    tree.Write()
    root_file.Close()
    print(f"==> Wrote {args.entries} events to {args.output} (tree: {treename})")


if __name__ == "__main__":
    main()
