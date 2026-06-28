# Status

> **Purpose:** the single "where are we right now" snapshot — current state, what's next, open questions.
> **Audience:** any contributor (human or AI) starting a session — read this and the index first.
> **Status:** living; update at the end of every session. **Updated:** 2026-06-27.
> **Contract:** [DOCUMENTATION_GUIDELINE.en.md](DOCUMENTATION_GUIDELINE.en.md) §3, §5. **Related:** [decisions.md](decisions.md) (why), [roadmap.md](roadmap.md) (what's next), [CHANGELOG.md](CHANGELOG.md) (what changed).

**Bottom line:** this is branch **`forTTHH_v1`**, a fork of treestream where ttHH-specific work will live. The base tooling (Super-Set generation, eventBuffer-only generation, deterministic output) is **stable and verified**. The ttHH-specific content this branch will add is **not yet defined** — see [D12, OPEN](decisions.md#d12--what-fortthh_v1-adds-beyond-base-treestream).

---

## Branch context

- **Branch:** `forTTHH_v1` (on a personal fork of treestream).
- **Base:** this treestream fork — standalone (no CMSSW), Python 3, ROOT 6, with the Super-Set / missing-branch-safe workflow. See [design.md](design.md).
- The base branch's last shipped state is `3.0.0`; the documentation-and-tooling work below is staged in [CHANGELOG `[Unreleased]`](CHANGELOG.md#unreleased).

## What works now (verified 2026-06-27)

- **`mkvariables.py`** — single-file and `--merge` (Super-Set) modes. DECIDED/stable (D2, D4).
- **`mkanalyzer.py`** — generates the analyzer package; output is **deterministic** (D8). DECIDED/stable.
- **`mkeventbuffer.py`** — emits **only** `eventBuffer.h`, byte-identical to a full `mkanalyzer.py` run (md5-verified on `variables_v18.txt`). DECIDED/stable (D7).
- **Local validation** — library self-tests and an end-to-end smoke test on the bundled `test/fatjet.root` (tree `Delphes`) are documented in [`../README.md` → Local testing](../README.md).

## In progress / next

| Item | Status | Where |
|---|---|---|
| Fail-fast on required branches | PROPOSED | roadmap §2 |
| Debug / value-level validation mode (branches `EventBufferDebug`, `codex/...` exist) | PROPOSED | roadmap §3 |
| Safe-access interface layer | PROPOSED (lower) | roadmap §4 |
| Single source of truth for the `variables.txt` format | PROPOSED | [D11](decisions.md#d11--single-source-of-truth-for-the-variablestxt-format) |

See [`roadmap.md`](roadmap.md) for the goal/sketch/acceptance of each.

## Open questions

- **`forTTHH_v1` scope** — what ttHH-specific content this branch adds beyond base treestream (a committed Super-Set `variables.txt` for the ttHH samples? branch keep/drop presets? analysis configs?) is **not decided**. Do not assume; the maintainer must specify. Tracked as [D12, OPEN](decisions.md#d12--what-fortthh_v1-adds-beyond-base-treestream).

## How to check the current state yourself

```bash
source setup.sh
python3 -m py_compile bin/*.py makingCommand.py     # generators compile
# end-to-end smoke test: see ../README.md "Local testing"
# docs link check: see DeveloperGuideline.md "Before you commit"
```
