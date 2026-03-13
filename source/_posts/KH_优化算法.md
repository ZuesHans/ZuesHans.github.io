---
title: KH优化算法
date: 2025-11-13
tags:
    - C++
    - 算法
    - Trick
    - 杂项
cover: /img/cover/picg_3.png
---


## 莫队

### 普通莫队做法

#### [P2709 【模板】莫队 / 小B的询问](https://www.luogu.com.cn/problem/P2709)

- **核心模型**:
- **思维误区 (Bug)**:
- **修正逻辑 (Patch)**:
- **关键代码**:

```cpp
struct qury
{
    int l, r, id;
};

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vi nums(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> nums[i];
    }
    vi cnt(k + 3);
    vector<qury> qry(m);

    for (int i = 0; i < m; i++)
    {
        cin >> qry[i].l >> qry[i].r;
        qry[i].id = i;
    }
    int bk = max(1, (int)sqrt(n));
    sort(all(qry), [&](qury a, qury b)
         {
    int aa=a.l/bk;
    int bb=b.l/bk;
        if(aa!=bb)return aa<bb;
        else
        {
            return a.r<b.r;
        } });

    int now = 0;
    auto add = [&](int x) -> void
    {
        now += 2 * cnt[nums[x]] + 1;
        cnt[nums[x]]++;
    };
    auto del = [&](int x) -> void
    {
        now -= 2 * cnt[nums[x]] - 1;
        cnt[nums[x]]--;
    };

    int lef = 1;
    int ri = 0;
    vi anss(m);
    ll ans = 0;
    for (int i = 0; i < m; i++)
    {
        while (lef > qry[i].l)
        {
            lef--;
            add(lef);
        }

        while (ri < qry[i].r)
        {
            ri++;
            add(ri);
        }

        while (lef < qry[i].l)
        {
            del(lef);
            lef++;
        }

        while (ri > qry[i].r)
        {
            del(ri);
            ri--;
        }

        anss[qry[i].id] = now;
    }
    for (int i = 0; i < m; i++)
    {
        cout << anss[i] << '\n';
    }
}
```

---
