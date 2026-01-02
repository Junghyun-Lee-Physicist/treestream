#!/usr/bin/env python3
# -----------------------------------------------------------------------------
# File:        mkdebug_ntuple.py
# Description: Create a small debug ntuple from a variables.txt-style file.
# -----------------------------------------------------------------------------
import argparse
import sys
from ctypes import (
    c_bool,
    c_double,
    c_float,
    c_int,
    c_long,
    c_longlong,
    c_short,
    c_ubyte,
    c_uint,
    c_ulong,
    c_ulonglong,
    c_ushort,
)

try:
    import ROOT as rt
except ImportError:
    sys.exit("\n\033[91m**Can not [import ROOT]. Please make sure ROOT is installed.\033[0m\n")

try:
    from treestream import otreestream
except Exception as exc:
    sys.exit(f"\n\033[91m**Can not import treestream otreestream: {exc}\033[0m\n")


CTYPE_MAP = {
    "bool": c_bool,
    "double": c_double,
    "float": c_float,
    "int": c_int,
    "long": c_long,
    "long64": c_longlong,
    "short": c_short,
    "uchar": c_ubyte,
    "uint": c_uint,
    "ulong": c_ulong,
    "ulong64": c_ulonglong,
    "ushort": c_ushort,
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

    stream = otreestream(args.output, treename, "debug ntuple")

    counter_max = {}
    for rtype, branchname, varname, maxcount, counter in records:
        if counter:
            counter_max[counter] = max(counter_max.get(counter, 0), maxcount)

    counters = {}
    for counter in sorted(counter_max):
        counters[counter] = c_int()
        stream.add(counter, counters[counter])

    scalars = {}
    vectors = {}

    for rtype, branchname, varname, maxcount, counter in records:
        if maxcount == 1:
            ctype = CTYPE_MAP.get(rtype)
            if ctype is None:
                raise ValueError(f"Unsupported scalar type: {rtype}")
            scalars[varname] = ctype()
            stream.add(branchname, scalars[varname])
        else:
            vector_type = VECTOR_TYPE_MAP.get(rtype)
            if vector_type is None:
                raise ValueError(f"Unsupported vector type: {rtype}")
            vectors[varname] = rt.vector(vector_type)()
            stream.add(branchname, vectors[varname])

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
            counters[counter].value = value
            counter_values[counter] = value

        var_index = 0
        for rtype, branchname, varname, maxcount, counter in records:
            if maxcount == 1:
                scalars[varname].value = scalar_value(rtype, entry, var_index)
            else:
                size = counter_values.get(counter, min(maxcount, (entry % 3) + 1))
                fill_vector(vectors[varname], rtype, entry, var_index, size)
            var_index += 1

        stream.commit()

    stream.close()
    print(f"==> Wrote {args.entries} events to {args.output} (tree: {treename})")


if __name__ == "__main__":
    main()
