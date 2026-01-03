#!/usr/bin/env python
#-----------------------------------------------------------------------------
# Description: Create ntuple analyzer using information supplied in a
#              variables.txt file. (See mkvariables.py).
#
#-----------------------------------------------------------------------------
# 이 스크립트(mkanalyzer.py)의 목적
# - variables.txt를 읽어 "브랜치 이름 / 타입 / 최대 개수(count) / leaf counter" 정보를 모은 뒤,
#   그 정보로 eventBuffer C++ 코드를 자동 생성한다.
# - 생성된 eventBuffer는 treestream(itreestream)의 select 기능을 이용해
#   각 브랜치 주소를 C++ 변수(스칼라/벡터)에 연결한다.
#
# eventBuffer의 큰 흐름 (Read-only 생성자 기준)
# 1) stream이 정상인지 확인한 뒤 initBuffers()를 호출한다.
#    - 여기서 스칼라 변수는 기본값(0)으로 초기화된다.
#    - 벡터 변수는 "선언만" 되어 있고, 기본적으로 empty 상태다.
# 2) choose 맵에 "기본적으로 어떤 브랜치를 선택할지"를 채운다.
#    - varlist를 주지 않으면 DEFAULT=True로 전체 선택 모드.
# 3) 각 브랜치에 대해 input->present("branch")로 존재 여부를 확인한다.
#    - 존재하면 input->select("branch", variable)로 연결한다.
#    - 없으면 select를 하지 않고 넘어간다.
# 4) 생성자 끝에서, 연결 성공/실패 브랜치 목록을 출력한다.
#    - successBranches / missingBranches 리스트로 요약 보고서를 만든다.
#
# 브랜치 타입별 처리 요약
# [1] 스칼라 (count == 1)
# - 예: run, lumi, event, rho, Flag_*, HLT_* 등
# - C++ 변수로 선언하고 initBuffers()에서 0으로 초기화한다.
# - 브랜치가 있을 때만 select로 연결된다.
# - 브랜치가 없으면 값은 "0인 채로 유지"된다.
#
# [2] 가변 길이 배열(대부분의 NanoAOD 오브젝트 필드)
# - NanoAOD의 많은 필드는 leaf counter(nJet, nElectron 등)를 따르는 배열 형태이지만,
#   eventBuffer에서는 일괄적으로 std::vector<T>로 받는다.
# - 브랜치가 있을 때만 select로 연결된다.
# - 브랜치가 없으면 그 벡터는 empty 상태로 남는다.
#
# [3] vector<T> 브랜치
# - variables.txt에서 타입이 vector<...>로 들어온 경우.
# - 브랜치가 존재할 때만:
#     (1) var.resize(MAXCOUNT)
#     (2) input->select(branch, var)
#     (3) var.clear()
#   를 수행한다.
#   이유:
#   - select는 내부적으로 "버퍼 메모리 주소"가 필요해서 resize로 메모리를 확보하고,
#   - clear로 논리적 크기를 다시 0으로 만들어 event 읽기 전 상태를 정리하려는 의도다.
#   - (주의) clear는 capacity를 유지하므로 메모리는 잡혀 있을 수 있다.
# - 브랜치가 없으면 resize/select/clear를 하지 않으므로 벡터는 그대로 empty 상태다.
#
# 오브젝트 struct 채우기(fillElectrons(), fillJets() 등)에서의 안전 처리
# - Data/MC 차이로 어떤 필드(예: Electron_genPartIdx)가 Data에는 없을 수 있다.
# - 이런 경우 해당 필드 벡터가 empty가 되므로 var[i] 접근은 크래시 위험이 있다.
# - 그래서 struct fill에서는
#     (var.size() > i) ? var[i] : 0
#   형태로 "부분적으로 없는 필드"를 0으로 채우도록 방어 로직을 넣었다.
#
# 브랜치가 없을 때 의미/주의점 (중요)
# - 현재 정책은 "없는 브랜치를 에러로 즉시 죽이기"가 아니라,
#   가능한 한 분석이 돌아가도록 missing을 0/empty로 처리한다.
# - 이 방식은 런타임 크래시는 줄이지만, 아래와 같은 위험이 있다:
#   1) 스칼라(HLT/Flag/Weight)가 없으면 0이 되어,
#      "실제로는 브랜치가 없었다"는 사실이 분석 로직에서 숨겨질 수 있다.
#      (즉, missing과 false(0)를 구분 못함)
#   2) 벡터/배열은 empty일 수 있으므로 analyzer에서 [i] 접근을 하면 터질 수 있다.
#      (현재는 struct fill에서는 방어하지만, analyzer에서 직접 벡터를 접근하면 위험)
#
# 향후 개선 계획 (간단 버전)
# - 목표는 "없는 브랜치를 조용히 0으로 쓰는 실수"를 줄이는 것.
# - 다음 중 하나(또는 혼합)를 고려한다:
#   A) fail-fast 모드:
#      - 분석에 필수인 브랜치 목록을 지정하고, 없으면 시작 단계에서 즉시 종료.
#   B) 안전 접근 인터페이스:
#      - analyzer 코드에서 _ev->HLT_* 같은 직접 접근을 줄이고,
#        TriggerMenu/Weights 같은 레이어를 통해서만 읽게 만든다.
#   C) 디버그/검증 출력 강화:
#      - 지금은 "present 여부"를 요약 출력하지만,
#        필요 시 특정 브랜치/오브젝트의 읽힌 값/크기까지 출력하는 모드를 확장한다.
#-----------------------------------------------------------------------------

#
# Created: 06-Mar-2010 Harrison B. Prosper
# Updated: 12-Mar-2010 HBP - fix appending of .root
#          08-Jun-2010 HBP - add creation of selector.h
#          02-Sep-2010 HBP - fix variables.txt record splitting bug
#          01-Oct-2010 HBP - add structs
#          02-Oct-2010 HBP - add cloning
#          10-Jan-2011 HBP - merge histFile and skimFile into outputFile
#          11-Mar-2011 HBP - fix naming bug
#          26-Apr-2011 HBP - alert user only if duplicate name is not a leaf
#                            counter
#          04-Jul-2013 HBP - make a better analyzer work area
#          14-Dec-2014 HBP - encapsulate variables within eventStream class
#          17-Dec-2014 HBP - change to eventBuffer since that is a better
#                            name for this class
#          14-May-2015 HBP - make compatible with latest version of Delphes
#          08-Jun-2015 HBP - fix makefile (define sharedlib)
#          13-Feb-2016 HBP - allow possibility to turn on/off branches
#          03-Dec-2017 HBP - get name of leaf counter from variables.txt
#          02-Feb-2018 HBP - collect leaf counter branches in one place
#          21-Feb-2018 HBP - fix Makefile to account for changes in how
#                            ROOT and Mac OS treat environment variables
#                          - protect against zero maxcount
#          23-Mar-2019 HBP - Add user supplied cppflags to CPPFLAGS
#          12-Oct-2020 HBP - Adapt to ROOT6 version of TNM
#-----------------------------------------------------------------------------
import os, sys, re, posixpath
from time import sleep, ctime
from glob import glob
#-----------------------------------------------------------------------------
# Functions
#-----------------------------------------------------------------------------
VERSION = 'v2.0.3 14-Oct-2020'
getvno  = re.compile(r'[0-9]+$')

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

def getauthor():
    regex  = re.compile(r'(?<=[0-9]:)[A-Z]+[a-zA-Z. ]+')
    record = str.strip(os.popen("which getent").read())
    if record != "":
        record = str.strip(os.popen("getent passwd $USER").read())
    author = "Shakespeare's ghost"
    if record != "":
        t = regex.findall(record)
        if len(t) > 0: author = t[0]
    return author
#-----------------------------------------------------------------------------
getvtype = re.compile('(?<=vector[<]).+(?=[>])')
#-----------------------------------------------------------------------------
AUTHOR = getauthor()

##if "CMSSW_BASE" in os.environ:
##    CMSSW_BASE     = os.environ["CMSSW_BASE"]
##    PACKAGE        = "%s/src/PhysicsTools/TheNtupleMaker" % CMSSW_BASE
##    TREESTREAM_HPP = "%s/interface/treestream.h" % PACKAGE    
##    TREESTREAM_CPP = "%s/src/treestream.cc"  % PACKAGE
##    
##    TNM_HPP = "%s/tnm/tnm.h"  % PACKAGE
##    TNM_CPP = "%s/tnm/tnm.cc" % PACKAGE
##    TNM_PY  = "%s/tnm/tnm.py" % PACKAGE
##elif 'TREESTREAM_PATH' in os.environ:
if 'TREESTREAM_PATH' in os.environ:
    area  = {'local': '%s' % os.environ['TREESTREAM_PATH']}
    TREESTREAM_HPP = "%(local)s/include/treestream.h" % area
    TREESTREAM_CPP = "%(local)s/src/treestream.cc" % area
    
    TNM_HPP = "%(local)s/tnm/tnm.h"  % area
    TNM_CPP = "%(local)s/tnm/tnm.cc" % area
    TNM_PY  = "%(local)s/tnm/tnm.py" % area
else:
    TREESTREAM_HPP = "treestream.h"
    TREESTREAM_CPP = "treestream.cc"
    
    TNM_HPP = "tnm.h"
    TNM_CPP = "tnm.cc"
    TNM_PY  = "tnm.py"

# Make sure that we can find treestream etc.

if not os.path.exists(TREESTREAM_HPP):
    print("\n** error ** - required file:\n%s\nNOT found!" % \
          TREESTREAM_HPP)
    sys.exit('''
    try installing treestream package:
    
    cd
    mkdir -p external/bin
    mkdir -p external/lib
    mkdir -p external/include
    cd external
    git clone https://github.com/hbprosper/treestream
 or
    git clone git://github.com/hbprosper/treestream

    then
    
    cd treestream
    make
    make install
    ''')

if not os.path.exists(TREESTREAM_CPP):
    sys.exit("\n** error ** - required file:\n\t%s\n\t\tNOT found!" % \
          TREESTREAM_CPP)
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

#pragma link C++ function error;
#pragma link C++ function strip;
#pragma link C++ function split;
#pragma link C++ function change;
#pragma link C++ function nameonly;
#pragma link C++ function shell;
#pragma link C++ function deltaPhi;
#pragma link C++ function deltaR;
#pragma link C++ function fileNames;
#pragma link C++ function setStyle;
#pragma link C++ function particleName;

#pragma link C++ class outputFile;
#pragma link C++ class commandLine;
#pragma link C++ class matchedPair;
#pragma link C++ class ptThing;

#pragma link C++ class itreestream;
#pragma link C++ class otreestream;
#pragma link C++ class eventBuffer;

%(pragma)s
#endif
'''

MACRO_DECL_H =\
'''
//----------------------------------------------------------------------------
// -- Declare variables
//----------------------------------------------------------------------------
struct %(Name)sEvent {
%(vardecl)s
//----------------------------------------------------------------------------
// --- Structs can be filled by calling fillObjects()
//----------------------------------------------------------------------------
%(structdecl)s
%(structimpl)s
%(structimplall)s
}; 
'''

MACRO_IMPL_H =\
'''
%(impl)s
'''

TEMPLATE_H =\
'''#ifndef EVENTBUFFER_H
#define EVENTBUFFER_H
//----------------------------------------------------------------------------
// File:        eventBuffer.h
// Description: Analyzer header for ntuples created by TheNtupleMaker
// Created:     %(time)s by mkanalyzer.py %(version)s
// Author:      %(author)s
//----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <map>
#include <cassert>
#include "treestream.h"

struct eventBuffer
{
  //--------------------------------------------------------------------------
  // --- Declare variables
  //--------------------------------------------------------------------------
%(vardecl)s
  //--------------------------------------------------------------------------
  // --- Structs can be filled by calling fill(), or individual fill
  // --- methods, e.g., fillElectrons()
  // --- after the call to read(...)
  //----------- --------------------------------------------------------------
%(structdecl)s
%(structimpl)s
%(structvec)s
%(structimplall)s
   //--------------------------------------------------------------------------
%(selectimpl)s
  //--------------------------------------------------------------------------
  // A read-only buffer 
  eventBuffer() : input(0), output(0), choose(std::map<std::string, bool>()) {}
  eventBuffer(itreestream& stream, std::string varlist="")
  : input(&stream),
    output(0),
    choose(std::map<std::string, bool>())
  {
    if ( !input->good() ) 
      {
        std::cout << "eventBuffer - please check stream!" 
                  << std::endl;
	    exit(0);
      }

    initBuffers();
    
    // default is to select all branches      
    bool DEFAULT = varlist == "";
%(choose)s
    if ( DEFAULT )
      {
        std::cout << std::endl
                  << "eventBuffer - All branches selected"
                  << std::endl;
      }
    else
      {
        std::cout << "eventBuffer - branches selected:"
                  << std::endl;      
        std::istringstream sin(varlist);
        while ( sin )
          {
            std::string key;
            sin >> key;
            if ( sin )
              {
		        std::map<std::string, bool>::iterator it;
		        for(it = choose.begin(); it != choose.end(); it++)
		          {
		            if ( it->first.length() > key.length() )
		              {
			            if ( it->first.substr(0, key.size()) == key )
			              {
			                choose[it->first] = true;
			              }
		              }
                  }
              }
          }
      }
    std::vector<std::string> successBranches;
    std::vector<std::string> missingBranches;
%(setb)s

    std::cout << "=========================================" << std::endl;
    std::cout << "Report for [ eventbuffer ] about branch access.." << std::endl;
    std::cout << std::endl;
    std::cout << "sucess branch list -----" << std::endl;
    for (size_t i = 0; i < successBranches.size(); ++i)
      {
        std::cout << successBranches[i] << std::endl;
      }
    std::cout << std::endl;
    std::cout << "failed branch list -----" << std::endl;
    for (size_t i = 0; i < missingBranches.size(); ++i)
      {
        std::cout << missingBranches[i] << std::endl;
      }
  }

  // A write-only buffer
  eventBuffer(otreestream& stream)
  : input(0),
    output(&stream)
  {
    initBuffers();

%(addb)s
  }

  void initBuffers()
  {
%(init)s
  }
      
  void read(int entry)
  {
    if ( !input ) 
      { 
        std::cout << "** eventBuffer::read - first  call read-only constructor!"
                  << std::endl;
        assert(0);
      }
    input->read(entry);

    // clear indexmap
    for(std::map<std::string, std::vector<int> >::iterator
    item=indexmap.begin(); 
    item != indexmap.end();
    ++item)
    item->second.clear();
  }

  void select(std::string objname)
  {
    indexmap[objname] = std::vector<int>();
  }

  void select(std::string objname, int index)
  {
    try
     {
       indexmap[objname].push_back(index);
     }
    catch (...)
     {
       std::cout << "** eventBuffer::select - first call select(""" 
                 << objname << """)" 
                 << std::endl;
       assert(0);
    }
  }

 void ls()
 {
   if( input ) input->ls();
 }

 int size()
 {
   if( input ) 
     return input->size();
   else
     return 0;
 }

 void close()
 {
   if( input )   input->close();
   if( output ) output->close();
 }

 // --- indexmap keeps track of which objects have been flagged for selection
 std::map<std::string, std::vector<int> > indexmap;

 // to read events
 itreestream* input;

 // to write events
 otreestream* output;

 // switches for choosing branches
 std::map<std::string, bool> choose;

}; 
#endif
'''


TEMPLATE_CC =\
'''//---------------------------------------------------------------------------
// File:        %(name)s.cc
// Description: Analyzer for simple ntuples, such as those created by
//              TheNtupleMaker
// Created:     %(time)s by mkanalyzer.py %(version)s
// Author:      %(author)s
//----------------------------------------------------------------------------
#include "tnm.h"
using namespace std;
//----------------------------------------------------------------------------
int main(int argc, char** argv)
{
  // If you want canvases to be visible during program execution, just
  // uncomment the line below
  //TApplication app("%(name)s", &argc, argv);

  // Get command line arguments
  commandLine cl(argc, argv);
    
  // Get names of ntuple files to be processed
  vector<string> filenames = fileNames(cl.filelist);

  // Create tree reader
  itreestream stream(filenames, "%(treename)s");
  if ( !stream.good() ) error("can't read root input files");

  // Create a buffer to receive events from the stream
  // The default is to select all branches
  // Use second argument to select specific branches
  // Example:
  //   varlist = 'Jet_PT Jet_Eta Jet_Phi'
  //   ev = eventBuffer(stream, varlist)

  eventBuffer ev(stream);
  
  int nevents = ev.size();
  cout << "number of events: " << nevents << endl;

  // Create output file for histograms; see notes in header 
  outputFile of(cl.outputfilename);

  // -------------------------------------------------------------------------
  // Define histograms
  // -------------------------------------------------------------------------
  //setStyle();

  // -------------------------------------------------------------------------
  // Loop over events
  // -------------------------------------------------------------------------
  
  for(int entry=0; entry < nevents; entry++)
    {
      // read an event into event buffer
      ev.read(entry);

    }
    
  ev.close();
  of.close();
  return 0;
}
'''


PYTEMPLATE =\
'''#!/usr/bin/env python
# ----------------------------------------------------------------------------
#  File:        %(name)s.py
#  Description: Analyzer for simple ROOT ntuples
#  Created:     %(time)s by mkanalyzer.py %(version)s
#  Author:      %(author)s
# ----------------------------------------------------------------------------
import os, sys, re
import tnm
import ROOT
# ----------------------------------------------------------------------------
# -- Constants, procedures and functions
# ----------------------------------------------------------------------------


# ----------------------------------------------------------------------------
def main():

    cl = ROOT.commandLine()
    
    # Get names of ntuple files to be processed
    filenames = ROOT.fileNames(cl.filelist)

    # Create tree reader
    stream = ROOT.itreestream(filenames, "%(treename)s")
    if not stream.good():
        error("can't read input files")

    # Create a buffer to receive events from the stream
    # The default is to select all branches.
    # Use second argument to select specific branches
    # Example:
    #   varlist = 'Jet_PT Jet_Eta Jet_Phi'
    #   ev = ROOT.eventBuffer(stream, varlist)
    #
    ev = ROOT.eventBuffer(stream)

    nevents = ev.size()
    print("number of events:", nevents)

    # Create file to store histograms
    of = ROOT.outputFile(cl.outputfilename)

    # ------------------------------------------------------------------------
    # Define histograms
    # ------------------------------------------------------------------------
    ROOT.setStyle()

    # ------------------------------------------------------------------------
    # Loop over events
    # ------------------------------------------------------------------------
    for entry in range(nevents):
        ev.read(entry)
        
    ev.close()
    of.close()
# ----------------------------------------------------------------------------
try:
   main()
except KeyboardInterrupt:
   print("bye!")
'''

MAKEFILE = '''#----------------------------------------------------------------------------
# Description: Makefile to build analyzers
# Created:     %(time)s by mkanalyzer.py %(version)s
# Author:      %(author)s
#----------------------------------------------------------------------------
ifndef ROOTSYS
$(error *** Please set up Root)
endif

name    := %(name)s

# Sub-directories
srcdir	:= src
tmpdir	:= tmp
libdir	:= lib
incdir	:= include

$(shell mkdir -p tmp)
$(shell mkdir -p lib)

# Set this equal to the @ symbol to suppress display of instructions
# while make executes
ifdef verbose
AT 	:=
else
AT	:= @
endif
#-----------------------------------------------------------------------
# sources and objects
#-----------------------------------------------------------------------
header  := $(incdir)/tnm.h
linkdef := $(incdir)/linkdef.h
cinthdr := $(srcdir)/dictionary.h
cintsrc := $(srcdir)/dictionary.cc

# Construct list of sources to be compiled into applications
appsrcs	:= $(wildcard *.cc)
appobjects	:= $(addprefix $(tmpdir)/,$(appsrcs:.cc=.o))

# Construct list of applications
applications := $(appsrcs:.cc=)

# Construct list of sources to be compiled into shared library
ccsrcs	:= $(filter-out $(cintsrc),$(wildcard $(srcdir)/*.cc))
sources	:= $(ccsrcs) $(cintsrc)
objects	:= $(subst $(srcdir)/,$(tmpdir)/,$(sources:.cc=.o))

# Display list of applications to be built
#say	:= $(shell echo "appsrcs:     $(appsrcs)" >& 2)
#say	:= $(shell echo "appobjects:  $(appobjects)" >& 2)
#say	:= $(shell echo "objects:     $(objects)" >& 2)
#$(error bye!) 

#-----------------------------------------------------------------------
# 	Define which compilers and linkers to use
#-----------------------------------------------------------------------
# If clang++ exists use it, otherwise use g++
COMPILER:= $(shell which clang++)
ifneq ($(COMPILER),)
CXX     := clang++
LINK	:= clang++
else
CXX     := g++
LINK	:= g++
endif 
CINT	:= rootcint

#-----------------------------------------------------------------------
# 	Define paths to be searched for C++ header files (#include ....)
#-----------------------------------------------------------------------
CPPFLAGS:= -I. -I$(incdir) -I$(srcdir) $(shell root-config --cflags) $(cppflags)

# 	Define compiler flags to be used
#	-c		perform compilation step only 
#	-g		include debug information in the executable file
#	-O2		optimize
#	-ansi	require strict adherance to C++ standard
#	-Wall	warn if source uses any non-standard C++
#	-pipe	communicate via different stages of compilation
#			using pipes rather than temporary files

CXXFLAGS:= -c -g -O2 -ansi -Wall -pipe -fPIC

#	C++ Linker
#   set path to ROOT libraries (Mac OS workaround)
LD	:= $(LINK) -Wl,-rpath,$(ROOTSYS)/lib

OS	:= $(shell uname -s)
ifeq ($(OS),Darwin)
    LDSHARED	:= $(LD) -dynamiclib
    LDEXT       := .dylib
else
    LDSHARED	:= $(LD) -shared
    LDEXT       := .so
endif

#	Linker flags

LDFLAGS := -g

# 	Libraries

LIBS	:=  \
$(shell root-config --libs) -L$(libdir) -lMinuit -lMathCore

sharedlib := $(libdir)/libtnm$(LDEXT)

#-----------------------------------------------------------------------
#	Rules
#	The structure of a rule is
#	target : source
#		command
#	The command makes a target from the source. 
#	$@ refers to the target
#	$< refers to the source
#-----------------------------------------------------------------------
all:	$(sharedlib) $(applications) 

bin:	$(applications)

lib:	$(sharedlib)

# Syntax:
# list of targets : target pattern : source pattern

# Make applications depend on shared libraries to force the latter
# to be built first

$(applications)\t: %(percent)s\t: $(tmpdir)/%(percent)s.o  $(sharedlib)
\t@echo "---> Linking $@"
\t$(AT)$(LD) $(LDFLAGS) $< $(LIBS) -ltnm -o $@

$(appobjects)\t: $(tmpdir)/%(percent)s.o\t: %(percent)s.cc
\t@echo "---> Compiling application `basename $<`" 
\t$(AT)$(CXX) $(CXXFLAGS) $(CPPFLAGS)  $< -o $@ # >& $*.FAILED
\t@rm -rf $*.FAILED

$(sharedlib)\t: $(objects)
\t@echo "---> Linking `basename $@`"
\t$(AT)$(LDSHARED) $(LDFLAGS) -fPIC $(objects) $(LIBS) -o $@

$(objects)	: $(tmpdir)/%(percent)s.o	: $(srcdir)/%(percent)s.cc
\t@echo "---> Compiling `basename $<`" 
\t$(AT)$(CXX) $(CXXFLAGS) $(CPPFLAGS)  $< -o $@ # >& $*.FAILED
\t$(AT)rm -rf $*.FAILED

$(cintsrc)  : $(header) $(linkdef)
\t@echo "---> Generating dictionary `basename $@`"
\t$(AT)$(CINT) -f $@ -c -I. -Iinclude -I$(ROOTSYS)/include $+
\t$(AT)mv $(srcdir)/*.pcm $(libdir)

# 	Define clean up rules
clean   :
\trm -rf $(tmpdir)/* $(libdir)/* $(srcdir)/dictionary* $(applications)
'''

README = '''Created: %(time)s

    o First add lib and python directories to LD_LIBRARY_PATH and PYTHONPATH,
      respectively, by doing

      source setup.sh  (assuming a bash shell)

    o To build all programs do

      make

      This will first build lib/libtnm.so from the codes in src, then
      build all the programs in the current directory, linked against the
      shared library.


    o To run the program, first create a text file (default name=filelist.txt)
    containing a list of the ntuples to be analyzed, one filename per line.
    Then do

      ./%(name)s

    If you wish to specify a different file list, say datafile.list, do

      ./%(name)s datafile.list

    If you wish to change the name of the root output file, say
    datahist.root, do

       ./%(name)s datafile.list datahist.root

For details, please refer to the documentation at:

    https://twiki.cern.ch/twiki/bin/viewauth/CMS/TheNtupleMaker

Notes 1
-------
    1. Use
    outputFile of(cl.outputfile, ev)

    where "ev" is the eventBuffer, if you wish to skim events to the output
    file in addition to writing out histograms. The current event is written
    to the file using

    of.write(event-weight) 

    where "of" is the output file. If omitted, the event-weight is
    taken to be 1.

    2. Use
    of.count(cut-name, event-weight)
    
    to keep track, in the count histogram, of the number of events passing
    a given cut. If omitted, the event-weight is taken to be 1. If you want
    the counts in the count histogram to appear in a given order, specify
    the order, before entering the event loop, as in the example below
    
    of.count("NoCuts", 0)
    of.count("GoodEvent", 0)
    of.count("Vertex", 0)
    of.count("MET", 0)
    
Notes 2
-------
    By default, when an event is written to the output file, all variables are
    written. However, before the event loop, you can use

    ev.select(objectname)

    e.g.,

    ev.select("GenParticle")

    to declare that you intend to select objects of this type. The
    selection is done, within the event loop, using

    ev.select(objectname, index)

    e.g.,

    ev.select("GenParticle", 3),

    which specifies that object 3 of GenParticle is to be kept. 

    NB: If you declare your intention to select objects of a given type
        by calling select(objectname), but subsequently fail to select
        them using select(objectname, index) then no objects of this
        type will be kept!
'''
#------------------------------------------------------------------------------
def cmp(x, y):
    if len(y) < len(x):
        return -1
    elif len(y) == len(x):
        return 0
    else:
        return 1
#------------------------------------------------------------------------------
isvector = re.compile('(?<!std::)vector')
getvtype = re.compile('(?<=vector[<]).*(?=[>])')
#------------------------------------------------------------------------------
def main():
    print("\n\tmkanalyzer.py")

    # Decode command line

    argv = sys.argv[1:]
    argc = len(argv)
    if argc < 1: usage()

    filename = nameonly(argv[0])
    t = str.split(filename, '/')
    force = False
    if len(t) > 1:
        filename = t[0]
        if t[-1][0] in ['f', 'F']:
            force = True
            
    if force:
        print('** force re-copying of all files except the %s.cc' % \
                  filename)
        
    if argc > 1:
        varfilename = argv[1]
    else:
        varfilename = "variables.txt"
    if not os.path.exists(varfilename):
        sys.exit("mkanalyzer.py - can't find variable file: %s" % varfilename)

    # Check for macro mode
    macroMode = argc > 2

    # Read variable names
    records = [str.strip(x) for x in open(varfilename, "r").readlines() ]
    #records = map(str.strip, open(varfilename, "r").readlines())

    # Get tree name(s)
    t = str.split(records[0])
    if str.lower(t[0]) == "tree:":
        treename = t[1]
    else:
        treename = ""
    start = 1
    for record in records[1:]:
        record = str.strip(record)
        if record == "": break
        t = str.split(record)
        if str.lower(t[0]) == "tree":
            treename += " %s" % t[1]
            start += 1

    # check whether we have a single tree
    single_tree = len(str.split(treename)) == 1
    
    # --------------------------------------------------------------------
    # Done with header, so loop over branch names
    # and get list of potential struct names (first field of
    # varname.
    # branchname:  name of branch
    # varname:     name of associated C++ variable
    # countername: name of branch that serves as a leaf counter
    # --------------------------------------------------------------------
    records = records[start:]
    tokens = []
    tmpmap = {}
    for index in range(len(records)):
        record = records[index]
        if record == "": continue

        # split record into its fields
        # varname = variable name as determined by mkvariables.py
        tokens.append(str.split(record, "/"))
        varname = tokens[-1][2]
            
        # varname should have the format
        # <objname>_<field-name>
        t = str.split(varname,'_')
        if len(t) > 1: # Need at least two fields for a struct
            key = t[0]
            if not (key in tmpmap): tmpmap[key] = 0
            tmpmap[key] += 1

    # If we have at least two fields, we'll create a struct
    structname = {}
    for key in tmpmap.keys():
        if tmpmap[key] > 1:
            structname[key] = tmpmap[key]

    # --------------------------------------------------------------------
    # Loop over tokens
    # --------------------------------------------------------------------
    usednames = {}
    varmap    = {}
    vectormap = {}
    varnum    = 1
    skipped = '' # variables that are skipped
    for index, tns in enumerate(tokens):

####        # check for leafcounter
####        has_leafcounter = len(tns) == 5
####        if has_leafcounter:
####            rtype, branchname, varname, count, countername = tns
####        elif len(tns) == 4:
####            rtype, branchname, varname, count = tns
####            countername = None
####        else:
####            sys.exit('''
#### ** mkanalyzer.py ***
####            missing maximum count at end of record:
####            %s
####            ''' % tns)
        # --------------------------------------------------------------------
        # [Fixed by Jh.Lee] Handle Branch names containing '/' (e.g., Events/BranchName)
        # --------------------------------------------------------------------
        try:
            # 1. Type is always the first token
            rtype = tns[0]

            # 2. Count info is always the last token
            last_token = tns[-1]
            if ' ' in last_token:
                count_str, countername = last_token.split()
            else:
                count_str = last_token
                countername = None
            
            count = count_str 

            # 3. Variable name is always the second to last token
            varname = tns[-2]

            # 4. Branch name is everything in between (Handle 'Events/Name')
            branchname = "/".join(tns[1:-2])

        except Exception as e:
             sys.exit('''
 ** mkanalyzer.py ***
            Parsing error for record: %s
            Error: %s
            ''' % (tns, e))


        # for now strings aren't supported
        if rtype.find("string") > -1: 
            continue

        # set up count
        count = int(count) # change type to an integer
        if count > 1:
            from math import sqrt
            count = int(count + 4*sqrt(count))
            ii = count / 4
            count = (ii+1)*4
        elif count < 1:
            count = 100
        tokens[index][3] = '%d' % count
        
        # make sure names are unique. If they aren't bail!

        if varname in varmap:
            varnum += 1
            print("** warning ** duplicate name %s; "\
            "changed to %s%d" % (varname, varname, varnum))
            varname = '%s%d' % (varname, varnum)
            
        # do something about annoying types

        if str.find(varname, '[') > -1 and count > 1:
            skipped += "%s[%d]\n" % (branchname, count)
            continue
        if str.find(str.lower(rtype), 'ref') > -1:
            skipped += "%s[%d]\n" % (branchname, count)
            continue

        if str.find(str.lower(rtype), 'lorentz') > -1:
            skipped += "%s[%d]\n" % (branchname, count)
            continue

        if rtype == "bool":
            rtype = "bool"
        elif rtype == "ulong64":
            rtype = "long"
        elif rtype == "long64":
            rtype = "long"            
        elif rtype == "int32":
            rtype = "int"
        elif rtype == "uchar":
            rtype = "int"
        elif rtype == "uint":
            rtype = "unsigned int"			

        objname = ''
        fldname = ''

        # get object and field names
        t = str.split(varname,'_')
        if len(t) > 0:
            # we have at least two fields in varname
            key = t[0]
            if key in structname:

                # This branch potentially belongs to a struct.
                objname = key
                # Make sure the count for this branch matches that
                # of existing struct
                if not (objname in usednames):
                    usednames[objname] = count;

                if usednames[objname] == count:
                    fldname = str.replace(varname, '%s_' % objname, '')
                else:
                    objname = ''
                    fldname = ''

        # update map for all variables
        varmap[varname] = [rtype, branchname, count, countername]
        
        # vector types must have the same object name and a max count > 1
        if count > 1:               
            if fldname != "":

                # Make sure fldname is a valid	c++ name		
                if fldname[0] in ['0','1','2','3','4','5','6','7','8','9']:
                    fldname = 'f%s' % fldname

                if not (objname in vectormap): vectormap[objname] = []	
                vectormap[objname].append((rtype,
                                               fldname,
                                               varname,
                                               count,
                                               countername))
                #print "%s.%s (%s)" % (objname, fldname, count)

    if skipped != "":
        open("variables_skipped.txt", "w").write(skipped)
    else:
        os.system("rm -rf variables_skipped.txt")
        
    # Declare all variables
    keys = [ x for x in varmap]
    keys.sort()
    declarevec= []
    declare   = []
    init      = []
    setb      = []
    addb      = []
    impl      = []
    choose    = []
    
    # get all leaf counters
    counters = set()
    for index, varname in enumerate(keys):
        rtype, branchname, count, countername = varmap[varname]
        if countername == None: continue
        counters.add(countername)
    for name in counters:
        declare.append("  %s\t%s;" % ('int', name))
        addb.append('  output->add("%s", \t%s);' % (name, name))
    declare.append('')
    addb.append('')

    for index, varname in enumerate(keys):
        rtype, branchname, count, countername = varmap[varname]

        if macroMode:
            #### FIXME ####
            if 0:
                impl.append('  countvalue& v%d = (*varmap)["%s"];'%\
                            (index, branchname))
                impl.append('  if ( v%d.count )' % index)
                impl.append('    %s = *v%d.count;' % (varname, index))
                impl.append('  else')
                impl.append('    %s = 0;' % varname)
                impl.append('')			

            elif count == 1:
                impl.append('  countvalue& v%d = (*varmap)["%s"];' %\
                            (index, branchname))

                impl.append('  if ( v%d.value )' % index)
                impl.append('    %s = *v%d.value;' % (varname, index))
                impl.append('  else')
                impl.append('    %s = 0;' % varname)
                impl.append('')
            else:
                # this is a vector
                impl.append('  countvalue& v%d = (*varmap)["%s"];' % \
                            (index, branchname))

                impl.append('  if ( v%d.value )' % index)
                impl.append('    {')
                impl.append('      %s.resize(*v%d.count);' % (varname, index))
                impl.append('      copy(v%d.value, v%d.value+*v%d.count, '\
                            '%s.begin());'% (index, index, index, varname))
                impl.append('    }')
                impl.append('  else')
                impl.append('    %s.clear();' % varname)
                impl.append('')

        if single_tree:
            choosename = str.split(branchname, '/')[-1]
        else:
            choosename = branchname
        choose.append('  choose["%s"]\t= DEFAULT;' % choosename)
        setb.append('  if ( choose["%s"] )'   % choosename)
####        cmd = '    input->select("%s", \t%s);' % (branchname, varname)
####        if len(cmd) < 75:
####            setb.append(cmd)
####        else:
####            setb.append('    input->select("%s",' % branchname)
####            setb.append('                   %s);' % varname)
# above 4 lines are changed by Jh.Lee 18th Dec, 2025
# [MODIFIED] Check existence before selecting (Super-Set Strategy)
       
####        # Branch가 파일에 존재할 때만 select를 호출하도록 보호
####        cmd = '    if (input->present("%s")) input->select("%s", %s);' % \
####              (branchname, branchname, varname)
####
####        # 긴 줄 처리 등은 무시하고, 위 한 줄로 깔끔하게 처리하거나
####        # 필요하다면 줄바꿈 처리를 추가할 수 있습니다. 위 코드로 충분합니다.
####        setb.append(cmd)
# [MODIFIED] Above line changed by Jh.Lee 18th Dec, 2025
        if count == 1:
            # Scalar: Just check existence
            cmd = '    if (input->present("%s")) { input->select("%s", %s); ' \
                  'successBranches.push_back("%s"); } else { ' \
                  'missingBranches.push_back("%s"); }' % \
                  (branchname, branchname, varname, branchname, branchname)
            setb.append(cmd)
        else:
            # Vector: Resize -> Select -> Clear pattern
            cmd = '    if (input->present("%s")) { ' \
                  '%s.resize(%d); ' \
                  'input->select("%s", %s); ' \
                  '%s.clear(); ' \
                  'successBranches.push_back("%s"); } else { ' \
                  'missingBranches.push_back("%s"); }' % \
                  (branchname, varname, count, branchname, varname, varname,
                   branchname, branchname)
            setb.append(cmd)



        # [SCALAR] count == 1
        if count == 1:
            # 스칼라 변수 분기, trigger나 event, run 등등의 변수가 여기 저장
            # nJet, nElectron 같은 다른 변수의 개수를 뜻하는 변수들(e.g. Jet_pt ...[nJet])
            # 의 경우 mkvariables에서 아예 카운트를 안함
            #    --> is_counter = (x[-1] == "*")
            #    --> if is_counter:
            #    -->    continue;
            # 위 구현이 mkvariabe에 있으니 확인
            declare.append("  %s\t%s;" % (rtype, varname))

            # [추가됨] 스칼라 변수는 0으로 초기화 (Branch가 없을 때 쓰레기 값 방지)
            init.append("    %s\t= 0;" % varname)

        # [VECTOR] count > 1 (else block)
        else:
            # this is either a vector or a variable length array
            if str.find(rtype, 'vector') > -1:
                # VECTOR
                rtype = isvector.sub("std::vector", rtype)
                vtype = getvtype.findall(rtype)
                if len(vtype) == 0:
                    sys.exit("** error ** unable to extract type from %s "\
                                 "for variable %s" % \
                                 (rtype, varname))
                vtype = vtype[0]
                
                declarevec.append("  %s\t%s;" % (rtype, varname))
####                init.append("    %s\t= %s(%d, (%s)0);" % \
####                        (varname, rtype, count, vtype))
                    # Above 2 line are commented out by Jh.Lee to prevent vector initialization
		    
            else:
                # VARIABLE LENGTH ARRAY
                # Central NanoAOD sample은전부 array 선언이라 위 vector 분기는 의미 없긴 함
                declarevec.append("  std::vector<%s>\t%s;" % (rtype, varname))
####                init.append("    %s\t= std::vector<%s>(%d,0);" % \
####                            (varname, rtype, count))
                    # Above 2 line are commented out by Jh.Lee to prevent vector initialization

                if countername == None:
                    sys.exit("** error ** array %s does not have a "\
                                 "leafcounter name" % varname)
                branchname += "[%s]" % countername

        cmd = '  output->add("%s", \t%s);' % (branchname, varname)
        if len(cmd) < 75:
            addb.append(cmd)
        else:            
            addb.append('  output->add("%s",' % branchname)
            addb.append('               %s);' % varname)

    # Create structs for vector variables

    pragma = []
    keys = [x for x in vectormap]
    keys.sort()
    structvec  = []	
    structdecl = []
    structimpl = []
    structimplall = []

    selectdecl = []
    selectimpl = []

    selectimpl.append('  // Save objects for which the select'\
                      ' function was called')
    selectimpl.append('  void saveObjects()')
    selectimpl.append('  {')
    if len(keys) > 0:
        selectimpl.append('    int n = 0;')
    structimplall.append('  void fillObjects()')
    structimplall.append('  {')

    for index, objname in enumerate(keys):
        values = vectormap[objname]
        varname= values[0][-3]

        structimplall.append('    fill%ss();' % objname)
        structimpl.append('  void fill%ss()' % objname)
        structimpl.append('  {')
        structimpl.append('    %s.resize(%s.size());' % (objname, varname))
        structimpl.append('    for(unsigned int i=0; i < %s.size(); ++i)' % \
                          objname)
        structimpl.append('      {')

        selectimpl.append('')
        selectimpl.append('    n = 0;')
        selectimpl.append('    try')
        selectimpl.append('      {')
        selectimpl.append('         n = indexmap["%s"].size();' % objname)
        selectimpl.append('      }')
        selectimpl.append('    catch (...)')
        selectimpl.append('      {}')
        selectimpl.append('    if ( n > 0 )')
        selectimpl.append('      {')
        selectimpl.append('        std::vector<int>& '\
                          'index = indexmap["%s"];' % objname)
        selectimpl.append('        for(int i=0; i < n; ++i)')
        selectimpl.append('          {')
        selectimpl.append('            int j = index[i];')
        structdecl.append('  struct %s_s' % objname)
        structdecl.append('  {')

        for rtype, fldname, varname, count, countername in values:
            # treat bools as ints
            if rtype == "bool":
                cast = '(bool)'
            else:
                cast = ''
                
            # check if this is a vector. if it is extract the
            # underlying type.
            vtype = getvtype.findall(rtype)
            if len(vtype) > 0:
                rtype = vtype[0]
                
            structdecl.append('    %s\t%s;' % (rtype, fldname))

####            structimpl.append('        %s[i].%s\t= %s%s[i];' % (objname,
####                                                              fldname,
####                                                              cast,
####                                                              varname))
# Above 4 linesa are modified by Jh.Lee 18th Dec, 2025
# To avoid empty vector, so why this happen?
# MC has object vector like electrons, muons, jet, etc
# MC's electron could have [ genPartIdx branch, pt branch, ... ]
# BUT DATA ELECTRON COULD HAVE [ pt branch, NOT genPartIdx, ... ], so if you use above line,
# then you could approch genPartIdx in Data sample even though they don't have genPartIdx branch
            # [Fix] Partial Branch Existence in Structs (Safe Access)
            # MC 변수(genPartIdx 등)가 Data에서 비어있을 때(Size=0) 접근하여 죽는 것 방지
            structimpl.append('        %s[i].%s\t= (%s.size() > i) ? %s%s[i] : 0;' % (objname,
                                                              fldname,
                                                              varname,
                                                              cast,
                                                              varname))


            selectimpl.append('            %s[i]\t= %s[j];' % (varname, varname))

        structvec.append('  std::vector<eventBuffer::%s_s> %s;' % \
                             (objname, objname))
        init.append('    %s\t= std::vector<eventBuffer::%s_s>(%d);' % (objname,
                                                                       objname,
                                                                       count))
        pragma.append('#pragma link C++ class eventBuffer::%s_s;' % objname)
        pragma.append('#pragma link C++ class vector<eventBuffer::%s_s>;' % \
                          objname)
        pragma.append('')

        structdecl.append('')		
        structdecl.append('    std::ostream& operator<<(std::ostream& os)')
        structdecl.append('    {')
        structdecl.append('      char r[1024];')
        structdecl.append('      os << "%s" << std::endl;' % objname)

        for rtype, fldname, varname, count, countername in values:
            structdecl.append('      sprintf(r, "  %s: %s\\n", "%s",'\
                              ' ( double)%s); '\
                              'os << r;' % ("%-32s", "%f", fldname, fldname))
        structdecl.append('      return os;')
        structdecl.append('    }')
        structdecl.append('  };\n')
        
        structimpl.append('      }')
        structimpl.append('  }\n')  # end of fill<object>s()
        selectimpl.append('          }')
        selectimpl.append('      }')

        # there is no leaf counter for vector types.
        if countername != None:
            selectimpl.append('    %s = n;' % countername)
    structimplall.append('  }')  # end of fillObjects()
    selectimpl.append('  }')  # end of saveObjects()

    # Write out files

    if macroMode:

        names = {'NAME': str.upper(filename),
                 'name': filename,
                 'time': ctime(),
                 'author': AUTHOR,
                 'vardecl': join("", declare, "\n"),
                 'selection': join("  ", select, "\n"),
                 'structdecl': join("", structdecl, "\n"),
                 'structimpl': join("", structimpl, "\n"),
                 'structimplall': join("", structimplall, "\n"),
                 'selectimpl': join("", selectimpl, "\n"),
                 'impl': join("", impl, "\n"),
                 'treename': treename,
                 'percent': '%' }

        record = MACRO_DECL_H % names
        outfilename = "%s_decl.h" % filename
        open(outfilename, "w").write(record)

        record = MACRO_IMPL_H % names
        outfilename = "%s_impl.h" % filename
        open(outfilename, "w").write(record)
        sys.exit(0)

    # Put everything into a directory

    outfilename = '%(dir)s/include/treestream.h' % {'dir': filename}
    if not os.path.exists(outfilename) or force:
        cmd = '''
        mkdir -p %(dir)s/tmp
        mkdir -p %(dir)s/lib
        mkdir -p %(dir)s/src
        mkdir -p %(dir)s/python
        mkdir -p %(dir)s/include
        cp %(hpp)s %(dir)s/include
        cp %(cpp)s %(dir)s/src
        ''' % {'dir': filename,
            'hpp': TREESTREAM_HPP,
            'cpp': TREESTREAM_CPP}
        os.system(cmd)

    outfilename = '%(dir)s/include/tnm.h' % {'dir': filename}
    if not os.path.exists(outfilename) or force:            
        cmd = '''
        cp %(hpp)s %(dir)s/include
        cp %(cpp)s %(dir)s/src
        cp %(py)s  %(dir)s/python
        ''' % {'dir': filename,
            'hpp': TNM_HPP,
            'cpp': TNM_CPP,
            'py' : TNM_PY
            }
        os.system(cmd)
    
    # Create Makefile

    names = {'name': filename,
             'filename': filename,
             'time': ctime(),
             'author': AUTHOR,
             'percent': '%',
             'version': VERSION
             }

    record = MAKEFILE % names
    open("%s/Makefile" % filename, "w").write(record)	

    # Create C++ code

    declarevec += [""] + declare
    names = {'NAME': str.upper(filename),
             'name': filename,
             'time': ctime(),
             'author': AUTHOR,
             'vardecl':    join("", declarevec, "\n"),
             'init':       join("", init, "\n"),
             'setb':       join("  ", setb, "\n"),
             'choose':     join("  ", choose, "\n"),
             'addb':       join("  ", addb, "\n"),
             'structdecl': join("", structdecl, "\n"),
             'structimpl': join("", structimpl, "\n"),
             'structimplall': join("", structimplall, "\n"),
             'selectimpl': join("", selectimpl, "\n"),
             'structvec':    join("", structvec, "\n"),
             'treename': treename,
             'percent': '%',
             'version': VERSION}

    # always recreate eventBuffer
    record = TEMPLATE_H % names
    outfilename = "%s/include/eventBuffer.h" % filename
    open(outfilename,"w").write(record)

    # Create cc file if one does not yet exist
    outfilename = "%s/%s.cc" % (filename, filename)
    if not os.path.exists(outfilename) or force:
        record = TEMPLATE_CC % names
        open(outfilename,"w").write(record)

    # Create README
    outfilename = "%s/README" % filename
    if not os.path.exists(outfilename) or force:    
        record = README % names
        open(outfilename,"w").write(record)

    # write out linkdef

    outfilename = "%s/include/linkdef.h" % filename
    if not os.path.exists(outfilename) or force:
        names['pragma'] = join("", pragma, "\n")       
        record = LINKDEF % names
        open(outfilename,"w").write(record)
    
    # write setup.sh
    record = '''DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export TNM_PATH=$DIR
export PYTHONPATH=$TNM_PATH/python:$PYTHONPATH
export LD_LIBRARY_PATH=$TNM_PATH/lib:$LD_LIBRARY_PATH
echo "TNM_PATH=$TNM_PATH"
'''
    outfilename = "%s/setup.sh" % filename    
    if not os.path.exists(outfilename) or force:    
        open(outfilename,"w").write(record)

    # write setup.csh
    record = '''set DIR=`pwd`
setenv TNM_PATH ${DIR}
setenv PYTHONPATH ${TNM_PATH}/python:${PYTHONPATH}
setenv LD_LIBRARY_PATH ${TNM_PATH}/lib:${LD_LIBRARY_PATH}
echo "TNM_PATH=${TNM_PATH}"
'''
    outfilename = "%s/setup.csh" % filename
    if not os.path.exists(outfilename) or force:    
        open(outfilename,"w").write(record)        

    # Create python program if one does not yet exist
    COLOR      ="\x1b[0;32;48m"
    RESETCOLOR ="\x1b[0m"
    
    outfilename = "%s/%s.py" % (filename, filename)
    if not os.path.exists(outfilename) or force:
        record = PYTEMPLATE % names
        open(outfilename,"w").write(record)
        os.system("chmod +x %s" % outfilename)

    fname = '%s%s%s' % (COLOR, filename, RESETCOLOR)
    print("\tcreated analysis directory: %s" % fname)
    print("\tdo")
    print("\t  cd %s" % fname)
    print("\t  make")
    print("\tto build shared library libtnm.so\n")
#------------------------------------------------------------------------------
main()
