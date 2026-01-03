from gitingest import ingest
import sys

def split_content_by_files(content):
    """
    GitIngest의 단일 content 문자열을 개별 파일 블록 리스트로 분리합니다.
    구분자: ================================================
    """
    separator = "=" * 48
    # 구분자로 분리 (첫 번째 요소는 보통 공백이거나 비어있음)
    parts = content.split(separator)
    
    files = []
    i = 1
    while i < len(parts) - 1:
        # 구조상 parts[odd]는 "FILE: 이름", parts[even]은 "소스코드 내용"
        header_part = parts[i]
        body_part = parts[i+1]
        
        if "FILE:" in header_part:
            # 파일 하나를 온전한 문자열로 복원
            full_block = f"{separator}{header_part}{separator}{body_part}"
            files.append(full_block)
            i += 2
        else:
            # 만약 코드 안에 구분자가 들어있어서 잘못 잘린 경우 (예외 처리)
            # 이전 파일 내용에 붙여버림
            if files:
                files[-1] += f"{separator}{header_part}"
            i += 1
            
    return files

def save_chunked_source(prefix, summary, tree, content, max_size_kb):
    """
    소스 코드를 max_size_kb 단위로 나누어 저장합니다. (파일 중간 절단 방지)
    """
    # 1. 개별 파일 단위로 분리
    file_blocks = split_content_by_files(content)
    
    # 2. 헤더 생성 (모든 분할 파일에 포함될 공통 정보)
    common_header = f"{summary}\n\n{tree}\n\n"
    
    current_chunk_idx = 1
    current_content = ""
    current_size = 0
    max_chars = max_size_kb * 1024 # 대략적인 문자 수로 변환 (1KB ~ 1024 char)

    print(f"   ℹ️  총 {len(file_blocks)}개의 소스 파일을 {max_size_kb}KB 단위로 패킹합니다.")

    for block in file_blocks:
        # 헤더 크기를 포함하여 예상 크기 계산
        estimated_size = len(common_header) + len(current_content) + len(block)
        
        # 현재 덩어리가 꽉 찼으면 저장하고 비움
        if current_content and estimated_size > max_chars:
            filename = f"{prefix}-source-{current_chunk_idx}.txt"
            with open(filename, "w", encoding="utf-8") as f:
                f.write(common_header + current_content)
            print(f"      📄 {filename} 생성 완료 ({len(current_content)//1024} KB)")
            
            current_chunk_idx += 1
            current_content = ""
        
        current_content += block

    # 남은 내용 저장
    if current_content:
        filename = f"{prefix}-source-{current_chunk_idx}.txt"
        with open(filename, "w", encoding="utf-8") as f:
            f.write(common_header + current_content)
        print(f"      📄 {filename} 생성 완료 ({len(current_content)//1024} KB)")


def main():
    print("==========================================")
    print("   GitIngest Smart Split Generator v2.0")
    print("==========================================")
    
    # 1. 프로젝트 이름 입력
    prefix = input("👉 생성할 파일의 이름을 입력하세요 (예: week7): ").strip()
    if not prefix:
        print("❌ 이름이 입력되지 않았습니다.")
        return

    # 2. 분할 크기 입력 (옵션)
    size_input = input("👉 소스 파일 분할 크기(KB)를 입력하세요 (0 또는 엔터: 분할 안 함): ").strip()
    max_size_kb = int(size_input) if size_input.isdigit() else 0

    print(f"\n🚀 '{prefix}' 프로젝트 분석 시작...\n")

    # ---------------------------------------------------------
    # PART 1: Structure Only (*-structure.txt)
    # ---------------------------------------------------------
    print(f"1️⃣  [Structure] 구조 파일 생성 중...")
    try:
        s, t, _ = ingest(".") 
        filename = f"{prefix}-structure.txt"
        with open(filename, "w", encoding="utf-8") as f:
            f.write(s + "\n" + t)
        print(f"   ✅ {filename} 완료")
    except Exception as e:
        print(f"   ❌ 오류 발생: {e}")

    # ---------------------------------------------------------
    # PART 2: Settings & Resources (*-setting.txt)
    # ---------------------------------------------------------
    print(f"2️⃣  [Settings] 설정 및 리소스 파일 생성 중...")
    try:
        setting_patterns = [
            "CMake*", "*.json", "*.md", ".clang-format",
            "*.cmake", "cmake/*", "*.vert", "*.frag", "*.html"
        ]
        s, t, c = ingest(".", include_patterns=setting_patterns)
        filename = f"{prefix}-setting.txt"
        with open(filename, "w", encoding="utf-8") as f:
            f.write(f"{s}\n\n{t}\n\n{c}")
        print(f"   ✅ {filename} 완료")
    except Exception as e:
        print(f"   ❌ 오류 발생: {e}")

    # ---------------------------------------------------------
    # PART 3: Source Code (*-source.txt or split)
    # ---------------------------------------------------------
    print(f"3️⃣  [Source] 핵심 소스 코드 생성 중...")
    try:
        source_patterns = [
            "source/*.cpp", "source/*.hpp", "source/*.h",
            "*.cpp", "*.hpp", "*.h"
        ]
        exclude_settings = ["CMake*", "cmake/*", "*.json", "*.md"]
        
        s, t, c = ingest(".", include_patterns=source_patterns, exclude_patterns=exclude_settings)
        
        if max_size_kb > 0:
            # 분할 저장 모드
            save_chunked_source(prefix, s, t, c, max_size_kb)
        else:
            # 기존 통파일 저장 모드
            filename = f"{prefix}-source.txt"
            with open(filename, "w", encoding="utf-8") as f:
                f.write(f"{s}\n\n{t}\n\n{c}")
            print(f"   ✅ {filename} 완료")
            
    except Exception as e:
        print(f"   ❌ 오류 발생: {e}")

    print("\n✨ 모든 작업이 완료되었습니다!")

if __name__ == "__main__":
    main()