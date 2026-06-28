import os
import glob

# 1. 원하는 버전의 기본 경로 설정
base_dir = "/pnfs/knu.ac.kr/data/cms/store/user/junghyun/ttHH2017UL_fullNano_v20"

# 2. 찾고자 하는 데이터셋 목록
datasets = [
    "BTagCSV/BTagCSV_Run2017B",
    "JetHT/JetHT_Run2017F",
    "TTToHadronic_TuneCP5_13TeV-powheg-pythia8/TTbar_Hadronic"
]

found_files = []

for dataset in datasets:
    # 하위 폴더의 타임스탬프/0000 상관없이 모든 slimmedNtuple_*.root 파일을 재귀적으로 찾음
    search_pattern = os.path.join(base_dir, dataset, "**", "slimmedNtuple_*.root")
    
    # recursive=True 옵션으로 ** 패턴 적용
    files = glob.glob(search_pattern, recursive=True)
    
    if files:
        # 파일이 여러 개일 수 있으니, 각 데이터셋당 무작위로 하나(혹은 첫 번째)만 선택
        found_files.append(files[0])
    else:
        print(f"⚠️ 경로에서 파일을 찾지 못했습니다: {dataset}")

# 3. 파일들을 모두 찾았다면 명령어 조합 및 출력
if found_files:
    command = "mkvariables.py --merge " + " ".join(found_files) + " --tree Events"
    
    print("\n✅ [생성된 명령어]")
    print("-" * 80)
    print(command)
    print("-" * 80)
    
    # (선택) 여기서 바로 명령어를 실행하고 싶다면 아래 주석을 해제하세요.
    # os.system(command)
else:
    print("❌ 실행할 .root 파일이 없습니다.")
