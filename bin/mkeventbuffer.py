#!/usr/bin/env python3
# -----------------------------------------------------------------------------
#  mkeventbuffer.py
#
#  Generate ONLY include/eventBuffer.h for a set of ntuple branches — not the
#  full analyzer skeleton that mkanalyzer.py produces (no <name>.cc, Makefile,
#  treestream/tnm copies, linkdef, setup scripts).
#
#  Why this is a thin wrapper around mkanalyzer.py, not a reimplementation
#  -----------------------------------------------------------------------------
#  The eventBuffer.h that mkanalyzer.py emits is the end product of a lot of
#  subtle generation logic: positional record parsing (branch names may contain
#  '/'), object-struct detection, the present()/select() guards, the
#  no-zero-init + resize/select/clear pattern, the bounds-checked struct fill,
#  and the three constructors. Re-deriving any of that by hand would eventually
#  drift from treestream. To guarantee BYTE-IDENTICAL output, this tool runs the
#  real mkanalyzer.py into a temporary directory and keeps only
#  include/eventBuffer.h. The result cannot differ from treestream, because it
#  *is* treestream's generator — just with everything except the buffer dropped.
#
#  Inputs (auto-detected)
#  -----------------------------------------------------------------------------
#    * a variables.txt  (the manifest produced by mkvariables.py)  -> used as is
#    * one  *.root file                            -> scanned with mkvariables.py
#                                                                   (single mode)
#    * many *.root files (or --merge)        -> scanned with mkvariables.py
#                                                       --merge (Super-Set union)
#
#  Usage
#  -----------------------------------------------------------------------------
#    mkeventbuffer.py variables.txt                     [-o eventBuffer.h]
#    mkeventbuffer.py ntuple.root            [--tree T] [-o eventBuffer.h]
#    mkeventbuffer.py --merge a.root b.root  [--tree T] [-o eventBuffer.h]
#
#  Environment: same requirement as mkanalyzer.py — TREESTREAM_PATH must point at
#  a treestream checkout (so include/treestream.h is found). Scanning .root files
#  additionally needs ROOT/PyROOT (same as mkvariables.py).
# -----------------------------------------------------------------------------

import os
import sys
import shutil
import argparse
import subprocess
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))


def find_tool(name):
    """Locate a sibling generator script (mkvariables.py / mkanalyzer.py)."""
    path = os.path.join(HERE, name)
    if not os.path.exists(path):
        sys.exit("[mkeventbuffer] cannot find %s next to this script (%s)" % (name, HERE))
    return path


def check_treestream_env():
    """mkanalyzer.py aborts unless TREESTREAM_PATH/include/treestream.h exists."""
    tp = os.environ.get("TREESTREAM_PATH")
    if not tp or not os.path.exists(os.path.join(tp, "include", "treestream.h")):
        sys.exit("[mkeventbuffer] TREESTREAM_PATH is not set (or has no "
                 "include/treestream.h).\n"
                 "                Run `source setup.sh` in your treestream "
                 "checkout first — mkanalyzer.py requires it.")


def run(cmd, cwd):
    """Run a child generator with the current interpreter; show output only on failure."""
    proc = subprocess.run([sys.executable] + cmd, cwd=cwd,
                          stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                          text=True)
    if proc.returncode != 0:
        sys.stderr.write(proc.stdout)
        sys.exit("[mkeventbuffer] %s failed (exit %d)"
                 % (os.path.basename(cmd[0]), proc.returncode))
    return proc.stdout


def scan_to_variables(roots, tree, merge, workdir):
    """Produce a variables.txt from .root file(s) via treestream's mkvariables.py."""
    mkvariables = find_tool("mkvariables.py")
    roots = [os.path.abspath(r) for r in roots]
    tree_args = (["--tree"] + tree) if tree else []
    out = os.path.join(workdir, "variables.txt")
    if merge or len(roots) > 1:
        run([mkvariables, "--merge"] + roots + tree_args + ["-o", out], cwd=workdir)
    else:
        # single mode always writes ./variables.txt in the working directory
        run([mkvariables] + roots + tree_args, cwd=workdir)
    if not os.path.exists(out):
        sys.exit("[mkeventbuffer] mkvariables.py did not produce variables.txt")
    return out


def generate_eventbuffer(variables_path, workdir):
    """Run the real mkanalyzer.py into workdir and return the eventBuffer.h it wrote."""
    mkanalyzer = find_tool("mkanalyzer.py")
    pkg = "_ebgen"  # throwaway analyzer package name, confined to workdir
    run([mkanalyzer, pkg, os.path.abspath(variables_path)], cwd=workdir)
    eb = os.path.join(workdir, pkg, "include", "eventBuffer.h")
    if not os.path.exists(eb):
        sys.exit("[mkeventbuffer] mkanalyzer.py did not produce eventBuffer.h")
    return eb


def main():
    ap = argparse.ArgumentParser(
        description="Generate ONLY eventBuffer.h (byte-identical to mkanalyzer.py).",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="examples:\n"
               "  mkeventbuffer.py variables.txt\n"
               "  mkeventbuffer.py ntuple.root --tree Events -o eventBuffer.h\n"
               "  mkeventbuffer.py --merge mc.root data.root --tree Events\n")
    ap.add_argument("input", nargs="+",
                    help="a variables.txt, or one/more .root files to scan")
    ap.add_argument("--tree", nargs="*", default=None,
                    help="tree name(s) when scanning .root files")
    ap.add_argument("--merge", action="store_true",
                    help="force Super-Set merge when scanning multiple .root files")
    ap.add_argument("-o", "--output", default="eventBuffer.h",
                    help="output path for eventBuffer.h (default: ./eventBuffer.h)")
    args = ap.parse_args()

    check_treestream_env()

    # Input mode: a single .txt is a variables manifest; otherwise .root file(s).
    is_varfile = len(args.input) == 1 and args.input[0].endswith(".txt")
    if not is_varfile and not all(f.endswith(".root") for f in args.input):
        sys.exit("[mkeventbuffer] inputs must be a single variables .txt, "
                 "or one/more .root files")

    with tempfile.TemporaryDirectory(prefix="mkeb_") as workdir:
        if is_varfile:
            variables_path = os.path.abspath(args.input[0])
            if not os.path.exists(variables_path):
                sys.exit("[mkeventbuffer] no such file: %s" % variables_path)
        else:
            variables_path = scan_to_variables(args.input, args.tree, args.merge, workdir)

        eb = generate_eventbuffer(variables_path, workdir)

        out = os.path.abspath(args.output)
        os.makedirs(os.path.dirname(out) or ".", exist_ok=True)
        shutil.copyfile(eb, out)

    nlines = sum(1 for _ in open(out))
    print("[mkeventbuffer] wrote %s  (%d lines)" % (out, nlines))


if __name__ == "__main__":
    main()
