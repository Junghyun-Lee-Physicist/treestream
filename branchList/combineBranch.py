import os

# 1. 파일 이름 정의
file_names = ["MC.txt", "Data_B.txt", "Data_C.txt"]

# 변수들을 담을 딕셔너리 (Key: 변수명, Value: 원본 전체 라인)
# 딕셔너리를 쓰면 자동으로 중복된 변수명은 하나만 남게 됩니다.
unique_lines = {}

print("파일 합치는 중...")

for fname in file_names:
    if os.path.exists(fname):
        with open(fname, 'r', encoding='utf-8') as f:
            for line in f:
                line = line.strip()
                
                # 'type/Events/변수명/...' 형식이 포함된 줄만 처리
                if "/Events/" in line:
                    parts = line.split('/')
                    # parts[2]가 변수명 (예: Electron_pt)
                    if len(parts) >= 3:
                        var_name = parts[2]
                        
                        # 딕셔너리에 넣기 (이미 있으면 덮어쓰거나 무시됨 -> 중복 제거 효과)
                        # 여기서는 가장 마지막에 읽은 파일의 형식을 따르게 됩니다.
                        unique_lines[var_name] = line

# 2. 변수명(알파벳) 순서로 정렬
sorted_vars = sorted(unique_lines.keys())

# 3. 결과 파일로 저장
output_file = "Total_Merged_List.txt"
with open(output_file, 'w', encoding='utf-8') as f:
    f.write(f"Total Combined Variables: {len(sorted_vars)}\n")
    f.write("-" * 50 + "\n")
    for var in sorted_vars:
        f.write(unique_lines[var] + "\n")

print(f"완료! 모든 변수를 합쳐서 '{output_file}'에 저장했습니다.")
print(f"총 {len(sorted_vars)}개의 변수가 정리되었습니다.")
