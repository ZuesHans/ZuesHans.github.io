---
title: wp_动态规划
date: 2025-12-06
tags:
    - 算法
    - DP

cover: /img/cover/picg_5.png
math: true
---

## 动态规划入门

- **我该怎么看出这是一道DP**
  - 求*最大/小值*求*方案数量*求*子序列*
  - 贪心做不了(有反例)
  - 依赖前面的值，无后效性

- **怎么写DP**
  - 状态是谁？状态有哪些？状态必须包含所有能够影响下一阶段决策的信息
  - 怎么转移？dp[i]是从哪里转移过来的？怎么转移代价最小/收益最大/能计算全部路径？
  - 初始状态

- **DP数组怎么写**
  - 一般求什么什么就是DP数组
  - 要不要开二维？就问自己:“如果有两个人同时走到第 $i$ 步，但他们之前的经历不同，这种不同会限制他们接下来的选择吗？”
  - 能不能压缩？用滚动数组来代替二维，我们只考虑会影响结果的值。只记我们需要记的，过期的扔掉。

### DP原理

#### 数字三角形

**用途**：从顶到底或底到顶，求最大路径和。  
**常见坑**：从底到顶递推可省去边界处理。

```cpp
void solve() {
    int n;
    cin >> n;
    int sjx[100][100];
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            cin >> sjx[i][j];
    for (int i = n-2; i >= 0; i--)
        for (int j = 0; j <= i; j++)
            sjx[i][j] += max(sjx[i+1][j], sjx[i+1][j+1]);
    cout << sjx[0][0] << '\n';
}
```

**复杂度**：O(n²)，空间 O(1)（直接在输入数组上修改）。

#### 2.5 记忆化搜索

**用途**：从未知到已知递推，适合复杂状态转移。  
**与 DP 区别**：

- DP：从已知到未知，严格顺序，循环实现，常数小。
- 记忆化搜索：从未知到已知，递归实现，需状态数组防重复计算。

```cpp
vector<int> mama(100230, -1);
int dfs(int a) {
    if (a == 1) return 1;
    if (mama[a] != -1) return mama[a];
    int cnt = 1;
    for (int i = 1; i <= a / 2; i++)
        cnt += dfs(i);
    mama[a] = cnt;
    return cnt;
}
void solve() {
    int n;
    cin >> n;
    cout << dfs(n) << '\n';
}
```

**复杂度**：O(n²)，空间 O(n)（状态数）。

---

### 线性DP

#### 最大子段和
>
> P1115 最大子段和
>
>题目描述
>
>给一个长度为 $n$ 的序列 $a$，选出其中连续且非空的一段使得这段和最大。
>
> 输入格式
>
>第一行是一个整数，表示序列的长度 $n$。
>第二行有 $n$ 个整数，第 $i$ 个整数表示序列的第 $i$ 个数字 $a_i$。
>
> 输出格式
>
>输出一行一个整数表示答案。
>
> 数据规模与约定
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

#### *G. Mukhammadali and the Smooth Array

##### 非常有意思的题目，请严肃学习1e9次题解

- **题号**: G
- **链接**: [题目链接](https://codeforces.com/contest/2167/problem/G)
- **算法类型**: DP 题目拆解与优化
- **错误原因**:
  - 贪心局部决策与回退混乱，无法考虑全局最优解
  - 贪心只看“能不能接”，没看“值不值”
- **AC 代码** 做法一：逆向加权LIS:

```cpp
void solve()
{
    int n;
    cin >> n;
    vi a(n + 1);
    vi c(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int d;
        cin >> d;
        a[i] = d;
    }
    int sumc=0;
    for (int i = 1; i <= n; i++)
    {
        cin >> c[i];
        sumc+=c[i];
    }
    if (n == 1)
    {
        cout << "0\n";
        return;
    }
    vi dp(n+1);
    for(int i=1;i<=n;i++)
    {
        dp[i]=c[i];
        for(int j=1;j<i;j++)
        {
            if(a[j]<=a[i])
            {
                dp[i]=max(dp[i],dp[j]+c[i]);
            }
        }
    }
    int hsh=*max_element(dp.begin()+1,dp.end());
    cout<<sumc-hsh<<'\n';
}
```

- **做法解析**:
  - 逆向思维：将修改价值和最小 -> 一定不用修改价值和最大
  > 首先我们可以知道,如果贪心修改会发现你对这个值a[x]得修改会影响后面数列大小关系的全局，就不满足DP里面最有子解以及有向无环的改变策略。对于每个需要修改的a[x]你需要判断其修改后一定不影响后面解集。！但是！如果你a[i+1]改大了，可能后面开销会大，如果你a[i]改小了，可能反过来不满足前面的序列增减
    **决策相互耦合 → 形成环 → 无法 DP**
    >>事实上正向也能做，但是不是贪心
  - 逆向思维==>当子集为LIS时这几个位置是一定不用修改的
   >这时候会有个疑问：对于没有加进LIS队伍的的数字是否一定保证他们有一个解且这个解不会影响LIS队伍中元素的修改？
   显而易见是一定的。
   问题二：对于没有加进lis的队伍有没有可能因为别人被修改过从而更优剩下了自己修改的开销？
   对于 LIS 他是‘LIS 资格证’，而不是‘LIS 全家桶’。将原数组的 LIS 算完之后剩下的点都是离散的
   **更加规范化的表达**：我们求出的 max(dp[i]) 对应的非降子序列，是一个 局部最优解（以某个 i 结尾），但它不一定包含所有可保留点。未被选中的点是『可独立修改』的，因为它们不参与最优链
- **思路**:
  - 最小修改成本,→ 最大保留收益,本题
  - 最小删除次数,→ 最长上升子序列,LIS
  - 最小交换次数,→ 逆序对计数，冒泡排序
- 为何最优解：
  当问题从寻找如何修改变成寻找lis时（带权重的LIS），我们知道接下来要最大化LIS权和，然后发现有重叠子问题（其实lis就是非常适合dp的），直接dp；
  ==所有单调子序列问题，本质都是 DAG 上的最长路径。==
  ==DP 转移 = 枚举前驱，max = 最长路径。==
- **AC 代码** 做法二 顺序dp:

```cpp
void solve()
{
    int ans = 1e18;
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
 
    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
    }
 
    vector<int> cpy = a;
    sort(cpy.begin(), cpy.end());
    int m = unique(cpy.begin(), cpy.end()) - cpy.begin();
 
    vector<int> dp(m);
    vector<int> mn(m);
    int cmn = 1e18;
    cpy.resize(m);
    for (int i = 0; i < m; i++)
    {
        if (a[0] == cpy[i])
        {
            dp[i] = 0;
        }
        else
        {
            dp[i] = c[0];
        }
        cmn = min(cmn, dp[i]);
        mn[i] = cmn;
    }
 
    for (int i = 1; i < n; i++)
    {
        cmn = 1e18;
        vector<int> cpn(m);
        for (int j = 0; j < m; j++)
        {
            int tp;
            if (a[i] == cpy[j])
            {
                tp = 0;
            }
            else
            {
               tp = c[i];
            }
            tp+=mn[j];
            dp[j] = tp;
            //mn[i] = cmn;
            cmn = min(cmn,dp[j]);
            cpn[j] = cmn;
        }
        mn = cpn;
    }
 
    cout << mn[m-1] << '\n';
    //cout << flush;
}
```

- **表达方式学习**:
  - `sort(cpy.begin(), cpy.end());`
    `int m = unique(cpy.begin(), cpy.end()) - cpy.begin();`
    这一步是为cpy去重`unique`函数。然后获得去重后容器的大小（不能用size！！**unique 不改变容器大小！**）。
    记得unique前==先排序==
  - cpy.resize(m)重新变更容器大小

### 位运算DP

#### P4310 绝世好题

>**不辜负他的题目名字，确实是绝世好题**

- **题目**

>给定一个长度为 $n$ 的数列 $a_i$，求 $a_i$ 的子序列 $b_i$ 的最长长度 $k$，满足 $b_i \& b_{i-1} \ne 0 $，其中 $2\leq i\leq k$， $\&$ 表示位运算取与。

- **解析**：有脑子的人一眼就能写出dp方程，解法类似于求LIS，但是这是n方做法，本题数据范围1e5。必然要想出一种nlogn级别的优化，怎么优化呢？实现上这是一种位运算特有的思路:每一个位置拆开来进行dp

- **AC代码**

```cpp
vi dp(32,0);
     int zuida=-1;
    for (int hsh : nums)
    {
     
        for (int i = 0; i < 32; i++)
        {
            if ((hsh >> i) & 1) {
                zuida=max(dp[i]+1,zuida);
            }
        }
          for (int i = 0; i < 32; i++)
        {
            if ((hsh >> i) & 1) {
                dp[i]=zuida;
            }
        }
    }

cout<<zuida;
```

---

### 01 背包（一维/二维）

**用途**：每个物品选或不选，求最大价值（不要求装满/要求恰好装满）。  
**常见坑**：

- 一维数组需倒序循环，防止覆盖。
- 恰好装满需初始化 dp[0]=0，dp[1...v]=-INF。
- 注意 long long 防溢出。

#### 一维数组

```cpp
void solve() {
    int n, v;
    cin >> n >> v;
    struct kind { int value, weight; };
    vector<kind> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i].weight >> nums[i].value;
    }
    vector<int> dp(v + 1);
    vector<int> dp2(v + 1, -99999999); // 恰好装满
    dp2[0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = v; j >= nums[i].weight; j--) {
            dp[j] = max(dp[j], dp[j - nums[i].weight] + nums[i].value);
            dp2[j] = max(dp2[j], dp2[j - nums[i].weight] + nums[i].value);
        }
    }
    cout << dp[v] << '\n';
    cout << (dp2[v] > 0 ? dp2[v] : 0) << '\n';
}
```

#### 二维数组

```cpp
void solve() {
    int t, m; // t=容量, m=物品数
    cin >> t >> m;
    struct cy { int time, ac; };
    vector<cy> cord(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> cord[i].time >> cord[i].ac;
    }
    int dp[105][1005] = {};
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= t; j++) {
            if (j >= cord[i].time)
                dp[i][j] = max(dp[i-1][j-cord[i].time] + cord[i].ac, dp[i-1][j]);
            else
                dp[i][j] = dp[i-1][j];
        }
    }
    cout << dp[m][t] << '\n';
}
```

**复杂度**：

- 一维：O(n*v)，空间 O(v)。
- 二维：O(n*t)，空间 O(n*t)。

### 完全背包

**用途**：物品可无限选，求最大价值。  
**常见坑**：正序循环（区别于 01 背包倒序），防止重复选择。

```cpp
void solve() {
    int time, n;
    cin >> time >> n;
    struct cy { int t, v; };
    vector<cy> hsh(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> hsh[i].t >> hsh[i].v;
    vector<int> dp(time + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = hsh[i].t; j <= time; j++)
            dp[j] = max(dp[j - hsh[i].t] + hsh[i].v, dp[j]);
    }
    cout << dp[time] << '\n';
}
```

**复杂度**：O(n*time)，空间 O(time)。

### 其他dp

#### 切蛋糕

- **错误原因**:没有错，单纯想要记录天才异或dp
- **题解思路**:
  >建立二维数组，直接模拟遍历切蛋糕，通过队每个（i，j）进行异或运算来记录每个1，1 ->i,j的可行状态。由几何关系可知每个（i，j）的状态仅仅取决于（i-1，j）和（i，j-1）。虽然这道题很简单我的解法比dp更简单更省空间
  >>我想说的是：由一个状态继承过来的做法就可以叫做dp
