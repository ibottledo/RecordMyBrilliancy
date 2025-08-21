#!/bin/bash

# chmod +x run_links.sh 권한부여

# 실행 간격 (초)
DELAY=180

# URL 목록 (원하면 여기에 쭉 추가)
URLS=(
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/141879128848?move=46&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/141908710966?move=29&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/141976811756?move=12&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/141985809832?move=43&tab=review"
)

# 반복 실행
for url in "${URLS[@]}"; do
    echo "Running with: $url"
    ./bin/Record_My_Brilliancy <<< "$url"

    remaining=$DELAY
    while [ $remaining -gt 0 ]; do
        echo "Waiting $remaining seconds..."
        if [ $remaining -ge 10 ]; then
            sleep 10
            remaining=$((remaining - 10))
        else
            sleep $remaining
            remaining=0
        fi
    done
done

echo "All URLs processed!"