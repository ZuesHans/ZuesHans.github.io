---
title: wp_优化
date: 2026-01-12
tags:

    - 算法
cover: /img/cover/picg_12.png
---

## 基于数据范围打表预处理

### 筛法枚举

#### [F. Easy Demon Problem]()

- **核心模型**:调和级数枚举预处理
- **思维误区 (Bug)**:首先是对于题目负因数case没写上。其次是复杂度。这道题错解是n√nlogn，注意到数据范围会变成1e8，加上map常数大会tle。第一步优化换了unorded_set （O(1)查询最坏on）题目卡哈希冲突。
- **修正逻辑 (Patch)**:看到`多次查询`&&`因子`||`倍数`||`最大公约数`，在数据范围允许的条件下可以对值域内所有数有的性质进行打表。
- **关键逻辑**：**双重循环，但是内层循环是按倍数增长，这一块的复杂度实际上是nlogn的**
- **关键代码**:

```cpp

```

#### [Codeforces 1154G - Minimum Possible LCM](https://codeforces.com/contest/1154/problem/G)

- **核心模型**:枚举gcd
- **思维误区 (Bug)**:记录第一直觉为什么错了 (如: 以为是DP其实是贪心 / 读错题)
- **修正逻辑 (Patch)**:下次看到什么特征，要修正为正确思路
- **关键代码**:

```cpp
// 只贴最核心的 3-5 行逻辑或 Check 函数，不要贴 main
```

---

## 时空复杂度优化

### BFS

#### [E. Product Queries](https://codeforces.com/contest/2193/problem/E)

- **核心模型**:由于是乘法，容易知道计算目标次数最多是logn级别，所以可以秒开BFS(严格的nlogn)
- **思维误区 (Bug)**:**！！注意queue是危险的**所以要去重；**没有剪枝会退化到n^2**
- **修正逻辑 (Patch)**:
- **关键代码**:

```cpp
void solve()
{
    int n;
    cin >> n;
    vi a(n);
    vi ans(n + 1, INF);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        ans[a[i]] = 1;
    }

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    if (!a.empty() && a[0] == 1)
    {
        a.erase(a.begin());
    }
    int pp = a.size();

    queue<pii> q;

    int cnt = 0;

    for (int i = 0; i < pp; i++)
        q.emplace(make_pair(a[i], 1));

    vi vis(n + 1);

    while (!q.empty())
    // for(int i=0;i<100;i++)
    {
        auto hsh = q.front();
        q.pop();
        for (int i = 0; i < pp; i++)
        {
            if (a[i] * hsh.first <= n)
            {
                if (ans[a[i] * hsh.first] >= INF)
                {
                    q.emplace(make_pair(a[i] * hsh.first, hsh.second + 1));
                     ans[a[i] * hsh.first] = hsh.second+1;
                }
            }
            else
                break; // 剪枝
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (ans[i] > 3e8)
            cout << -1 << ' ';
        else
            cout << ans[i] << ' ';
    }
    cout << '\n';
}

```

---
