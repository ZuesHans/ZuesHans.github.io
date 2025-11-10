---
title: wp_11_2
date: 2025年11月7日 02点45分
tags:
    - 算法
    - C++
cover:
    /img/cover/熏鱼我爱你.png
---



    From 2025年11月3日
  
## 新题新思路
>
>大概是我绞劲脑汁都没想到如此精妙的解法

### 简单 Dijkstra 模板题

#### P4779 【模板】单源最短路径（标准版）

- **题号**: P4799
- **链接**: [题目链接](https://www.luogu.com.cn/problem/P4799)
- **算法类型**: 图论模板
- **AC 代码**:

```cpp
void solve()
{
    ll n,m,s;
    cin>>n>>m>>s;
    //前面是点,后面是距离
    vector<vector<pair<int,ll>>> mp(n+1);
    rep(i,0,m-1)
    {
        int u,v,w;
        cin>>u>>v>>w;
        mp[u].push_back({v,w});
   //     mp[v].push_back({u,w});这道题是有向边所以不要入两次！！
    }

    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>>pos ;
    vector<ll> dist(n+1,LINF);
    dist[s]=0;
    pos.emplace(0,s);

    while(!pos.empty())
    {
        auto [nowd,nowp] = pos.top();
        pos.pop();
        if(nowd>dist[nowp])continue;
        for(auto [nextp,nextd]:mp[nowp])
        {
            if(dist[nextp]>dist[nowp]+nextd)
            {
                dist[nextp]=dist[nowp]+nextd;
                pos.emplace(dist[nextp],nextp);
            }
        }
    }
    rep(i,1,n)
    {
        cout<<dist[i]<<' ';
    }
}

```

- **注意事项**:
  - 注意Dijkstra算法用最小堆优化可以时间复杂度最低
  - Dijkstra算法只能处理非负权路径问题
  - 为什么不用队列？：贪心最快，如果是菊花图复杂度会退化到nm
  - 含负权路用什么算法？用队列
- **思路**:
  - 认真研读并学习114514次

### 数据结构

#### Cool Partition

- **题号**: Div3C
- **链接**: [题目链接]()
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

### DP

#### 最大子段和
>
># P1115 最大子段和
>
>## 题目描述
>
>给一个长度为 $n$ 的序列 $a$，选出其中连续且非空的一段使得这段和最大。
>
>## 输入格式
>
>第一行是一个整数，表示序列的长度 $n$。
>第二行有 $n$ 个整数，第 $i$ 个整数表示序列的第 $i$ 个数字 $a_i$。
>
>## 输出格式
>
>输出一行一个整数表示答案。
>
>#### 数据规模与约定
>
>- 对于 $40\%$ 的数据，保证 $n \leq 2 \times 10^3$。
>- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 2 \times 10^5$，$-10^4 \leq a_i \leq 10^4$。

- **AC代码**

```cpp

void solve()
{
    int n;
    cin>>n;
    vi nums(n+1);

    for (int i=1;i<=n;i++) cin>>nums[i];
    vi dp(n+1);
    int ans=-4545556565;
        for(int j=1;j<=n;j++)
        {
            dp[j]=dp[j-1]+nums[j];
            if (dp[j]<=0) dp[j]=nums[j];
            ans=max(ans,dp[j]);
        }
cout<<ans<<'\n';
}

```

---

## 错题整理
>
>记录错题，可能只是神秘UB，还有伟大的边界处理

### 复杂度优化

#### P2058 [NOIP 2016 普及组] 海港

- **错点**：TLE
- 错题记录：

> 一开始我想用quene来模拟时间维度上的滑动，结果发现quene不支持遍历。于是用了deque
> 第一次本地WA：我想用set记录每艘船上面的游客种类，然后和他的时间一起emplace进去队列，ans+=每一个时间点的种类。属于是读错题了。
> 第二次提交TLE：我想那就开一个map来存所有数据，然后遍历放进set里面进行去重...数据范围K总和3e5，n为2e5随爆炸
> 后来乱交了两罚，因为想不通
>
- 打开题解：用桶来装数字，当这个桶里面的数字是第一次被装到1，他就多一个种类，反之少一个种类。需要将出队判断移到后面。实现在线处理ans，实在精妙

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
### 边界处理
#### P2004 领地选择
- **分析**
  - 题目是非常简单而且典型的滑动窗口二维前缀和。最大的问题出在你滑动窗口的时候的推导式：详情见P2280 HNOI2003 激光炸弹
- **出错的推导点**`int hsh = qzh[i + c-1][j + c-1] + qzh[i-1][j-1]- qzh[i + c-1][j-1] - qzh[i-1][j + c-1];`
- 首先注意减去边界格的时候要-1往里面一格（因为要包含到ij），然后是因为是C*C的数组所以要往里面移动一格（请你以后先列式子算一下）
---

## 赛后补题
>
>网络赛也是赛
>
### 11月2日华南理工大学秋季新生赛（第一场）

- **名次** 总榜36，校内榜5
- **存在问题** 签到题出太慢（可恶的devcpp），看不懂题目（泥工怎么出题不给题目名词解释！！太不规范了！！），D题读题失误，错写dp！！（有环图！）

#### 因数分解

- **题号**: G
- **链接**: [题目链接](https://ac.nowcoder.com/acm/contest/121614/G)
- **算法类型**: 二分查找
- **错误原因**:
  - 看不懂题目在讲啥
  
>有 **n** 堆石子排成一行，从左到右依次编号为 **1** 到 **n**，第 **i** 堆有 \( a_i \) 个石子。trilliverse 和宇暧微霄两人轮流进行游戏，trilliverse 先手。
>每回合，当前玩家必须选择**最左边的石子数大于 0 的石子堆**（即下标最小的非空石子堆），石子数量为 \( a_i \)，并从中取走 \( k \) 个石子，其中 \( k \) 必须满足以下条件之一：
> $$\ k = a_i $$
>\[\forall i,\ a_i \equiv 0 \pmod{a_i - k}\]
>>!!对于每一个 $ i $，$ ai $ 都能被 $ ai - k $ 整除，即 $ ai - k $ 是 $ ai $ 的除数。

- **AC 代码**:

```cpp
  void solve()
  {
    int n;
    cin >> n;
    bool by = (n % 2 == 1);
    vi nums(n + 1);
    rep(i, 1, n)
    {
        int d;
        cin >> nums[i];
    }
    if (n == 1)
    {
        cout << "CandidateMaster" << '\n';
        return;
    }
    rep(i, 1, n)
    {
        if ( i % 2 == 0)
        {
            if (nums[i] != 1)
            {
                cout << "LegendaryGrandmaster" << '\n';
                return;
            }
        }
        else if (  i % 2 == 1)
        {
            if (nums[i] != 1)
            {
                cout << "CandidateMaster" << '\n';
                return;
            }
        }
    }
    if (by)
        cout << "CandidateMaster" << '\n';
    else
        cout << "LegendaryGrandmaster" << '\n';
  }
```

- **解析**:
  - **关键点**想到对于每个人来说取石子的最优解是==当石子大于1的时候取ai-1==
  - 可以想到，先手拿到的是奇数位上的控制权，后手拿到偶数上的控制权。一旦某人拿到大于1的数字，就可以通过取k个（ai-k==1）来拿到后续的控制权。从而把后面所有的情况压缩为1
  - 博弈疑问？为什么可以压缩?万一后面的人可以通过在后来拿到主动权来改变先后手优势吗？答：注意到如果要改变先后手优势，你就得走到别人的位置上（先手走偶数，后手走奇数）如果后面还有主动权，我大可以跳过前面的所有选项来获得我必有的控制权。
- **改进思路**:
  - 思维题，一般这种简单博弈都不要想的太难。一般某个人能拿到绝对主动权，看绝对主动权给谁最重要

#### 爆破鸭科夫

- **题号**: L
- **链接**: [题目链接](https://ac.nowcoder.com/acm/contest/121614/L)
- **算法类型**: 二分查找
- **错误原因**:
  - 看不懂题目在讲啥
- **AC 代码**:

```cpp

```

- **注意事项**:
  - 注意二分查找的左右边界初始化。
  - 确保 check 函数逻辑正确。
- **改进思路**:
  - 考虑严格 cnt == k 的情况，调整 check 函数

#### 水群

- **题号**: D
- **链接**: [题目链接](https://ac.nowcoder.com/acm/contest/121614/D)
- **算法类型**: Disjkstr最短路
- **错误原因**:
  - 看成DP了！！有向无环有向无环有向无环！
  - 迪克算法还在追我
  - 最短路问题
- **AC 代码**:

```cpp
void solve()
{
【输入】
    vector<vector<pair<ll, int>>> mp(n + 1);
    for (int i = n-1; i >= 1; i --)
    {
        mp[i].push_back({x, i +1});
        mp[i + 1].push_back({x, i});
    }
    rep(i, 0, m - 1)
    {
        int a, b;
        cin >> a >> b;
        mp[a].push_back({y, b});
     //   mp[b].push_back({y, a});
    }
【迪克算法】
    cout<<dist[1]<<'\n';
}
```

- **思路**:
  - 没什么好说的，迪克算法模板，我都懒得贴出代码，详情请见[简单 Dijkstra 模板题](#p4779-模板单源最短路径标准版)

#### 代号N

- **题号**: E
- **链接**: [题目链接](https://ac.nowcoder.com/acm/contest/121614/E)
- **算法类型**: 带权无向图[相似题目学习](https://www.luogu.com.cn/problem/P2097)
- **错误原因**:
  - 看不懂一些[基础名词](#附件)

> 精简题干: 定义一棵树:共n个节点:一个度数为3的节点,若干个度数为2的节点,3个度数为1的节点.给出n-1条边,给出两个端点以及边权,可以操作k次将某条边边权变成0.求根节点到叶节点的度数最大值的最小值.

- **AC 代码**:

```cpp
struct edge
{
    int to, w;
};
int cmp(const vi &sums)
{
    if(sums[0]>sums[1])
    {
        if(sums[0]>sums[2])
        {
            return 0;
        }
        else return 2;
    }
    else
    {
        if(sums[1]>sums[2])
        {
            return 1;
        }
        else return 2;
    }
}
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<edge>> mp(n + 1);
    vi nums(n + 1);
    for (int i = 0; i < n-1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        mp[u].push_back({v, w});
        mp[v].push_back({u, w});
        nums[u]++;
        nums[v]++;
    }
    auto it = find(all(nums), 3);
    int sdot = (it - nums.begin());
    vector<vector<int>> chain(3);
    vi sums(3);
    vector<priority_queue<int>> pq(3);                     // <--- 改动：为每条链维护大根堆
    for (int i = 0; i < 3; i++)
    {
        queue<pii> pos;
        pos.emplace(mp[sdot][i].to, sdot);
        chain[i].push_back(mp[sdot][i].w);
        sums[i] += mp[sdot][i].w;
        pq[i].push(mp[sdot][i].w);                         // <--- 改动：把边权加入堆
        while (!pos.empty())
        {
            auto [now, par] = pos.front();
            pos.pop();
  
            for (auto &nextdot : mp[now])
            {
                if (nextdot.to == par)
                    continue;
                else
                {
                    chain[i].push_back(nextdot.w);
                    sums[i] += nextdot.w;
                    pq[i].push(nextdot.w);             // <--- 改动：把遍历到的边权加入堆
                    pos.emplace(nextdot.to,now);
                }
            }
        }
    }
    while(k--)
    {
        int idx = cmp(sums);
        if (pq[idx].empty()) break;                    // 防止空链
        int mx = pq[idx].top(); 
        pq[idx].pop();         // O(log len)
        sums[idx] -= mx;
        // 下面的两行可以删掉，保留只为保持原结构
        // sums[cmp(sums)] -= *max_element(all(chain[cmp(sums)]));
        // chain[cmp(sums)].erase(max_element(all(chain[cmp(sums)])));
    }
    cout << sums[cmp(sums)];
}
```

- **思路剖析**:
  - 非常简单的大数据和的最大值的最小值.解法一:`sort`之后逐个`pop_back()`(注意vector的pop是最后一位,所以要从小到大排序).解法二:维护最大根堆`priority_queue<int>`,n次操作复杂度nlogn.
  - 事实上解法一是优解,但是为了学习这个有意思的容器这道题用的做法是最大根堆
  - 这道题的难点是读懂题...然后是建带权无向图...依旧模板.
  - **记得**带权无向图两个端点都pushback一次
  - 然后就是用bfs带着上一个节点和下一个节点广度优先探索(这个还能用dfs解法,下文附上,作为图论路径转移学习,请严肃学习114514次)

 > 大部分图论用BFS做,在面临剪枝需求/需要回溯/所有方案的时候用DFS做

- **细节注意**:
  - 二维拓展数组记得这样开`vector<vector<edge>> mp(n + 1);`不会爆空间
  - Cpp17不支持结构体取地址,就这么写`auto [now, par] = pos.front();`
  - 记得k次操作不一定用玩一定要提前出循环`if (pq[idx].empty()) break;`以免UB

- **新结构**
  - `priority_queue` : 自动维护堆的“插入+弹出最大/最小”工具，“贪心/最短路/Top-K/滑动窗口最大值” 都能靠它快速实现
  - 注意优先队列没办法删除除了堆顶以外的元素,所以**注意**`if (d > dist[u]) continue;`

| 声明代码 | 含义 |
|----------|------|
| `priority_queue<int> pq;` | **大根堆**（默认，队头最大） |
| `priority_queue<int, vector<int>, greater<int>> pq;` | **小根堆**（队头最小） |
| `priority_queue<pair<int,int>> pq;` | `pair` 大根堆（`first` 越大越前） |
| `priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;` | `pair` 小根堆（`first` 越小越前） |

---

| 操作 | 代码 | 说明 | 复杂度 |
|------|------|------|--------|
| 插入 | `pq.push(x);` | 插入元素 `x` | **O(log n)** |
| 取顶 | `pq.top();` | **只读** 队头 | **O(1)** |
| 删除顶 | `pq.pop();` | 删除队头 | **O(log n)** |
| 判空 | `pq.empty();` | 是否为空 | **O(1)** |
| 大小 | `pq.size();` | 元素个数 | **O(1)** |

#### 爆零什么的千万不要啊

- **题号**: A（最难，防AK题）
- **链接**: [题目链接](https://ac.nowcoder.com/acm/contest/121614/A)
- **算法类型**: 二分查找
- **记录原因**:
  - 非常有意思的处理方法，已严肃学习
- **AC 代码**:

```cpp

```

- **注意事项**:
  - 注意二分查找的左右边界初始化。
  - 确保 check 函数逻辑正确。
- **改进思路**:
  - 考虑严格 cnt == k 的情况，调整 check 函数

### 11月2日晚牛客挑战赛

#### 小红的区间构造

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

### 2025年11月5日晚上牛客基础组

#### 子段异或和

- **题号**: D
- **链接**: [题目链接](https://ac.nowcoder.com/acm/contest/120453/D)
- **算法类型**: 异或，前缀和
- **AC 代码**:

```cpp
void solve()
{
    int n;
    cin>>n;
    vi nums(n + 1);
    nums[0] = 0;
    vi cf(n + 1);
    map<int, int> bg;
    int ans = 0;
    bg[0]++;
    for (int i = 1; i <= n; i++)
    {
        cin >> nums[i];
        cf[i] = cf[i - 1] ^ nums[i];
        int key = cf[i] ^ 0; // a^b=0 ->a^0=b
        if (bg.find(key) != bg.end())
        {
            ans += bg[key];
        }
        bg[cf[i]]++;
    }

    cout << ans;
}

```

- **异或前缀和思路**:
  - 异或的“逆运算”就是它自己。
  - 所以通过求异或前缀和来实现对 [l, r] 区间的异或和的O(1)查找——>就等于 cf[r] ^ cf[l-1]。
  - 异或的一些小妙招：
    - 寻找出现次数偶数/奇数次数数列里面出现奇数/偶数次数的数
    - N堆石子，每次可以取任意多个至少一个。异或和==0先手必败

- **改进技巧：哈希表**:
  - O(N) 优化 (使用哈希表)： 我们用一个哈希表 countMap 存储历史上的前缀和 cf[j] 出现过的次数（复杂度O(logN)
  - 能O(1)查询的字段和都可以采用

>“前缀和+哈希表”是处理“子数组/子段”的小妙招

#### 子段乘积（简单）

- **题号**: C
- **链接**: [题目链接](https://ac.nowcoder.com/acm/contest/120453/C)
- **算法类型**: 滑动窗口（双指针）
- **AC 代码**:

```cpp
void solve()
{
    int n, k;
    cin >> n >> k;
    vi nums(n + 1);
    rep(i, 1, n)
    {
        cin >> nums[i];
    }

    int left = 1;
    int right = 1;
    int ans = 0;
    int sz = 1;
    int mod = 998244353;
    while (right <= n)
    {
        while (right <= n && left + k > right)
        {
            if (nums[right] == 0)
            {
                left = right + 1;
                right = left;
                sz = 1;
                continue;
            }
            sz = (sz * nums[right]) % mod;
            right++;
        }
        if (right > n || left > n - k)
            break;

       // if (right - left == k)这是保险起见之举，事实上没有必要
            ans = max(ans, sz);

        sz = (sz * inverse_fermat(nums[left], mod)) % mod;
        left++;
    }
    cout << ans;
}

```

- **注意事项**:
  - 1-Based存数方式lr初始在1
  - 记得滑动窗口的while，不要惯性思维认为*答案更新*/*大小比较*都在while的末尾。while只是一个路径，前面是快指针移动，后面是慢指针移动。中间夹着你的数字更新
  - 适用于固定区间长度的数据处理
  - 维护r的界限和nums[r]的更新逻辑是难点

### [Div1+2CF](https://codeforces.com/contest/2164)

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

### 广州大学2024新生赛VP

#### 在ACM里面打ACM（map的使用：模拟：数据处理）

-**AC代码**

```cpp
struct hsh
{
    bool accepted = false;
    int wrangans = 0;
    int time = 0;
};
void solve()
{
    int n;
    cin >> n;
    map<string, map<char, hsh>> ljl;
    map<string, int> sumtime;
    map<string, int> sumac;
    string ans;
    for (int i = 0; i < n; i++)
    {
        string n;
        char th;
        bool ac;
        int tme;
        cin >> n >> th >> ac >> tme;
        ans = n;
        if (ljl[n][th].accepted)
            continue;
        if (ac)
        {
            ljl[n][th].time += tme;
            ljl[n][th].time += ljl[n][th].wrangans * 20;
            ljl[n][th].accepted=true;
            sumac[n]++;
            sumtime[n] += ljl[n][th].time;
        }
        else
        {
            ljl[n][th].wrangans++;
        }
    }

    for (auto it : ljl)
    {
        if (sumac[it.first] > sumac[ans])
        {
            ans = it.first;
        }
        if (sumac[it.first] == sumac[ans])
        {
            if (sumtime[it.first] < sumtime[ans])
            {
                ans = it.first;
            }
        }
    }
    cout<<ans<<' '<<sumac[ans]<<' '<<sumtime[ans];
}

```

#### [逆=辶+屰](https://ac.nowcoder.com/acm/contest/97487/B)

放在这里是为了告诉你：正确分析复杂度是多么的重要。。。以及数学好真的很重要
以及有时候大脑真的不要把题目想的太难，可以根据过题人数考虑是否需要考虑唐氏做法
这道题纯纯预处理一下就行了
//可能我通宵了，大脑垃圾太多了，竟然放过了一道这么唐氏且简单还珍贵的题目
>来自数院的小楠喜欢研究数学，他给定了一个数字 \( n \)，然后提出了 \( q \) 个问题，每个问题给出两个整数 \( k \) 和 \( r \)，现在他想知道，在他的每个问题中，他给出的数字 \( n \) 是否满足**不少于 \( k \) 个不同的正整数** \( c_1, c_2, c_3, \dots, c_k \) 能够使得：
\[
n \mod c_i = r, \quad i = 1, 2, 3, \dots, k.
\]
其中 `mod` 代表求余，例如：  
 \( 5 \mod 2 = 1 \)  
\( 8 \mod 2 = 0 \)
>第一行输入两个整数 n(1≤n≤1×10^6), q(1≤q≤1×10^4)，
分别代表小楠给出的这个数字 n 和提出的问题数量 q。
接下来 q 行，每行输入两个整数 k(1≤k≤1×10^6), r(0≤r<n)，
代表 n 是否满足有不少于 k 个不同的正整数 c1,c2,...,ck 使得 n mod ci = r。
>输出共 q 行，
如果 n 能够满足第 i 个问题，则输出 "YES"，
否则输出 "NO"。
（输出不含双引号，且必须严格大写）
>

```cpp
void solve()
{
    int n, q;
    cin >> n >> q;
    vi nums(n + 1);
    for (int i = 1; i <= n; i++)
    {
        nums[n % i]++;
    }
    for (int i = 1; i <= q; i++)
    {
        int k, r;
        cin >> k >> r;
        if (k <= nums[r])
            cout << "YES" << '\n';
        else
            cout << "NO" << '\n';
    }
}
```

---

## 附件

1.图论名词

| 名词 | 无歧义定义（竞赛语境） |
|------|-----------------------|
| **简单图** | 不含 **自环** 且任意两顶点之间 **至多一条边** 的图。 |
| **多重图** | 允许同一对顶点之间存在 **多条边**（平行边）。 |
| **自环** | 起点与终点为同一顶点的边，记作 \((u,u)\)。 |
| **邻接** | 若存在边连接顶点 \(u\) 与 \(v\)，则称 \(u\) 与 \(v\) **相邻**。 |
| **度数** | 顶点 \(u\) 所连接的 **边数**；无向图中记作 \(\deg(u)\)，有向图分为 **出度** 与 **入度**。 |
| **路径** | 顶点序列 \(v_0, v_1, \dots, v_k\)，相邻顶点间均有边；长度为边数 \(k\)。 |
| **简单路径** | 路径中 **无重复顶点**。 |
| **环** | 起点与终点相同的路径（闭合路径）。 |
| **简单环** | 除起点与终点外 **无重复顶点** 的环。 |
| **连通** | 无向图中任意两顶点之间 **存在路径**。 |
| **强连通** | 有向图中任意两顶点 \(u,v\) 均满足 \(u \to v\) 与 \(v \to u\) 均有路径。 |
| **连通分量** | 无向图的 **极大连通子图**。 |
| **强连通分量 (SCC)** | 有向图的 **极大强连通子图**。 |
| **树** | **无向连通无环图**；\(n\) 个顶点恰有 \(n-1\) 条边。 |
| **生成树** | 连通无向图的 **无环连通子图**，包含所有顶点。 |
| **叶子节点** | 度数为 1 的节点（树中常见）。 |
| **根节点** | 树中指定的起点节点（有根树）。 |
| **子树** | 以某节点为根及其所有后代构成的树。 |
| **边权** | 每条边附加的数值（整数/实数），常表示距离、费用等。 |
| **加权图** | 边带有权值的图。 |
| **最短路径** | 路径上 **边权之和最小** 的路径。 |
| **负权边** | 权值为负数的边。 |
| **负环** | 环上权值和为负的环。 |
| **二分图** | 顶点可分为两个互斥集合 \(A,B\)，且 **所有边均连接 \(A\) 与 \(B\)**。 |
| **完全二分图** | 二分图中 \(A\) 中每个点与 \(B\) 中每个点均有边。 |
| **匹配** | 二分图中 **边集无公共顶点** 的子集。 |
| **最大匹配** | 包含 **边数最多** 的匹配。 |
| **完美匹配** | 匹配覆盖 **所有顶点**。 |
| **DAG** | **有向无环图**（Directed Acyclic Graph）。 |
| **拓扑序** | DAG 的顶点线性序列，满足：若 \(u \to v\)，则 \(u\) 在 \(v\) 前。 |
| **割点** | 删除后 **连通分量数增加** 的顶点。 |
| **桥** | 删除后 **连通分量数增加** 的边。 |
| **点双连通** | 删除任意单个顶点后仍连通（无割点）。 |
| **边双连通** | 删除任意单条边后仍连通（无桥）。 |
| **欧拉路径** | **经过每条边恰好一次** 的路径。 |
| **欧拉回路** | **闭合** 的欧拉路径。 |
| **哈密顿路径** | **经过每个顶点恰好一次** 的路径。 |
| **哈密顿回路** | **闭合** 的哈密顿路径。 |
| **最小生成树 (MST)** | 连通加权无向图中 **边权和最小** 的生成树。 |
| **最大流** | 从 **源点** 到 **汇点** 的 **最大流量**（容量限制）。 |
| **最小割** | 容量和最小的 **割集**，等于最大流（最大流最小割定理）。 |
| **残余网络** | 网络流中记录 **剩余容量** 的辅助图。 |
| **增广路径** | 残余网络中从源到汇的路径，用于提升流量。 |
| **LCA** | 树上两节点 **深度最大** 的公共祖先（最近公共祖先）。 |
| **树直径** | 树上 **最长简单路径** 的长度。 |
| **差分约束** | 一组形如 \(x_i - x_j \leq c_k\) 的不等式，可转化为最短路求解。 |
| **费用流** | 每单位流量有费用，求 **最小费用** 的 **最大流**。 |
