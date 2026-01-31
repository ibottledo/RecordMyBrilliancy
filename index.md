---
layout: default
title: Main Page
---

<div>
  {% include streak.html %}
</div>

<div style="margin-top: 16px;"></div>

---

<link rel="stylesheet" as="style" crossorigin href="https://cdn.jsdelivr.net/gh/orioncactus/pretendard@v1.3.9/dist/web/static/pretendard.min.css" />

<style>
  /* 스타일 정의 */
  .brilliant-container {
    font-family: 'Pretendard', -apple-system, BlinkMacSystemFont, system-ui, Roboto, sans-serif;
    max-width: 600px;
    margin: 20px auto;
    padding: 30px 30px 12px 30px;
    border-radius: 16px;
    background: #ffffff;
    box-shadow: 0 10px 25px rgba(0, 0, 0, 0.05); /* 부드러운 그림자 */
    border: 1px solid #eaeaea;
    text-align: center;
  }

  .brilliant-container h2 {
    margin: 0 0 10px 0;
    font-size: 22px;
    font-weight: 700;
    color: #333;
  }

  .brilliant-container p {
    color: #666;
    font-size: 15px;
    margin-bottom: 24px;
    line-height: 1.5;
  }

  .input-group {
    display: flex;
    gap: 10px;
    justify-content: center;
  }

  /* 입력창 스타일 */
  #chess-url {
    flex: 1;
    padding: 12px 16px;
    font-size: 15px;
    border: 1px solid #ddd;
    border-radius: 8px;
    outline: none;
    transition: all 0.2s;
    font-family: inherit;
  }

  #chess-url:focus {
    border-color: #8FD9E5;
    box-shadow: 0 0 0 3px rgba(76, 175, 80, 0.1);
  }

  /* 버튼 스타일 */
  #submit-button {
    padding: 12px 24px;
    font-size: 15px;
    font-weight: 600;
    color: white;
    background-color: #3894A5;
    border: none;
    border-radius: 8px;
    cursor: pointer;
    transition: background-color 0.2s;
    font-family: inherit;
    white-space: nowrap;
  }

  #submit-button:hover {
    background-color: #8FD9E5;
  }

  #submit-button:disabled {
    background-color: #ccc;
    cursor: not-allowed;
  }

  /* 상태 메시지 */
  #status-message {
    margin-top: 16px;
    font-size: 14px;
    min-height: 20px;
  }

  /* 모바일 대응 */
  @media (max-width: 480px) {
    .input-group {
      flex-direction: column;
    }
    #submit-button {
      width: 100%;
    }
  }
</style>

<div class="brilliant-container">
  <p>Chess.com 탁월한 수 URL을 입력하세요.</p>
  
  <div class="input-group">
    <input type="text" id="chess-url" placeholder="https://www.chess.com/analysis/game/..." autocomplete="off">
    <button onclick="submitBrilliantMove()" id="submit-button">기록하기</button>
  </div>
  
  <div id="status-message"></div>
</div>

<script>
  // 스크립트는 기존 로직 유지 (UI 조작 부분만 약간 다듬음)
  async function submitBrilliantMove() {
    const urlInput = document.getElementById('chess-url');
    const messageElement = document.getElementById('status-message');
    const submitButton = document.getElementById('submit-button');
    const originalBtnText = submitButton.textContent;

    const url = urlInput.value.trim();
    
    // 초기화
    messageElement.textContent = '';
    messageElement.style.color = '#333';

    if (!url || !url.includes('chess.com')) {
      messageElement.innerHTML = '⚠️ Chess.com URL을 정확히 입력해주세요.';
      messageElement.style.color = '#e74c3c';
      return;
    }

    // 로딩 상태
    submitButton.disabled = true;
    submitButton.textContent = '처리 중...';
    urlInput.disabled = true;

    try {
      const apiEndpoint = 'https://record-my-brilliancy.vercel.app/api/add-move'; // TODO: 주소 확인
      const response = await fetch(apiEndpoint, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ url: url }),
      });

      const result = await response.json();

      if (response.status === 202) {
        messageElement.innerHTML = '✅ <b>요청 성공!</b> 약 1분 뒤 반영됩니다.';
        messageElement.style.color = '#27ae60';
        urlInput.value = '';
      } else {
        messageElement.textContent = `❌ 오류: ${result.message}`;
        messageElement.style.color = '#e74c3c';
      }
    } catch (error) {
      messageElement.textContent = `❌ 네트워크 오류: ${error.message}`;
      messageElement.style.color = '#e74c3c';
    } finally {
      submitButton.disabled = false;
      submitButton.textContent = originalBtnText;
      urlInput.disabled = false;
      urlInput.focus();
    }
  }
</script>

---
{% for post in site.posts reversed %}
---

## 🗓 {{ post.date | date: "%Y-%m-%d" }}.
{% if post.white_player and post.black_player and post.pgn %}
{{ post.white_player }} vs {{ post.black_player }} <span style="color:#FFFFFF">{{ post.pgn }}</span>
{% else %}
{%- assign first_line = post.content | strip_newlines | split: '\n' | first -%}
{%- assign players = first_line | remove: '[' | split: ']' | first -%}
{{ players }}
{% endif %}

[→ 탁월수 보기]({{ site.baseurl }}{{ post.url }})
{% endfor %}

