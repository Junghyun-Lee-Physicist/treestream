# Changelog

> **Purpose:** the single canonical record of what changed and when.
> **Audience:** anyone (human or AI) asking "what changed?". **Status:** living, append-only. **Updated:** 2026-10-03.
> **Contract:** [DOCUMENTATION_GUIDELINE.en.md](DOCUMENTATION_GUIDELINE.en.md) §3. **Related:** [decisions.md](decisions.md) (why), [STATUS.md](STATUS.md) (now), [troubleshooting.md](troubleshooting.md).

The **single canonical** record of notable changes to this `treestream` fork.
Format loosely follows [Keep a Changelog](https://keepachangelog.com/). There is
no separate `RELEASE_NOTES` file — it was removed so there is only one log to
keep in sync. Every code change gets an entry here
([Guideline Rule 2](DeveloperGuideline.md#rule-2--every-code-change-gets-a-changelog-entry)).

Entry shape: **what** (file/function) — **how** — **why**. Link the commit and
any [troubleshooting](troubleshooting.md) entry. At release time, curate the
`[Unreleased]` items into a version block.

---

## [Unreleased]

_Changes staged for the next release tag. See [`roadmap.md`](roadmap.md) for
what's still planned._

<!--
Example:
### Added
- `mkanalyzer.py` — new `--buffer-only` flag that writes only
  `include/eventBuffer.h` and skips `<name>.cc`/Makefile/README/linkdef.
  Why: generate just the data structure for embedding in an existing project
  (roadmap §1). Validated by: `make` of an existing package including the
  emitted header. Troubleshooting: n/a.
-->

### Added
- **`bin/mkeventbuffer.py`** — new tool that generates **only**
  `include/eventBuffer.h` (no `<name>.cc` / Makefile / `treestream`+`tnm`
  copies / linkdef / setup). It drives the real `mkvariables.py` (for `.root`
  inputs) and `mkanalyzer.py` into a temp dir and keeps just the buffer, so the
  output is **byte-identical** to a full `mkanalyzer.py` run. Why: roadmap §1
  (embed the typed buffer in an existing project without the skeleton).
  Validated by: `diff` against `mkanalyzer.py`'s `eventBuffer.h` on
  `variables_v18.txt` — identical (md5 match).
- **`docs/` documentation contract & logs** — adopted
  [`DOCUMENTATION_GUIDELINE.en.md`](DOCUMENTATION_GUIDELINE.en.md) + `.ko.md` as the
  project-agnostic documentation contract; added [`decisions.md`](decisions.md)
  (decision log) and [`STATUS.md`](STATUS.md) (status/progress). Why: comply with
  the contract's required doc types
  ([decisions D9](decisions.md#d9--adopt-documentation_guidelineenmd-as-the-documentation-contract)).

### Changed
- **`../README.md` rewritten (Korean, slimmed).** Quick-commands-first:
  `variables.txt` → eventBuffer-only (`mkeventbuffer.py`) *or* full skeleton
  (`mkanalyzer.py`); a worked `--merge` example with its Data+MC rationale; a
  local smoke-test section; brief concepts with the explanatory depth delegated
  to [`design.md`](design.md). Closes
  [D10](decisions.md#d10--slim-the-top-level-readmemd-into-docs).
- **All `docs/` files** — now carry a standard header (purpose · audience ·
  status · last-updated · related). `DeveloperGuideline.md` trimmed to a
  treestream overlay that references the contract (the generic "reuse" framework
  was removed as duplication); `roadmap.md` / `README.md` / Rule 1 adopt the
  `DECIDED / PROPOSED / OPEN / DEPRECATED` status vocabulary.
- **Setup switched to CMSSW_14_2_1 (ttHH workflow).** The top-level README now
  provides ROOT 6 + Python 3 via `cmsrel CMSSW_14_2_1` / `cmsenv` and builds the
  fork in place (`source setup.sh && make`); the conda / `TREESTREAM_PREFIX` /
  `make install` path was dropped (build needs only the `ROOTSYS` that `cmsenv`
  sets). `makingCommand.py` dataset base dir → the `ttHH2017UL_fullNano_v20`
  campaign.

### Fixed (2026-10-03, NanoAOD v15 review — troubleshooting A11–A17)
- **`mkanalyzer.py` object sizing** — `fill<Obj>s()` sized `Obj` from the
  *first* field (`Jet.resize(Jet_area.size())`); with a v15 Super-Set the first
  field is `Jet_PNetRegPtRawCorr`, so a file without that one branch gave **zero
  jets** with every other `Jet_*` present. Now the generated code takes the
  longest bound field of the object. ([§A11](troubleshooting.md#a11-zero-objects-when-the-first-field-of-an-object-is-absent))
- **`mkanalyzer.py` ghost structs** — `initBuffers()` pre-sized every object
  vector (`Jet = std::vector<Jet_s>(N)`), so `ev.Jet.size()==N` zero-valued jets
  until the first `fillObjects()`. Now `Jet.clear(); Jet.reserve(N);`.
  ([§A12](troubleshooting.md#a12-object-vectors-pre-sized-ghost-structs-before-the-first-fill))
- **`mkanalyzer.py` leaf counters** — `int nJet;` etc. were declared but never
  initialized nor read (garbage in read mode). Now 0 in `initBuffers()`, and
  read (`Events/nJet`) when an array that uses the counter is read, so a varlist
  still limits what is read. ([§A13](troubleshooting.md#a13-leaf-counters-njet--never-initialized-or-read))
  *Migration:* an analyzer that called `stream.select("Events/nJet", myN)`
  itself before building the buffer now has that address replaced by `ev.nJet`.
- **`src/treestream.cc` `readbranch`** — the return value of
  `TBranch::GetEntry` was ignored; an unreadable basket (zlib error, `-1`) left
  the previous entry's values in place and the job exited 0. Now `fatal()` with
  branch, entry and file. ([§A14](troubleshooting.md#a14-io-error-on-a-basket-returned-the-previous-entrys-values))
- **`mkanalyzer.py` `eventBuffer::read`** — ignored a negative
  `itreestream::read()` (an entry that cannot be loaded, e.g. a chain file that
  cannot be opened); the buffers kept the previous values and the job exited 0.
  Now it stops with exit 1. ([§A17](troubleshooting.md#a17-an-entry-that-cannot-be-loaded-kept-the-previous-values))
- **`mkvariables.py` single mode** — the documented `mkvariables.py file.root
  Events` ignored `Events` (argparse put it into the file list) and scanned the
  first tree in the file; the header listed every tree in the file. Now the
  words after the file are tree names and the header lists only the scanned
  trees. ([§A15](troubleshooting.md#a15-mkvariablespy-single-mode-ignored-the-tree-name))
- **`mkanalyzer.py` varlist** — `eventBuffer(stream, "Jet_pt")` matched nothing
  (keys are `Events/Jet_pt`, and an exact key was excluded by a strict `>`
  length test). Now a key selects a branch whose full or short name starts with
  it (exact names included). ([§A16](troubleshooting.md#a16-varlist-selected-nothing))

### Changed (2026-10-03)
- **`mkvariables.py --merge`** prints `[Type conflicts]` (branch, type per file)
  and keeps the widest type; before, the first file's type won silently
  (NanoAOD v9 vs v15: 84 conflicts, e.g. `Int_t` -> `Short_t`/`UChar_t`, and
  `TrigObj_filterBits` `Int_t` -> `ULong64_t`). A type outside the table never
  wins.
- **`mkanalyzer.py`** — `successBranches` / `missingBranches` are members (an
  analyzer can test them after construction); `choose` keys are always the full
  `Tree/branch` name (as in every buffer made from NanoAOD files: their headers
  list three or more trees; a manifest with exactly two `Tree` lines used to get
  short keys); the skeleton `<name>.cc` opens the tree the records belong to
  (`Events`), not the header's tree list; `if (choose[..]) { .. }` braces (no
  `-Wdangling-else`); `exit(1)` (was `exit(0)`) on a bad stream.

### Fixed
- **`mkanalyzer.py` non-deterministic output** — leaf-counter scalar
  declarations (`int nJet; …`) were emitted by iterating a Python `set`, whose
  order is `PYTHONHASHSEED`-dependent, so `eventBuffer.h` differed run-to-run
  (and `mkeventbuffer.py` couldn't be byte-identical). Now `sorted(counters)`
  → deterministic, reproducible output.
  ([§A10](troubleshooting.md#a10-non-deterministic-eventbufferh-leaf-counter-ordering))

### Removed
- **`Command.txt`** — the loose scratch note holding the last `--merge` command.
  Its command is now inlined in [`../README.md`](../README.md) (and generated on
  demand by `makingCommand.py`), so the file no longer drifts on its own.
  ([D10](decisions.md#d10--slim-the-top-level-readmemd-into-docs))

---

## [3.0.0] — 2026-03-15

Standalone (no CMSSW), Python 3, modern ROOT 6. The release that introduced the
Super-Set workflow and missing-branch safety.

### Added
- **`mkvariables.py --merge`** — scan multiple ROOT files and emit a Super-Set
  `variables.txt` annotated `[COMMON]` / `[ONLY:…]` / `[PARTIAL:…]`. Replaces
  the manual `combineBranch.py` / per-sample `variables_*.txt` workflow.
  Why: one analyzer must span Data/MC/period samples with different branch sets.
  See [design.md §3](design.md#3-the-super-set-strategy).
- **Branch Access Report** — generated `eventBuffer` prints
  `[OK] connected / [MISSING] not found` (+ missing list) at construction.
  Why: make missing branches visible instead of silent.
- **`makingCommand.py`** — helper that globs one `slimmedNtuple_*.root` per
  dataset under a base dir and prints the `mkvariables.py --merge …` command.

### Changed
- **`eventBuffer` present/select** — every `select()` is guarded by
  `input->present()`; missing branches are recorded, not fatal. Enables the
  Super-Set Strategy. (mkanalyzer.py `setb` builder, 18-Dec-2025.)
- **`mkanalyzer.py` record parsing** — positional (type=first, count=last,
  varname=second-to-last, branch=between) to handle `/` in branch names (e.g.
  `Events/Jet_pt`). Fixes troubleshooting [§A4](troubleshooting.md#a4-branch-names-containing--parsed-wrong).
- **`src/treestream.cc`** — missing-branch behavior on a *direct* `select()`
  changed from `warning()` to `fatal()` (18-Dec-2025). Backstop for
  hand-written code; the generated buffer never trips it.
  ([§A8](troubleshooting.md#a8-direct-select-on-a-missing-branch--when-it-should-be-fatal))
- **Makefile** — `COMPILER_SELECT=gcc|clang` (default gcc), `-std=c++17`
  (was `-ansi`), Python3-first detection, `.PHONY`, split `lib`/`tests` targets,
  error if `TREESTREAM_PREFIX` unset on `make install`.

### Fixed
- **Ghost objects** — removed forced `std::vector<T>(count,0)` pre-allocation in
  `initBuffers()`; collection vectors now start `size()==0`. Present vectors use
  resize → select → clear. Scalars still init to `0`. Prevents analysis loops
  iterating over fake zero-valued particles.
  ([§A5](troubleshooting.md#a5-ghost-objects--loops-iterate-over-fake-zero-valued-particles---priority-1), priority #1.)
- **Safe struct fill** — `Obj[i].fld = (fld.size() > i) ? fld[i] : 0;` guards
  partially-missing fields (e.g. MC-only `genPartIdx` on Data).
  ([§A7](troubleshooting.md#a7-segfault-filling-structs-on-data-mc-only-fields))
- **`--merge` count mismatch** — unify counts to the max per leaf counter so
  smaller-count sample-specific branches aren't dropped from structs.
  ([§A6](troubleshooting.md#a6---merge-silently-drops-sample-specific-branches-from-structs))
- **`#`-comments in `variables.txt`** — `mkanalyzer.py` skips `#` lines
  (required for `--merge` output). ([§A3](troubleshooting.md#a3-mkanalyzerpy-chokes-on-a---merge-variablestxt))
- **Py3 shebangs** — `#!/usr/bin/env python3` everywhere ([§A1](troubleshooting.md#a1-mkanalyzerpy--mkvariablespy-crash-on-launch-in-a-cmssw-shell)).
- **`import *` placement** — moved to module level in `mkvariables.py`
  ([§A2](troubleshooting.md#a2-syntaxerror-in-mkvariablespy)).
- **Standalone build path** — key off `TREESTREAM_PATH`, not `CMSSW_BASE`
  ([§A9](troubleshooting.md#a9-crab-stageout--wrong-build-path-in-cmssw)).

### Removed
- `branchList/` directory (superseded by `--merge`).
- Per-sample `variables_*.txt` (BTagCSVB, JetHTB/F, SingleMuonB/D, tttW, tttt);
  kept `variables_Combine_with_Bperiod.txt` as reference.
- `Makefile.BK251217`, `compileWithNoWarning.sh`.

### Documentation
- Complete README rewrite with workflow diagrams, the missing-branch init flow,
  Data/MC examples, the two-layer safety diagram, and a vs-master comparison.
  (Migration of that material into `docs/` is tracked in
  [roadmap Housekeeping](roadmap.md#housekeeping--debt).)

---

## Upstream history (HBP lineage, pre-fork)

Condensed from the original treestream release notes (now folded in here so
this file is self-contained).

- **2.0.3** — fix destructor in `otreestream` to avoid double delete.
- **2.0.2** — return to a single header (`treestream.h`); splitting the headers
  had broken `mkanalyzer.py`.
- **2.0.1** — minor fix in `testme.h`.
- **2.0.0** — add the `testtreestream.ipynb` notebook; align `.py`, `.cc`, and
  `.ipynb` as closely as possible.
- **1.1.2** — drop `add`/`select` for `char` / `unsigned long` (they broke
  PyROOT overloading in `otreestream`); split `treestream.h` into
  `itreestream.h` / `otreestream.h`; add `testtreestream.cc`; add
  `treestream.py` (`from treestream import itreestream`); split `Field` into
  `Field.h`; verified with ROOT 6.14.04.
- **1.1.1** — fix faulty interaction between chains and friends.
- **1.1.0** — allow reading multiple trees; update `mkvariables`/`mkanalyzer` to
  use it.
- **1.0.2** — improve Makefile; allow branch selection in `eventBuffer`.
- **1.0.1** — fix Makefile.
- **1.0.0** — first release of treestream as a package separate from
  TheNtupleMaker.
