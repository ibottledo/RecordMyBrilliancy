import json
import os
import re

def update_config_yml(file_path, key, value):
    # Read the file
    with open(file_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    updated = False
    for i, line in enumerate(lines):
        # Use regex to match key at the beginning of the line, ignoring leading spaces
        if re.match(rf"^\s*{key}:", line):
            lines[i] = f"{key}: {value}\n"
            updated = True
            break
    
    # If key not found, append it (e.g., for baseurl if it wasn't there)
    if not updated:
        if not lines or not lines[-1].endswith('\n'): # Ensure last line has a newline if file is empty or doesn't end with one
            lines.append('\n')
        lines.append(f"{key}: {value}\n")
        updated = True

    if updated:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.writelines(lines)
        return True
    return False

def main():
    print("🚀 RecordMyBrilliancy 설정 스크립트를 시작합니다.")
    print("체스닷컴 사용자 이름, 깃허브 정보를 입력해주세요.")

    # 사용자 정보 입력받기
    chess_username = input("Enter your Chess.com username: ").strip()
    github_username = input("Enter your GitHub username: ").strip()
    github_repo = input("Enter your GitHub repository name (e.g., RecordMyBrilliancy): ").strip()
    author_name = input("Enter your name (for blog author): ").strip()
    author_email = input("Enter your email (for blog author): ").strip()

    print("-" * 40)
    print("입력된 정보:")
    print(f"Chess.com Username: {chess_username}")
    print(f"GitHub Username: {github_username}")
    print(f"GitHub Repo: {github_repo}")
    print(f"Author Name: {author_name}")
    print(f"Author Email: {author_email}")
    print("-" * 40)

    confirm = input("이 정보가 맞습니까? (y/n) ").strip().lower()
    if confirm != 'y':
        print("설정을 취소했습니다.")
        return

    # 1. config.json 파일 생성
    print("⚙️  config.json 파일을 생성하는 중...")
    config_data = {
        "chess_username": chess_username,
        "github_username": github_username,
        "github_repo": github_repo,
        "author_name": author_name,
        "author_email": author_email
    }
    with open('config.json', 'w', encoding='utf-8') as f:
        json.dump(config_data, f, indent=2, ensure_ascii=False)
    print("✅ config.json 파일 생성 완료.")

    # 2. _config.yml 파일 업데이트
    print("⚙️  _config.yml 파일을 업데이트하는 중...")
    config_yml_path = '_config.yml'

    # Update existing keys or add if not present
    update_config_yml(config_yml_path, "title", github_repo)
    update_config_yml(config_yml_path, "author", author_name)
    update_config_yml(config_yml_path, "email", author_email)
    update_config_yml(config_yml_path, "baseurl", f"\"/{github_repo}\"") # baseurl needs quotes in YAML

    print("✅ _config.yml 파일 업데이트 완료.")

    print("🎉 모든 설정이 완료되었습니다!")
    print("다음 단계를 위해 README.md 파일을 확인해주세요.")

if __name__ == "__main__":
    main()
