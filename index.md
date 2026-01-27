---
layout: default
title: Brilliant Moves
---

<h1>Brilliant Move Streak</h1>
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
    padding: 30px;
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

# [Brilliant Move Archive](https://github.com/ibottledo/RecordMyBrilliancy/tree/main)

## 🗓 2025-01-22.
Mr_Creative_69 vs ibottledo <span style="color:#FFFFFF">24... Re1</span>

[→ 탁월수 보기](_posts/2025-01-22-brilliant.md)

---

## 🗓 2025-02-22.
hawynelik vs ibottledo <span style="color:#FFFFFF">38... Qf1+</span>

[→ 탁월수 보기](_posts/2025-02-22-brilliant.md)

---

## 🗓 2025-03-22.
Sershantt vs ibottledo <span style="color:#FFFFFF">11... Nxb4</span>

[→ 탁월수 보기](_posts/2025-03-22-brilliant.md)

---

## 🗓 2025-03-22-2.
ibottledo vs mertosthere <span style="color:#FFFFFF">14. Rxa4</span>

[→ 탁월수 보기](_posts/2025-03-22-brilliant-2.md)

---

## 🗓 2025-03-23.
ibottledo vs sydyata <span style="color:#FFFFFF">27. Rxb7+</span>

[→ 탁월수 보기](_posts/2025-03-23-brilliant.md)

---

## 🗓 2025-03-23-2.
raje23456 vs ibottledo <span style="color:#FFFFFF">17... Qe1+</span>

[→ 탁월수 보기](_posts/2025-03-23-brilliant-2.md)

---

## 🗓 2025-03-24.
Werty937 vs ibottledo <span style="color:#FFFFFF">19... g6</span>

[→ 탁월수 보기](_posts/2025-03-24-brilliant.md)

---

## 🗓 2025-03-27.
Knightlife2 vs ibottledo <span style="color:#FFFFFF">45... Nxf3+</span>

[→ 탁월수 보기](_posts/2025-03-27-brilliant.md)

---

## 🗓 2025-03-27-2.
Skit73 vs ibottledo <span style="color:#FFFFFF">19... Nxh3+</span>

[→ 탁월수 보기](_posts/2025-03-27-brilliant-2.md)

---

## 🗓 2025-03-27-3.
fhnhx vs ibottledo <span style="color:#FFFFFF">17... Rxd4</span>

[→ 탁월수 보기](_posts/2025-03-27-brilliant-3.md)

---

## 🗓 2025-03-28.
ibottledo vs Moin_cp <span style="color:#FFFFFF">20. Nxc6</span>

[→ 탁월수 보기](_posts/2025-03-28-brilliant.md)

---

## 🗓 2025-04-23.
ibottledo vs malaka1802 <span style="color:#FFFFFF">34. Nxb3</span>

[→ 탁월수 보기](_posts/2025-04-23-brilliant.md)

---

## 🗓 2025-04-23-2.
ibottledo vs malaka1802 <span style="color:#FFFFFF">6. Bxf7+</span>

[→ 탁월수 보기](_posts/2025-04-23-brilliant-2.md)

---

## 🗓 2025-04-27.
ibottledo vs jorgo6922 <span style="color:#FFFFFF">23. Qe8+</span>

[→ 탁월수 보기](_posts/2025-04-27-brilliant.md)

---

## 🗓 2025-05-05.
ibottledo vs Bvc578 <span style="color:#FFFFFF">9. Bxf7+</span>

[→ 탁월수 보기](_posts/2025-05-05-brilliant.md)

---

## 🗓 2025-05-05-2.
ibottledo vs Bvc578 <span style="color:#FFFFFF">25. Rxg5</span>

[→ 탁월수 보기](_posts/2025-05-05-brilliant-2.md)

---

## 🗓 2025-05-06.
kmanirudh vs ibottledo <span style="color:#FFFFFF">8... Bxf2+</span>

[→ 탁월수 보기](_posts/2025-05-06-brilliant.md)

---

## 🗓 2025-05-10.
ibottledo vs Pixel_Shader <span style="color:#FFFFFF">23. Rxe6</span>

[→ 탁월수 보기](_posts/2025-05-10-brilliant.md)

---

## 🗓 2025-05-14.
AGeamana vs ibottledo <span style="color:#FFFFFF">25... Nf3+</span>

[→ 탁월수 보기](_posts/2025-05-14-brilliant.md)

---

## 🗓 2025-05-17.
ibottledo vs KetaRahu <span style="color:#FFFFFF">12. Bxh7+</span>

[→ 탁월수 보기](_posts/2025-05-17-brilliant.md)

---

## 🗓 2025-05-20.
Bim_Bam_Boom vs ibottledo <span style="color:#FFFFFF">20... Ng6</span>

[→ 탁월수 보기](_posts/2025-05-20-brilliant.md)

---

## 🗓 2025-06-01.
ibottledo vs NonExizt <span style="color:#FFFFFF">24. Bxe6+</span>

[→ 탁월수 보기](_posts/2025-06-01-brilliant.md)

---

## 🗓 2025-06-03.
ibottledo vs Limaeriton <span style="color:#FFFFFF">7. Bxf7+</span>

[→ 탁월수 보기](_posts/2025-06-03-brilliant.md)

---

## 🗓 2025-06-06.
ibottledo vs drortev <span style="color:#FFFFFF">14. Bxh6</span>

[→ 탁월수 보기](_posts/2025-06-06-brilliant.md)

---

## 🗓 2025-06-07.
Jice05 vs ibottledo <span style="color:#FFFFFF">21... Nxc2</span>

[→ 탁월수 보기](_posts/2025-06-07-brilliant.md)

---

## 🗓 2025-06-13.
ibottledo vs ccd1313 <span style="color:#FFFFFF">16. Bxh6</span>

[→ 탁월수 보기](_posts/2025-06-13-brilliant.md)

---

## 🗓 2025-06-15.
ibottledo vs edcasutedcasut <span style="color:#FFFFFF">21. Nxd6</span>

[→ 탁월수 보기](_posts/2025-06-15-brilliant.md)

---

## 🗓 2025-06-20.
ibottledo vs Oneday200 <span style="color:#FFFFFF">14. Bxf7+</span>

[→ 탁월수 보기](_posts/2025-06-20-brilliant.md)

---

## 🗓 2025-07-04.
denizyelo vs ibottledo <span style="color:#FFFFFF">8... exd3</span>

[→ 탁월수 보기](_posts/2025-07-04-brilliant.md)

---

## 🗓 2025-07-05.
FauziAnwar08 vs ibottledo <span style="color:#FFFFFF">24... Nxd5</span>

[→ 탁월수 보기](_posts/2025-07-05-brilliant.md)

---

## 🗓 2025-07-09.
ibottledo vs anuj6789 <span style="color:#FFFFFF">3. Nxe5</span>

[→ 탁월수 보기](_posts/2025-07-09-brilliant.md)

---

## 🗓 2025-07-17.
ibottledo vs chernota1995 <span style="color:#FFFFFF">10. Bxh7+</span>

[→ 탁월수 보기](_posts/2025-07-17-brilliant.md)

---

## 🗓 2025-07-18.
ibottledo vs mezanates2025 <span style="color:#FFFFFF">32. Re1</span>

[→ 탁월수 보기](_posts/2025-07-18-brilliant.md)

---

## 🗓 2025-07-21.
ibottledo vs yungcashnomoney <span style="color:#FFFFFF">22. Nxc7</span>

[→ 탁월수 보기](_posts/2025-07-21-brilliant.md)

---

## 🗓 2025-07-24.
pramodgupta321 vs ibottledo <span style="color:#FFFFFF">23... Qxh3+</span>

[→ 탁월수 보기](_posts/2025-07-24-brilliant.md)

---

## 🗓 2025-07-25.
ibottledo vs mickako2 <span style="color:#FFFFFF">13. Bxh6</span>

[→ 탁월수 보기](_posts/2025-07-25-brilliant.md)

---

## 🗓 2025-07-28.
ibottledo vs HansHolbein <span style="color:#FFFFFF">9. Bxh7+</span>

[→ 탁월수 보기](_posts/2025-07-28-brilliant.md)

---

## 🗓 2025-07-29.
MmeSoulier vs ibottledo <span style="color:#FFFFFF">18... Qxe5</span>

[→ 탁월수 보기](_posts/2025-07-29-brilliant.md)

---

## 🗓 2025-07-31.
ibottledo vs ganjamafia420 <span style="color:#FFFFFF">19. Nf5</span>

[→ 탁월수 보기](_posts/2025-07-31-brilliant.md)

---

## 🗓 2025-08-02.
mos5mos vs ibottledo <span style="color:#FFFFFF">11... O-O-O</span>

[→ 탁월수 보기](_posts/2025-08-02-brilliant.md)

---

## 🗓 2025-08-02-2.
ibottledo vs kintsugilyo <span style="color:#FFFFFF">22. Rxe7</span>

[→ 탁월수 보기](_posts/2025-08-02-brilliant-2.md)

---

## 🗓 2025-08-06.
ibottledo vs Sergafanio <span style="color:#FFFFFF">20. Nxe6</span>

[→ 탁월수 보기](_posts/2025-08-06-brilliant.md)

---

## 🗓 2025-08-06-2.
ibottledo vs Sergafanio <span style="color:#FFFFFF">22. Qxf8+</span>

[→ 탁월수 보기](_posts/2025-08-06-brilliant-2.md)

---

## 🗓 2025-08-06-3.
ibottledo vs Myrtun <span style="color:#FFFFFF">21. Rxd7+</span>

[→ 탁월수 보기](_posts/2025-08-06-brilliant-3.md)

---

## 🗓 2025-08-10.
Randbauer2 vs ibottledo <span style="color:#FFFFFF">27... Re6+</span>

[→ 탁월수 보기](_posts/2025-08-10-brilliant.md)

---

## 🗓 2025-08-14.
MrcioCrhist vs ibottledo <span style="color:#FFFFFF">12... Bxe4</span>

[→ 탁월수 보기](_posts/2025-08-14-brilliant.md)

---

## 🗓 2025-08-14-2.
seungminyerr vs ibottledo <span style="color:#FFFFFF">21... Bxh3</span>

[→ 탁월수 보기](_posts/2025-08-14-brilliant-2.md)

---

## 🗓 2025-08-14-3.
ibottledo vs sinkobay <span style="color:#FFFFFF">24. Qxe8+</span>

[→ 탁월수 보기](_posts/2025-08-14-brilliant-3.md)

---

## 🗓 2025-08-15.
bobits_fisher vs ibottledo <span style="color:#FFFFFF">15... Qf5</span>

[→ 탁월수 보기](_posts/2025-08-15-brilliant.md)

---

## 🗓 2025-08-17.
ibottledo vs EverTico <span style="color:#FFFFFF">7. Nxf7</span>

[→ 탁월수 보기](_posts/2025-08-17-brilliant.md)

---

## 🗓 2025-08-17-2.
StandingGargoyle vs ibottledo <span style="color:#FFFFFF">22... Bxc3</span>

[→ 탁월수 보기](_posts/2025-08-17-brilliant-2.md)

---

## 🗓 2025-08-21.
ibottledo vs TheRouteOfTheKnight <span style="color:#FFFFFF">23. exf6</span>

[→ 탁월수 보기](_posts/2025-08-21-brilliant.md)

---

## 🗓 2025-08-24.
ibottledo vs marcuskayo <span style="color:#FFFFFF">17. Bxg7</span>

[→ 탁월수 보기](_posts/2025-08-24-brilliant.md)

---

## 🗓 2025-08-24.
ibottledo vs marcuskayo <span style="color:#FFFFFF">16. Bxh6</span>

[→ 탁월수 보기](_posts/2025-08-24-brilliant.md)

---

## 🗓 2025-08-27.
ibottledo vs Ichsan440 <span style="color:#FFFFFF">7. Bxf7+</span>

[→ 탁월수 보기](_posts/2025-08-27-brilliant.md)

---

## 🗓 2025-08-27-2.
ibottledo vs Ichsan440 <span style="color:#FFFFFF">17. Ng5</span>

[→ 탁월수 보기](_posts/2025-08-27-brilliant-2.md)

---

## 🗓 2025-08-27-3.
LRKrolow vs ibottledo <span style="color:#FFFFFF">18... Bxg4</span>

[→ 탁월수 보기](_posts/2025-08-27-brilliant-3.md)

---

## 🗓 2025-08-29.
ibottledo vs anotherstyle15 <span style="color:#FFFFFF">14. Bxd5</span>

[→ 탁월수 보기](_posts/2025-08-29-brilliant.md)

---

## 🗓 2025-08-29-2.
ibottledo vs Colicci2002 <span style="color:#FFFFFF">21. Rxg6+</span>

[→ 탁월수 보기](_posts/2025-08-29-brilliant-2.md)

---

## 🗓 2025-08-30.
ibottledo vs poker_addict <span style="color:#FFFFFF">11. Nxe6</span>

[→ 탁월수 보기](_posts/2025-08-30-brilliant.md)

---

## 🗓 2025-09-01.
Melvernzz vs ibottledo <span style="color:#FFFFFF">14... Bxh3</span>

[→ 탁월수 보기](_posts/2025-09-01-brilliant.md)

---

## 🗓 2025-09-01-2.
Melvernzz vs ibottledo <span style="color:#FFFFFF">15... Bxg2</span>

[→ 탁월수 보기](_posts/2025-09-01-brilliant-2.md)

---

## 🗓 2025-09-01-3.
gdkjm vs ibottledo <span style="color:#FFFFFF">8... Rxe5</span>

[→ 탁월수 보기](_posts/2025-09-01-brilliant-3.md)

---

## 🗓 2025-09-01-4.
ibottledo vs 4llthingsconsidered <span style="color:#FFFFFF">12. Nxe6</span>

[→ 탁월수 보기](_posts/2025-09-01-brilliant-4.md)

---

## 🗓 2025-09-02.
ibottledo vs usedtoplay25 <span style="color:#FFFFFF">19. Rxe4</span>

[→ 탁월수 보기](_posts/2025-09-02-brilliant.md)

---

## 🗓 2025-09-02-2.
ibottledo vs usedtoplay25 <span style="color:#FFFFFF">20. Bxg7</span>

[→ 탁월수 보기](_posts/2025-09-02-brilliant-2.md)

---

## 🗓 2025-09-03.
ibottledo vs TFHand <span style="color:#FFFFFF">9. Bxh7+</span>

[→ 탁월수 보기](_posts/2025-09-03-brilliant.md)

---

## 🗓 2025-09-06.
ibottledo vs antonsoka <span style="color:#FFFFFF">9. Nxf7</span>

[→ 탁월수 보기](_posts/2025-09-06-brilliant.md)

---

## 🗓 2025-09-07.
seungminyerr vs ibottledo <span style="color:#FFFFFF">8... Qxc4</span>

[→ 탁월수 보기](_posts/2025-09-07-brilliant.md)

---

## 🗓 2025-09-07-2.
ibottledo vs MoazMohamed73 <span style="color:#FFFFFF">12. Nf5</span>

[→ 탁월수 보기](_posts/2025-09-07-brilliant-2.md)

---

## 🗓 2025-09-08.
peao_atrevido vs ibottledo <span style="color:#FFFFFF">26... Nxe3</span>

[→ 탁월수 보기](_posts/2025-09-08-brilliant.md)

---

## 🗓 2025-09-08-2.
peao_atrevido vs ibottledo <span style="color:#FFFFFF">30... Rae8</span>

[→ 탁월수 보기](_posts/2025-09-08-brilliant-2.md)

---

## 🗓 2025-09-08-3.
peao_atrevido vs ibottledo <span style="color:#FFFFFF">31... Qf1+</span>

[→ 탁월수 보기](_posts/2025-09-08-brilliant-3.md)

---

## 🗓 2025-09-11.
abbivalli vs ibottledo <span style="color:#FFFFFF">14... Re8</span>

[→ 탁월수 보기](_posts/2025-09-11-brilliant.md)

---

## 🗓 2025-09-14.
BigHorse42 vs ibottledo <span style="color:#FFFFFF">14... Bxh3</span>

[→ 탁월수 보기](_posts/2025-09-14-brilliant.md)

---

## 🗓 2025-09-15.
ibottledo vs 88MLY_AHMED <span style="color:#FFFFFF">26. Nxd5</span>

[→ 탁월수 보기](_posts/2025-09-15-brilliant.md)

---

## 🗓 2025-09-18.
ibottledo vs recursiveneuronnetwork <span style="color:#FFFFFF">16. Bb4</span>

[→ 탁월수 보기](_posts/2025-09-18-brilliant.md)

---

## 🗓 2025-09-20.
cowboy-z1 vs ibottledo <span style="color:#FFFFFF">17... Bxh2+</span>

[→ 탁월수 보기](_posts/2025-09-20-brilliant.md)

---

## 🗓 2025-09-20-2.
neutrinos2102 vs ibottledo <span style="color:#FFFFFF">19... Nd4</span>

[→ 탁월수 보기](_posts/2025-09-20-brilliant-2.md)

---

## 🗓 2025-09-20-3.
ibottledo vs NedoTM <span style="color:#FFFFFF">23. Bxg7</span>

[→ 탁월수 보기](_posts/2025-09-20-brilliant-3.md)

---

## 🗓 2025-09-20-4.
ibottledo vs keval2122 <span style="color:#FFFFFF">15. Nd5</span>

[→ 탁월수 보기](_posts/2025-09-20-brilliant-4.md)

---

## 🗓 2025-09-21.
cyberbabble1 vs ibottledo <span style="color:#FFFFFF">5... Nxd4</span>

[→ 탁월수 보기](_posts/2025-09-21-brilliant.md)

---

## 🗓 2025-09-21-2.
cyberbabble1 vs ibottledo <span style="color:#FFFFFF">6... Nf6</span>

[→ 탁월수 보기](_posts/2025-09-21-brilliant-2.md)

---

## 🗓 2025-09-21-3.
cyberbabble1 vs ibottledo <span style="color:#FFFFFF">7... O-O</span>

[→ 탁월수 보기](_posts/2025-09-21-brilliant-3.md)

---

## 🗓 2025-09-21-4.
Batero vs ibottledo <span style="color:#FFFFFF">22... Qh4</span>

[→ 탁월수 보기](_posts/2025-09-21-brilliant-4.md)

---

## 🗓 2025-09-22.
benblumberg vs ibottledo <span style="color:#FFFFFF">5... Bxf2+</span>

[→ 탁월수 보기](_posts/2025-09-22-brilliant.md)

---

## 🗓 2025-09-22-2.
Vivekhosteller vs ibottledo <span style="color:#FFFFFF">12... Ng3</span>

[→ 탁월수 보기](_posts/2025-09-22-brilliant-2.md)

---

## 🗓 2025-09-22-3.
meemee121 vs ibottledo <span style="color:#FFFFFF">22... Rxh3+</span>

[→ 탁월수 보기](_posts/2025-09-22-brilliant-3.md)

---

## 🗓 2025-09-22-4.
DrMahirKorat vs ibottledo <span style="color:#FFFFFF">18... d3</span>

[→ 탁월수 보기](_posts/2025-09-22-brilliant-4.md)

---

## 🗓 2025-09-23.
ibottledo vs AntooCocon <span style="color:#FFFFFF">20. Qxf5</span>

[→ 탁월수 보기](_posts/2025-09-23-brilliant.md)

---

## 🗓 2025-09-24.
ibottledo vs robertpintilie <span style="color:#FFFFFF">12. Bxh7+</span>

[→ 탁월수 보기](_posts/2025-09-24-brilliant.md)

---

## 🗓 2025-09-24-2.
VDP_Albany vs ibottledo <span style="color:#FFFFFF">11... Nxe4</span>

[→ 탁월수 보기](_posts/2025-09-24-brilliant-2.md)

---

## 🗓 2025-09-24-3.
VDP_Albany vs ibottledo <span style="color:#FFFFFF">12... Rxe4</span>

[→ 탁월수 보기](_posts/2025-09-24-brilliant-3.md)

---

## 🗓 2025-09-24-4.
ibottledo vs Maxim_Dk <span style="color:#FFFFFF">5. Nxe5</span>

[→ 탁월수 보기](_posts/2025-09-24-brilliant-4.md)

---

## 🗓 2025-09-26.
ibottledo vs fabiuk1 <span style="color:#FFFFFF">26. Rxe7+</span>

[→ 탁월수 보기](_posts/2025-09-26-brilliant.md)

---

## 🗓 2025-09-27.
Umid1904 vs ibottledo <span style="color:#FFFFFF">25... Qxf2</span>

[→ 탁월수 보기](_posts/2025-09-27-brilliant.md)

---

## 🗓 2025-09-29.
ibottledo vs chris432 <span style="color:#FFFFFF">20. Rd8+</span>

[→ 탁월수 보기](_posts/2025-09-29-brilliant.md)

---

## 🗓 2025-09-29-2.
ibottledo vs Nieaau <span style="color:#FFFFFF">9. Nxe5</span>

[→ 탁월수 보기](_posts/2025-09-29-brilliant-2.md)

---

## 🗓 2025-09-29-3.
DaniloMolenarov vs ibottledo <span style="color:#FFFFFF">13... Nxe4</span>

[→ 탁월수 보기](_posts/2025-09-29-brilliant-3.md)

---

## 🗓 2025-10-02.
Willouzer vs ibottledo <span style="color:#FFFFFF">14... Qxh3</span>

[→ 탁월수 보기](_posts/2025-10-02-brilliant.md)

---

## 🗓 2025-10-04.
ibottledo vs calynkelly <span style="color:#FFFFFF">10. Rxe5</span>

[→ 탁월수 보기](_posts/2025-10-04-brilliant.md)

---

## 🗓 2025-10-05.
ibottledo vs exello7 <span style="color:#FFFFFF">23. Rxd4</span>

[→ 탁월수 보기](_posts/2025-10-05-brilliant.md)

---

## 🗓 2025-10-07.
Gman007Chessmaster vs ibottledo <span style="color:#FFFFFF">37... Rxf4+</span>

[→ 탁월수 보기](_posts/2025-10-07-brilliant.md)

---

## 🗓 2025-10-11.
ibottledo vs Stily06 <span style="color:#FFFFFF">19. Bxh6</span>

[→ 탁월수 보기](_posts/2025-10-11-brilliant.md)

---

## 🗓 2025-10-12.
ibottledo vs kaushaletchess <span style="color:#FFFFFF">7. Bxf7+</span>

[→ 탁월수 보기](_posts/2025-10-12-brilliant.md)

---

## 🗓 2025-10-12-2.
ibottledo vs kaushaletchess <span style="color:#FFFFFF">23. Rxd7+</span>

[→ 탁월수 보기](_posts/2025-10-12-brilliant-2.md)

---

## 🗓 2025-10-14.
gunrhaizel vs ibottledo <span style="color:#FFFFFF">7... Bxf2+</span>

[→ 탁월수 보기](_posts/2025-10-14-brilliant.md)

---

## 🗓 2025-10-14-2.
gunrhaizel vs ibottledo <span style="color:#FFFFFF">15... f6</span>

[→ 탁월수 보기](_posts/2025-10-14-brilliant-2.md)

---

## 🗓 2025-10-23.
Ivoroconnor vs ibottledo <span style="color:#FFFFFF">11... Qh4</span>

[→ 탁월수 보기](_posts/2025-10-23-brilliant.md)

---

## 🗓 2025-10-24.
ibottledo vs thisisadrien <span style="color:#FFFFFF">24. Ne5</span>

[→ 탁월수 보기](_posts/2025-10-24-brilliant.md)

---

## 🗓 2025-10-26.
ibottledo vs Jef47 <span style="color:#FFFFFF">21. Bxb6</span>

[→ 탁월수 보기](_posts/2025-10-26-brilliant.md)

---

## 🗓 2025-10-27.
ibottledo vs BhawaneshDixit <span style="color:#FFFFFF">28. Rxh6+</span>

[→ 탁월수 보기](_posts/2025-10-27-brilliant.md)

---

## 🗓 2025-10-28.
ibottledo vs Costa_Ezra <span style="color:#FFFFFF">9. Bxh7+</span>

[→ 탁월수 보기](_posts/2025-10-28-brilliant.md)

---

## 🗓 2025-11-02.
ibottledo vs Lord_Tareq <span style="color:#FFFFFF">8. Nxd5</span>

[→ 탁월수 보기](_posts/2025-11-02-brilliant.md)

---

## 🗓 2025-11-07.
ibottledo vs Paradox_05 <span style="color:#FFFFFF">8. Bxh7+</span>

[→ 탁월수 보기](_posts/2025-11-07-brilliant.md)

---

## 🗓 2025-11-14.
ibottledo vs cacahotflu <span style="color:#FFFFFF">15. Bxh6</span>

[→ 탁월수 보기](_posts/2025-11-14-brilliant.md)

---

## 🗓 2025-11-14-2.
ibottledo vs PhilbyOz <span style="color:#FFFFFF">26. Rxg5+</span>

[→ 탁월수 보기](_posts/2025-11-14-brilliant-2.md)

---

## 🗓 2025-11-19.
ibottledo vs Elmunecon <span style="color:#FFFFFF">19. Rxf6</span>

[→ 탁월수 보기](_posts/2025-11-19-brilliant.md)

---

## 🗓 2025-11-19-2.
ibottledo vs d_ln <span style="color:#FFFFFF">26. Ndb5+</span>

[→ 탁월수 보기](_posts/2025-11-19-brilliant-2.md)

---

## 🗓 2025-11-21.
nirakar23 vs ibottledo <span style="color:#FFFFFF">4... Nxd4</span>

[→ 탁월수 보기](_posts/2025-11-21-brilliant.md)

---

## 🗓 2025-11-22.
ibottledo vs niusha20 <span style="color:#FFFFFF">8. Nxc6</span>

[→ 탁월수 보기](_posts/2025-11-22-brilliant.md)

---

## 🗓 2025-11-25.
salawda vs ibottledo <span style="color:#FFFFFF">21... Bxh3</span>

[→ 탁월수 보기](_posts/2025-11-25-brilliant.md)

---

## 🗓 2025-11-25-2.
salawda vs ibottledo <span style="color:#FFFFFF">26... Rf8+</span>

[→ 탁월수 보기](_posts/2025-11-25-brilliant-2.md)

---

## 🗓 2025-11-27.
MrAzurite vs ibottledo <span style="color:#FFFFFF">26... Qxf1+</span>

[→ 탁월수 보기](_posts/2025-11-27-brilliant.md)

---

## 🗓 2025-11-27-2.
Aquiles_Vaesa vs ibottledo <span style="color:#FFFFFF">20... Qe1+</span>

[→ 탁월수 보기](_posts/2025-11-27-brilliant-2.md)

---

## 🗓 2025-11-29.
ayushbarai vs ibottledo <span style="color:#FFFFFF">17... Nxg4</span>

[→ 탁월수 보기](_posts/2025-11-29-brilliant.md)

---

## 🗓 2025-12-02.
McCakeIV vs ibottledo <span style="color:#FFFFFF">16... Rxe6</span>

[→ 탁월수 보기](_posts/2025-12-02-brilliant.md)

---

## 🗓 2025-12-02-2.
McCakeIV vs ibottledo <span style="color:#FFFFFF">20... Bxh2+</span>

[→ 탁월수 보기](_posts/2025-12-02-brilliant-2.md)

---

## 🗓 2025-12-04.
ibottledo vs Carlos8327 <span style="color:#FFFFFF">18. Nd5</span>

[→ 탁월수 보기](_posts/2025-12-04-brilliant.md)

---

## 🗓 2025-12-04-2.
ibottledo vs Carlos8327 <span style="color:#FFFFFF">19. Bc4</span>

[→ 탁월수 보기](_posts/2025-12-04-brilliant-2.md)

---

## 🗓 2025-12-07.
ibottledo vs Capt416B <span style="color:#FFFFFF">8. Bxh7+</span>

[→ 탁월수 보기](_posts/2025-12-07-brilliant.md)

---

## 🗓 2025-12-10.
ibottledo vs diegofoca <span style="color:#FFFFFF">11. Nxe6</span>

[→ 탁월수 보기](_posts/2025-12-10-brilliant.md)

---

## 🗓 2025-12-10-2.
ibottledo vs willswg <span style="color:#FFFFFF">7. O-O</span>

[→ 탁월수 보기](_posts/2025-12-10-brilliant-2.md)

---

## 🗓 2025-12-11.
ibottledo vs alzwen3535 <span style="color:#FFFFFF">11. Bxa6</span>

[→ 탁월수 보기](_posts/2025-12-11-brilliant.md)

---

## 🗓 2025-12-11-2.
ibottledo vs alzwen3535 <span style="color:#FFFFFF">15. d5</span>

[→ 탁월수 보기](_posts/2025-12-11-brilliant-2.md)

---

## 🗓 2025-12-12.
Shuggy94 vs ibottledo <span style="color:#FFFFFF">25... Qf1+</span>

[→ 탁월수 보기](_posts/2025-12-12-brilliant.md)

---

## 🗓 2025-12-17.
JAVAS02 vs ibottledo <span style="color:#FFFFFF">18... Rxe3</span>

[→ 탁월수 보기](_posts/2025-12-17-brilliant.md)

---

## 🗓 2025-12-17-2.
ibottledo vs paulinhomiranda <span style="color:#FFFFFF">9. Bxh7+</span>

[→ 탁월수 보기](_posts/2025-12-17-brilliant-2.md)

---

## 🗓 2025-12-17-3.
ibottledo vs paulinhomiranda <span style="color:#FFFFFF">15. Nf6+</span>

[→ 탁월수 보기](_posts/2025-12-17-brilliant-3.md)

---

## 🗓 2026-01-01.
ibottledo vs iPossible <span style="color:#FFFFFF"></span>

[→ 탁월수 보기](_posts/2026-01-01-brilliant.md)

---

## 🗓 2026-01-03.
ibottledo vs suunny54 <span style="color:#FFFFFF">27. Bxb6</span>

[→ 탁월수 보기](_posts/2026-01-03-brilliant.md)

---

## 🗓 2026-01-12.
Nooks00 vs ibottledo <span style="color:#FFFFFF">22... Rd1+</span>

[→ 탁월수 보기](_posts/2026-01-12-brilliant.md)

---

## 🗓 2026-01-13.
gigig2022 vs ibottledo <span style="color:#FFFFFF">4... Nxe4</span>

[→ 탁월수 보기](_posts/2026-01-13-brilliant.md)

---

## 🗓 2026-01-14.
ibottledo vs TheOceanClub <span style="color:#FFFFFF">6. Bxf7+</span>

[→ 탁월수 보기](_posts/2026-01-14-brilliant.md)

---

## 🗓 2026-01-14-2.
ibottledo vs TheOceanClub <span style="color:#FFFFFF">19. Ne5+</span>

[→ 탁월수 보기](_posts/2026-01-14-brilliant-2.md)

---

## 🗓 2026-01-14-3.
ibottledo vs Wagnerlogan <span style="color:#FFFFFF">12. Bxb5</span>

[→ 탁월수 보기](_posts/2026-01-14-brilliant-3.md)

---

## 🗓 2026-01-15.
Blunder_Muki vs ibottledo <span style="color:#FFFFFF">15... Bxh2+</span>

[→ 탁월수 보기](_posts/2026-01-15-brilliant.md)

---

## 🗓 2026-01-16.
ibottledo vs Tooombucket <span style="color:#FFFFFF">14. Qxc7</span>

[→ 탁월수 보기](_posts/2026-01-16-brilliant.md)

---

## 🗓 2026-01-16-2.
ibottledo vs Tooombucket <span style="color:#FFFFFF">16. Qd8+</span>

[→ 탁월수 보기](_posts/2026-01-16-brilliant-2.md)

---

## 🗓 2026-01-16-3.
ibottledo vs Denizenofmultiworld <span style="color:#FFFFFF">24. b5</span>

[→ 탁월수 보기](_posts/2026-01-16-brilliant-3.md)

---

## 🗓 2026-01-16-4.
ibottledo vs Denizenofmultiworld <span style="color:#FFFFFF">25. axb5</span>

[→ 탁월수 보기](_posts/2026-01-16-brilliant-4.md)

---

## 🗓 2026-01-17.
gorlammi vs ibottledo <span style="color:#FFFFFF">27... Rxa2</span>

[→ 탁월수 보기](_posts/2026-01-17-brilliant.md)

---

