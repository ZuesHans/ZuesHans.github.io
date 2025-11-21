---
title: Against the Difference
date: 2025-11-19
tags:
    - 算法
    - dp
cover: /img/cover/我的老杀头像.png
---

这道题卡了我两天，遂单独收集

#### A. Against the Difference

- **题目**

>We define that a block is an array where all elements in it are equal to the length of the array. For example, $[3, 3, 3]$, $[1]$, and $[4, 4, 4, 4]$ are blocks, while $[1, 1, 1]$ and $[2, 3, 3]$ are not.
An array is called neat if it can be obtained by the concatenation of an arbitrary number of blocks (possibly zero). Note that an empty array is always neat.
You are given an array $a$ consisting of $n$ integers. Find the length of its longest neat subsequence$^{\text{∗}}$.
$^{\text{∗}}$A sequence $c$ is a subsequence of a sequence $a$ if $c$ can be obtained from $a$ by the deletion of several (possibly, zero or all) element from arbitrary positions.
>我们定义block是一个数组，其中的所有元素都等于该数组的长度。例如， $[3, 3, 3]$ ， $[1]$ 和 $[4, 4, 4, 4]$ 是块，而 $[1, 1, 1]$ 和 $[2, 3, 3]$ 不是块。
如果数组可以通过任意数量的块（可能为零）的连接获得，则称为整齐数组。注意，空数组总是整洁的。
给定一个由 $n$ 个整数组成的数组 $a$ 。求它的最长整洁子序列 $^{\text{∗}}$ 的长度。
$^{\text{∗}}$ 序列 $c$ 是序列 $a$ 的子序列，如果 $c$ 可以从 $a$ 中删除任意位置的几个（可能为零或全部）元素。

- **思路**
  - 首先这道题目是典型dp，因为他是通过删掉一些数字找一个最大的子序列，对于每个数字来说他面临两种状态:删掉或者不删掉(或者说是选择或者不选择)。而决定他是否被选择的权值就是到目前这个位置他做多少做贡献。容易发现只有在他结算的时候才会做贡献。我们只需要贪心地(**我的意思是他要找离他最近地跟他数字相同的，这样子才能给后面留空间。因为递推所以有i<j必然有dp[i]<=dp[j]**)找他开头的那一刻的那一刻结算就行。
  
- **AC代码**：用桶和打表数组来处理每个数字的位置

```cpp
void solve()
{
    int n;
    cin>>n;
    vi nums(n+1);
    vector<vi> idx(n+1);
    vi ery(n+1);
    rep(i,1,n)
    {
        cin>>nums[i];
        idx[nums[i]].push_back(i);
        ery[i]=idx[nums[i]].size();
    }

    vi dp(n+1);
    dp[0]=0;
     vi xz(n+1);
    for(int i=1;i<=n;i++)
    {
        int pans=0;
        int cur=ery[i]-nums[i];
        if(cur>=xz[i]*nums[i])
        {
           pans=dp[idx[nums[i]][cur]-1]+nums[i];
            xz[nums[i]]++;
        }
       dp[i]=max(pans,dp[i-1]);

    }
    
    cout<<dp[n]<<'\n';

}

```
