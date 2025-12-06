---
title: wp_Trick
date: 2025-12-06
tags:
    - Trick
    - 算法
cover: /img/cover/picg_9.png
math: true
---


### stl优化复杂度

#### Map 前缀和

**用途**：用 Map 记录前缀和，求最短满足条件的子串。  
**常见坑**：初始化 Map，处理空字符串情况。

```cpp
void solve() {
    int n, sum = 0;
    cin >> n;
    string s;
    cin >> s;
    map<int, int> caonima;
    caonima[0] = -1;
    int niubi = 0, ans = n;
    for (int i = 0; i < n; i++) {
        niubi += s[i] == 'a' ? 1 : -1;
        caonima[niubi] = i;
        if (caonima.count(niubi - sum))
            ans = min(ans, i - caonima[niubi - sum]);
    }
    cout << (ans == n ? -1 : ans) << '\n';
}
```

**复杂度**：O(n*log n)，空间 O(n)。

#### Cool Partition

- **题号**: Div3C
- **算法类型**: 贪心

- **AC 代码**:

```cpp
  void solve()
  {
      int n;
      cin >> n;
      set<int> basedonen;
      set<int> basedln;
      int ans = 0;
      rep(i, 1, n)
      {
          int d;
          cin >> d;
          basedln.emplace(d);
          basedonen.emplace(d);
          if (basedln.size() == basedonen.size())
          {
              ans++;
              basedln.clear();
          }
      }
      cout << ans << '\n';
  }

```

- **注题目解析**
  - 事实上这是一个set使用快乐题，一道普及-的贪心。
  - 需要划分区间尽可能地多，就是需要每个区间京可能地小。对于一个区间存在的数的种类，必然等于从0到他的数的种类

#### C

- **记录原因**：介绍可以进行O(logn)复杂度查询的容器：set，map，multiset
- **思路**：可以轻易的发现，我们需要贪心：分成两块，如果有奖励（可以不断刷新剑的伤害）我们先做，后面再开没有奖励的怪物。
  该死，我明明已经会了，结果写的时候脑子糊糊的忘记了。。。对于有奖励的组，我们需要遍历怪物（来达到每个怪物只能打一次的效果）。因为怪物是可以sort的，sort的规则是血量从小到大。因为我们知道再有奖励的组别里面剑的攻击力只会增加不会减少。。
  - 我们优化的难点在如何降低复杂度：我们要找到能打败这个怪物条件下攻击力最小的剑，传统的维护最小值是O（n），我猪脑过载想到的是sort加二分O(logn)。这个时候就出现我们伟大的基于红黑树的快速查找容器`set，map，multiset`。
  -

>==**优化场景**==
>动态维护有序集合， O(log n) 查找/插入/删除。
>可以实现二分查找`lower_bound`和`upper_bound`
>set用来去重
>map用来根据键值对快速查找。

- **AC 代码**:

```cpp
struct mon
{
    int b, c;
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vi a(n);
    vector<mon> mnst(m);
    rep(i, 0, n - 1)
    {
        cin >> a[i];
    }
    rep(i, 0, m - 1)
    {
        cin >> mnst[i].b;
    }
    rep(i, 0, m - 1)
    {
        cin >> mnst[i].c;
    }
    vector<mon> youjl;
    vector<mon> meijl;
    rep(i, 0, m - 1)
    {
        if (mnst[i].c == 0)
        {
            meijl.push_back(mnst[i]);
        }
        else
            youjl.push_back(mnst[i]);
    }
    int ms = meijl.size();
    int ys = youjl.size();
    int ans = 0;
    sort(all(youjl), [](mon aa, mon bb)
         { if(aa.b!=bb.b) return aa.b<bb.b;
        else  return  aa.c > bb.c;});
    sort(all(meijl), [](mon aa, mon bb)
         { return aa.b<bb.b; });
    multiset<int> hsh;
    rep(i, 0, n - 1)
    {
        hsh.emplace(a[i]);
    }

    for (int j = 0; j < ys; j++)
    {

        if (!hsh.empty())
        {
            
            auto cnm = hsh.lower_bound(youjl[j].b);
            if (cnm != hsh.end())
            {
                int zl = *cnm;
                hsh.emplace(max(youjl[j].c, zl));
                ans++;
                hsh.erase(cnm);
            }
        }

    }
    for (int j = 0; j < ms; j++)
    {

        if (!hsh.empty())
        {
            auto cnm = hsh.lower_bound(meijl[j].b);
            if (cnm != hsh.end())
            {
                ans++;
                hsh.erase(cnm);
            }
        }
        if (hsh.empty())
        {
            break;
        }
    }

    cout << ans << '\n';
}
```

#### P2058 [NOIP 2016 普及组] 海港

- **错点**：TLE
- 错题记录：

> 一开始我想用quene来模拟时间维度上的滑动，结果发现quene不支持遍历。于是用了deque
> 第一次本地WA：我想用set记录每艘船上面的游客种类，然后和他的时间一起emplace进去队列，ans+=每一个时间点的种类。属于是读错题了。
> 第二次提交TLE：我想那就开一个map来存所有数据，然后遍历放进set里面进行去重...数据范围K总和3e5，n为2e5随爆炸
> 后来乱交了两罚，因为想不通
>
- 打开题解：用桶来装数字，当这个桶里面的数字是第一次被装到1，他就多一个种类，反之少一个种类。需要将出队判断移到后面。实现线性处理ans，实在精妙

> //然后自己手搓了了，AC

- **AC代码**

```cpp
struct ship
{
    int t;
    int gj;
};

void solve()
{
    int n;
    cin >> n;
    deque<ship> bc;
    vi nums(1e5 + 2);
    int ans = 0;
    rep(i, 0, n - 1)
    {
        int t, k;
        cin >> t >> k;
        // 这里要写一个出队判断
        rep(j, 0, k - 1)
        {
            int d;
            cin >> d;
            nums[d]++;
            if (nums[d] == 1)
                ans++;
            bc.push_back({t, d});
        }
        while (!bc.empty() && bc.front().t <= t - 86400)
        {
            auto hsh = bc.front();
            nums[hsh.gj]--;
            if (nums[hsh.gj] == 0)
                ans--;
            bc.pop_front();
        }
        cout << ans << '\n';
    }
}

```

#### LIS

- **题目**：给个序列nums，求他的最长上升子序列
- O(n^2)做法:$$dp[i] = \max(dp[j]) + 1 \quad \text{其中 } 0 \le j < i, a[i] > a[j]$$
- O(nlogn)做法：

```cpp
int LIS_nlogn(vector<int>& a) {
    if (a.empty()) return 0;
    
    // low[i] 存的是长度为 i+1 的子序列的最小结尾
    // 注意：为了方便，low 的下标从 0 开始，所以 low[len-1] 是长度为 len 的结尾
    vector<int> low;
    
    for (int x : a) {
        // Case 1: 如果 low 为空，或者 x 比 low 最后一个元素大
        if (low.empty() || x > low.back()) {
            low.push_back(x);
        }
        // Case 2: 否则，在 low 里找到第一个 >= x 的位置，替换它
        else {
            // lower_bound 返回迭代器，指向第一个 >= x 的元素
            auto it = lower_bound(low.begin(), low.end(), x);
            *it = x; // 贪心：让该长度的结尾变得更小
        }
    }
    
    return low.size();
}
```

- **优化思考路径**
  - 这是一种优化贪心，将dp对象转换成能达到的长度，每一位都代表着如果要达到这个长度我最小要有多大，精辟在更新。相当于转换了dp的两个对象：
  - ==`最长能有多长`->`如果要达到这个长度需要最小什么条件`==

- ==**应用**==：
  - **Dilworth定理：最少的下降序列个数就等于整个序列最长上升子序列的长度**
  - LCS解法->将一个数组的每一个数字跟他的位置映射在一起，相当于开了个桶

- **注意**：求下降序列需要`auto it= upper_bound(all(hei),hsh,greater<int>());`。普通的公式只能算：**排列好后的不下降数列**

### 题意理解+stl

#### I题是个签到题

- **错误原因**：在处理这个条件`或者通过人数是所有题目前三多的题（也就是最多有两个题目通过人数严格比它多）叫做签到题。`的时候第一次用的set，本来想的是找到第三大的数字然后直接比较，获得set的rbegin() (**set容器从小到大排**)。结果发现：bro，他说是最多两个题目。。。谢谢你的脑抽：贡献了13发罚时
==以后觉得有问题先考虑是不是读错题了==

### 推式子优化复杂度

- 从n方缩减成O(n)或者nlogn,我们通过分离lr与计算贡献的方式抽象题目的问法

#### C. Range Operation

- **题目**

>You are given an integer array $a$ of length $n$.
>You can perform the following operation: choose a range $[l, r]$ ($1 \le l \le r \le n$) and replace the value of elements $a_l, a_{l+1}, \dots, a_r$ with $(l + r)$.
>Your task is to calculate the maximum possible total array sum if you can perform the aforementioned operation at most once.
>您将得到一个长度为 $n$ 的整数数组 $a$ 。
您可以执行以下操作：选择范围 $[l, r]$ （ $1 \le l \le r \le n$ ），并将元素 $a_l, a_{l+1}, \dots, a_r$ 的值替换为 $(l + r)$ 。
您的任务是计算最大可能的阵列总和，前提是您最多可以执行一次上述操作。

- **思路**
  - `区间总和`->前缀和优化
  - 对于每个数字我们是否能判断他更改的收益从而确定他要不要被更改,随后贪心解决一切？
  - 第一条思路：让他和他自己比较的贪心：但是你会发现这只能确定一些“必须更改”的数字，不符合题目里面的边界，l和r的改变随时能够影响更改的权重。这个思路假的很明显
  - 第二条思路：要去寻找rl的最优值肯定是n方解法，我们能不能通过假设存在lr然后推导出对于每一组lr的收益表达式来找到他贪心的点呢？
    - 对于确定的lr，更改之后的收益是: (l+r)*(r-l+1)-(qzh[r]-qzh[l-1])
    - 学过高中数学我们就知道l和r是可以分离开的:得到贪心最大化式子:l^2-r^2+l+r+qzh[r]+qzh[l-1]
    - 然后我们就发现可以通过O(n)的处理得出每一部分得权重，然后贪心最大化
  - 注意这里有一个小细节：r>=l,所以我们在处理的时候需要注意处理l得同时处理r
  - 这里还有个实现层面的优化：你可能会发现如果对于每个r都要扫一边l我们前面做的降维全都白费了，我们通过同时维护ans1和ans2(两个需要最大化的贪心模块)让他在一边扫的时候可以同时更新同时过。这也是一个重要的trick

```cpp
for (int i = 1; i <= n; i++)
    {

        if (chaxun2[i] - chaxun2[zuobian] > ans2)
        {
            ans2 = chaxun2[i] - chaxun2[zuobian];
        }
        if (chaxun2[i] < ans1)//这里的更新顺序是因为我们的优化已经让i=l-1了，所以顺序不能错
        {
            ans1 = chaxun2[i];//边处理边更新线性扫过去是非常常见的优化方法
            zuobian = i;
        }
    }

    cout << qzh[n] + ans2 << '\n';
```

```cpp
void solve()
{
    int n;
    cin >> n;
    vi nums(n + 1);
    vi qzh(n + 1);
    vi chaxun1(n + 1);
    vi chaxun2(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int d;
        cin >> d;
        nums[i] = d;
    }
    for (int i = 1; i <= n; i++)
    {
        qzh[i] = qzh[i - 1] + nums[i];
        chaxun1[i] = (i * i) + i - qzh[i];
        chaxun2[i] = (i * i) + i - qzh[i];
    }
    int ans1 = 0;
    int zuobian = 0;
    int youbian = 0;

    int ans2 = 0;

    for (int i = 1; i <= n; i++)
    {

        if (chaxun2[i] - chaxun2[zuobian] > ans2)
        {
            ans2 = chaxun2[i] - chaxun2[zuobian];
        }
        if (chaxun2[i] < ans1)
        {
            ans1 = chaxun2[i];
            zuobian = i;
        }
    }

    cout << qzh[n] + ans2 << '\n';
}
```

### 对区间以及结果进行排列—>切换入点

#### C. Monopati

- [link] (<https://codeforces.com/contest/2163/problem/C>)
- **思路**
    题意转换：对于每个合法的路径，必然存在某一个合法的转换列i让他从上行过度到下行。因为要求出lr的区间所以我们需要得上行从前往后的最大值和最小值，下行从后往前的最小值和最大值。√
    对于每个 $i$，路径存在的充要条件是：$l \le L_i$ 且 $r \ge R_i$。（其中 $L_i$ 是该路径上的最小值，$R_i$ 是该路径上的最大值）。
    ->最终目标：统计 $(l, r)$ 的数量，使得 存在至少一个 $i$ 满足上述条件。即求 $n$ 个约束区域（矩形）的 并集 覆盖的整数点数。
    如果对每个点i进行分析太难了，我们可以考虑进一步转化问题：

    要求合法的lr对数:固定每一个l，统计合法的r的数量。原理：**固定一个变量，用数据结构（堆/线段树）维护另一个变量的可行域。**
    更新方程是：`sum+=2*n+prdq.top()[0];`

    容器选择：理想的实现应该做到:过滤过期：随着 $l$ 增大，剔除那些 $L_i < l$ 的约束（因为它们不再能覆盖当前的 $l$）。
    查询最优：在剩下的合法约束中，找到 $R_i$ 最小的那个（$R$ 越小，合法的 $r$ 越多）。

    **易被忽视的细节**：对于每个r的约束是：我们找到的和他配对的l'必须小于r在的数对的l
    所以在堆里的排序规则是：r越小越好，l越大越好。这样子我们筛掉的点对既不会漏掉r也不会漏掉l

- `priority_queue<array<int, 2>> prdq;`默认按照prdq()[0]大小排序

- **AC代码**(优先队列法)

```cpp
void solve()
{
    int n;
    cin >> n;
    vi mpu(n);
    vi mpd(n);
    vi mxu(n);
    vi mnu(n);
    vi mxd(n);
    vi mnd(n);
    for (int i = 0; i < n; i++)
    {
        cin >> mpu[i];
        mpu[i]--;
        if (!i)
        {
            mxu[i] = mpu[i];
            mnu[i] = mpu[i];
        }
        else
        {
            mxu[i] = max(mxu[i - 1], mpu[i]);
            mnu[i] = min(mnu[i - 1], mpu[i]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        cin >> mpd[i];
        mpd[i]--;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (i == n - 1)
        {
            mxd[i] = mpd[i];
            mnd[i] = mpd[i];
        }
        else
        {
            mxd[i] = max(mxd[i + 1], mpd[i]);
            mnd[i] = min(mnd[i + 1], mpd[i]);
        }
    }
    priority_queue<array<int, 2>> prdq;
    for (int i = 0; i < n; i++)
    {
        prdq.push({-max(mxd[i], mxu[i]), min(mnd[i], mnu[i])});
    }
    ll sum = 0;
    for (int i = 0; i < 2 * n; ++i)
    {
        while (!prdq.empty() && prdq.top()[1] < i)
        {
            prdq.pop();
        }
        if (!prdq.empty())
        {
            sum += 2 * n + prdq.top()[0];
        }
    }
    cout << sum << '\n';
}
```

#### P2887 [USACO07NOV] Sunscreen (收录意义是请和C. Monopati对比学习)

- **题目**

>题目描述
有 $C$ 头奶牛进行日光浴，第 $i$ 头奶牛需要 $minSPF[i]$ 到 $maxSPF[i]$ 单位强度之间的阳光。
每头奶牛在日光浴前必须涂防晒霜，防晒霜有 $L$ 种，涂上第 $i$ 种之后，身体接收到的阳光强度就会稳定为 $SPF[i]$，第 $i$ 种防晒霜有 $cover[i]$ 瓶。
求最多可以满足多少头奶牛进行日光浴

- **思路**
  - Monopati也是用到了这个思路。把l固定然后遍历r。但是贪心是要证明无后效性的。就是你这个牛子过了之后你能保证他后面没有可能匹配到别人。最适合的就是拿右值来排序
  - 我本来写的区间大小，但是这样子就和我通过统一左值来做的方法矛盾
  - 如果一方有‘容忍范围’（min-max），可以:固定一边（排序），扫描另一边，并用优先队列维护‘最紧急/最容易过期’的选项。”

- **AC代码**

```cpp
struct spf
{
    int low, hei;
};
struct fss
{
    int sp, fg;
};

void solve()
{
    int c, l;
    cin >> c >> l;
    vector<spf> cows(c);
    rep(i, 0, c - 1)
    {
        cin >> cows[i].low >> cows[i].hei;
    }
    vector<fss> choi(l);
    rep(i, 0, l - 1)
    {
        cin >> choi[i].sp >> choi[i].fg;
    }

    sort(all(choi), [](fss a, fss b)
         {
    if(a.sp!=b.sp)return a.sp<b.sp;
    else return a.fg>b.fg; });
    sort(all(cows), [](spf a, spf b)
         {
    if(a.low!=b.low)return a.low<b.low;
    else return a.hei>b.hei; });
    priority_queue<int,vector<int>,greater<int>> dui;
  
    int ans=0;
    int niuniu=0;
   
    for(int i=0;i<l;i++)
    {
        while(niuniu<c&&cows[niuniu].low<=choi[i].sp)
        {
            dui.push(cows[niuniu].hei);
            niuniu++;
        }
        while(!dui.empty()&&dui.top()<choi[i].sp)
        {
            dui.pop();
        }
        while(choi[i].fg>0&&!dui.empty())
        {
            ans++;
            choi[i].fg--;
            dui.pop();
        }
    }
    cout<<ans;
}
```

#### P2859 [USACO06FEB] Stall Reservations S(收录意义是学会读题以及请和Sunscreen一起学习)

- 这道题可以和上面三道题以及后悔贪心那道题一起看
- 个人认为这道题并不贪心，只是一个堆的使用典例。我认为是Monopati的前戏
- 这里主要在证明为什么用这样的贪心策略:先排序左端点，然后将右端点如堆。可以保证对于每一次的运算不会漏掉情况。因为可能漏掉的情况一定同时满足以下两个条件:左端点比当前位置更前，右端点比当前位置更前。可以简单的发现根据这样的排列不存在例外插入情况。
- 这里依旧贴出大根堆代码，用来多多评鉴。
- 这里有一些小细节，因为最后要输出每个牛在那个栅栏，这个细节调了挺久的

```cpp
sort(all(nums), [](hsh a, hsh b)
         {
    if(a.st!=b.st) return a.st<b.st;
    else return a.et<b.et; });

    priority_queue<pii, vector<pii>, greater<pii>> dui;
    vector<hsh> ans(n);
    int weilan = 1;
    for (int i = 0; i < n; i++)
    { // 对于第i头牛
        auto it = nums[i];
        int now=0;
        if (dui.empty())
        {
            dui.push({it.et, weilan});
            ans[i].et = weilan;
            ans[i].id = it.id;

            continue;
        }
        auto ljl = dui.top();

        if (it.st <= ljl.first)
        {
            weilan++;
            dui.push({it.et, weilan});

            now=weilan;
        }
        else
        {
            dui.pop();
            dui.push({it.et, ljl.second});
            now=ljl.second;
        }
        ans[i].et=now;
        ans[i].id=it.id;

    }
    cout << dui.size() << '\n';
    sort(all(ans), [](hsh a, hsh b)
         { return a.id < b.id; });
    for (auto jjj : ans)
    {
        cout << jjj.et << '\n';
    }
```

#### 数据抽象化构造

**用途**：根据贡献构造数组，处理复杂关系。  
**常见坑**：注意边界（i=1 时特殊处理）。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> b(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> b[i];
    vector<int> aa(n + 1);
    for (int i = 1; i <= n; i++) {
        int kk = (i == 1 ? 0 : b[i-1]);
        int pp = b[i] - kk;
        int pos = i - pp;
        aa[i] = (pos <= 0 ? i : aa[pos]);
        cout << aa[i] << ' ';
    }
    cout << '\n';
}
```

**复杂度**：O(n)，空间 O(n)。

### 构造数列

### 数列贪心构造

#### C. Cyclic Merging(贪心)

- **题目**
- >You are given $n$ non-negative integers $a_1,a_2,\ldots,a_n$ arranged on a ring. For each $1\le i< n$, $a_i$ and $a_{i+1}$ are adjacent; $a_1$ and $a_n$ are adjacent.
You need to perform the following operation **exactly** $n-1$ times:
 Choose any pair of adjacent elements on the ring, let their values be $x$ and $y$, and merge them into a single element of value $\max(x,y)$ with cost $\max(x,y)$.
Note that this operation will decrease the size of the ring by $1$ and update the adjacent relationships accordingly.
Please calculate the minimum total cost to merge the ring into one element.

>给你一个排列在环上的非负整数 $$$n$$$ 。对于每个 $$$1\le i&lt; n$$$ ， $$$a &#95; i$$$ 和 $$$a &#95; {i+1}$$$ 相邻； $$$a &#95; 1$$$ 和 $$$a &#95; n$$$ 相邻。
以下操作需要**精确** $$$n-1$$$ 次：
-在环上选择任意一对相邻的元素，设它们的值为 $$$x$$$ 和 $$$y$$$ ，并将它们合并成一个值为 $$$\max(x,y)$$$ ，代价为 $$$\max(x,y)$$$ 的元素。
注意，此操作将使环的大小减少 $$$1$$$ ，并相应地更新相邻关系。
请计算将圆环合并为一个元件的最低总成本。

- **错误想法**
  - 双指针：双指针/滑动窗口通常用于处理固定不变的序列，寻找满足某种条件的连续子段（比如和、最值等）。而这道题首先是环形，其次是他会破坏掉数字的结构
  - DP？数据范围2e5秒了肯定不是
  >2e5我们最好想一些数据结构或者贪心（某种意义上的排列）来优化这一切（logn或者n，这很常见）
- **思考路径(看完整清晰的请往下看，这是我个人的一个思路整理)**
  - 当我拆解数据 1 1 4 5 1 4 1的时候我总是会算错，这个样例我研究了20分钟我才研究出来他的正确合成方法:而这道题的正确做法就藏在我的试错里面:只是我忽略了:当我从小合并到大(其实这是猜猜看的结果)他最优
  - 贪心最大的难度就是让我相信：他是贪心
  - 相信他是贪心最主要的点在：对于每个数他的命运岔路口只有当左右两边的数字都大于他的时候。可以简单想到，通过更改(合成)左右两个数来改变消掉我们这个数的代价绝对不是最优，最优解**存在且仅存在于**他与隔壁的一个数字合体或着他与隔壁两个数字中更小的数字合体
  - 这里我们可以发现从最小的数字开始合并收益一定最大(如果从一个不是最大也不是最小的数字开始合并，他的消失他就可能会影响更小的数字合成代价变大。因为他消失了更小的数字只能和更大的数字合成了)

- **细节难点**：
  - 实现方法上需要学习的:**模拟环形**(模拟链表)以及左右更新
  - 大根堆的处理:要认清楚:**大根堆的最用只是帮你快速定位到最小的元素是谁**

- **AC代码**

```cpp

struct node
{
    int idx, num;
};

struct cmp
{
    bool operator()(const node &a, const node &b)
    {
        return a.num > b.num; // 小根堆逻辑
    }
};
void solve()
{
    int n;
    cin >> n;
    vi nums(n);
    vi left(n);
    vi right(n);
    left[0] = n - 1;
    right[n - 1] = 0;
    priority_queue<node, vector<node>, cmp> dl;
    rep(i, 0, n - 1)
    {
        cin >> nums[i];
        if (i != 0)
        {
            left[i] = i - 1;
        }
        if (i != n - 1)
        {
            right[i] = i + 1;
        }
        dl.push({i, nums[i]});
    }

    int cz = n - 1;
    ll ans=0;
    while (cz && !dl.empty())
    {
        auto hsh = dl.top();
        dl.pop();
        int idl = left[hsh.idx];
        int idr = right[hsh.idx];

        if(nums[idl]>nums[idr])ans+=nums[idr];
        if(nums[idl]<=nums[idr])ans+=nums[idl];
     //   cerr<<ans<<'\n';
        left[idr]=idl;
        right[idl]=idr;
        cz--;
    }
    cout<<ans<<'\n';
}
```

你以为到这里就结束了吗？并非
诚然这个算法很直观，但是却不是最简单，没有找到这道题最本质的一点
**我们容易发现**: merge 取的是 max，这意味着**邻居只会越变越大**。对于一个当前的最小值来说，“现在”永远是它能遇到的最好时机。任何推迟操作都可能导致它身边的邻居变大，从而增加它最终被消除的代价。

!这样子我们就能获得时间复杂度O(n)，空间复杂度O(1)的算法:

```cpp
void solve()
{
    int n,first,now=0;
    ll ans = 0;
    cin >> n;
    cin >> first;
    int last = first;
    int mx=first;
    rep(i, 2, n)
    {
        cin >> now;
        mx = max(mx, now);
        ans += max(last, now);
        last = now;
    }
    ans+=max(first,now);
    cout<<ans-mx<<'\n';
}
```

- 后话:**我们该如何证明贪心是对的**
  - 如果数据范围是 $N=2 \times 10^5$，而且不像线段树/图论，那只能是贪心或者数学推导。
  - 贪心规则，检查有没有:后效性，更优？

#### 小红的区间构造->数列前缀和构造（区间重叠用前缀和）

- **算法** ：前缀和
- **思路&错误原因**
  - 这道题想要你构造区间，最坏情况是所有点都是一个区间。题目给出来的条件就非常前缀和，直接差分处理然后一个一个insert左右端点就完事儿了
- **注意事项**
  - 注意数据范围**提前退出**以免mle（致敬我调了一个晚上的点）
  - 注意学习左右端点的处理方法：因为是差分处理所以两个数组大小一定一样
- **AC代码**

```cpp
    void solve()

{
    int n, m;
    cin >> n >> m;
    vi nums(n + 2);
    vi cf(n + 2);
    int sum=0;
    for (int i = 1; i <= n; i++)
    {
        cin >> nums[i];
        sum += nums[i];
        if (nums[i] > m)
        {
            cout << "-1" << '\n';
            return;
        }
        cf[i] = nums[i] - nums[i - 1];
    }
    if(sum < m){cout << -1 << '\n';return;}
    cf[n + 1] = nums[n + 1] - nums[n];
    vi left;
    vi right;
    for (int i = 1; i <= n + 1; i++)
    {
        if (cf[i] > 0)
            for (int j = 0; j < cf[i]; j++)
                left.push_back(i);
        if (cf[i] < 0)
            for (int j = 0; j < abs(cf[i]); j++)
                right.push_back(i - 1);
    }
    int k = left.size();
    int gap = m - left.size();
    if (left.size() > m)
    {
        cout << "-1" << '\n';
        return;
    }
    ll cnt=0;
    for (int j = 0; j < k; j++)
    {
        cnt+= right[j] - left[j] + 1;
    }
    if(cnt<m)
    {
         cout << "-1" << '\n';
        return;
    }

    for (int j = 0; j < k; j++)
    {
        if(gap==0)
        cout<<left[j]<<' '<<right[j]<<'\n';

        if (right[j] - left[j] < gap&& gap!=0)
        {    for (int i = left[j]; i <=right[j]; i++)
            {
                cout<<i<<' '<<i<<'\n';
            }
            gap-=(right[j] - left[j]);
            continue;
        }
        if (right[j] - left[j]  >= gap && gap!=0)
        {    for (int i = left[j] ; i < left[j]+gap; i++)
            {
                cout<<i<<' '<<i<<'\n';
            }
         
            cout<<left[j]+gap<<' '<<right[j]<<'\n';
            gap=0;
            continue;
        }

    }
}
```
