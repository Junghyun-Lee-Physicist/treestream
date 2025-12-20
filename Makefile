# Build libtreestream.so
# Created 27 Feb 2013 HBP & SS
#         30 May 2015 HBP - standardize structure (src, lib, include)
#         12 Sep 2022 HBP - use TREESTREAM_PREFIX as installation area
# ----------------------------------------------------------------------------
# 2025-12-19 (Jh.Lee)
# - Added argument support for manual OS and compiler selection.
# - Switched to rootcling for ROOT 6 compatibility.
# - Explicitly defaults to python3 (customizable via PYTHON_CMD).
# - Updated clean/uninstall targets to remove test executables and installed files.
#
# [Usage Examples]
# ! Before compling, please use $source setup.sh !
#   1. Default Build (Auto-detect OS, use python3):
#      $ make
#
#   2. Force specific OS or Compiler:
#      $ make OS_SELECT=macos
#      $ make COMPILER_SELECT=clang
#
#   3. Use specific Python version:
#      $ make PYTHON_CMD=python3.9
#
#   4. Install (requires TREESTREAM_PREFIX or CONDA_PREFIX set):
#      $ make install
# ----------------------------------------------------------------------------

UNAME_S := $(shell uname -s)

# Select OS: linux or macos
# You can override this via command line: make OS_SELECT=macos
ifndef OS_SELECT
ifeq ($(UNAME_S),Darwin)
OS_SELECT := macos
else
OS_SELECT := linux
endif
endif

$(info [Makefile] OS_SELECT=$(OS_SELECT) (uname -s=$(UNAME_S)))

# Map OS_SELECT to an OS string used throughout the Makefile
ifeq ($(OS_SELECT),macos)
OS := Darwin
else
OS := Linux
endif

# Auto-select compiler from OS_SELECT (still overridable if needed)
ifndef COMPILER_SELECT
ifeq ($(OS_SELECT),macos)
COMPILER_SELECT := clang
else
COMPILER_SELECT := gcc
endif
endif

ifndef ROOTSYS
$(error *** Please set up Root)
endif

ifndef TREESTREAM_PREFIX
ifdef CONDA_PREFIX
TREESTREAM_PREFIX := $(CONDA_PREFIX)
endif
endif

# ----------------------------------------------------------------------------
NAME	:= treestream
incdir	:= include
srcdir	:= src
libdir	:= lib
bindir	:= bin
testdir	:= test

SRCTESTS:= \
$(testdir)/testtreestream.cc \
$(testdir)/testdelphes.cc \
$(testdir)/testvector.cc

OBJTESTS:= $(SRCTESTS:.cc=.o)
TESTS	:= $(SRCTESTS:.cc=)

$(shell mkdir -p lib)

# get lists of sources

SRCS	:= 	$(srcdir)/treestream.cc \
		$(srcdir)/pdg.cc \
		$(srcdir)/testme.cc

CINTSRCS	:= $(wildcard $(srcdir)/*_dict.cc)

OTHERSRCS	:= $(filter-out $(CINTSRCS) $(SRCS),$(wildcard $(srcdir)/*.cc))

# list of dictionaries to be created
DICTIONARIES	:= $(SRCS:.cc=_dict.cc)

# get list of objects
OBJECTS		:= $(SRCS:.cc=.o) $(OTHERSRCS:.cc=.o) $(DICTIONARIES:.cc=.o)

# ----------------------------------------------------------------------------
# Python Configuration
# ----------------------------------------------------------------------------
# Use python3 by default. Override with: make PYTHON_CMD=python3.9
PYTHON_CMD ?= python3

PYVER	:= $(shell $(PYTHON_CMD) --version 2>&1 | cut -d' ' -f2)
PY1	:= $(shell echo "$(PYVER)" | cut -d. -f1)
PY2	:= $(shell echo "$(PYVER)" | cut -d. -f2)
PYTHONLIB	:= python$(PY1).$(PY2)

# ----------------------------------------------------------------------------
# Select dictionary generator: prefer rootcling (ROOT 6+), fallback to rootcint
ROOT_DICT_GEN := $(shell command -v rootcling >/dev/null 2>&1 && echo rootcling || echo rootcint)

# check for clang++, otherwise use g++
ifeq ($(COMPILER_SELECT),clang)
CXX		:= clang++
LD		:= clang++
else
CXX		:= g++
LD		:= g++
endif

CPPFLAGS	:= -I. -I$(incdir)
CXXFLAGS	:= -O -Wall -fPIC -g -ansi -Wshadow -Wextra \
$(shell root-config --cflags)
LDFLAGS		:= -g
# ----------------------------------------------------------------------------
# which operating system?
ifeq ($(OS),Darwin)
	LDFLAGS += -dynamiclib
	LDEXT	:= .dylib
else
	LDFLAGS	+= -shared
	LDEXT	:= .so
endif


LDFLAGS += $(ROOTFLAGS) -Wl,-rpath,$(ROOTSYS)/lib
LIBS 	:= $(shell root-config --libs)
LIBRARY	:= $(libdir)/lib$(NAME)$(LDEXT)
# ----------------------------------------------------------------------------
.PHONY: all install tidy clean uninstall

all: $(LIBRARY) $(TESTS)

ifdef TREESTREAM_PREFIX
install:
	cp $(bindir)/mk*.py $(TREESTREAM_PREFIX)/bin
	cp $(incdir)/treestream.h $(TREESTREAM_PREFIX)/include
	cp $(incdir)/pdg.h $(TREESTREAM_PREFIX)/include
	cp $(libdir)/lib$(NAME)$(LDEXT) $(TREESTREAM_PREFIX)/lib
	find $(libdir) -name "*.pcm" -exec cp {} $(TREESTREAM_PREFIX)/lib \;
	mkdir -p $(TREESTREAM_PREFIX)/lib/$(PYTHONLIB)/site-packages
	cp treestream.py $(TREESTREAM_PREFIX)/lib/$(PYTHONLIB)/site-packages
endif


$(LIBRARY)	: $(OBJECTS)
	@echo ""
	@echo "=> Linking shared library $@"
	$(LD) $(LDFLAGS) $^ $(LIBS)  -o $@

$(OBJECTS)	: %.o	: 	%.cc
	@echo ""
	@echo "=> Compiling $<"
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(DICTIONARIES)	: $(srcdir)/%_dict.cc	: $(incdir)/%.h $(srcdir)/%_linkdef.h
	@echo ""
	@echo "=> Building dictionary $@"
	$(ROOT_DICT_GEN)	-f $@ -c $(CPPFLAGS) $^
	find $(srcdir) -name "*.pcm" -exec mv {} $(libdir) \; 2>/dev/null || true


$(OBJTESTS)	: %.o	:	%.cc
	@echo ""
	@echo "=> Compiling $<"
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@


$(TESTS)	: %	:	%.o	$(LIBRARY)
	@echo ""
	@echo "=> Linking test program $@"
	$(LD) $(ROOTFLAGS) $^ -L$(libdir) -l$(NAME) $(LIBS) -o $@


tidy:
	rm -rf $(srcdir)/*_dict*.* $(srcdir)/*.o $(testdir)/*.o

clean:
	# Clean lib, src objects, and now test objects as well
	rm -rf $(libdir)/* $(srcdir)/*_dict*.* $(srcdir)/*.o $(testdir)/*.o
	rm -f $(TESTS) $(OBJTESTS)

ifdef TREESTREAM_PREFIX
uninstall:
	rm -rf $(libdir)/* $(srcdir)/*_dict*.* $(srcdir)/*.o
	rm -rf $(TESTS) $(OBJTESTS)
	rm -rf $(TREESTREAM_PREFIX)/lib/*$(NAME)*
	rm -rf $(TREESTREAM_PREFIX)/lib/pdg_*.pcm
	rm -rf $(TREESTREAM_PREFIX)/include/*$(NAME)*
	rm -rf $(TREESTREAM_PREFIX)/include/pdg.h
	rm -rf $(TREESTREAM_PREFIX)/lib/$(PYTHONLIB)/site-packages/$(NAME).py
endif
