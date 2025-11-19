var OriginTitle = document.title;
var titleTime;
document.addEventListener('visibilitychange', function () {
    if (document.hidden) {
        // 离开标签页时
        document.title = '不要猫猫了嘛呜呜😭';
        clearTimeout(titleTime);
    } else {
        // 回来时
        document.title = '好开心❤你回来了';
        titleTime = setTimeout(function () {
            document.title = OriginTitle;
        }, 2000);
    }
});