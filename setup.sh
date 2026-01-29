#!/bin/bash

echo "🚀 RecordMyBrilliancy 설정 스크립트를 시작합니다."
echo "체스닷컴 사용자 이름, 깃허브 정보를 입력해주세요."

# 사용자 정보 입력받기
read -p "Enter your Chess.com username: " chess_username
read -p "Enter your GitHub username: " github_username
read -p "Enter your GitHub repository name (e.g., RecordMyBrilliancy): " github_repo
read -p "Enter your name (for blog author): " author_name
read -p "Enter your email (for blog author): " author_email

echo "----------------------------------------"
echo "입력된 정보:"
echo "Chess.com Username: $chess_username"
echo "GitHub Username: $github_username"
echo "GitHub Repo: $github_repo"
echo "Author Name: $author_name"
echo "Author Email: $author_email"
echo "----------------------------------------"
read -p "이 정보가 맞습니까? (y/n) " confirm

if [ "$confirm" != "y" ]; then
    echo "설정을 취소했습니다."
    exit 1
fi

# 1. config.json 파일 생성
echo "⚙️  config.json 파일을 생성하는 중..."
cat > config.json << EOL
{
  "chess_username": "$chess_username",
  "github_username": "$github_username",
  "github_repo": "$github_repo",
  "author_name": "$author_name",
  "author_email": "$author_email"
}
EOL
echo "✅ config.json 파일 생성 완료."

# 2. _config.yml 파일 업데이트
echo "⚙️  _config.yml 파일을 업데이트하는 중..."

# sed를 사용하여 값 변경 (macOS와 Linux 호환성을 위해 -i 뒤에 '' 추가)
sed -i '' "s/^title: .*/title: $github_repo/" _config.yml
sed -i '' "s/^author: .*/author: $author_name/" _config.yml
sed -i '' "s/^email: .*/email: $author_email/" _config.yml

# baseurl이 있는지 확인하고 없으면 추가, 있으면 변경
if grep -q "^baseurl:" _config.yml; then
    sed -i '' "s|^baseurl:.*|baseurl: \"/$github_repo\"|" _config.yml
else
    # Ensure _config.yml ends with a newline before appending
    [[ -n "$(tail -c 1 "_config.yml")" ]] && echo >> "_config.yml"
    echo "baseurl: \"/$github_repo\"" >> _config.yml
fi

echo "🎉 모든 설정이 완료되었습니다!"
echo "다음 단계를 위해 README.md 파일을 확인해주세요."
