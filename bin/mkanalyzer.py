#!/usr/bin/env python3
#-----------------------------------------------------------------------------
# Description: Create ntuple analyzer using information supplied in a
#              variables.txt file. (See mkvariables.py).
#
# Created: 06-Mar-2010 Harrison B. Prosper
# Updated: 21-Dec-2025 Junghyun Lee - Python 3 Port, Robust Logic, Debug Mode
#-----------------------------------------------------------------------------
import os, sys, re, posixpath
from time import ctime

#-----------------------------------------------------------------------------
# Configuration & Constants
#-----------------------------------------------------------------------------
VERSION = 'v3.0.0 (Python 3) 21-Dec-2025'
AUTHOR  = 'Junghyun Lee'

# Regex for type extraction
isvector = re.compile(r'(?<!std::)vector')
getvtype = re.compile(r'(?<=vector[<]).*(?=[>])')

def usage():
    sys.exit('''
    Usage:
        mkanalyzer.py <analyzer-name> [variables.txt]
    ''')

def nameonly(s):
    return posixpath.splitext(posixpath.split(s)[1])[0]

def join(left, a, right):
    s = ""
    for x in a:
        s = s + "%s%s%s" % (left, x, right)
    return s

#-----------------------------------------------------------------------------
# Templates
#-----------------------------------------------------------------------------

LINKDEF = \
'''
#include <map>
#include <string>
#include <vector>

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ class outputFile;
#pragma link C++ class commandLine;
#pragma link C++ class itreestream;
#pragma link C++ class otreestream;
#pragma link C++ class eventBuffer;
%(pragma)s
#endif
'''

TEMPLATE_H = \
'''#ifndef EVENTBUFFER_H
#define EVENTBUFFER_H
//----------------------------------------------------------------------------
// File:        eventBuffer.h
// Description: Analyzer header for ntuples created by TheNtupleMaker
// Created:     %(time)s by mkanalyzer.py %(version)s
// Author:      %(author)s
//----------------------------------------------------------------------------
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <cassert>
#include "treestream.h"

// Global debug flag for eventBuffer diagnostics.
// Set true in your analyzer to print branch wiring and initialization details.
extern bool eventBufferDebug;

struct eventBuffer
{
  //--------------------------------------------------------------------------
  // --- Declare variables
  //--------------------------------------------------------------------------
%(vardecl)s

  //--------------------------------------------------------------------------
  // --- Structs can be filled by calling fill(), or individual fill methods
  //--------------------------------------------------------------------------
%(structdecl)s
%(structimpl)s
%(structvec)s
%(structimplall)s

  //--------------------------------------------------------------------------
  // --- Selection Logic
  //--------------------------------------------------------------------------
%(selectimpl)s

  //--------------------------------------------------------------------------
  // Constructor: Read-Only
  //--------------------------------------------------------------------------
  eventBuffer() : input(0), output(0), choose(std::map<std::string, bool>()) {}

  eventBuffer(itreestream& stream, std::string varlist="")
  : input(&stream),
    output(0),
    choose(std::map<std::string, bool>())
  {
    if ( !input->good() ) {
        std::cerr << "** eventBuffer: Stream error!" << std::endl;
        exit(1);
    }
    initBuffers();
    
    // Default: Select all
    bool DEFAULT = (varlist == "");
    %(choose)s
    
    // If specific vars requested, parse varlist
    if ( !DEFAULT ) {
        if(eventBufferDebug) std::cout << "[eventBuffer] Selecting specific branches..." << std::endl;
        std::istringstream sin(varlist);
        while ( sin ) {
            std::string key;
            sin >> key;
            if ( sin ) {
                 // Simple prefix match logic
                 for(auto it = choose.begin(); it != choose.end(); ++it) {
                     if ( it->first.substr(0, key.size()) == key ) {
                         choose[it->first] = true;
                     }
                 }
            }
        }
    }
    // Apply selections
    %(setb)s
  }

  //--------------------------------------------------------------------------
  // Constructor: Write-Only
  //--------------------------------------------------------------------------
  eventBuffer(otreestream& stream)
  : input(0), output(&stream)
  {
    initBuffers();
    %(addb)s
  }

  void initBuffers()
  {
    if(eventBufferDebug) std::cout << "[eventBuffer] initBuffers() called." << std::endl;
%(init)s
  }
      
  void read(int entry)
  {
    if ( !input ) { 
        std::cerr << "** eventBuffer::read - Error: Read-only mode!" << std::endl;
        exit(1);
    }
    input->read(entry);
    
    // Clear selection index map
    for(auto& item : indexmap) item.second.clear();
  }

  int size() { return input ? input->size() : 0; }
  void close() {
      if(input) input->close();
      if(output) output->close();
  }

  // Members
  std::map<std::string, std::vector<int> > indexmap;
  itreestream* input;
  otreestream* output;
  std::map<std::string, bool> choose;
}; 
#endif
'''

TEMPLATE_CC = \
'''//---------------------------------------------------------------------------
// File:        %(name)s.cc
// Description: Analyzer for simple ntuples
// Created:     %(time)s by mkanalyzer.py %(version)s
// Author:      %(author)s
//----------------------------------------------------------------------------
#include "tnm.h"
#include <iostream>

using namespace std;

// Global debug flag for eventBuffer diagnostics.
// Set true to print branch wiring and initialization details.
bool eventBufferDebug = false;

int main(int argc, char** argv)
{

  // Get command line arguments
  commandLine cl(argc, argv);
    
  // Get names of ntuple files
  vector<string> filenames = fileNames(cl.filelist);

  // Create tree reader
  itreestream stream(filenames, "%(treename)s");
  if ( !stream.good() ) error("can't read root input files");

  // Create event buffer
  eventBuffer ev(stream);
  
  int nevents = ev.size();
  cout << "number of events: " << nevents << endl;

  // Output file
  outputFile of(cl.outputfilename);

  // -------------------------------------------------------------------------
  // Loop over events
  // -------------------------------------------------------------------------
  for(int entry=0; entry < nevents; entry++)
    {
      if(entry % 1000 == 0) cout << "Processing entry " << entry << endl;
      
      // Read event
      ev.read(entry);

      // [Example] Fill Objects to use clean structs
      ev.fillObjects();

      // [Debug Check]
      // if (ev.nElectron > 0) cout << "  Electron 0 PT: " << ev.Electron[0].pt << endl;
    }
    
  ev.close();
  of.close();
  return 0;
}
'''

# New Dynamic Makefile
MAKEFILE = \
'''# Build libtreestream.so
# Updated 2025-12-21 Junghyun Lee - Dynamic Compiler/OS Selection

# [USER OPTION] Select Compiler: 'gcc' or 'clang'
# You can override this via command line: make COMPILER_SELECT=clang
COMPILER_SELECT ?= gcc

ifndef ROOTSYS
$(error *** Please set up Root)
endif

# ----------------------------------------------------------------------------
NAME    := treestream
incdir  := include
srcdir  := src
libdir  := lib
bindir  := bin
tmpdir  := tmp

$(shell mkdir -p $(libdir) $(tmpdir))

# Detect OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  OS_SELECT := macos
else
  OS_SELECT := linux
endif

# Compiler Settings
ifeq ($(COMPILER_SELECT),clang)
  CXX := clang++
  LD  := clang++
else
  CXX := g++
  LD  := g++
endif

CPPFLAGS := -I. -I$(incdir) -I$(srcdir) $(shell root-config --cflags)
CXXFLAGS := -O -Wall -fPIC -g -ansi -Wshadow -Wextra

# Linker Flags
LDFLAGS := -g
ifeq ($(OS_SELECT),macos)
  LDFLAGS += -dynamiclib
  LDEXT   := .dylib
else
  LDFLAGS += -shared
  LDEXT   := .so
endif

LDFLAGS += -Wl,-rpath,$(ROOTSYS)/lib
LIBS    := $(shell root-config --libs) -lMinuit -lMathCore

# App Logic
appsrcs   := $(wildcard *.cc)
apps      := $(appsrcs:.cc=)
sharedlib := $(libdir)/libtnm$(LDEXT)

# Source for library
header    := $(incdir)/tnm.h
linkdef   := $(incdir)/linkdef.h
cinthdr   := $(srcdir)/dictionary.h
cintsrc   := $(srcdir)/dictionary.cc
ccsrcs    := $(filter-out $(cintsrc),$(wildcard $(srcdir)/*.cc))
sources   := $(ccsrcs) $(cintsrc)
objects   := $(subst $(srcdir)/,$(tmpdir)/,$(sources:.cc=.o))

ROOT_DICT_GEN := $(shell command -v rootcling >/dev/null 2>&1 && echo rootcling || echo rootcint)

all: $(sharedlib) $(apps)

$(apps): % : $(tmpdir)/%.o $(sharedlib)
\t@echo "=> Linking $@"
\t$(LD) $(LDFLAGS) $< $(LIBS) -L$(libdir) -ltnm -o $@

$(tmpdir)/%.o: %.cc
\t@echo "=> Compiling App $<"
\t$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(sharedlib): $(objects)
\t@echo "=> Linking Shared Lib $@"
\t$(LD) $(LDFLAGS) $(objects) $(LIBS) -o $@

$(tmpdir)/%.o: $(srcdir)/%.cc
\t@echo "=> Compiling Lib $<"
\t$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(cintsrc): $(header) $(linkdef)
\t@echo "=> Generating Dictionary"
\t$(ROOT_DICT_GEN) -f $@ -c -I. -I$(incdir) -I$(ROOTSYS)/include $+
\tmv $(srcdir)/*.pcm $(libdir) 2>/dev/null || true

clean:
\trm -rf $(tmpdir)/* $(libdir)/* $(srcdir)/dictionary* $(apps)
'''

#-----------------------------------------------------------------------------
# Main Logic
#-----------------------------------------------------------------------------
def main():
    print("\n\t[mkanalyzer.py] - Generating Analyzer Code (Debug Mode Enabled)")

    argv = sys.argv[1:]
    argc = len(argv)
    if argc < 1: usage()

    filename = nameonly(argv[0])
    # Handle path in filename
    if '/' in filename:
        filename = filename.split('/')[-1]
    
    varfilename = argv[1] if argc > 1 else "variables.txt"
    if not os.path.exists(varfilename):
        sys.exit(f"Error: Variable file {varfilename} not found.")

    # Macro mode check (simplified logic)
    macroMode = argc > 2

    # Read variables.txt
    with open(varfilename, "r") as f:
        records = [line.strip() for line in f if line.strip()]

    # Parse Tree Name
    treename = ""
    start_idx = 0
    
    # Simple parser for "Tree Events" lines
    for i, rec in enumerate(records):
        parts = rec.split()
        if parts[0].lower() in ["tree", "tree:"]:
            if len(parts) > 1:
                treename += " " + parts[1]
            start_idx = i + 1
        else:
            break
            
    if not treename: treename = "Events" # Default
    treename = treename.strip()
    single_tree = len(treename.split()) == 1

    #-------------------------------------------------------------------------
    # Analyze Structure (Objects vs Scalars)
    #-------------------------------------------------------------------------
    records = records[start_idx:]
    tmpmap = {}
    
    # 1. Identify Struct Candidates (e.g., Electron_pt -> Electron)
    for rec in records:
        parts = rec.split('/')
        if len(parts) < 3: continue
        varname = parts[2]
        
        # Split by '_' to find prefix
        subparts = varname.split('_')
        if len(subparts) > 1:
            key = subparts[0]
            tmpmap[key] = tmpmap.get(key, 0) + 1
            
    # Structs must have >1 variables
    structname = {k: v for k, v in tmpmap.items() if v > 1}

    # 2. Parse all variables
    varmap = {}
    vectormap = {} # Groups variables by Object name
    
    declare     = []
    init        = []
    setb        = []
    addb        = []
    choose      = []
    structdecl  = []
    structimpl  = []
    structvec   = []
    structimplall = []
    selectimpl  = []

    # Helper maps
    varnum = 1
    skipped_str = ""
    
    for index, rec in enumerate(records):
        tns = rec.split('/')
        
        # Robust Parsing
        try:
            rtype = tns[0]
            # Handle "Events/Electron_pt" case
            branchname = "/".join(tns[1:-2]) 
            varname = tns[-2]
            
            last_token = tns[-1]
            if ' ' in last_token:
                count_str, countername = last_token.split()
            else:
                count_str = last_token
                countername = None
            count = int(count_str)
        except Exception as e:
             print(f"[Warning] Skipping malformed line: {rec} ({e})")
             continue

        # Clean types
        rtype = rtype.replace("ulong64", "unsigned long").replace("long64", "long")
        
        # Logic: Object Mapping
        objname = ''
        fldname = ''
        
        t = varname.split('_')
        if len(t) > 1:
            key = t[0]
            if key in structname:
                 objname = key
                 fldname = varname.replace(f"{objname}_", "")
        
        # Store metadata
        varmap[varname] = {'rtype': rtype, 'branch': branchname, 'count': count, 'counter': countername}

        #---------------------------------------------------------------------
        # Logic: Code Generation
        #---------------------------------------------------------------------
        
        # 1. Selection (choose & setb)
        choosename = branchname.split('/')[-1] if single_tree else branchname
        choose.append(f'    choose["{choosename}"] = DEFAULT;')
        setb.append(f'    if ( choose["{choosename}"] ) {{')

        if count == 1:
            # SCALAR
            declare.append(f"    {rtype}\t{varname};")
            # [Fix] Initialize to 0
            init.append(f"    {varname}\t= 0;")
            
            # [Fix] Safe Select
            setb.append(f'      if (eventBufferDebug) std::cout << "[eventBuffer] branch {branchname}: ";')
            setb.append(f'      if (input->present("{branchname}")) {{')
            setb.append(f'        if (eventBufferDebug) std::cout << "present" << std::endl;')
            setb.append(f'        input->select("{branchname}", {varname});')
            setb.append(f'      }} else if (eventBufferDebug) {{')
            setb.append(f'        std::cout << "missing" << std::endl;')
            setb.append(f'      }}')
            
            # Add to output
            addb.append(f'    output->add("{branchname}", {varname});')

        else:
            # VECTOR
            if 'vector' in rtype:
                # Extract C++ type
                real_type = isvector.sub("std::vector", rtype)
                match = getvtype.findall(real_type)
                if not match: 
                    print(f"Error parsing type: {rtype}")
                    sys.exit(1)
                inner_type = match[0]
                
                declare.append(f"    {real_type}\t{varname};")
                
                # [Fix] Do NOT initialize vectors (prevents Ghost Objects)
                
                # [Fix] Resize -> Select -> Clear Pattern
                setb.append(f'      if (eventBufferDebug) std::cout << "[eventBuffer] branch {branchname}: ";')
                setb.append(f'      if (input->present("{branchname}")) {{')
                setb.append(f'        if (eventBufferDebug) std::cout << "present" << std::endl;')
                setb.append(f'        {varname}.resize({count});')
                setb.append(f'        input->select("{branchname}", {varname});')
                setb.append(f'        {varname}.clear();')
                setb.append(f'      }} else if (eventBufferDebug) {{')
                setb.append(f'        std::cout << "missing" << std::endl;')
                setb.append(f'      }}')
                
                # Group into Objects for Structs
                if objname:
                    if fldname[0].isdigit(): fldname = f"f{fldname}" # Handle '3charge' -> 'f3charge'
                    
                    if objname not in vectormap: vectormap[objname] = []
                    vectormap[objname].append({
                        'type': inner_type, 'field': fldname, 
                        'var': varname, 'count': count, 'counter': countername
                    })

                # Add to output
                addb.append(f'    output->add("{branchname}", {varname});')

        setb.append('    }')

    #-------------------------------------------------------------------------
    # Struct Generation (The Critical Part)
    #-------------------------------------------------------------------------
    
    # Setup Leaf Counters for Output
    counters = set()
    for v in varmap.values():
        if v['counter']: counters.add(v['counter'])
    
    for c in sorted(counters):
        declare.append(f"    int\t{c};")
        # Initialize scalar counters
        init.append(f"    {c}\t= 0;") 
        addb.append(f'    output->add("{c}", {c});')
        # Logic for reading counters is implicitly handled by treestream if scalar

    # Generate Structs
    structimplall.append('  void fillObjects()')
    structimplall.append('  {')
    structimplall.append('    if(eventBufferDebug) std::cout << "[eventBuffer] fillObjects() called." << std::endl;')

    sorted_objects = sorted(vectormap.keys())
    
    for obj in sorted_objects:
        fields = vectormap[obj]
        
        # 1. Define Struct
        structdecl.append(f'  struct {obj}_s')
        structdecl.append('  {')
        for f in fields:
            structdecl.append(f"    {f['type']}\t{f['field']};")
        
        # Add ostream operator for debug
        structdecl.append('    friend std::ostream& operator<<(std::ostream& os, const ' + obj + '_s& v) {')
        structdecl.append(f'      os << "{obj}"; return os;')
        structdecl.append('    }')
        structdecl.append('  };') # End Struct
        
        # 2. Define Vector of Structs
        structvec.append(f"  std::vector<eventBuffer::{obj}_s> {obj};")
        
        # 3. Define fill Function
        func_name = f"fill{obj}s"
        structimplall.append(f"    {func_name}();")
        
        structimpl.append(f"  void {func_name}()")
        structimpl.append("  {")
        
        # [CRITICAL FIX] Robust Sizing Logic
        # Try to find a counter variable first
        counter_var = None
        for f in fields:
            if f['counter']:
                counter_var = f['counter']
                break
        
        structimpl.append(f'    size_t count = 0;')
        
        if counter_var:
            # Scenario A: We have a trusted leaf counter (e.g., nElectron)
            structimpl.append(f'    count = {counter_var};')
            structimpl.append(f'    if(eventBufferDebug && count > 0) std::cout << "  [eventBuffer] {obj} count via {counter_var}: " << count << std::endl;')
        else:
             # Scenario B: No counter, scan vectors for max size
             structimpl.append('    // No counter found, scanning vectors for max size')
             for f in fields:
                 structimpl.append(f'    if({f["var"]}.size() > count) count = {f["var"]}.size();')
             structimpl.append(f'    if(eventBufferDebug && count > 0) std::cout << "  [eventBuffer] {obj} count inferred: " << count << std::endl;')

        structimpl.append(f"    {obj}.resize(count);")
        structimpl.append(f"    for(size_t i=0; i < count; ++i)")
        structimpl.append("    {")
        
        # [CRITICAL FIX] Safe Filling (Ternary Check)
        for f in fields:
             structimpl.append(f"      // Safe access for {f['var']}")
             structimpl.append(f"      {obj}[i].{f['field']}\t= ({f['var']}.size() > i) ? {f['var']}[i] : 0;")
        
        structimpl.append("    }")
        structimpl.append("  }") # End fill function

    structimplall.append('  }') # End fillObjects

    #-------------------------------------------------------------------------
    # Write Files
    #-------------------------------------------------------------------------
    
    # Prepare Dictionary for Templates
    subst = {
        'name': filename,
        'treename': treename,
        'time': ctime(),
        'version': VERSION,
        'author': AUTHOR,
        'vardecl': "\n".join(declare),
        'init': "\n".join(init),
        'structdecl': "\n".join(structdecl),
        'structimpl': "\n".join(structimpl),
        'structvec': "\n".join(structvec),
        'structimplall': "\n".join(structimplall),
        'selectimpl': "\n".join(selectimpl), # Currently empty but kept for compat
        'choose': "\n".join(choose),
        'setb': "\n".join(setb),
        'addb': "\n".join(addb),
        'pragma': ""
    }

    # 1. eventBuffer.h
    print(f"\tWriting {filename}/include/eventBuffer.h...")
    # Ensure dirs exist
    os.makedirs(f"{filename}/include", exist_ok=True)
    os.makedirs(f"{filename}/src", exist_ok=True)
    os.makedirs(f"{filename}/lib", exist_ok=True)
    os.makedirs(f"{filename}/tmp", exist_ok=True)
    os.makedirs(f"{filename}/bin", exist_ok=True) # Optional
    
    with open(f"{filename}/include/eventBuffer.h", "w") as f:
        f.write(TEMPLATE_H % subst)

    # 2. Main App (.cc)
    cc_path = f"{filename}/{filename}.cc"
    if not os.path.exists(cc_path):
        print(f"\tWriting {cc_path}...")
        with open(cc_path, "w") as f:
            f.write(TEMPLATE_CC % subst)

    # 3. Makefile
    print(f"\tWriting {filename}/Makefile...")
    with open(f"{filename}/Makefile", "w") as f:
        f.write(MAKEFILE)

    # 4. Helpers (treestream.h/cc copy commands would go here normally)
    # For now, we assume user follows instructions or script handles it.
    
    # 5. LinkDef
    with open(f"{filename}/include/linkdef.h", "w") as f:
        f.write(LINKDEF % subst)

    print("\n\t[Done] Created analyzer framework.")
    print(f"\tTo build: cd {filename} && make")

if __name__ == "__main__":
    main()
