# Design & Architecture

> **Purpose:** how this treestream fork works and **why** — the data model, the generation pipeline, and component reference.
> **Audience:** anyone (human or AI) who needs to understand or change the tool. **Status:** living. **Updated:** 2026-06-27.
> **Note on type:** per [contract §7](DOCUMENTATION_GUIDELINE.en.md), this single doc combines *Purpose & rationale* + *Architecture* + *Reference* because, at this scope, they are read and changed together (see [decisions D5](decisions.md#d5--merge-conceptsmd--architecturemd-into-designmd)).
> **Related:** [DeveloperGuideline.md](DeveloperGuideline.md), [decisions.md](decisions.md), [troubleshooting.md](troubleshooting.md), [roadmap.md](roadmap.md).

The single source for how this `treestream` fork works **and why**. It merges
what were previously two files (`concepts.md` = the "why"/data model,
`architecture.md` = the "what/how"/reference); they overlapped on the same
mechanisms (Super-Set, initialization, present/select), so keeping them apart
cost double-maintenance. The doc reads explanation-first, then reference.

For the rules on editing the project see
[`DeveloperGuideline.md`](DeveloperGuideline.md); for the incident history see
[`troubleshooting.md`](troubleshooting.md); for what's planned see
[`roadmap.md`](roadmap.md).

> Scope note: "design/theory" here means treestream's **own** model — how
> ntuple branches map to C++ buffers and why missing-branch handling is shaped
> the way it is. Physics theory of any specific analysis (categories,
> observables, …) belongs in *that analysis's* repo, not in this tool.

---

## 1. Pipeline overview

```
   one or more *.root ntuples
            │
            │  bin/mkvariables.py            (scan; --merge = union over files)
            ▼
       variables.txt                          (the branch manifest / contract)
            │
            │  bin/mkanalyzer.py <name>       (read manifest, emit C++)
            ▼
   <name>/                                    (a compile-ready analyzer package)
   ├── include/eventBuffer.h   <- regenerated every run
   ├── include/treestream.h    include/tnm.h  include/linkdef.h
   ├── src/treestream.cc       src/tnm.cc
   ├── python/tnm.py
   ├── <name>.cc               <- the "MyAnalyzer" main; written only if absent
   ├── Makefile
   └── README
            │
            │  make   (uses ROOT + the copied core)
            ▼
   ./<name>   analyzer binary  →  reads ntuples via eventBuffer
```

`bin/mklist.py` is a side utility: open one file, print its branch/leaf listing
(`stream.ls()`) — handy for eyeballing a file before generating anything.

---

## 2. The data model (the "theory")

A NanoAOD `Events` tree is a flat list of branches. They come in three shapes;
`mkvariables.py` classifies each:

| On-file shape | Example | In `variables.txt` | In `eventBuffer` |
|---|---|---|---|
| **scalar** (one value/event) | `run`, `MET_pt`, `HLT_*`, `Flag_*` | `count = 1` | a plain `int`/`float`/`bool` member |
| **variable-length array** (one value/object, length from a counter) | `Jet_pt[nJet]` | `count = capacity`, `leafcounter = nJet` | a `std::vector<T>` member |
| **`vector<T>` branch** | a stored STL vector | `vector<T>`, capped count 50 | a `std::vector<T>` member |

Most central NanoAOD object fields are the **variable-length array** case.
`eventBuffer` represents every collection field as `std::vector<T>` regardless
of the on-file encoding.

**Leaf counters.** A *leaf counter* states how many entries a collection has
this event — `nJet`, `nElectron`, `nFatJet`. It is **not** its own record in
`variables.txt`; it appears only as the trailing `leafcounter` field of every
branch that uses it. (In the raw listing a counter row ends in `*`;
`mkvariables.py` drops those rows on purpose.) Every field of one object shares
the same counter — which is exactly why all of an object's branches must share
the same `count` (see [§3, count unification](#3-the-super-set-strategy)).

**Object structs.** When several fields share an `<obj>_` prefix (`Jet_pt`,
`Jet_eta`, `Jet_btag`), `mkanalyzer.py` also generates a struct `Jet_s` and a
`std::vector<Jet_s> Jet`. After `read(entry)` you call `fillJets()` to transpose
the parallel field vectors into a vector of per-jet structs — the natural "loop
over jets" view.

---

## 3. The Super-Set strategy

**Problem.** The branch *set* is not constant across the files you analyze:

- **Data vs MC.** MC carries generator-truth branches (`Electron_genPartIdx`,
  `*_genPartFlav`, LHE/PU weights, …) that Data simply lacks.
- **Sample vs sample.** Different MC productions and data eras enable different
  branches; even the same object can have a different number of stored entries.

A `variables.txt` scanned from **one** file describes only that file. Generate
from a Data file and the analyzer is blind to MC-truth branches; generate from
MC and run on Data and it asks for branches that aren't there.

**Solution.** `mkvariables.py --merge` scans many representative files and emits
the **union** of all branches — a *Super-Set* — annotated by presence:

- `COMMON` — in every input file (safe everywhere).
- `ONLY:<file>` — in exactly one file.
- `PARTIAL:<files>` — in some but not all.

One analyzer generated from the Super-Set then knows about *every* branch any
target sample might have; at runtime each `eventBuffer` only binds the branches
actually present in the file it opened (§4), so the same binary runs over Data
and MC alike. This replaced an older manual `combineBranch.py` / per-sample
`variables_*.txt` workflow.

**Mechanism (`run_merge`).**
1. **Scan each file** with `scan_file()`; keep a per-file `{varname → record}`
   map and print each file's branch count.
2. **Union** all varnames, keeping for shared names the record with the **max**
   `maxcount`. Track `presence[varname] = {labels}`.
3. **Count unification** — for each leaf counter (`nJet`, `nElectron`, …) find
   the max count across **all** branches that use it, then raise every such
   branch to that max. `mkanalyzer.py` requires all fields of one struct to
   share a count; without this, a sample-specific field with a smaller count is
   silently dropped from the struct (the bug behind commit *"Fix --merge count
   mismatch that excludes sample-specific branches from structs"*;
   troubleshooting [§A6](troubleshooting.md#a6---merge-silently-drops-sample-specific-branches-from-structs)).
4. **Classify** present-in-all → `COMMON`; else group by presence pattern into
   `ONLY:<file>` / `PARTIAL:<files>`.
5. **Write** `variables.txt` (or `-o <name>`): a `Tree` header, a `#`-comment
   block explaining the tags, then COMMON records, then sample-specific records
   grouped by pattern with `# [ONLY:…]` / `# [PARTIAL:…]` headers.

The annotations are comments (`mkanalyzer.py` ignores them) but tell a human
exactly which branches are absent in which inputs, and pair with the runtime
Branch Access Report to make missing branches visible.

`makingCommand.py` is a convenience helper: point it at a sample base directory
and a list of dataset subpaths; it globs one `slimmedNtuple_*.root` per dataset
and prints the ready `mkvariables.py --merge … --tree Events` command. A worked
example of that merge command — and **why** it merges Data+MC — is in the
top-level [`../README.md`](../README.md).

---

## 4. Runtime presence & the generated eventBuffer

`eventBuffer` (template `TEMPLATE_H` in `mkanalyzer.py`) is a struct with three
constructors:

- **read-only** `eventBuffer(itreestream& stream, std::string varlist="")` —
  the analyzer path. It `initBuffers()`, fills the `choose` map (all branches if
  `varlist` is empty, else only those matching the prefixes in `varlist`), then
  for each chosen branch runs present/select below and prints the Branch Access
  Report.
- **write-only** `eventBuffer(otreestream& stream)` — for skimming/writing;
  `initBuffers()` then `output->add(...)` per branch.
- **default** `eventBuffer()` — empty.

**present/select per branch** (generated into the `setb` block). The Super-Set
is a superset, so any given file is missing some of it; every bind is guarded:

- *scalar* (`count==1`):
  `if (input->present(b)) { select(b,var); success.push_back(b);} else { missing.push_back(b);}`
- *vector* (`count>1`):
  `if (input->present(b)) { var.resize(count); select(b,var); var.clear(); success…} else { missing…}`
  — `resize` gives treestream's `select()` a valid buffer address to bind to;
  `clear()` resets the logical size to 0 (capacity retained) so nothing is
  "pre-filled". See [§5](#5-initialization--the-ghost-object-problem).

**Branch Access Report.** At construction the buffer prints
`[OK] N connected / [MISSING] M not found`, lists the missing branches, and
notes that missing branches are expected for a Super-Set across Data/MC/periods
(scalars default to 0, vectors stay empty). This is the antidote to silent
failure — you *see* what wasn't bound.

**Object structs.** After `read(entry)` you call `fillObjects()` (or
`fillJets()` etc.). Each `fill<Obj>s()` resizes the struct vector to the
collection length and copies field-by-field with a bounds check:

```cpp
Jet[i].btag = (Jet_btag.size() > i) ? Jet_btag[i] : 0;
```

so a field vector that is empty/short (a **partially** missing field — e.g. an
MC-only field while running on Data, where `Jet` exists but `Jet_genPartIdx`
does not) yields `0` instead of indexing out of bounds and crashing
(troubleshooting [§A7](troubleshooting.md#a7-segfault-filling-structs-on-data-mc-only-fields)).

**Selection bookkeeping.** `select(obj)` / `select(obj,index)` push into
`indexmap`; `saveObjects()` compacts the chosen indices and updates the leaf
counters; `read(entry)` clears `indexmap` each event.

---

## 5. Initialization & the ghost-object problem

Priority #1, and the most counter-intuitive design point. The rule:

- **Scalars are initialized to `0`** (in `initBuffers()`). A missing scalar
  branch therefore reads as `0` rather than uninitialized garbage.
- **Vectors are *not* pre-filled.** The forced `std::vector<T>(count, 0)`
  pre-allocation the original code put in `initBuffers()` was **removed** in
  this fork.

**Why removing vector zero-init matters.** If a collection vector is pre-filled
with `count` zeros, then even before any event is read `Jet` "contains" `count`
fake jets with all fields `0`; and if the branch is **missing** in this file the
vector stays full of those zeros, so any `for (i in 0..Jet_pt.size())` loop
iterates over **ghost objects** — phantom particles that never existed, silently
polluting histograms and counts. By **not** initializing the vectors, a missing
or not-yet-read collection has `size()==0`, so loops correctly do nothing. Real
data appears only once a present branch is bound and an event is read.

**The resize → select → clear dance** (for a *present* vector, at construction):

```cpp
var.resize(count);          // give treestream real memory to bind an address to
input->select("branch", var);
var.clear();                // reset logical size to 0 (capacity retained)
```

`select()` needs a valid buffer address (hence `resize`); `clear()` then makes
the vector logically empty until `read()` fills it. Net effect: capacity is
reserved (no per-event reallocation) with **no ghost entries**. The struct fill
in §4 then adds the bounds check for partially-missing fields. (Commits around
*"update eventBuffer … to prevent initialization"* / *"delete init"*,
18-Dec-2025; troubleshooting
[§A5](troubleshooting.md#a5-ghost-objects--loops-iterate-over-fake-zero-valued-particles---priority-1).)

**Memory in practice.** Connected vectors grow to a per-job high-water mark and
stay there — capacity is retained across events **by design** (ROOT needs a
stable buffer address, so never call `shrink_to_fit()`). To cut memory/IO:
(1) pass a runtime `varlist` — `eventBuffer ev(stream, "Jet_pt Jet_eta MET_pt")`
reads only the matching branches; (2) trim unused branches from `variables.txt`
before generating; (3) skip `fillObjects()` and read the flat vectors
(`ev.Jet_pt[i]`) directly in memory-critical loops.

---

## 6. Two-layer missing-branch safety

1. **Generated layer (eventBuffer):** every `select()` is guarded by
   `present()`. Missing branches are recorded and reported, never fatal.
   Scalars stay `0`, vectors stay empty.
2. **Core layer (`src/treestream.cc`):** as of 18-Dec-2025, a *direct*
   `select()` on a non-existent branch calls `fatal()` (was `warning()`). This
   only fires if **user code** calls `select()` itself without a `present()`
   guard; the generated buffer never trips it.

Intent: the common path (the generated buffer) is forgiving so one analyzer
spans heterogeneous samples; the raw API is strict so a genuine typo in
hand-written code fails loudly instead of silently reading garbage.

---

## 7. The scripts & CLI

### `mkvariables.py` — scan ntuple(s) → `variables.txt`
- **single:** `mkvariables.py file.root [Tree]` — original HBP behavior, one
  record per branch.
- **`--merge`:** `mkvariables.py --merge a.root b.root … --tree Events
  [-o out.txt]` — this fork's union/Super-Set mode (§3).

Internals: `scan_file()` opens an `itreestream`, parses `stream.str()` into
records `(btype, branch, varname, maxcount, lc)`, skips
`TLorentzVector`/`TRef`/`TRefArray` and fixed C-arrays, lowercases the type and
strips `_t`, caps `vector<T>` counts at 50, runs the CMS name-cleanup regexes
(strip `edm/reco/pat`, dedupe collisions). Pure counter rows (ending `*`) are
dropped; the counter survives only as the `lc` field.

### `mkanalyzer.py` — `variables.txt` → analyzer package
- **CLI:** `mkanalyzer.py <name>[/f] [variables.txt] [macro]`. A `/f` (`/F`)
  suffix on the name forces re-copy of all files **except** `<name>.cc`. A third
  argument switches on `macroMode` (a rarely-used decl/impl-header output path).
- **Parse:** reads the `Tree` header line(s), then each record. **Skips blank
  lines and lines starting with `#`** (required for `--merge` output). Uses
  *positional* field parsing — type = first token, count(+counter) = last,
  varname = second-to-last, branch = everything between — so branch names
  containing `/` (e.g. `Events/Jet_pt`) parse correctly.
- **Struct detection:** a `varname` of form `<obj>_<field>` whose `<obj>` prefix
  appears ≥2 times becomes an object struct.
- **Generate:** builds the code-string lists (`declare`, `declarevec`, `init`,
  `setb`, `choose`, `addb`, struct decl/impl/vec) that fill `TEMPLATE_H`, then
  writes files (§9).

### `mklist.py` — quick listing
`mklist.py <file.root> [Tree …]` → `itreestream(...).ls()`. No output file.

### `mkeventbuffer.py` — eventBuffer.h only
`mkeventbuffer.py <variables.txt | file.root…> [--tree T] [--merge] [-o out.h]`.
A thin wrapper that produces **only** `include/eventBuffer.h`, byte-identical to
a full `mkanalyzer.py` run: it runs `mkvariables.py` (for `.root` inputs) and
`mkanalyzer.py` in a temp dir and copies out just the buffer. Use it to embed
the typed buffer in another project without the skeleton. Identity is by
construction — it *is* the generator — and depends on the determinism fix in
troubleshooting [§A10](troubleshooting.md#a10-non-deterministic-eventbufferh-leaf-counter-ordering).

---

## 8. The variables.txt format (contract)

One record per branch — the interface between the two tools, which **must stay
in sync** ([Guideline Rule 6](DeveloperGuideline.md#rule-6--mkvariablespy-and-mkanalyzerpy-share-one-contract-the-variablestxt-format)):

```
type / branch[/sub…] / variable-name / maxcount [leafcounter]
```

- **type** — lowercased C++ scalar (`int`, `float`, `bool`, …) or `vector<T>`.
- **branch** — on-file branch name; may itself contain `/` (e.g.
  `Events/Electron_pt`).
- **variable-name** — the C++ member name to bind it to.
- **maxcount** — `1` for a scalar; buffer capacity for an array/vector.
- **leafcounter** — (optional, space-separated) the counter branch, e.g.
  `nElectron`.

Header lines start with `Tree <name>`. In `--merge` output a block of
`#`-comment lines follows, describing the merge. Example rows:

```
int/Events/Electron_charge/Electron_charge/8 nElectron
float/Events/Electron_pt/Electron_pt/8 nElectron
```

---

## 9. Generated package layout (reference)

| Path | Regenerated? | Role |
|---|---|---|
| `<name>/include/eventBuffer.h` | **every run** | the generated buffer (edit the template in `mkanalyzer.py`, not this) |
| `<name>/include/treestream.h`, `src/treestream.cc` | if missing / forced | copied core I/O |
| `<name>/include/tnm.h`, `src/tnm.cc`, `python/tnm.py` | if missing / forced | copied ROOT analysis helpers |
| `<name>/include/linkdef.h` | if missing / forced | ROOT dictionary pragmas |
| `<name>/<name>.cc` | **only if missing** (or `/f`) | the analyzer main — *your* code |
| `<name>/Makefile` | every run | build rules (`COMPILER_SELECT`, c++17) |
| `<name>/README` | if missing / forced | per-package usage stub |

`tnm` (= "TheNtupleMaker" helpers) provides `outputFile`, `commandLine`,
`matchedPair`, `ptThing`, histogram/utility helpers, and includes
`eventBuffer.h`. It is copied in so generated packages build standalone.

---

## 10. Known limitations

The forgiving design trades one failure mode for a milder one — and seeds the
[roadmap](roadmap.md) safety items:

1. **Missing scalar ≡ `0`.** A missing `HLT_*`/`Flag_*`/weight reads as
   `0`/false, indistinguishable in analysis logic from a branch that genuinely
   *was* `0`. The absence is hidden once past the startup report. (Roadmap:
   optional fail-fast on a declared required-branch list.)
2. **Direct vector access is the caller's responsibility.** Struct fill is
   bounds-checked, but reading a field `std::vector` directly (not via the
   struct) for a missing branch needs a `.size()` check in the analysis code.
3. **The Super-Set is only as complete as the files you scanned.** A branch
   present in *no* scanned file is absent from `variables.txt` and the analyzer
   never knows about it. Scan representative Data **and** MC (and each era you
   care about).

---

## 11. Glossary

- **ntuple** — a flat ROOT `TTree` of per-event branches (here, CMS NanoAOD).
- **NanoAOD** — CMS's compact, flat analysis data tier.
- **branch / leaf** — a column in the tree / its underlying storage.
- **leaf counter** — a branch (`nJet`, `nElectron`) giving a collection's
  per-event length; in `variables.txt` it lives as a trailing field, not a row.
- **eventBuffer** — the generated C++ struct binding branches to typed members;
  the central artifact of this tool.
- **object struct** (`Jet_s`, …) — a per-object view assembled by transposing
  parallel field vectors via `fill<Obj>s()`.
- **Super-Set** — the union of branches across several scanned files, annotated
  COMMON / ONLY / PARTIAL, produced by `mkvariables.py --merge`.
- **present() / select()** — treestream calls to test branch existence and to
  bind a branch to a C++ variable.
- **itreestream / otreestream** — treestream's input (read) and output (write)
  tree streams.
- **tnm** — "TheNtupleMaker" ROOT analysis helpers, copied into generated
  packages.
- **CRAB** — CMS grid job-submission tool; the ntuples here are typically CRAB
  output (`slimmedNtuple_*.root`).
