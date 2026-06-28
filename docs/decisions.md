# Decision Log

> **Purpose:** why each non-obvious choice was made, what was rejected, and whether it still holds.
> **Audience:** any contributor (human or AI) about to change a load-bearing behavior — check here first.
> **Status:** living, append-only. **Updated:** 2026-06-27.
> **Contract:** [DOCUMENTATION_GUIDELINE.en.md](DOCUMENTATION_GUIDELINE.en.md) §3, §5. **Related:** [design.md](design.md), [troubleshooting.md](troubleshooting.md), [CHANGELOG.md](CHANGELOG.md), [roadmap.md](roadmap.md).

Status vocabulary (per the contract): **DECIDED** (in force) · **PROPOSED** (suggested, not settled) · **OPEN** (unresolved/unknown) · **DEPRECATED** (was decided, now retired). Never silently reopen a DECIDED item or treat a PROPOSED item as settled — change its status explicitly and say why.

Each entry is dated and links to where it is implemented/explained. Decisions are append-only; to reverse one, add a new entry that supersedes it and flip the old one to DEPRECATED.

---

## D1 — No vector zero-initialization (ghost-object fix)
**Status:** DECIDED · 2025-12-18
- **Decision:** the generated `eventBuffer` does **not** pre-fill collection vectors; scalars are initialized to `0`.
- **Rationale:** a pre-sized zero-filled vector creates phantom objects, and for a *missing* branch it stays full of `count` zeros, so analysis loops iterate over ghost particles.
- **Rejected:** keep the original `std::vector<T>(count,0)` initialization → ghost objects.
- **Where:** [design.md §5](design.md#5-initialization--the-ghost-object-problem), [troubleshooting A5](troubleshooting.md#a5-ghost-objects--loops-iterate-over-fake-zero-valued-particles---priority-1).

## D2 — Super-Set + runtime `present()` guard
**Status:** DECIDED · 2026-03-15
- **Decision:** `variables.txt` is the union of branches across files (`mkvariables.py --merge`); the generated `eventBuffer` guards every `select()` with `present()`.
- **Rationale:** one analyzer must run over Data/MC/period samples whose branch sets differ.
- **Rejected:** per-sample `variables_*.txt` + manual `combineBranch.py` (see D-DEP1).
- **Where:** [design.md §3](design.md#3-the-super-set-strategy), [§4](design.md#4-runtime-presence--the-generated-eventbuffer).

## D3 — Direct `select()` on a missing branch is fatal (was a warning)
**Status:** DECIDED · 2025-12-18
- **Decision:** `src/treestream.cc` calls `fatal()` for a missing branch on a *direct* `select()`.
- **Rationale:** hand-written typos should fail loudly; the generated buffer always guards with `present()`, so it never trips this.
- **Rejected:** keep `warning()` (silently reads nothing → garbage).
- **Where:** [design.md §6](design.md#6-two-layer-missing-branch-safety), [troubleshooting A8](troubleshooting.md#a8-direct-select-on-a-missing-branch--when-it-should-be-fatal).

## D4 — `--merge` count unification
**Status:** DECIDED · 2026-03-15
- **Decision:** raise every branch sharing a leaf counter to the max count seen for that counter before writing `variables.txt`.
- **Rationale:** `mkanalyzer.py` requires all fields of one struct to share a count; otherwise a smaller-count sample-specific field is dropped from the struct.
- **Where:** [design.md §3](design.md#3-the-super-set-strategy), [troubleshooting A6](troubleshooting.md#a6---merge-silently-drops-sample-specific-branches-from-structs).

## D5 — Merge `concepts.md` + `architecture.md` into `design.md`
**Status:** DECIDED · 2026-06-27
- **Decision:** one `design.md` instead of separate why/how docs.
- **Rationale:** per the contract [§7](DOCUMENTATION_GUIDELINE.en.md), for a tool this small the why and how are read together and change together; keeping them apart duplicated the Super-Set / init / present-select material and drifted.
- **Rejected (for now):** separate `concepts.md` + `architecture.md` (the contract's default for larger projects). Revisit if the codebase grows past a single small tool.
- **Where:** [design.md](design.md) header.

## D6 — Remove `RELEASE_NOTES`; `CHANGELOG.md` is the single canonical log
**Status:** DECIDED · 2026-06-27
- **Decision:** delete the top-level `RELEASE_NOTES`; fold its upstream history into `CHANGELOG.md`.
- **Rationale:** two release logs drift apart; contract §4 "one fact, one place".
- **Where:** [CHANGELOG.md](CHANGELOG.md).

## D7 — eventBuffer-only as a separate wrapper, not a `--buffer-only` flag
**Status:** DECIDED · 2026-06-27
- **Decision:** add `bin/mkeventbuffer.py`, which drives the real `mkvariables.py` + `mkanalyzer.py` and keeps only `eventBuffer.h`.
- **Rationale:** output is byte-identical to `mkanalyzer.py` **by construction** (it *is* the generator), with no edits to the ~1500-line generator's hot path.
- **Rejected:** a `--buffer-only` flag inside `mkanalyzer.py` (in-place change; risk of divergence and of touching the generator).
- **Where:** [roadmap §1](roadmap.md#1-eventbuffer-only-generation-mode--highest-priority), [design.md §7](design.md#7-the-scripts--cli).

## D8 — Deterministic leaf-counter ordering (`sorted()`)
**Status:** DECIDED · 2026-06-27
- **Decision:** iterate `sorted(counters)` in `mkanalyzer.py` when emitting `int n<Counter>;`.
- **Rationale:** iterating a `set` is `PYTHONHASHSEED`-dependent, so `eventBuffer.h` differed run-to-run and broke the byte-identical guarantee (D7).
- **Where:** [troubleshooting A10](troubleshooting.md#a10-non-deterministic-eventbufferh-leaf-counter-ordering).

## D9 — Adopt `DOCUMENTATION_GUIDELINE.en.md` as the documentation contract
**Status:** DECIDED · 2026-06-27
- **Decision:** the en/ko guideline is the authoritative, project-agnostic contract; `DeveloperGuideline.md` becomes the treestream-specific overlay that references it.
- **Rationale:** one canonical generic contract; the generic "reusing this structure" framework previously embedded in `DeveloperGuideline.md` duplicated it (one fact, one place).
- **Where:** [DOCUMENTATION_GUIDELINE.en.md](DOCUMENTATION_GUIDELINE.en.md), [DeveloperGuideline.md](DeveloperGuideline.md).

---

## Open / proposed

## D10 — Slim the top-level `../README.md` into `docs/`
**Status:** DECIDED · 2026-06-27
- **Context:** the top-level README carried explanatory material; the contract (and DeveloperGuideline Rule 1) want it to be run-commands only, with explanation in `docs/`.
- **Outcome:** the README was rewritten in **Korean** as quick-commands-first (variables.txt → eventBuffer-only *or* full skeleton) + brief concepts + pointers; the depth (Super-Set, init/ghost flow, memory, design-vs-master) lives in [`design.md`](design.md) / [`CHANGELOG.md`](CHANGELOG.md). `Command.txt` was removed and its `--merge` command inlined into the README with its Data+MC rationale.
- **Where:** [`../README.md`](../README.md), [roadmap Housekeeping](roadmap.md#housekeeping--debt).

## D11 — Single source of truth for the `variables.txt` format
**Status:** PROPOSED · 2026-06-27
- **Context:** `mkvariables.py` (writer) and `mkanalyzer.py` (reader) duplicate the record-format knowledge; a shared spec/parser would stop drift (root cause of troubleshooting A3/A4).
- **Where:** [roadmap Housekeeping](roadmap.md#housekeeping--debt), [DeveloperGuideline Rule 6](DeveloperGuideline.md#rule-6--mkvariablespy-and-mkanalyzerpy-share-one-contract-the-variablestxt-format).

## D12 — What `forTTHH_v1` adds beyond base treestream
**Status:** OPEN · 2026-06-27
- **Context:** this branch is a ttHH-focused fork. The ttHH-specific content it will carry (e.g. a committed Super-Set `variables.txt` for the ttHH samples, branch keep/drop presets, analysis configs) is **not yet defined**. Do not assume; the maintainer must specify.
- **Where:** [STATUS.md](STATUS.md).

---

## Deprecated

## D-DEP1 — Per-sample `variables_*.txt` + `combineBranch.py`
**Status:** DEPRECATED · 2026-03-15
- **Was:** branches handled per sample, combined manually.
- **Superseded by:** D2 (`--merge` Super-Set). Files removed in 3.0.0 (`variables_Combine_with_Bperiod.txt` kept only as reference).
- **Where:** [CHANGELOG 3.0.0 Removed](CHANGELOG.md).
