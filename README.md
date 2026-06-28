# treestream

ROOT `TTree`를 읽고 쓰는 가벼운 C++/Python 인터페이스 + **코드 생성기**.
ntuple(주로 **CMS NanoAOD**, **Delphes**)을 스캔해 모든 branch를 기술한
`variables.txt`를 만들고, 그것으로 바로 컴파일 가능한 C++ analyzer(안전한
`eventBuffer` 포함)를 생성한다. 이 브랜치(`forTTHH_v1`)는 scram 패키지가 아니라
일반 `make`로 repo 안에서 빌드하며(standalone build), 실행에 필요한 **Python 3 /
ROOT 6 / 컴파일러**는 **CMSSW_14_2_1**(`cmsenv`)이 제공한다 — conda나 외부 prefix는
쓰지 않는다.

> 내부 동작·데이터 모델·설계 근거·이슈 이력 등 **깊은 설명은 [`docs/`](docs/)** 에 있다 →
> [design](docs/design.md) · [troubleshooting](docs/troubleshooting.md) ·
> [decisions](docs/decisions.md) · [STATUS](docs/STATUS.md) · [CHANGELOG](docs/CHANGELOG.md).
> 문서 색인은 [`docs/README.md`](docs/README.md).

---

## 빠른 명령어 (Quick commands)

### 0) 환경 설정 · 빌드

```bash
# (1) CMSSW 환경 = ROOT 6 + Python 3 + 컴파일러 (conda/외부 prefix 불필요)
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsrel CMSSW_14_2_1
cd CMSSW_14_2_1/src
cmsenv

# (2) fork를 받아 '그 자리에서' 빌드 — make install / TREESTREAM_PREFIX 불필요
git clone -b forTTHH_v1 https://github.com/Junghyun-Lee-Physicist/treestream.git
cd treestream
source setup.sh   # PATH/PYTHONPATH/LD_LIBRARY_PATH/TREESTREAM_PATH 를 이 repo로 설정
make              # cmsenv가 잡아준 ROOTSYS 로 빌드
```

> CMSSW에 이미 들어있는 treestream을 쓰거나 conda로 ROOT를 까는 방식이 **아니다**.
> CMSSW는 ROOT/Python 제공자로만 쓰고, 모듈은 GitHub fork에서 직접 받아 그 자리에서 빌드·실행한다.

### 1) `variables.txt` 만들기 — 모든 branch의 청사진

```bash
# (a) 단일 파일
mkvariables.py data.root Events

# (b) 여러 샘플 합치기(Super-Set): Data/MC가 서로 다른 branch를 가지므로 "합집합"을 만든다
mkvariables.py --merge mc.root data_B.root data_C.root --tree Events -o variables.txt
```

`--merge`는 입력 파일들을 모두 스캔해 branch의 **합집합**을 계산하고
`[COMMON]`/`[ONLY:…]`/`[PARTIAL:…]` 주석이 달린 `variables.txt`를 쓴다.
**왜 합치는지**는 아래 [§ --merge를 쓰는 이유](#--merge를-쓰는-이유-실제-예시)에서 설명한다.

### 2) `variables.txt`로 생성하기 — 둘 중 하나

```bash
# (A) eventBuffer.h '만' 만들기 (기존 프로젝트의 버퍼만 교체할 때)
mkeventbuffer.py variables.txt                     # -> ./eventBuffer.h
mkeventbuffer.py test/fatjet.root --tree Delphes   # root 파일에서 스캔+생성 한 번에
mkeventbuffer.py --merge mc.root data.root --tree Events -o eventBuffer.h

# (B) 전체 스켈레톤 analyzer 만들기
mkanalyzer.py MyAnalyzer variables.txt             # MyAnalyzer/ 패키지 생성
cd MyAnalyzer && source setup.sh && make
./MyAnalyzer filelist.txt output.root              # filelist.txt = 입력 .root 경로 목록
```

`mkeventbuffer.py`의 출력은 `mkanalyzer.py`가 쓰는 `eventBuffer.h`와 **바이트 단위로 동일**하다
(전체 생성기를 그대로 구동한 뒤 `eventBuffer.h`만 남기는 래퍼이기 때문 —
[decisions D7](docs/decisions.md#d7--eventbuffer-only-as-a-separate-wrapper-not-a---buffer-only-flag)).

---

## `--merge`를 쓰는 이유 (실제 예시)

**문제.** CMS 분석은 branch 집합이 서로 다른 여러 샘플을 한 analyzer로 돌려야 한다.
MC에만 있는 gen-level branch(`GenPart_*`, `Electron_genPartIdx`, `genWeight` …),
Data에만 있는 filter flag, 그리고 **같은 해라도 data-taking period마다 다른 trigger menu**가
있다. 어떤 한 파일만 스캔해 `variables.txt`를 만들면, 그 파일에 없는 branch는
`eventBuffer`에 아예 선언되지 않아 **다른 샘플에서 변수를 놓치게** 된다.

**해결.** branch 집합이 다를 수 있는 **모든 종류에서 대표 파일을 하나씩** 골라
`--merge`로 합집합 `variables.txt`를 만든다. 그러면 모든 변수가 버퍼에 선언되고,
런타임에는 `eventBuffer`가 각 branch를 `present()`로 확인해 **없는 branch는 안전하게
건너뛴다**(스칼라는 `0`, 벡터는 빈 상태). 시작 시 **Branch Access Report**가 어떤 branch가
연결/누락됐는지 출력하므로, 어떤 값이 진짜이고 어떤 값이 기본값(0)인지 알 수 있다.
(런타임 동작·초기화·ghost object 방지는 [design §3–§6](docs/design.md#3-the-super-set-strategy).)

**실제로 쓴 명령어** (ttHH 2017UL, 대표 파일 = Data 2017B + Data 2017F + TTToHadronic MC):

```bash
BASE=/pnfs/knu.ac.kr/data/cms/store/user/junghyun/ttHH2017UL_fullNano_v20

mkvariables.py --merge \
  $BASE/BTagCSV/BTagCSV_Run2017B/.../slimmedNtuple_1.root \
  $BASE/JetHT/JetHT_Run2017F/.../slimmedNtuple_2.root \
  $BASE/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/TTbar_Hadronic/.../slimmedNtuple_3.root \
  --tree Events -o variables.txt
```

- 여기서 세 종류(Data 두 period + Hadronic MC)는 branch 집합이 서로 다를 수 있어 각각 한 파일씩 넣는다.
  같은 종류 안에서는 branch가 균일하다고 보고 한 파일이면 충분하다.
- 위 경로들을 손으로 적기 번거로우면 **`makingCommand.py`** 를 쓴다: `base_dir`와 dataset
  하위경로 목록을 적으면 각 dataset에서 `slimmedNtuple_*.root`를 하나씩 glob해
  완성된 `mkvariables.py --merge … --tree Events` 명령어를 출력해 준다.

---

## 개념 한눈에

- **`variables.txt`** — 모든 branch의 청사진(타입·트리경로·카운터). `mkvariables.py`가 생성, `mkanalyzer.py`/`mkeventbuffer.py`가 소비. 포맷: [design §8](docs/design.md#8-the-variablestxt-format-contract).
- **`eventBuffer`** — `variables.txt`로 생성되는 C++ 버퍼. branch ↔ 변수 바인딩. 없는 branch는 `present()`로 건너뜀(스칼라 0 / 벡터 빈 상태). 자세히: [design §4–§6](docs/design.md#4-runtime-presence--the-generated-eventbuffer).
- **Super-Set / `--merge`** — Data/MC/period의 branch 합집합. 자세히: [design §3](docs/design.md#3-the-super-set-strategy).
- **초기화·ghost object 방지, two-layer safety, 메모리** — [design §5–§6](docs/design.md#5-initialization--the-ghost-object-problem).
- **이슈/검증 이력** — [troubleshooting](docs/troubleshooting.md). **결정/근거** — [decisions](docs/decisions.md). **현재 상태** — [STATUS](docs/STATUS.md).

---

## 요구사항

- 실행에 필요한 **ROOT 6 · Python 3 · C++ 컴파일러**는 **CMSSW_14_2_1**으로 한 번에 충족된다
  (`source /cvmfs/cms.cern.ch/cmsset_default.sh` → `cmsrel CMSSW_14_2_1` → `cmsenv`).
- treestream 자체는 **scram 패키지가 아니다** — 일반 `make`로 repo 안에서 빌드하고
  `source setup.sh`로 그 자리에서 쓴다. **conda · 외부 prefix · `make install` 불필요.**

## 로컬 테스트 (실제 잡 제출 전 검증)

```bash
# 1. 라이브러리 self-test (make 후)
cd test && ./testtreestream && ./testvector && ./testdelphes

# 2. 엔드투엔드 스모크 테스트 — 번들 샘플 test/fatjet.root (트리 이름 = Delphes)
source setup.sh
mklist.py test/fatjet.root                  # 트리명/branch 먼저 확인
mkvariables.py test/fatjet.root Delphes
mkanalyzer.py SmokeTest variables.txt
cd SmokeTest && source setup.sh && make
echo "$PWD/../test/fatjet.root" > filelist.txt
./SmokeTest filelist.txt smoke.root
rootls smoke.root
```

## 빌드 설정 (요약)

```bash
make           # 빌드 (cmsenv가 설정한 ROOTSYS 사용)
make clean     # 빌드 산출물 제거
```

주요 환경변수: `ROOTSYS`(= `cmsenv`가 설정) · `TREESTREAM_PATH`(= `source setup.sh`가 설정).
`make install` / `TREESTREAM_PREFIX` / `CONDA_PREFIX`는 이 워크플로에서 쓰지 않는다(설치 없이 in-place 사용).

## 기존 analyzer 업데이트

ntuple 구조가 바뀌면 **버퍼만** 재생성하면 된다(분석 로직 `MyAnalyzer.cc`는 보존):

1. 새 샘플로 `mkvariables.py`(또는 `--merge`) 실행
2. `mkeventbuffer.py variables.txt` 로 `eventBuffer.h`만 다시 만들거나, `mkanalyzer.py TempProject variables.txt` 후 `include/eventBuffer.h`(필요시 `include/treestream.h`, `src/treestream.cc`)를 프로젝트로 복사
3. `make clean && make`

---

원저자: Harrison B. Prosper (FSU / CERN CMS) ·
이 브랜치 유지: Junghyun Lee (junghyun.lee@cern.ch) ·
변경 이력: [docs/CHANGELOG.md](docs/CHANGELOG.md)
