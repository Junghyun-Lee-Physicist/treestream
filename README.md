treestream
=======
A simple interface to Root files containing simple trees, such as the
CMS NanoAOD or the Root files created using __Delphes__. The enviroment variable __TREESTREAM_PREFIX__ should be set to the directory in which you wish to install treestream, that is, to the directory containing the bin, lib, and include directories. If you do not use an environment management system such as miniconda3 (a slim version of Anaconda), we suggest
that you create a directory called __external__ in your home directory,
as shown below to contain all external packages, and install
treestream in that directory.  You should clone (download) external packages to __external__, but do not try to install treestream within the treestream directory itself!

INSTALLATION
```bash
	cd
	mkdir -p external/bin
	mkdir -p external/lib
	mkdir -p external/include
	mkdir -p external/share

	cd $HOME/external
	git https://github.com/hbprosper/treestream.git
	cd treastream
	export TREESTREAM_PREFIX=$HOME/external (or $CONDA_PREFIX if you use miniconda3)
	make
	make install
```
TEST
```bash
	cd test
	./testtreestream
	./testdelphes
	./testvector
```
There is also a __jupyter__ notebook version of the test program.

ANALYZER UTILITIES

1. __mkvariables.py__  reads a Root file and creates the file __variables.txt__
containing a description of (by default) the first tree it finds.

2. __mkanalyzer.py__ reads __variables.txt__ and creates the skeleton of an C++ 
and Python analyzer program for the Root tree.


## Overall Workflow

step1) source setup.sh
step2) mkvariables.py --> output : variables.txt

```bash
# mkvariables.py [ input ntuple ] [ tree name ]
$ mkvariables.py data.root Events
```

step3) mkanalyzer.py --> output : analyzer directories including eventBuffer.h, analyzer.cc, etc..
step4) compile --> output : library and execution files
step5) run analyzer



## 🛠️ Detailed Usage Guide
The standard workflow for generating a safe Analyzer using this package is as follows:

### 1. Set environment variable
```bash
source setup.sh
// or source setup.csh
```

### 2. mkvariables.py

**mkvariables.py** scans a ROOT Ntuple to generate a schema file (`variables.txt`), which is required by `mkanalyzer.py` to auto-generate C++ analyzer code. It automatically detects branch types (including vectors), strips C++ namespaces for cleaner variable names, and identifies leaf counters, while skipping complex objects like `TLorentzVector`.

#### Usage
```bash
# Syntax
python3 bin/mkvariables.py [options] <filename.root> [TreeName1 TreeName2 ...]
```

# Examples
```bash
python3 bin/mkvariables.py input.root           # Scan default tree
python3 bin/mkvariables.py input.root Events    # Scan 'Events' tree only
python3 bin/mkvariables.py --usetree data.root  # Prefix variables with tree name
```

Output Format (**variables.txt**)
The output defines the mapping for the analyzer struct. Format: `<Type>/<BranchName>/<VariableName>/<MaxCount> [LeafCounter]`

Example:
```
vector<float>/patElectrons.pt/Electron_pt/50 npatElectrons
int/eventInfo.run/RunNumber/1
```

---

# mkanalyzer

**mkanalyzer** is a Python 3 tool that auto-generates a robust C++ analysis framework based on a ROOT Ntuple schema (`variables.txt`).

## Features
- **Auto-Struct Generation:** Groups variables (e.g., `Electron_pt`, `Electron_eta`) into clean C++ structs (`ev.Electron[i].pt`).
- **Data/MC Compatibility:** Safely handles missing branches (e.g., using Data files that lack MC-only variables) without crashing, by defaulting missing values to 0.
- **Debug Mode:** Generated code includes built-in verbose logging to trace variable loading and struct filling.

## Quick Start
1. Generate the schema:
    ```bash
    ./mkvariables.py samples.root > variables.txt
    ```

2. Generate the analyzer:

    ```Bash
    ./mkanalyzer.py MyAnalyzer variables.txt
    ```

3. Build and Run:

    ```Bash
    cd MyAnalyzer
    make
    ./MyAnalyzer filelist.txt
    ```

