# Troubleshooting

> **Purpose:** every bug/crash/failure hit so far — symptom, cause, fix — plus validation methods.
> **Audience:** anyone (human or AI) seeing an error or wanting to verify correctness. **Status:** living, append-only. **Updated:** 2026-06-27.
> **Contract:** [DOCUMENTATION_GUIDELINE.en.md](DOCUMENTATION_GUIDELINE.en.md) §3. **Related:** [design.md](design.md), [decisions.md](decisions.md), [CHANGELOG.md](CHANGELOG.md).

Concrete failures hit while developing this fork, and how each was resolved.
Add to **Part A** whenever you hit a bug/crash/confusing-log
([Guideline Rule 3](DeveloperGuideline.md#rule-3--every-problem-gets-a-troubleshooting-entry)).
Add to **Part B** when you find or invalidate a way of checking correctness.

Template for Part A entries: **Symptom · Signature · Root cause · Fix · Validated by.**

---

## Part A — Bugs & fixes

### A1. `mkanalyzer.py` / `mkvariables.py` crash on launch in a CMSSW shell
- **Symptom:** scripts fail immediately, or run under the wrong interpreter,
  inside a CMSSW environment.
- **Signature:** interpreter/path errors from a `#!/usr/bin/env python` shebang
  resolving to a broken build-time python.
- **Root cause:** `/usr/bin/python` (Py2, or a CMSSW build-time path) was picked
  up.
- **Fix:** all shebangs changed to `#!/usr/bin/env python3` (commit *"Fix
  mkanalyzer.py shebang: python -> python3"*; CHANGELOG [3.0.0]).
- **Validated by:** scripts run from a clean Py3 + ROOT 6 shell and from an
  lxplus CMSSW shell without interpreter errors.

### A2. `SyntaxError` in `mkvariables.py`
- **Symptom:** `mkvariables.py` won't even parse.
- **Signature:** `SyntaxError` referencing `import *`.
- **Root cause:** a `from … import *` sat inside a function/conditional rather
  than at module level (illegal in Py3).
- **Fix:** moved the wildcard import to module scope (commit *"Fix SyntaxError:
  move import * to module level in mkvariables.py"*).
- **Validated by:** `python3 -m py_compile bin/mkvariables.py` clean.

### A3. `mkanalyzer.py` chokes on a `--merge` `variables.txt`
- **Symptom:** generating from a Super-Set file fails to parse records.
- **Signature:** parse error / bad token split on lines beginning with `#`.
- **Root cause:** `--merge` output contains `#`-comment annotation lines
  (`# [COMMON]`, `# [ONLY:…]`, header block). The parser tried to treat them as
  branch records.
- **Fix:** skip blank lines and lines starting with `#` in the record loop
  (`if record.startswith("#"): continue`, mkanalyzer.py ~L935; commit *"Fix
  mkanalyzer.py: skip comment lines in variables.txt"*; CHANGELOG [3.0.0]).
- **Validated by:** `mkanalyzer.py` runs cleanly on `variables_v18.txt` (a real
  Super-Set file with comment blocks).
- **Cross-ref:** half of the [variables.txt contract](DeveloperGuideline.md#rule-6--mkvariablespy-and-mkanalyzerpy-share-one-contract-the-variablestxt-format).

### A4. Branch names containing `/` parsed wrong
- **Symptom:** records for branches like `Events/Jet_pt` produce wrong
  type/name/count assignments.
- **Signature:** fields shifted; type or count comes out empty/garbled.
- **Root cause:** naive split on `/` assumed a fixed field count; a `/` inside
  the branch name added tokens.
- **Fix:** positional parsing in `mkanalyzer.py` — type = first token,
  count(+leafcounter) = last token, varname = second-to-last, branchname =
  everything between (CHANGELOG [3.0.0]).
- **Validated by:** records with `Events/<branch>` generate correct
  declarations and `select()` calls.
- **Cross-ref:** the other half of the variables.txt contract (A3).

### A5. Ghost objects — loops iterate over fake zero-valued particles  ⭐ priority #1
- **Symptom:** collections appear non-empty with all-zero entries even when the
  branch is absent or before reading; histograms/counts polluted by phantom
  objects.
- **Signature:** `Jet.size()` (etc.) equals the buffer capacity rather than the
  true per-event count; loops process zero-valued entries.
- **Root cause:** `initBuffers()` pre-filled every collection vector with
  `std::vector<T>(count, 0)`, so a missing/not-yet-read vector held `count`
  zeros.
- **Fix:** removed the forced vector zero-initialization (the
  `std::vector<T>(count,0)` / `(count,(T)0)` lines are commented out in
  `mkanalyzer.py`); vectors now start `size()==0`. Present vectors use
  resize → select → clear so capacity is reserved without ghost entries.
  Scalars are still set to `0`. (Commits around *"update eventBuffer … to
  prevent initialization"* / *"delete init"*; 18-Dec-2025; CHANGELOG [3.0.0].)
- **Validated by:** running on a file missing a given collection yields
  `size()==0` for it; the Branch Access Report lists it under MISSING.
- **Deep dive:** [design.md §5](design.md#5-initialization--the-ghost-object-problem).

### A6. `--merge` silently drops sample-specific branches from structs
- **Symptom:** a field present in a minority sample disappears from the
  generated object struct after merging.
- **Signature:** struct `<Obj>_s` missing an expected field; no error.
- **Root cause:** the field's `count` differed from the rest of the object (its
  sample had fewer entries when scanned), and `mkanalyzer.py` requires all
  fields of a struct to share one count, so the odd-count field was excluded.
- **Fix:** **count unification** in `mkvariables.py --merge` — raise every
  branch sharing a leaf counter to the max count seen for that counter before
  writing (commit *"Fix --merge count mismatch that excludes sample-specific
  branches from structs"*).
- **Validated by:** merge summary prints "Count unification: N branches
  updated"; the previously-missing field now appears in the struct.
- **Deep dive:** [design.md §3](design.md#3-the-super-set-strategy).

### A7. Segfault filling structs on Data (MC-only fields)
- **Symptom:** crash inside `fill<Obj>s()` when running on Data with an analyzer
  generated from a Super-Set.
- **Signature:** out-of-bounds / segfault indexing a field vector while the
  object collection is non-empty.
- **Root cause:** the object (`Jet`/`Electron`) exists in Data, but an MC-only
  field (`*_genPartIdx`, `*_genPartFlav`) does not, so that field vector is
  empty (`size()==0`) while the loop ran to the collection length.
- **Fix:** bounds-checked copy in the struct fill:
  `Obj[i].fld = (fld_vec.size() > i) ? cast fld_vec[i] : 0;` (mkanalyzer.py
  ~L1342; 18-Dec-2025; CHANGELOG [3.0.0]).
- **Validated by:** the same analyzer runs over Data and MC; Data fills MC-only
  fields with `0` instead of crashing.

### A8. Direct `select()` on a missing branch — when it *should* be fatal
- **Symptom:** (intended behavior) hand-written code that selects a branch by
  name typos it or assumes a branch that isn't there.
- **Signature:** `fatal(...)` abort from `src/treestream.cc` on a missing branch
  during a direct `select()`.
- **Root cause / design:** `treestream.cc` was changed from `warning()` to
  `fatal()` for missing branches (18-Dec-2025; CHANGELOG [3.0.0]). Deliberate:
  the generated `eventBuffer` always guards with `present()` and never trips it,
  but **direct** user `select()` calls now fail loudly instead of silently
  reading nothing.
- **Fix / guidance:** if you call `select()` yourself, guard it with
  `input->present(...)`, or rely on the generated `eventBuffer` which already
  does. See [design.md §6](design.md#6-two-layer-missing-branch-safety).

### A9. CRAB stageout / wrong build path in CMSSW
- **Symptom:** treestream picks up a broken `CMSSW_BASE` path; clang
  auto-detection points at the wrong compiler.
- **Root cause:** standalone use inside a shell where CMSSW is set up but not
  used for treestream.
- **Fix:** standalone build keys off `TREESTREAM_PATH` only (CMSSW path
  disabled; CHANGELOG [3.0.0]); Makefile adds `COMPILER_SELECT=gcc|clang`
  (default gcc) and `-std=c++17`.
- **Validated by:** `make` succeeds in a clean shell and in a CMSSW shell with
  `COMPILER_SELECT=gcc`.

### A10. Non-deterministic `eventBuffer.h` (leaf-counter ordering)
- **Symptom:** regenerating `eventBuffer.h` from the *same* `variables.txt`
  produces files that differ between runs; `diff`/`md5sum` mismatch with no
  input change. Surfaced when verifying that `mkeventbuffer.py` matches
  `mkanalyzer.py`.
- **Signature:** only the leaf-counter scalar lines permute, e.g.
  ```
  130c130
  <   int   nFatJet;
  ---
  >   int   nJet;
  ```
  (same set of branches, different order); identical line counts.
- **Root cause:** `mkanalyzer.py` collected leaf counters into a Python `set`
  and iterated it (`for name in counters:`) to emit the `int n<Counter>;`
  declarations and their `output->add(...)`. String-set iteration order is
  `PYTHONHASHSEED`-randomized per process, so two runs ordered them differently.
- **Fix:** iterate `sorted(counters)` (mkanalyzer.py ~L1123). The order of these
  independent scalar declarations is semantically irrelevant, so sorting is safe
  and makes output reproducible. CHANGELOG [Unreleased].
- **Validated by:** two direct `mkanalyzer.py` runs now produce identical
  `eventBuffer.h`; `mkeventbuffer.py` output is byte-identical to `mkanalyzer.py`
  (same md5) on `variables_v18.txt`. Before the fix, forcing `PYTHONHASHSEED`
  also made them match — confirming the cause.

---

## Part B — Validation methods (and their limits)

### B1. Branch Access Report (startup)
The generated `eventBuffer` prints `[OK] connected / [MISSING] not found` with
the missing list at construction. **Use it as the first check** that the right
branches bound for a given file. *Limit:* it confirms presence/binding, not that
values are correct or that a "missing scalar = 0" isn't masking a real problem
(see [design.md §10](design.md#10-known-limitations)).

### B2. Merge summary counts
`--merge` prints total-union / COMMON / per-file-unique counts and any count
unification. Sanity-check these against expectation (MC should contribute the
gen-truth ONLY/PARTIAL branches; Data should not). A surprising COMMON count
often means you scanned non-representative files.

### B3. Compile round-trip
`python3 -m py_compile bin/*.py` for the generators; then generate a package and
`make` it. A change that parses fine but breaks generated C++ is only caught at
`make`. *Limit:* compiling proves it builds, not that it reads the ntuple
correctly — pair with B1 on a real file.

### B4. Cross-sample run
Run one generated binary over both a Data file and an MC file. Correct behavior:
both run; MC-only fields are bound on MC and reported MISSING (and filled `0`)
on Data; no segfault. This exercises A5/A6/A7 together.

### B5. `mklist.py` spot check
`mklist.py file.root Events` dumps the raw branch listing — use it to confirm
whether a specific branch truly exists in a file before assuming a generator
bug.
