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



## 🛠️ 상세 사용 가이드 (Detailed Usage Guide)

이 패키지를 사용하여 안전한 Analyzer를 생성하는 표준 워크플로우는 다음과 같습니다.

### 1. 변수 정의 파일 생성 (`mkvariables.py`)

ROOT Ntuple 파일을 스캔하여 분석에 사용할 Branch 목록(`variables.txt`)을 생성합니다.

Bash

```
# 사용법
python3 bin/mkvariables.py <Input_ROOT_File> [Tree_Name(s)]

# 예시
python3 bin/mkvariables.py my_ntuple.root Events
```

    
- **Leaf Counter 연결:** 배열(Vector)형 변수의 크기를 결정하는 Counter 변수(`nJet` 등)를 연결합니다.
    
#### 📄 `variables.txt`의 역할

이 파일은 **Analyzer 생성의 설계도(Blueprint)** 역할을 합니다. `mkanalyzer.py`는 이 파일을 참조하여 C++ 코드를 작성합니다.

- **ROOT 파일의 실제 구조 반영:** `mkvariables.py` 실행 시점에 **실제로 존재하는 Branch**들만 기록됩니다.
    
- **데이터 타입 매핑:** `float`, `int`, `vector<float>` 등 각 Branch의 C++ 데이터 타입을 정의합니다.
    
- **Leaf Counter 연결:** 배열(Vector)형 변수의 크기를 제어하는 Counter 변수(`nJet` 등)를 연결합니다.

---

### 2. 분석기 코드 생성 (`mkanalyzer.py`)

`variables.txt`를 기반으로 C++ 분석 코드(`eventBuffer.h`, `Analyzer.cc` 등)를 자동으로 생성합니다.

Bash

```
# 사용법
python3 bin/mkanalyzer.py <Project_Name> <Variables_File>

# 예시
python3 bin/mkanalyzer.py MyAnalyzer variables.txt
```

이 단계가 완료되면 `MyAnalyzer/` 디렉토리가 생성되며, 내부에 컴파일 가능한 C++ 프레임워크가 준비됩니다.

---

## 🚨 중요 변경 사항: 데이터 무결성 강화 (Fail-Fast Mechanism)
이전 버전의 treestream은 존재하지 않는 Branch를 요청했을 때 **경고(Warning)**만 출력하고, 해당 변수를 **0으로 초기화(Zero-Initialization)**하여 분석을 강행했습니다. 이는 **"Ghost Object" (실제로는 없는데 값이 0인 입자)**를 만들어내어 분석 결과에 치명적인 오류를 줄 수 있습니다.

이를 방지하기 위해 **"데이터가 없으면 즉시 종료(Crash)"**하도록 소스 코드를 수정했습니다.

### 1. `src/treestream.cc` 수정

ROOT 파일에서 Branch를 찾지 못했을 때, 경고 대신 Fatal Error를 발생시킵니다. 그리고 프로그램이 강제 종료됩니다.

**변경 전 (Warning only):**

C++

```
// ... (Lines near 950)
else
{
  warning("itreestream - branch " + namen + " not found"); // 경고만 출력
  _statuscode = kBADBRANCH;
}
```

**변경 후 (Fatal Error):**

C++

```
// ...
else
{
  // [CRITICAL UPDATE] Branch 부재 시 즉시 종료하여 Ghost Object 생성 방지
  fatal("itreestream - CRITICAL ERROR: Branch '" + namen + "' not found! Aborting."); 
}
```

---

### 2. `bin/mkanalyzer.py` 수정

`eventBuffer.h`를 생성할 때, 벡터 변수들을 강제로 `0`으로 초기화하는 코드를 제거(주석 처리)하였습니다. 이로 인해 데이터가 없을 때 벡터 크기가 `0`인 상태로 유지되어, 잘못된 루프 진입을 원천 차단합니다.

**변경 내용 (Lines around 630-650):**

Python

```
# ...
        else:
            # this is either a vector or a variable length array
            if str.find(rtype, 'vector') > -1:
                # VECTOR
                # ... (type parsing logic) ...
                
                declarevec.append("  %s\t%s;" % (rtype, varname))
                
                # [CRITICAL UPDATE 1] 강제 초기화 코드 주석 처리 (Ghost Vector 방지)
                # init.append("    %s\t= %s(%d, (%s)0);" % \
                #         (varname, rtype, count, vtype))
                
            else:
                # VARIABLE LENGTH ARRAY
                declarevec.append("  std::vector<%s>\t%s;" % (rtype, varname))
                
                # [CRITICAL UPDATE 2] 강제 초기화 코드 주석 처리
                # init.append("    %s\t= std::vector<%s>(%d,0);" % \
                #             (varname, rtype, count))
                
                if countername == None:
                    # ...
```

### 3. 파싱 로직 수정 (Branch 이름에 `/`가 들어갈 때 에러 해결)

- **위치:** `bin/mkanalyzer.py` 약 860번째 줄 근처 (`for index, tns in enumerate(tokens):` 바로 아래)
    

#### ❌ [변경 전] (기존 코드)

Python

```
        # check for leafcounter
        has_leafcounter = len(tns) == 5
        if has_leafcounter:
            rtype, branchname, varname, count, countername = tns
        elif len(tns) == 4:
            rtype, branchname, varname, count = tns
            countername = None
        else:
            sys.exit('''
 ** mkanalyzer.py ***
            missing maximum count at end of record:
            %s
            ''' % tns)
```

#### ✅ [변경 후] (수정된 코드 - 복사해서 위 부분을 덮어쓰세요)

Python

```
        # --------------------------------------------------------------------
        # [Fix] Handle Branch names containing '/' (e.g., Events/BranchName)
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
```

---


### ✅ 결과: 생성되는 코드 (`eventBuffer.h - 구조체`)의 변화

위 변경 사항 덕분에, `mkanalyzer.py`로 생성된 `eventBuffer.h`의 `initBuffers()` 함수는 더 이상 위험한 초기화를 수행하지 않습니다.

**[Before: 위험한 코드]** Branch가 없어도 벡터가 25개짜리 `[0, 0, ..., 0]` 배열이 됨 → **루프가 25번 돌면서 가짜 입자 분석.**

C++

```
// eventBuffer.h (기존 방식)
void initBuffers() {
  FatJet_pt = std::vector<float>(25, 0); // ⚠️ 위험: 강제로 0으로 채워짐
  Jet_pt    = std::vector<float>(50, 0);
}
```

**[After: 안전한 코드]** 초기화 코드가 제거됨. 데이터가 없으면 벡터 크기는 `0`. 만약 코드에서 접근하려 하면 **Index Out of Range** 혹은 `treestream`의 **Fatal Error**로 인해 즉시 멈춤.

C++

```
// eventBuffer.h (현재 방식)
void initBuffers() {
  // 🔒 안전: 아무런 강제 초기화를 하지 않음.
  // 데이터가 로드되지 않으면 vector.size() == 0 상태 유지.
}
```

### ✅ 결과: 생성되는 코드(`treestream.cc - 엔진`)의 변화
변화: Branch가 없으면 fatal() 함수를 호출하여 분석을 즉시 중단합니다.

효과: 잘못된 데이터나 Ntuple 버전 불일치를 즉시 감지합니다.


## ⚡ 기존 Analyzer 업데이트 및 샘플 변경 시 대응 방법

이미 만들어둔 Analyzer가 있거나, **새로운 Ntuple 샘플(Branch가 추가/변경됨)**을 분석해야 할 경우, 전체 프로젝트를 다시 만들 필요 없이 **핵심 파일만 덮어쓰면 됩니다.**

1. **새로운 변수 목록 생성:**

2. **새로운 버퍼 코드 생성 (임시 폴더 등 활용):**

3. **파일 이식 (Copy & Replace):** 생성된 `TempProject` 폴더에서 아래 3개 파일만 기존 분석 작업 폴더로 복사해 넣으십시오.

    - `src/treestream.cc` (수정된 안전장치 엔진)

    - `include/treestream.h` (헤더)

    - `include/eventBuffer.h` (새로운 Branch 구조 및 초기화 방지 적용됨)


> **Note:** 이렇게 하면 기존에 작성한 분석 로직(`MyAnalyzer.cc` 등)은 유지하면서, 변경된 Ntuple 구조와 안전장치를 즉시 적용할 수 있습니다.


# Future update 목록
1. mkanalyzer안에 보면 CMSSW_BASE가 있으면 NtupleMaker라는 모듈에서부터 위 라이브리러 동작을 시도함. 이러면 찾지를 못함. 실제론 scram 안했으니까. 따라서 주석 처리 필요 아래처럼.
```python
####if "CMSSW_BASE" in os.environ:
####    CMSSW_BASE     = os.environ["CMSSW_BASE"]
####    PACKAGE        = "%s/src/PhysicsTools/TheNtupleMaker" % CMSSW_BASE
####    TREESTREAM_HPP = "%s/interface/treestream.h" % PACKAGE
####    TREESTREAM_CPP = "%s/src/treestream.cc"  % PACKAGE
####
####    TNM_HPP = "%s/tnm/tnm.h"  % PACKAGE
####    TNM_CPP = "%s/tnm/tnm.cc" % PACKAGE
####    TNM_PY  = "%s/tnm/tnm.py" % PACKAGE
```

2. 

기존 Makefile은 
```Makefile
# check for clang++, otherwise use g++

COMPILER := $(shell which clang++)

ifneq ($(COMPILER),)
CXX := /usr/bin/clang++
LD := /usr/bin/clang++

else
CXX := g++
LD := g++

endif
CPPFLAGS := -I. -I$(incdir)
CXXFLAGS := -O -Wall -fPIC -g -ansi -Wshadow -Wextra \

$(shell root-config --cflags)

LDFLAGS := -g
```

이와 같은 논리를 가짐. 문제는 CMSSW 환경에선 clang이 있어서 COMPILER가 true 값이 될 수 있지만 위치가 cvmfs이지 `/usr/bin/clang++`이 아님. 즉 위 로직이 에러를 일으킨다는 것.

따라서 사용자가 직접 컴파일러를 선택할 수 있도록 코드를 아래처럼 바꾸었음
```Makefile
# Build libtreestream.so
# Created 27 Feb 2013 HBP & SS
#         30 May 2015 HBP - standardize structure (src, lib, include)
#         12 Sep 2022 HBP - use TREESTREAM_PREFIX as installation area and
#                           allow installation only if the variable is defined
# ----------------------------------------------------------------------------

# [USER OPTION] Select Compiler: 'gcc' or 'clang'
# You can override this via command line: make COMPILER_SELECT=clang
##COMPILER_SELECT := clang
COMPILER_SELECT := gcc

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

SRCS	:=  	$(srcdir)/treestream.cc \
		$(srcdir)/pdg.cc \
		$(srcdir)/testme.cc

CINTSRCS	:= $(wildcard $(srcdir)/*_dict.cc)

OTHERSRCS	:= $(filter-out $(CINTSRCS) $(SRCS),$(wildcard $(srcdir)/*.cc))

# list of dictionaries to be created
DICTIONARIES	:= $(SRCS:.cc=_dict.cc)

# get list of objects
OBJECTS		:= $(SRCS:.cc=.o) $(OTHERSRCS:.cc=.o) $(DICTIONARIES:.cc=.o)

PYVER	:= $(shell python --version | cut -d' ' -f2)
PY1	:= $(shell echo "$(PYVER)"  | cut -d. -f1)
PY2	:= $(shell echo "$(PYVER)"  | cut -d. -f2)
PYTHONLIB	:= python$(PY1).$(PY2)

#say := $(shell echo "DICTIONARIES:     $(DICTIONARIES)" >& 2)
#say := $(shell echo "" >& 2)
#say := $(shell echo "SRCS: $(SRCS)" >& 2)
#say := $(shell echo "PYTHON_LIB: $(PYTHONLIB)" >& 2)
#$(error bye)
# ----------------------------------------------------------------------------
ROOTCINT	:= rootcint

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
OS := $(shell uname -s)
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
all: $(LIBRARY) $(TESTS)

ifdef TREESTREAM_PREFIX
install:
	cp $(bindir)/mk*.py $(TREESTREAM_PREFIX)/bin
	cp $(incdir)/treestream.h $(TREESTREAM_PREFIX)/include
	cp $(incdir)/pdg.h $(TREESTREAM_PREFIX)/include
	cp $(libdir)/lib$(NAME)$(LDEXT) $(TREESTREAM_PREFIX)/lib
	find $(libdir) -name "*.pcm" -exec cp {} $(TREESTREAM_PREFIX)/lib \;
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
	$(ROOTCINT)	-f $@ -c $(CPPFLAGS) $^
	find $(srcdir) -name "*.pcm" -exec mv {} $(libdir) \;


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
```

동작은 아래처럼 하면 됨

### 사용법 요약

1. **기본 (g++) 사용 시:**
```bash
make
```
2. **clang 사용 시:**
```bash
make COMPILER_SELECT=clang
```


