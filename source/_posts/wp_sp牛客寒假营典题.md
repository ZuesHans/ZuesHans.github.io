---
title: wp_spţ牛客寒假营典题
date: 2026-02-11
tags:
    - 算法
cover: /img/cover/picg_5.png
---

>> 补题所得，按照知识板块分，可能加上其他地方找到的题

## 代码实现

### [乘法逆元] (<https://oi-wiki.org/math/number-theory/inverse/>)

- 快速幂法求逆元

```cpp
inline ll qpow(ll a, ll b, ll mod = MOD) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
ll inv(ll a, ll mod) {
    return qpow(a, mod - 2, mod);
}

```

- 乘法原理（独立事件同时发生）
- 加法原理（互斥事件）

#### [A+B problem](https://ac.nowcoder.com/acm/contest/120561/A)

- **核心模型**: 题目给出一群概率如何打表？如何转化题目条件
- 题目条件转化
   这道题我认为最难的是读懂同时满足的三条条件
   >最终所有显示器均有灯管被点亮（也就是说显示器的灯管不能全灭）。
   >最终所有显示器显示的结果均为合法数字。
   >第一排的显示器前后拼接形成的四位十进制数记作 A，第二排的显示器前后拼接形成的四位十进制数记作 B 的话，满足：A+B=C。（两排显示器从左到右依次作为千位、百位、十位、个位进行拼接，可以存在前导 0）。
   当我们读完题目可以当一个组合满足第三条条件时同时可以满足前两个。
   题目要求你对“显示器”做算术运算，你只需要关心**这个显示器显示了哪个数字**。只要它显示了数字，它就一定亮了，也一定合法。其他都是出题人故意写的干扰项。
   **以后遇到这种n个条件叠加在一起的概率题药仔细想想是不是里面又逻辑包含/递推关系**

- **概率转换思路**

```cpp
    每根灯管亮起来的分数概率用乘法逆元转换
    vi pr80(9);
    for (int i = 0; i < 7; i++)
    {
        pr80[i] = P[i] * inv(100, MOD) % MOD;
    }
    每个数字亮起来的概率，根据乘法原理亮起来的概率是联动的事件所以用乘法
    vi deng(10);
    for (int p = 0; p < 10; p++)
    {
        ll cur = 1;
        for (int i = 0; i < 7; i++)
        {
            if (biao[p][i])
                cur = cur * pr80[i] % MOD;
            else
                cur = cur * (1 - pr80[i] + MOD) % MOD;
        }
        deng[p] = cur;
    }

```

- **数位DP正解** :可以容纳高精度，复杂度$$O(L \cdot 10^2)$$ $L$ 为数字的位数（本题中 $L=4$）

```cpp


int biao[10][7] = {
    {1, 1, 1, 0, 1, 1, 1},
    {0, 0, 1, 0, 0, 1, 0},
    {1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 1},
    {0, 1, 1, 1, 0, 1, 0},
    {1, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1}};

ll qpow(ll a, ll b, ll mod)
{
    ll res = 1;
    a %= mod;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

// 求 a 在 mod 下的逆元
ll inv(ll a, ll mod)
{
    return qpow(a, mod - 2, mod);
}

void solve()
{
    int c;
    cin >> c;
    vi P(8);
    for (int i = 0; i < 7; i++)
    {
        cin >> P[i];
    }
    vi pr80(9);
    for (int i = 0; i < 7; i++)
    {
        pr80[i] = P[i] * inv(100, MOD) % MOD;
    }

    vi deng(10);
    for (int p = 0; p < 10; p++)
    {
        ll cur = 1;
        for (int i = 0; i < 7; i++)
        {
            if (biao[p][i])
                cur = cur * pr80[i] % MOD;
            else
                cur = cur * (1 - pr80[i] + MOD) % MOD;
        }
        deng[p] = cur;
    }

    vi nums;

    // while (c > 0)
    for (int i = 0; i < 4; i++)
    {
        nums.push_back(c % 10);
        c /= 10;
    }

    vector<vi> dp(5, vi(2));
    dp方程设置：第一维是位数，第二维（0/1）是是否有进位
    dp[0][0] = 1;
    1. 遍历每一个位置（个位 -> 十位 -> 百位 -> 千位）
    for (int i = 0; i < 4; i++)
    {
        2. 遍历当前位置接收到的进位（上一轮传过来的）
        for (int j = 0; j < 2; j++)
        {
            如果当前状态概率为0，说明之前的路走不通，直接跳过（剪枝）
            if (dp[i][j] == 0)
                continue;
            3. 枚举 A 在这一位可能显示的数字 (0-9)
            for (int a = 0; a <= 9; a++)
            {
                4. 枚举 B 在这一位可能显示的数字 (0-9)
                for (int b = 0; b <= 9; b++)
                {
                    这一位算出来的结果，必须等于 C 在这一位的数字
                    //也就是这个(a + b + j) % 10 
                    if ((a + b + j) % 10 == nums[i])
                    {
                        int nj = (a + b + j) / 10;

                        ll mtf = deng[a] * deng[b] % MOD;
                        dp[i + 1][nj] = (dp[i + 1][nj] + dp[i][j] * mtf) % MOD;
                    }
                }
            }
        }
    }

    cout << dp[4][0] << "\n";
}


```

- **小数据AC代码**:

```cpp
// Time: 2026-02-03 16:11:12 (周二)
// Author:  Keronshans

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define all(x) (x).begin(), (x).end()
#define int long long

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 998244353;
const double EPS = 1e-9;

/* ======================================== */
/*

算出每个任务的概率

算出合法数字x的概率加起来?
生成某个数字的概率假设为p
所有灯管的pi相乘

比如第一根灯点亮


*/
int biao[10][7] = {
    {1, 1, 1, 0, 1, 1, 1},
    {0, 0, 1, 0, 0, 1, 0},
    {1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 1},
    {0, 1, 1, 1, 0, 1, 0},
    {1, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1}};

ll qpow(ll a, ll b, ll mod)
{
    ll res = 1;
    a %= mod;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

// 求 a 在 mod 下的逆元
ll inv(ll a, ll mod)
{
    return qpow(a, mod - 2, mod);
}

void solve()
{
    int c;
    cin >> c;
    vi P(8);
    for (int i = 0; i < 7; i++)
    {
        cin >> P[i];
    }
    vi pr80(9);
    for (int i = 0; i < 7; i++)
    {
        pr80[i] = P[i] * inv(100, MOD) % MOD;
    }

    vi deng(10);
    for (int p = 0; p < 10; p++)
    {
        ll cur = 1;
        for (int i = 0; i < 7; i++)
        {
            if (biao[p][i])
                cur = cur * pr80[i] % MOD;
            else
                cur = cur * (1 - pr80[i] + MOD) % MOD;
        }
        deng[p] = cur;
    }

    vi nums;
    ll ans = 0;
    for (int i = 0; i <= c; i++)
    {
        int a = i;
        int b = c - i;
        int now = 1;
        for (int j = 0; j < 4; j++)
        {
            now = now * deng[a % 10] % MOD;
            a /= 10;
        }
        for (int j = 0; j < 4; j++)
        {
            now = now * deng[b % 10] % MOD;
            b /= 10;
        }
        ans += now;
        ans %= MOD;
    }
    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 1;
    cin >> T; // 多组数据时取消注释

    while (T--)
    {
        solve();
    }

    return 0;
}
```

---
