#!/bin/bash

# chmod +x run_links.sh 권한부여

# 실행 간격 (초)
DELAY=180

# URL 목록 (원하면 여기에 쭉 추가)
URLS=(
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/140315635840?move=15&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/140358074676?move=47&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/140501326904?move=4&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/ded65578-5ff5-11f0-9493-59c71301000f?move=12&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/3b3072f8-6311-11f0-9493-59c71301000f?move=18&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/140817067548?move=62&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/6c156fd0-65dc-11f0-91b1-f23cba01000f?move=42&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/f438a2ef-689a-11f0-9493-59c71301000f?move=45&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/51d84409-6916-11f0-91b1-f23cba01000f?move=24&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/141193615078?move=16&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/d697fdd4-6c4a-11f0-91b1-f23cba01000f?move=35&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/d0a051fa-6dd3-11f0-8c00-fdf47001000f?move=36&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/6e855072-6f51-11f0-8c00-fdf47001000f?move=21&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/42451fef-6f92-11f0-89e5-c5b76a01000f?move=42&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/aa9b5895-72c0-11f0-94aa-f4632301000f?move=38&tab=review"
    "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/aa9b5895-72c0-11f0-94aa-f4632301000f?move=42&tab=review"
)

# 반복 실행
for url in "${URLS[@]}"; do
    echo "Running with: $url"
    ./bin/Record_My_Brilliancy <<< "$url"
    echo "Waiting $DELAY seconds..."
    sleep $DELAY
done