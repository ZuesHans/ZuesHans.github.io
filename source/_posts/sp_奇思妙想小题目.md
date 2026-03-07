---
title: sp_奇思妙想小题目
date: 2026-02-16
tags:
    - 杂谈
    - 算法
cover: /img/cover/picg_20.png
---
这里记录着我对题目的奇思妙想。因为我找不到oj，但是我又觉得这种题目很典，所以就搞了一个专门记录的帖子。不保证代码和分析全队，正确性由gemini3 pro支持..

## 1

- 题目描述
  - 给出长度为n的数组ai（均为正整数），给出m，选择子序列使得子序列里面的乘积==n
- 解法解答：使用拆因子dp做法->在已经有的因子里面选择（这里一个实现难点是不能重复，而愚蠢的zues一开始没实现这个），跑背包dp
- 跑过随机数据代码：

```cpp
void solve()
{
    int n;
    cin >> n;
    int m;
    cin >> m;
    // m = 67;

    map<int, int> mp;

    for (int i = 0; i < n; i++)
    {
        int d;
        cin >> d;
        if (m % d == 0)
        {
            mp[d]++;
        }
    }

    map<int, int> dp;
    dp[1] = 1;

    for (auto [nb, cnt] : mp)
    {
        vi now;
        for (auto it : dp)
        {
            now.push_back(it.first);
        }

        for (int j = 0; j < now.size(); j++)
        {
            ll sum = now[j];
            for (int i = 0; i < cnt; i++)
            {
                sum *= nb;
                if (m % sum == 0)
                {
                    if (sum == m)
                    {
                        cout << "yes" << '\n';
                        return;
                    }
                    else
                    {
                        dp[sum]++;
                    }
                }
            }
        }
    }
    cout << "no" << '\n';
}

```
