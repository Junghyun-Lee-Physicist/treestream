# Developer Guidelines — treestream

> **Purpose:** the treestream-specific contributor rules and doc map (the project overlay).
> **Audience:** anyone (human or AI) editing this repo. **Status:** living. **Updated:** 2026-06-27.
> **Contract:** the generic, project-agnostic documentation rules are in
> [`DOCUMENTATION_GUIDELINE.en.md`](DOCUMENTATION_GUIDELINE.en.md) (authoritative; Korean mirror
> [`DOCUMENTATION_GUIDELINE.ko.md`](DOCUMENTATION_GUIDELINE.ko.md)) — **read it first.**
> **Related:** [README.md](README.md), [design.md](design.md), [decisions.md](decisions.md), [STATUS.md](STATUS.md).

This file does **not** restate the generic contract; it is the **treestream layer** on
top of it — the project's doc map, the project-specific rules (Rules 0–6), and the
pre-commit checks. Where this file and the contract overlap, the contract wins; this
file only adds treestream specifics.

## The doc set (where each thing lives, mapped to the contract's types)

| File | Job | Type (contract §3) |
|---|---|---|
| [`DOCUMENTATION_GUIDELINE.en.md`](DOCUMENTATION_GUIDELINE.en.md) / [`.ko.md`](DOCUMENTATION_GUIDELINE.ko.md) | the generic documentation contract | — |
| [`README.md`](README.md) | index / where to start | Index |
| `DeveloperGuideline.md` (this) | treestream contributor rules + doc map | Contributor rules |
| [`design.md`](design.md) | how it works **and** why (model + pipeline + reference) | Purpose & rationale + Architecture + Reference — combined per [contract §7](DOCUMENTATION_GUIDELINE.en.md) (narrow scope) |
| [`decisions.md`](decisions.md) | why each choice; what was rejected; status | Decision log |
| [`STATUS.md`](STATUS.md) | where we are right now | Status / progress |
| [`troubleshooting.md`](troubleshooting.md) | symptom → cause → fix; validation methods | Troubleshooting / incidents |
| [`CHANGELOG.md`](CHANGELOG.md) | what changed, when (single canonical log) | Changelog |
| [`roadmap.md`](roadmap.md) | what's next | forward-looking plans |

---

## Rule 0 — Read `docs/` before you change anything

Before your first edit in a session, read the files in
[`docs/`](README.md). The bugs documented here are subtle and recur (zombie
input branches, ghost zero-valued objects, count mismatches that silently drop
branches, `#`-comment parsing). Reading first is cheaper than rediscovering
them. Order: [`README.md`](README.md) → this file → [`design.md`](design.md) →
[`troubleshooting.md`](troubleshooting.md).

## Rule 1 — The top-level `README.md` describes how to **run**

`../README.md` is for setup, installation, the workflow commands, and concrete
usage. Everything explanatory — internals, the data model, incident history,
design rationale — belongs in `docs/`, with at most a one-line pointer from the
README.

> **Resolved (2026-06-27, [D10](decisions.md#d10--slim-the-top-level-readmemd-into-docs)):** the top-level `../README.md` was rewritten (Korean) as quick-commands + brief concepts + pointers; the explanatory depth (Super-Set, init/ghost flow, memory, design-vs-master) now lives in [`design.md`](design.md) / [`CHANGELOG.md`](CHANGELOG.md). If README and a `docs/` file ever disagree, **`docs/` is authoritative** for internals; the README is authoritative for run commands.

## Rule 2 — Every code change gets a CHANGELOG entry

When you change code, add an entry to [`CHANGELOG.md`](CHANGELOG.md) under
**[Unreleased]** recording:

- **what** changed (file / function),
- **how** it changed (the concrete edit), and
- **why** — the problem it fixes *or* the purpose it serves.

Bad: *"updated mkanalyzer."* Good: *"`mkanalyzer.py` setb generation — wrapped
`select()` in `if (input->present(...))` so a Super-Set `variables.txt` does
not abort on branches absent from a given file."*

`CHANGELOG.md` is the **single canonical** record of what changed and when. (An
older `RELEASE_NOTES` file was removed to avoid maintaining two logs that drift
apart.) At release time, curate the `[Unreleased]` items into a version block in
the same file.

## Rule 3 — Every problem gets a troubleshooting entry

When you hit a bug, crash, confusing log, or build/CRAB failure, add an entry to
[`troubleshooting.md`](troubleshooting.md) Part A using the template:

- **Symptom** — what you observed.
- **Signature** — the exact error text / log snippet (paste it verbatim).
- **Root cause** — why it happened.
- **Fix** — the change that resolved it (link the commit if there is one).
- **Validated by** — how you confirmed the fix.

Do this *even if the fix was quick.* Several entries in Part A are one-line
fixes (a shebang, a missing `#` skip) that each cost real time precisely because
they were undocumented.

## Rule 4 — Record in the doc that matches the situation

| What you did / found | Where it goes |
|---|---|
| Any code change | [`CHANGELOG.md`](CHANGELOG.md) (always) |
| A bug / crash / failure + its fix | [`troubleshooting.md`](troubleshooting.md) Part A |
| A new validation method, or a limit of one | [`troubleshooting.md`](troubleshooting.md) Part B |
| Changed how it works, or a data-model / design decision (model, pipeline, generated `eventBuffer`, Super-Set) | [`design.md`](design.md) |
| A new or changed run command / CLI surface | [`../README.md`](../README.md) **and** CHANGELOG |
| A new planned feature or design intent | [`roadmap.md`](roadmap.md) |
| A decision made / rejected / superseded, with rationale | [`decisions.md`](decisions.md) |
| The current state, next steps, or an open question | [`STATUS.md`](STATUS.md) |

If a change touches several, update all of them — they cross-link, so stale
references are easy to catch with the link check below.

## Rule 5 — Keep generators, the core, and generated output separate

- **Generators** (`bin/mkvariables.py`, `bin/mkanalyzer.py`,
  `bin/mkeventbuffer.py`, `bin/mklist.py`) produce text and C++; treat them as
  the product.
- **Core** (`src/`, `include/`, `tnm/`) is the C++ library that generated
  packages compile against and that the generators copy in.
- **Generated packages** (the `<name>/` directory `mkanalyzer.py` emits) are
  **output, not source.** Do not hand-edit a generated `eventBuffer.h` and
  commit it as if it were the template — fix the template inside
  `mkanalyzer.py` (`TEMPLATE_H` / the `setb`/`init` builders) and regenerate.
  `eventBuffer.h` is rewritten on every run; `<name>.cc` is written only if
  absent (or with the `f` force suffix), so user analysis code is preserved.

## Rule 6 — `mkvariables.py` and `mkanalyzer.py` share one contract: the `variables.txt` format

The record format is the interface between the two tools and **must stay in
sync** (see [`design.md` §8](design.md#8-the-variablestxt-format-contract)):

```
type / branch[/sub] / variable-name / maxcount [leafcounter]
```

If you change how `mkvariables.py` *writes* a record (fields, separators,
comment markers, `--merge` annotations), update how `mkanalyzer.py` *parses* it
in the same commit — and vice versa. Two real bugs came from breaking this
silently: `#`-comment lines the parser didn't skip, and branch names containing
`/` the parser mis-split (troubleshooting §A3, §A4).

---

## Before you commit (quick self-check)

- [ ] CHANGELOG entry added (Rule 2).
- [ ] Any new bug/fix recorded in troubleshooting (Rule 3).
- [ ] Relevant doc(s) updated (Rule 4).
- [ ] Generators still compile: `python3 -m py_compile bin/*.py makingCommand.py`.
- [ ] A round-trip still works: `mkvariables.py <a.root> Events` then
      `mkanalyzer.py testgen` produces a `testgen/` that `make`s cleanly (for
      `--merge` changes, repeat with two files and confirm the Branch Access
      Report at startup).
- [ ] Internal doc links resolve. A quick checker:

  ```bash
  python3 - <<'PY'
  import re, pathlib
  bad = 0
  for md in pathlib.Path("docs").rglob("*.md"):
      for m in re.finditer(r"\]\(([^)]+)\)", md.read_text()):
          t = m.group(1).split("#")[0]
          if t and not t.startswith("http") and not (md.parent / t).resolve().exists():
              print(f"BROKEN: [{md}] -> {m.group(1)}"); bad += 1
  print("OK" if not bad else f"{bad} broken link(s)")
  PY
  ```

---

## Generic guidance lives in the contract

How to apply this documentation structure to *other* projects — the portable
spine, the merge/split test, scaling up and down, the doc-type menu, and the
AI-thread rationale — is the job of the contract,
[`DOCUMENTATION_GUIDELINE.en.md`](DOCUMENTATION_GUIDELINE.en.md). This file
deliberately does not duplicate it ([decisions.md D9](decisions.md#d9--adopt-documentation_guidelineenmd-as-the-documentation-contract)).
