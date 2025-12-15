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

#### 📄 `variables.txt`의 역할

이 파일은 **Analyzer 생성의 설계도(Blueprint)** 역할을 합니다.

- **ROOT 파일의 실제 구조 반영:** `mkvariables.py` 실행 시점에 존재하는 Branch들만 기록됩니다.
    
- **데이터 타입 정의:** 각 Branch가 `float`, `int`, `vector<float>` 등으로 매핑되는 정보를 담고 있습니다.
    
- **Leaf Counter 연결:** 배열(Vector)형 변수의 크기를 결정하는 Counter 변수(`nJet` 등)를 연결합니다.
    

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

이전 버전에서는 존재하지 않는 Branch를 읽으려 할 때 **경고(Warning)**만 발생하고, 해당 변수가 **0으로 초기화된 상태(Ghost Objects)**로 분석이 진행되는 위험이 있었습니다.

이를 방지하기 위해, **데이터가 없으면 즉시 프로그램을 종료하고, 불필요한 초기화를 하지 않도록** 코드를 수정하였습니다.

### 1. `src/treestream.cc` 수정

Branch가 존재하지 않을 경우, 경고 대신 **Fatal Error**를 발생시켜 프로그램을 강제 종료합니다.

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

### ✅ 이 변경으로 인한 효과

1. **Ghost Object 방지:** 실제 데이터가 없는데도 `pT=0`인 입자가 존재하는 것처럼 루프가 도는 현상이 사라집니다.
    
2. **명확한 에러:** `variables.txt`에는 정의되어 있으나 실제 ROOT 파일에 해당 Branch가 없으면, 분석 시작 즉시 에러 메시지와 함께 종료되므로 문제를 바로 파악할 수 있습니다.

