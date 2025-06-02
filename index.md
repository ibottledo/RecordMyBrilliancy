---
layout: default
title: Brilliant Moves
---
layout: default
title: RecordMyBrilliancy
---

# 🧠 My Brilliancy Streak

<div class="streak-grid"></div>

<style>
  .streak-grid {
    display: grid;
    grid-template-columns: repeat(53, 14px);
    grid-auto-rows: 14px;
    gap: 4px;
    margin-top: 20px;
  }

  .day {
    width: 14px;
    height: 14px;
    background-color: #ebedf0;
    border-radius: 3px;
  }

  .day.active-1 { background-color: #a5d8ff; }
  .day.active-2 { background-color: #4dabf7; }
  .day.active-3 { background-color: #1c7ed6; }
</style>

<script>
const brilliantCounts = {
  "2025-05-20": 1,
  "2025-05-22": 2,
  "2025-05-24": 3
};

const grid = document.querySelector(".streak-grid");

function getClass(count) {
  if (count === 1) return "active-1";
  if (count === 2) return "active-2";
  if (count >= 3) return "active-3";
  return "";
}

const today = new Date();
for (let i = 0; i < 365; i++) {
  const date = new Date();
  date.setDate(today.getDate() - i);
  const yyyy = date.getFullYear();
  const mm = String(date.getMonth() + 1).padStart(2, "0");
  const dd = String(date.getDate()).padStart(2, "0");
  const key = `${yyyy}-${mm}-${dd}`;
  const count = brilliantCounts[key] || 0;

  const box = document.createElement("div");
  box.className = `day ${getClass(count)}`;
  box.title = key;
  if (count > 0) {
    box.onclick = () => window.location.href = `/RecordMyBrilliancy/brilliant-${key.replaceAll("-", ".")}`;
  }
  grid.prepend(box);
}
</script>

---

# 💡 Brilliant Move Archive

## 🗓 2025.01.22
**Brilliant Move:** 24... Re1!!

[→ 전체 보기](_posts/brilliant-2025.01.22.md)

---

## 🗓 2025.02.22
**Brilliant Move:** 38... Qf1+!!

[→ 전체 보기](_posts/brilliant-2025.02.22.md)

---

## 🗓 2025.03.23
**Brilliant Move:** 27. Rxb7+!!

[→ 전체 보기](_posts/brilliant-2025.03.23.md)

---

## 🗓 2025.03.23
**Brilliant Move:** 17... Qe1+!!

[→ 전체 보기](_posts/brilliant-2025.03.23-2.md)

---

## 🗓 2025.04.23
**Brilliant Move:** 6. Bxf7+!!

[→ 전체 보기](_posts/brilliant-2025.04.23.md)

---

## 🗓 2025.04.23
**Brilliant Move:** 34. Nxb3!!

[→ 전체 보기](_posts/brilliant-2025.04.23-2.md)

---

## 🗓 2025.03.24
**Brilliant Move:** 19... g6!!

[→ 전체 보기](_posts/brilliant-2025.03.24.md)

---

## 🗓 2025.05.05
**Brilliant Move:** 9. Bxf7+!!

[→ 전체 보기](_posts/brilliant-2025.05.05.md)

---

## 🗓 2025.05.05
**Brilliant Move:** 25. Rxg5!!

[→ 전체 보기](_posts/brilliant-2025.05.05-2.md)

---

## 🗓 2025.05.06
**Brilliant Move:** 8... Bxf2+!!

[→ 전체 보기](_posts/brilliant-2025.05.06.md)

---

## 🗓 2025.05.10
**Brilliant Move:** 23. Rxe6!!

[→ 전체 보기](_posts/brilliant-2025.05.10.md)

---

## 🗓 2025.05.14
**Brilliant Move:** 25... Nf3+!!

[→ 전체 보기](_posts/brilliant-2025.05.14.md)

---

## 🗓 2025.05.17
**Brilliant Move:** 12. Bxh7+!!

[→ 전체 보기](_posts/brilliant-2025.05.17.md)

---

## 🗓 2025.05.20
**Brilliant Move:** 20... Ng6!!

[→ 전체 보기](_posts/brilliant-2025.05.20.md)

---

## 🗓 2025.04.27
**Brilliant Move:** 23. Qe8+!!

[→ 전체 보기](_posts/brilliant-2025.04.27.md)

---

## 🗓 2025.03.28
**Brilliant Move:** 20. Nxc6!!

[→ 전체 보기](_posts/brilliant-2025.03.28.md)

---

## 🗓 2025.03.27
**Brilliant Move:** 17... Rxd4!!

[→ 전체 보기](_posts/brilliant-2025.03.27.md)

---

## 🗓 2025.03.27
**Brilliant Move:** 19... Nxh3+!!

[→ 전체 보기](_posts/brilliant-2025.03.27-2.md)

---

