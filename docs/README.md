# treestream — Developer Documentation

> **Purpose:** index/map of `docs/` — where to start and which doc answers what.
> **Audience:** every contributor (human or AI) on this repo; start here. **Status:** living index. **Updated:** 2026-06-27.
> **Contract:** [DOCUMENTATION_GUIDELINE.en.md](DOCUMENTATION_GUIDELINE.en.md) (authoritative) / [DOCUMENTATION_GUIDELINE.ko.md](DOCUMENTATION_GUIDELINE.ko.md) (mirror). **Related:** every doc below.

**Branch:** this is `forTTHH_v1`, a ttHH-focused fork of treestream. Where things stand right now — and what `forTTHH_v1` will add beyond base treestream — is in [`STATUS.md`](STATUS.md).

This is the index for everything explanatory about this fork of
[treestream](https://github.com/hbprosper/treestream). The top-level
[`../README.md`](../README.md) tells you how to **run** the tools; the files
here tell you how they **work**, why they were changed, what broke along the
way, and what is planned next.

The goal: another developer — or a fresh AI thread with no prior context — can
open `docs/`, reconstruct accurate project state, and leave it accurate for the
next agent. The rules that make that work are the contract,
[`DOCUMENTATION_GUIDELINE.en.md`](DOCUMENTATION_GUIDELINE.en.md) — **read it first.**

---

## What this project is (one paragraph)

`treestream` is a thin C++/Python layer over ROOT `TTree` I/O plus a **code
generator**: you point `mkvariables.py` at one or more NanoAOD ntuples, it
writes a `variables.txt` describing every branch, and `mkanalyzer.py` turns
that into a ready-to-compile C++ analyzer whose `eventBuffer` binds each branch
to a C++ variable. This fork builds **standalone (no CMSSW)**, on **Python 3**
and **modern ROOT 6**, and adds a **Super-Set / missing-branch-safe** workflow
so one generated analyzer runs over heterogeneous Data/MC/period samples whose
branch sets differ.

---

## The doc set (what each file answers)

| File | The question it answers | Type (contract §3) |
|---|---|---|
| [`DOCUMENTATION_GUIDELINE.en.md`](DOCUMENTATION_GUIDELINE.en.md) / [`.ko.md`](DOCUMENTATION_GUIDELINE.ko.md) | *What are the documentation rules?* (the contract) | — |
| [`README.md`](README.md) (this) | *Where do I start? What's here?* | Index |
| [`DeveloperGuideline.md`](DeveloperGuideline.md) | *How do I change things safely?* (treestream overlay on the contract) | Contributor rules |
| [`design.md`](design.md) | *How does it work, and why?* | Purpose + Architecture + Reference |
| [`decisions.md`](decisions.md) | *Why this choice? what was rejected? still in force?* | Decision log |
| [`STATUS.md`](STATUS.md) | *Where are we right now?* | Status / progress |
| [`troubleshooting.md`](troubleshooting.md) | *It broke — cause and fix?* | Troubleshooting |
| [`CHANGELOG.md`](CHANGELOG.md) | *What changed, and when?* | Changelog |
| [`roadmap.md`](roadmap.md) | *What's next?* | Plans |

**Reading order for a newcomer:** this index → [`DeveloperGuideline.md`](DeveloperGuideline.md) (rules; it points to the contract) → [`design.md`](design.md) (understand the tool) → [`STATUS.md`](STATUS.md) (where we are) → others as needed.

---

## Current priorities

Status labels per the contract (**DECIDED / PROPOSED / OPEN / DEPRECATED**). The live snapshot is [`STATUS.md`](STATUS.md); the rationale behind each choice is in [`decisions.md`](decisions.md).

| # | Topic | Status | Where |
|---|---|---|---|
| 1 | **Ntuple variable initialization** — scalars default to `0`; vectors not pre-filled (no "ghost objects"); bounds-checked struct fill | DECIDED | [design §5](design.md#5-initialization--the-ghost-object-problem), [troubleshooting A5/A7](troubleshooting.md) |
| 2 | **Branch-set differences (Data/MC, sample-to-sample)** — `variables.txt` is the **union** via `mkvariables.py --merge` (COMMON/ONLY/PARTIAL) | DECIDED | [design §3](design.md#3-the-super-set-strategy) |
| 3 | **eventBuffer-only generation** — emit just `eventBuffer.h` without the skeleton | DECIDED (`bin/mkeventbuffer.py`) | [roadmap §1](roadmap.md#1-eventbuffer-only-generation-mode--highest-priority), [decisions D7](decisions.md) |

---

## Map of the live tree (what the docs describe)

```
treestream/
├── bin/
│   ├── mkvariables.py    # scan ntuple(s) -> variables.txt   (has --merge)
│   ├── mkanalyzer.py     # variables.txt -> analyzer package (eventBuffer + .cc)
│   ├── mkeventbuffer.py  # variables.txt|.root -> ONLY eventBuffer.h (identical)
│   └── mklist.py         # quick branch listing of one ntuple
├── src/  include/  lib/ # treestream core C++ library + built .so/.pcm
├── tnm/                 # ROOT analysis helpers copied into generated packages
├── makingCommand.py     # convenience: build a --merge command from a sample dir
├── variables_v18.txt    # a generated Super-Set variables.txt (v18 samples)
├── README.md            # how to run (top-level)
└── docs/                # <- you are here
```

> Change history lives only in [`CHANGELOG.md`](CHANGELOG.md) (there is no separate
> `RELEASE_NOTES`). The current state is in [`STATUS.md`](STATUS.md); the "why"
> behind choices is in [`decisions.md`](decisions.md).
