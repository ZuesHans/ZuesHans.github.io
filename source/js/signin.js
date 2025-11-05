// 签到模块：使用localStorage存储签到日期
document.addEventListener('DOMContentLoaded', function() {
  const signinBtn = document.getElementById('signin-btn'); // 按钮ID，自定义
  const streakEl = document.getElementById('streak-count'); // 显示连续天数
  const calendarEl = document.getElementById('calendar-grid'); // 可选：简单日历网格

  // 获取签到历史
  function getSignins() {
    return JSON.parse(localStorage.getItem('hexo-signins') || '[]');
  }

  // 计算连续签到天数
  function calculateStreak(signins) {
    const today = new Date();
    today.setHours(0, 0, 0, 0);
    let streak = 0;
    for (let i = 0; i < signins.length; i++) {
      const date = new Date(signins[i]);
      date.setHours(0, 0, 0, 0);
      if (date.getTime() === today.getTime() - i * 86400000) { // 连续一天
        streak = i + 1;
      } else {
        break;
      }
    }
    return streak;
  }

  // 签到
  function signIn() {
    const signins = getSignins();
    const today = new Date().toISOString().split('T')[0]; // YYYY-MM-DD
    if (!signins.includes(today)) {
      signins.push(today);
      localStorage.setItem('hexo-signins', JSON.stringify(signins));
      updateDisplay();
      // 可扩展：签到后提示“去写日记？”并跳转到写作页
      if (confirm('签到成功！今天要更新文章或日记吗？')) {
        window.open('/writing-guide/'); // 替换成你的写作指南页
      }
    } else {
      alert('今天已签到啦，继续保持！');
    }
  }

  // 更新显示
  function updateDisplay() {
    const signins = getSignins();
    const streak = calculateStreak(signins);
    if (streakEl) streakEl.textContent = `连续签到 ${streak} 天`;
    // 可选：渲染简单日历（标记签到日）
    if (calendarEl) {
      renderSimpleCalendar(calendarEl, signins);
    }
  }

  // 简单日历渲染（扩展点：用CSS网格显示本月，标记签到日）
  function renderSimpleCalendar(el, signins) {
    const today = new Date();
    const year = today.getFullYear();
    const month = today.getMonth();
    const daysInMonth = new Date(year, month + 1, 0).getDate();
    let html = '<div class="calendar-grid">';
    for (let day = 1; day <= daysInMonth; day++) {
      const dateStr = `${year}-${String(month + 1).padStart(2, '0')}-${String(day).padStart(2, '0')}`;
      const isSigned = signins.includes(dateStr);
      html += `<div class="calendar-day ${isSigned ? 'signed' : ''}">${day}</div>`;
    }
    html += '</div>';
    el.innerHTML = html;
  }

  // 绑定事件
  if (signinBtn) signinBtn.addEventListener('click', signIn);
  updateDisplay(); // 页面加载时更新
});