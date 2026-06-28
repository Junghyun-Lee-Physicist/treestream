# ----------------------------------------------------------------------------
# Makefile for libtreestream
#
# Created:  27-Feb-2013  Harrison B. Prosper & Sezen Sekmen
# Updated:  30-May-2015  HBP - standardize structure (src, lib, include)
#           12-Sep-2022  HBP - use TREESTREAM_PREFIX as installation area
# ----------------------------------------------------------------------------
# Updated:  Junghyun Lee <junghyun.lee@cern.ch>
#           Dec-2025  JhLee - User-selectable compiler (gcc/clang)
#                           - CONDA_PREFIX fallback for TREESTREAM_PREFIX
#                           - Fix clang path issue in CMSSW environments
#           Mar-2026  JhLee - Clean up debug comments
#                           - Add python3 detection with fallback
#                           - Consolidate clean/tidy targets
# ----------------------------------------------------------------------------

# ---- User Options ----------------------------------------------------------
# Select compiler: 'gcc' (default) or 'clang'
# Override via command line:  make COMPILER_SELECT=clang
COMPILER_SELECT := gcc

# ---- Prerequisites ---------------------------------------------------------
ifndef ROOTSYS
$(error *** ROOTSYS not set. Please set up ROOT first.)
endif

ifndef TREESTREAM_PREFIX
ifdef CONDA_PREFIX
TREESTREAM_PREFIX := $(CONDA_PREFIX)
endif
endif

# ---- Project Layout --------------------------------------------------------
NAME    := treestream
incdir  := include
srcdir  := src
libdir  := lib
bindir  := bin
testdir := test

$(shell mkdir -p $(libdir))

# ---- Sources ---------------------------------------------------------------
SRCS := $(srcdir)/treestream.cc \
        $(srcdir)/pdg.cc \
        $(srcdir)/testme.cc

CINTSRCS     := $(wildcard $(srcdir)/*_dict.cc)
OTHERSRCS    := $(filter-out $(CINTSRCS) $(SRCS),$(wildcard $(srcdir)/*.cc))
DICTIONARIES := $(SRCS:.cc=_dict.cc)
OBJECTS      := $(SRCS:.cc=.o) $(OTHERSRCS:.cc=.o) $(DICTIONARIES:.cc=.o)

# ---- Tests -----------------------------------------------------------------
SRCTESTS := $(testdir)/testtreestream.cc \
            $(testdir)/testdelphes.cc \
            $(testdir)/testvector.cc

OBJTESTS := $(SRCTESTS:.cc=.o)
TESTS    := $(SRCTESTS:.cc=)

# ---- Python version detection (for install target) -------------------------
PYVER     := $(shell python3 --version 2>/dev/null | cut -d' ' -f2 || \
               python --version 2>&1 | cut -d' ' -f2)
PY1       := $(shell echo "$(PYVER)" | cut -d. -f1)
PY2       := $(shell echo "$(PYVER)" | cut -d. -f2)
PYTHONLIB := python$(PY1).$(PY2)

# ---- Toolchain -------------------------------------------------------------
ROOTCINT := rootcint

ifeq ($(COMPILER_SELECT),clang)
CXX := clang++
LD  := clang++
else
CXX := g++
LD  := g++
endif

CPPFLAGS := -I. -I$(incdir)
CXXFLAGS := -O2 -Wall -fPIC -g -std=c++17 -Wshadow -Wextra \
            $(shell root-config --cflags)
LDFLAGS  := -g

# ---- Platform detection ----------------------------------------------------
OS := $(shell uname -s)
ifeq ($(OS),Darwin)
    LDFLAGS += -dynamiclib
    LDEXT   := .dylib
else
    LDFLAGS += -shared
    LDEXT   := .so
endif

LDFLAGS += -Wl,-rpath,$(ROOTSYS)/lib
LIBS    := $(shell root-config --libs)
LIBRARY := $(libdir)/lib$(NAME)$(LDEXT)

# ---- Build Targets ---------------------------------------------------------
.PHONY: all lib tests install uninstall clean tidy

all: $(LIBRARY) $(TESTS)

lib: $(LIBRARY)

tests: $(TESTS)

# ---- Shared Library --------------------------------------------------------
$(LIBRARY): $(OBJECTS)
	@echo ""
	@echo "=> Linking shared library $@"
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

$(OBJECTS): %.o: %.cc
	@echo ""
	@echo "=> Compiling $<"
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(DICTIONARIES): $(srcdir)/%_dict.cc: $(incdir)/%.h $(srcdir)/%_linkdef.h
	@echo ""
	@echo "=> Building dictionary $@"
	$(ROOTCINT) -f $@ -c $(CPPFLAGS) $^
	@find $(srcdir) -name "*.pcm" -exec mv {} $(libdir) \;

# ---- Test Programs ---------------------------------------------------------
$(OBJTESTS): %.o: %.cc
	@echo ""
	@echo "=> Compiling $<"
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(TESTS): %: %.o $(LIBRARY)
	@echo ""
	@echo "=> Linking test program $@"
	$(LD) $^ -L$(libdir) -l$(NAME) $(LIBS) -o $@

# ---- Install / Uninstall ---------------------------------------------------
ifdef TREESTREAM_PREFIX
install:
	@echo "=> Installing to $(TREESTREAM_PREFIX)"
	@cp $(bindir)/mk*.py $(TREESTREAM_PREFIX)/bin
	@cp $(incdir)/treestream.h $(TREESTREAM_PREFIX)/include
	@cp $(incdir)/pdg.h $(TREESTREAM_PREFIX)/include
	@cp $(libdir)/lib$(NAME)$(LDEXT) $(TREESTREAM_PREFIX)/lib
	@find $(libdir) -name "*.pcm" -exec cp {} $(TREESTREAM_PREFIX)/lib \;
	@cp treestream.py $(TREESTREAM_PREFIX)/lib/$(PYTHONLIB)/site-packages 2>/dev/null || true
	@echo "=> Done."

uninstall:
	rm -f $(TREESTREAM_PREFIX)/lib/*$(NAME)*
	rm -f $(TREESTREAM_PREFIX)/lib/pdg_*.pcm
	rm -f $(TREESTREAM_PREFIX)/include/treestream.h
	rm -f $(TREESTREAM_PREFIX)/include/pdg.h
	rm -f $(TREESTREAM_PREFIX)/lib/$(PYTHONLIB)/site-packages/$(NAME).py
	rm -f $(TREESTREAM_PREFIX)/bin/mk*.py
else
install:
	$(error *** Set TREESTREAM_PREFIX or CONDA_PREFIX before 'make install')
uninstall:
	$(error *** Set TREESTREAM_PREFIX or CONDA_PREFIX before 'make uninstall')
endif

# ---- Clean -----------------------------------------------------------------
clean:
	rm -f $(libdir)/*
	rm -f $(srcdir)/*_dict*.*
	rm -f $(srcdir)/*.o
	rm -f $(testdir)/*.o
	rm -f $(TESTS)

tidy:
	rm -f $(srcdir)/*_dict*.*
	rm -f $(srcdir)/*.o
	rm -f $(testdir)/*.o
