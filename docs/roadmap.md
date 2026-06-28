# Roadmap & To-Do

> **Purpose:** planned and proposed work, with goal/sketch/acceptance for each.
> **Audience:** anyone (human or AI) picking up the next task. **Status:** living. **Updated:** 2026-06-27.
> **Contract:** [DOCUMENTATION_GUIDELINE.en.md](DOCUMENTATION_GUIDELINE.en.md). **Related:** [STATUS.md](STATUS.md) (current state), [decisions.md](decisions.md) (why), [CHANGELOG.md](CHANGELOG.md) (done). Status labels per contract: **DECIDED / PROPOSED / OPEN / DEPRECATED**.

Planned work, in rough priority order. Each item states the **goal**, a
**sketch** of the approach, and **acceptance** criteria, so another developer or
AI thread can pick it up. When you start one, open an `[Unreleased]` entry in
[`CHANGELOG.md`](CHANGELOG.md); when you hit a bug doing it, log it in
[`troubleshooting.md`](troubleshooting.md).

Some of these already have exploratory git branches (e.g. `EventBufferDebug`,
`codex/add-debug-prints-for-eventbuffer-validation`,
`codex/analyze-and-update-mkanalyzer.py`) — check them before starting.

---

## 1. eventBuffer-only generation mode  (highest priority)

> **DECIDED — done (2026-06-27).** Implemented as `bin/mkeventbuffer.py`. It drives the real
> `mkvariables.py` + `mkanalyzer.py` and keeps only `include/eventBuffer.h`, so
> output is byte-identical to a full `mkanalyzer.py` run (verified by `diff` /
> `md5sum`). Meeting the byte-identical criterion required fixing a latent
> non-determinism in `mkanalyzer.py` first (troubleshooting §A10). The original
> sketch (a `--buffer-only` flag *inside* `mkanalyzer.py`) was dropped in favor
> of a separate wrapper, to avoid touching the generator's hot path and to keep
> identity guaranteed by construction. The design notes below are kept as the
> record of why.

**Goal.** Let `mkanalyzer.py` emit *only* `include/eventBuffer.h` — the data
structure — without the full `MyAnalyzer` scaffolding (`<name>.cc`, `Makefile`,
`README`, `linkdef.h`, and the copied `treestream`/`tnm`). The full package is
unnecessary overhead when you only want the generated buffer to drop into an
existing project (another framework, a notebook, NtupleForge, etc.).

**Why.** Today `mkanalyzer.py <name>` always materializes a whole compile-ready
directory. For "I just need the typed buffer for these branches" that produces a
tree of files you immediately delete. The buffer is the reusable artifact; the
rest is a starter template.

**Sketch.**
- Add a flag, e.g. `--buffer-only` (or `-b`). Argument parsing already
  special-cases the `name/f` force suffix in `main()`; add the flag alongside it.
- In the file-writing block (`mkanalyzer.py` ~L1413–1505), when the flag is set:
  still build all the code-string lists and **always** write
  `include/eventBuffer.h` (that path already runs every time), but **skip** the
  copies of `treestream.{h,cc}` / `tnm.*`, the `Makefile`, `<name>.cc`,
  `README`, and `linkdef.h`.
- Decide the output location: either still `<name>/include/eventBuffer.h`, or a
  flat `eventBuffer.h` in the CWD / a `-o` path. A `-o`/flat option is friendlier
  for embedding.
- `eventBuffer.h` `#include "treestream.h"`, so document that buffer-only mode
  assumes the consumer already provides `treestream.h` on its include path
  (don't silently emit a header that won't compile in isolation).

**Acceptance.**
- `mkanalyzer.py mybuf --buffer-only variables.txt` writes only the header (no
  stray package dir / files).
- The emitted header is byte-identical to the `eventBuffer.h` from a full run on
  the same `variables.txt` (the flag must not change generation, only what gets
  written).
- A consuming project that already has `treestream.h` compiles against it.
- CHANGELOG `[Unreleased]` + a usage line in `../README.md`.

---

## 2. Fail-fast on required branches  (safety)

> **Status: PROPOSED** (2026-06-27).

**Goal.** Optionally abort early if a *declared-required* branch is missing,
instead of silently treating it as `0`/empty.

**Why.** Priority-#1 init made missing branches forgiving, which closed the
ghost-object failure but opened a subtler one: a missing scalar (`HLT_*`,
`Flag_*`, a weight) reads as `0`, indistinguishable from a real `0`
([design.md §10](design.md#10-known-limitations)). For a branch the analysis
truly cannot run without, silent-zero is worse than a clean abort. This is
option (A) from the design notes in `mkanalyzer.py`'s header.

**Sketch.** Accept a required-branch list (file or CLI). In the `eventBuffer`
constructor, after the present/select loop, if any required branch landed in
`missingBranches`, print and `exit`/`assert`. Keep it opt-in so the default
Super-Set behavior is unchanged.

**Acceptance.** With a required list, running on a file lacking a required
branch aborts with a clear message naming it; without the list, behavior is
identical to today.

---

## 3. Debug / value-level validation mode  (safety)

> **Status: PROPOSED** (2026-06-27); partial prototypes on branches `EventBufferDebug`, `codex/add-debug-prints-for-eventbuffer-validation`.

**Goal.** Beyond the present/absent **Branch Access Report**, an opt-in mode
that prints read values/sizes for chosen branches/objects on the first N events.

**Why.** Confirms not just that a branch *bound* but that it reads sane
values/lengths — catching e.g. a wrong leaf-counter pairing or a unit/type
surprise. Option (C) from the header notes; partly prototyped on the
`EventBufferDebug` / `codex/add-debug-prints-for-eventbuffer-validation`
branches — fold those in rather than starting fresh.

**Acceptance.** A debug flag prints, for the first few events, the size of each
object vector and a few field values; off by default; no effect on normal runs.

---

## 4. Safe-access interface layer  (design, lower priority)

> **Status: PROPOSED** (2026-06-27), lower priority — sequence after §2–§3.

**Goal.** Reduce direct `_ev->HLT_*` / raw-vector access in analysis code in
favor of small accessor layers (a trigger menu, a weights object) that
centralize presence handling. Option (B) from the header notes.

**Why.** Localizes "is this branch here?" logic so analyzers don't each
re-implement guards, and makes the missing-scalar ambiguity (§2) handleable in
one place. Larger design change — sequence it after 1–3.

---

## Housekeeping / debt

> **Status: PROPOSED** — remaining items tracked in [decisions.md](decisions.md) (D11 variables.txt single-source = PROPOSED). D10 (README slim) is now **DECIDED/done**.

- ~~**Slim `../README.md` into `docs/`.**~~ **Done (2026-06-27, [D10](decisions.md#d10--slim-the-top-level-readmemd-into-docs)):** the top-level README was rewritten (Korean) as quick-commands + brief concepts + pointers; deep material lives in [`design.md`](design.md). `Command.txt` was removed and its `--merge` command inlined into the README with rationale.
- **Single source of truth for the `variables.txt` format.** The writer
  (`mkvariables.py`) and reader (`mkanalyzer.py`) duplicate the format
  knowledge. Consider a tiny shared parser/spec so the
  [contract](DeveloperGuideline.md#rule-6--mkvariablespy-and-mkanalyzerpy-share-one-contract-the-variablestxt-format)
  can't drift (the root cause behind troubleshooting §A3/§A4).
- **Trim committed build artifacts.** `src/*.o`, `lib/*.so`, `lib/*.pcm`,
  `test/*.o` are build outputs; confirm `.gitignore` covers them so they don't
  drift in the repo.
