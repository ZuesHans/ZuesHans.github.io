---
title: sp_Valentine's Day
date: 2026-02-14
tags:
    - 杂谈
    - special
cover: /img/cover/default.png
---
```cpp

void solve()
{
    int n;
    cin >> n;
    map<int, int> love;
    for (int i = 0; i < n; i++)
    {
        int d;
        cin >> d;
        love[d]++;
    }
    for (auto hsh : love)
    {
        auto [ilove, ljl] = hsh;
        if (ljl % 2)
        {
            cout << "NO" << '\n';
            return;
        }
    }
    cout << "YES" << '\n';
    for (auto hsh : love)
    {
        auto [ilove, ljl] = hsh;

        for (int i = 0; i < ljl; i++)
        {
            cout << ilove << ' ';
        }
    }
}


```

> 好想念unk呜呜┭┮﹏┭┮
> 情人节快乐喵喵~~
