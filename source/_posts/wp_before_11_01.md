---
title: wp_before_11_02
date: 2025-11-05 16:48:10
tags:
  - 算法
  - C++
  - Problems
cover: /img/cover/picg_9.png

---


# 题目整理

- [题目整理](#题目整理)
  - [练习题](#练习题)
    - [洛谷](#洛谷)
      - [P1067 \[NOIP 2009 普及组\] 多项式输出](#p1067-noip-2009-普及组-多项式输出)
      - [P4924  魔法少女小Scarlet](#p4924--魔法少女小scarlet)
      - [爬楼梯](#爬楼梯)
      - [P2280 \[HNOI2003\] 激光炸弹](#p2280-hnoi2003-激光炸弹)
      - [P5026 Lycanthropy](#p5026-lycanthropy)
      - [P2241 统计方形（数据加强版](#p2241-统计方形数据加强版)
      - [P3799 小 Y 拼木棒](#p3799-小-y-拼木棒)
      - [P1618 三连击（升级版）](#p1618-三连击升级版)
      - [P1434 \[SHOI2002\] 滑雪](#p1434-shoi2002-滑雪)
      - [BFS例题：P1443 马的遍历](#bfs例题p1443-马的遍历)
      - [P1162 填涂颜色 提供深搜广搜两种做法](#p1162-填涂颜色-提供深搜广搜两种做法)
      - [P1088火星人](#p1088火星人)
      - [P1825 \[USACO11OPEN\] Corn Maze S](#p1825-usaco11open-corn-maze-s)
      - [P2895 \[USACO08FEB\] Meteor Shower S](#p2895-usaco08feb-meteor-shower-s)
  - [赛后补题](#赛后补题)
    - [2025年10月19日广东工业大学新生月赛](#2025年10月19日广东工业大学新生月赛)
      - [K最不上升也降序列](#k最不上升也降序列)
      - [切蛋糕](#切蛋糕)
    - [10月22日 牛客练习（新生组）](#10月22日-牛客练习新生组)
      - [数三角](#数三角)
      - [判正误](#判正误)
    - [2025年10月28日Div4](#2025年10月28日div4)
      - [D. Yet Another Array Problem](#d-yet-another-array-problem)
      - [C. Isamatdin and His Magic Wand](#c-isamatdin-and-his-magic-wand)
      - [E. khba Loves to Sleep](#e-khba-loves-to-sleep)
      - [\*G. Mukhammadali and the Smooth Array](#g-mukhammadali-and-the-smooth-array)
          - [非常有意思的题目，请严肃学习1e9次题解](#非常有意思的题目请严肃学习1e9次题解)
    - [10月31日牛客赛](#10月31日牛客赛)
      - [B：Del](#bdel)
      - [C 丢手绢](#c-丢手绢)
  - [杂谈](#杂谈)
    - [快速幂](#快速幂)
    - [二进制转化器](#二进制转化器)
    - [乘法逆元](#乘法逆元)
  - [教学](#教学)
    - [以滑雪为例题讲解BFS与拓扑DP](#以滑雪为例题讲解bfs与拓扑dp)
      - [part1：建立反图（计算入度）](#part1建立反图计算入度)
      - [part2：BFS](#part2bfs)
    - [神秘UB记录点](#神秘ub记录点)
    - [stl记录](#stl记录)
  - [总结](#总结)

## 练习题
>
>这里收录着各种练习题，可能是由更好的思路或是我根本不会

### 洛谷

#### P1067 [NOIP 2009 普及组] 多项式输出

- **题号**: P5678
- **链接**: [题目链接](https://www.luogu.com.cn/problem/P1067)
- **算法类型**: 模拟
- **错误原因**:
  - 分类讨论大师，不读题导致的
  - 这道题需要特判0，1，最高次项
  - 一开始把下标和数字分开处理使非常愚蠢的做法！
- **AC 代码**:

```cpp
for (int i = n, j = 0; i >= 0; i--, j++) // 以后两个变量都写在这里
bool fh = (nums[j] > 0);
bool notOne = (nums[j] != 1);
bool isfuOne = (nums[j] == -1);
```

- **注意事项**:
  - 读题读题读对题
  - 想好再写
  - 模拟题一定要有耐心，认真讨论所有可能的条件
  - bool变量是对的！分讨大师请多多使用bool变量做分叉
  - 记得特判要continue，想好在什么时候刷新判断

#### P4924  魔法少女小Scarlet

- **题号**: P4924
- **链接**: [题目链接](https://www.luogu.com.cn/problem/P4924)
- **算法类型**: 模拟
- **错误原因**:
  - 乍一看很复杂，要不是定级只有橙我肯定跳了
  - **可恶的边界以及循环顺序**
  - **可恶的边界以及循环顺序**
  - **可恶的边界以及循环顺序**
  - '外层循环写左边，内层循环写右边'
- **AC 代码**:

```cpp
void solve()
{
    int n, m;
    cin >> n >> m;
    vvi nums(505, vi(505));
    int chg[505][505];
    int cnt = 1;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            nums[i][j] = cnt;
            cnt++;
        }

    while (m--)
    {
        memset(chg, 0, sizeof(chg));
        int x, y, r, z;
        cin >> x >> y >> r >> z;
        if (z == 0)
        {
            for (int i = x - r; i <= x + r; i++)
                for (int j = y - r; j <= y + r; j++)
                    if (i >= 1 && i <= n && j >= 1 && j <= n)
                        chg[j - y + x][x - i + y] = nums[i][j];
        }

        else
        {
            for (int i = x - r; i <= x + r; i++)
                for (int j = y - r; j <= y + r; j++)
                    if (i >= 1 && i <= n && j >= 1 && j <= n)
                        chg[x + y - j][i - x + y] = nums[i][j];
        }

        for (int i = x - r; i <= x + r; i++)

            for (int j = y - r; j <= y + r; j++)

                if (i >= 1 && i <= n && j >= 1 && j <= n && chg[i][j] != 0)
                    nums[i][j] = chg[i][j];
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)

            cout << nums[i][j] << ' ';
    cout << '\n';
}

```

- **注意事项**:
  - 思考路径：

> 1\.**相对化坐标** 通过平移使得*平面内任意一点*的普遍情况转换成*以(0,0)为基准点的*特殊情况，方便观察规律
> 2\.**做几何变换**
> 3\.**绝对化坐标** 一般来说就是用计算完的结果加回去
> 4\.**带入原始坐标**
  
#### 爬楼梯

- **题号**: P5678
- **链接**: [题目链接](https://www.luogu.com.cn/problem/P5678)
- **算法类型**: 高精度，递归
- **错误原因**:
  - 因为高精度不能用dp
  - 状态转移方程能错真是神人
- **注意事项**:
  - 注意数据范围
  - 数据范围：检查输入范围 $ N $ 是否会导致结果超出常用整数类型的上限。

  >如果 $ N \leq 50 $，结果可能还在 64 位整数范围内（视具体语言而定）。
  如果 $ N $ 较大（例如 $ N \geq 100 $），斐波那契数列的数值会快速增长，超出 $ 10^{18} $，需要高精度。
  >题目提示：题目提到“对于 60% 的数据，$ N \leq 50 $”，暗示当 $ N $ 较大时（接近 5000），需要特殊处理，通常是高精度计算。
  结果的规模：如果预期输出可能达到几十位或更多位，就需要高精度。例如，$ f(5000) $ 可能有上千位。

#### P2280 [HNOI2003] 激光炸弹

- **题号**: P2280
- **链接**: [题目链接](https://www.luogu.com.cn/problem/P2280)
- **算法类型**: 二维差分
- **算法**:
  - 二维差分的适用性

> **离散化地图**：目标点的坐标 $(x_i, y_i)$ 分布在 $0 \leq x_i, y_i \leq 5000$ 的整数格点上，可以用一个二维数组 $sum[x][y]$ 记录每个格点 $(x, y)$ 的总价值（可能有多个目标点在同一位置）。
>**区域和计算**：对于一个正方形区域 $[x, x+m-1] \times [y, y+m-1]$，我们需要快速计算这个矩形区域内所有点的价值和。直接遍历点的时间复杂度为 $O(n)$，而通过二维前缀和或二维差分，可以将区域和的计算优化到 $O(1)$ 或接近 $O(1)$。

- 二维前缀和方程（自推）

~~~
   pre[i][j]=pre[i][j-1]+pre[i-1][j]-pre[i-1][j-1]
~~~

- **代码错误**

 >无偏移的问题：
 >>**“边界不摧毁”对你的代码没有影响**，问题出在别处。
错误细节：坐标范围：0 ~ 5000。
>
> - 对于 m=1，右下角最小应为0（单点覆盖），但你从1开始，漏掉坐标0的单点。
样例中有点(0,0)和(1,1)，你只算到(1,1)，碰巧输出1（过了样例），但如果测试点只有(0,0)或依赖低坐标，必然错。
> - 对于更大m，如果目标集中在x=0 ~ m-2，需要左上=0的正方形来覆盖，你也漏了。

  简单来说，你的原代码从 *int j = m* 开始，导致至少从 *（1，1）*开始查找，会导致漏掉边界数据

- **AC 代码**:

```cpp

for (int i = 1; i <= 5001; i++)
    {
        for (int j = 1; j <= 5001; j++) // i是列j是行记得记得别搞乱了
        {
            if (i == 1 && j == 1)
                continue;
            dbg(i, j);
            if (i == 1)
            {
                arr[1][j] = arr[1][j - 1] + arr[1][j];
                continue;
            }
            if (j == 1)
            {
                arr[i][1] = arr[i - 1][1] + arr[i][1];
                continue;
           }
            arr[i][j] = arr[i][j - 1] + arr[i - 1][j] - arr[i - 1][j - 1] + arr[i][j];
        }
    }
    int ans = 0;
    for (int i = m; i <= 5001; i++)
    {
        for (int j = m; j <= 5001; j++) // i是列j是行记得记得别搞乱了
        {
            int hsh = arr[i][j] - arr[i - m][j] - arr[i][j - m] + arr[i - m][j - m];
            ans = max(ans, hsh);
        }
    }
    cout << ans;

```

- **注意事项**
  -

- **改进思路**:
  - 二维差分适合这道题，因为它能高效处理二维平面上的矩形区域和问题，通过预处理将区域和查询优化到 $O(1)$，总复杂度可控

#### P5026 Lycanthropy

- **题号**: P5026
- **链接**: [题目链接](https://www.luogu.com.cn/problem/P5026)
- **算法类型**: 差分，O(1)查询，指针/index模拟坐标正负数
- **错误原因**:
  - 数组范围
  - 指针运用
- **AC 代码**:
  - **第一：指针法**

```cpp
int hsh[2100000]；
int ljl[2100000];
void solve()
{
    // 1-based
    int n, m;
    cin >> n >> m;
    int *a = hsh + 1000000;
    int *b=ljl+1000000;
    for (int i = 1; i <= n; i++)
    {
        int v, x;
        cin >> v >> x;
        a[x - 3 * v + 1] += 1;
        a[x - 2 * v+1] -= 2;
        a[x + 1] += 2;
        a[x + 2 * v+1] -= 2;
        a[x + 3 * v + 1] += 1;
    }
    for (int i =-40000 ; i <= 40000+m; i++)
    {
        a[i] += a[i - 1];
        b[i]+=b[i-1]+ a[i];
    }
  for (int i = 1; i <= m; i++)
    {
        cout <<b[i]<<' ';
    }
}
```

- **index补充**

  ```cpp
  const int offset = 1000000;
  const int SIZE = 2100000; // 确保 SIZE > 2 * OFFSET
    // 创建 vector 并初始化所有元素为 0
    // 使用 long long 防止累加时溢出
    vector<ll> a(SIZE, 0); 
    vector<ll> b(SIZE, 0);
    // --- 改动结束 ---
        // 所有访问都加上 OFFSET
        a[x - 3 * v + 1 + OFFSET] += 1;
        a[x - 2 * v + 1 + OFFSET] -= 2;
  ```

- **注意事项**:
  - 如果非要用指针，记得在全局变量的地方定义它，要不然全都在访问垃圾值！！
  - 如果用vector容器（推荐），记得想好index和偏移量的关系
- **双重差分算法讲解**:
  - 首先你要记得：双重差分的递推**在同一个循环里同时操作**
  - 二阶差分：解决“区间加等差数列”
  - 难点：边界条件处理

>*以下是思考路径记录，比赛跳过*
>
> - 思考：“为了让数组在 X 点之后呈现出我想要的效果，我应该在差分数组的 X 点做什么操作？”
>
>>根据一阶差分我们可知我们可以通过给a[l]++，a[**r+1**]--表达区间内的统一操作（++）
>>那么同理易得二阶差分里面我们要实现增长可以a[l]++,a[r+1]--
>
> - 首先我知道差分数组本身的差分处理意义就是去通过去打标记实现最终o1的复杂度。
> - 对于其中一阶差分数组的处理实质上只是打标记
> - 而实现让二阶数组呈现增长是因为**前缀和**
> - 如果我们再进行一个三阶前缀和就会让她呈现x方的增长
> - 而修改它+1还是-2单纯是因为增长点和下降点重合了
> - 如何处理我们“W”形的上下坡操作边界？我们发现对a[r+1]的修改叠在了一起，一段的终点就是下一段的起点

  ```cpp
    a[i] += a[i - 1];
    b[i]+=b[i-1]+ a[i];
  ```

#### P2241 统计方形（数据加强版

- **题号**: 2241
- **链接**: [题目链接](https://www.luogu.com.cn/problem/P2241)
- **算法类型**: 数学
- **记录原因**:我他妈自己写出来了自己推导的公式！我真是他妈的天才
- **AC 代码**:

```cpp
int cjqj(int c)
{return c*(c+1)/2;}
void solve()
{
    int n,m;
    cin>>n>>m;
    int d=min(n,m);
    int ans1=0;
    for(int i=1;i<=d;i++)
        ans1+=(n-i+1)*(m-i+1);
    int ans2=cjqj(n)*cjqj(m)-ans1;
    cout<<ans1<<' '<<ans2;
}
```

- **思路记录**:
  - 首先你要剥去情景迷雾，将它抽象成每个元素的组合
  - 你在想：怎么放置正方形 ->因为可以重叠就一个个排开
  - 然后我们就能得到正方形特殊到一般的计数方法
  - 然后我们要看看这里面一共有多少个子矩形？
  - 矩形是什么？两个横线两个竖线的累加 -> 通过线段的组合计算总数
  - 然后ans2-ans1=AC！！
  
#### P3799 小 Y 拼木棒

- **题号**: P3799
- **链接**: [题目链接](https://www.luogu.com.cn/problem/P53799)
- **算法类型**: 几何
- **错误原因**:
  - if条件判断：最好两个分开的条件分开写
  - 处理小巧思：为了不要算重复两个补集，可以写成for（j，i-j）
- **AC 代码**:

```cpp
void solve()
{
    vi nums(5050, 0);
    int n;
    int mod = 1e9 + 7;
    cin >> n;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int d;
        cin >> d;
        nums[d]++;//桶排处理：智慧的算法
    }
    for (int i = 1; i < 5001; i++)
    {
        if (nums[i] < 2)
            continue;
        int hsh1 = ((nums[i] * (nums[i] - 1)) / 2) % mod;
        for (int j = 1; j <= i-j; j++) // 智慧的处理方法：今日审美积累中
        {
            int k = i - j;
            if (k > 5001 || !nums[k] || !nums[j] || k <= 0||k==i||j==i)//专门挑出例外continue难道不比写特殊情景方便吗
                continue;
            if (k == j && nums[j] >= 2)
            {
                int hsh2 =(nums[j] * (nums[j] - 1)/2)%mod;
                ans =(ans+ hsh1 * hsh2) % mod;
            }
            else if(k!=j)
            {
                int hsh3 = (nums[j] * nums[k])%mod;
                ans =(ans+ hsh1 * hsh3) % mod;
            }
        }
    }
    cout << ans<<'\n';
}
```

- **注意事项**:
  - 最好把C（n，2）写成单独的一个变量，模块化方便操作（比如我这里的hsh1，hsh2）
  - 关于取模：“在每一步中间运算完成后，立即安全地取模”，尤其是加法、乘法、幂运算
  - for (int j = 1; j <= i-j; j++) // 智慧的处理方法：防止计算重复
  - else if(k!=j)//请把你的**条件完整写出来**，**非必要不要用else**除非完全在处理补集
  - 专门挑出例外continue比特判方便（特判容易漏条件）

#### P1618 三连击（升级版）

- **题号**: P1618
- **链接**: [题目链接]([P1618 三连击（升级版） - 洛谷](https://www.luogu.com.cn/problem/P1618))
- **算法类型**: 暴力枚举
- **题目概述**:
  - 分别组成三个三位数，且使这三个三位数的比例是 A:B:C
- **AC 代码**:

```cpp
bool cek()
{
    // 必须用浮点数比较比例！不能整数除
    if (abs(1.0 * pans[0] / pans[1] - 1.0 * a / b) > eps)
        return false;
    if (abs(1.0 * pans[1] / pans[2] - 1.0 * b / c) > eps)
        return false;
    if (abs(1.0 * pans[0] / pans[2] - 1.0 * a / c) > eps)
        return false;
    return true;
}
```

- **注意事项**:
  - 注意比较比例需要用浮点数
  - 写法 ：abs(1.0 *pans[0] / pans[1] - 1.0* a / b) > eps）
  - eps是浮点数误差，板子里面有

#### P1434 [SHOI2002] 滑雪

- **链接**: [题目链接](https://www.luogu.com.cn/problem/P14348)
- **算法类型**: 拓扑dp
- **此为标准代码请认真研读**
- **AC 代码**:

```cpp
vi dr = {1, 0, -1, 0};
vi dc = {0, 1, 0, -1};
void solve()
{
    vvi height(101, vi(110));
    vvi indigree(101, vi(110,0));
    int c, r;
    cin >> r >> c;
    for (int i = 1; i <= r; i++) // 我还是喜欢1 based存图
    {
        for (int j = 1; j <= c; j++)
        {
            cin >> height[i][j];
        }
    }
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                if (i + dr[k] <= 0 || i + dr[k] > r || j + dc[k] <= 0 || j + dc[k] > c)
                    continue;
                if (height[i + dr[k]][j + dc[k]] < height[i][j])
                {
                    indigree[i][j]++;
                }
            }
        }
    }
    int ans=0;
    vvi dp(101,vi(101,1));
    queue<pair<int, int>> pos;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
            if (indigree[i][j] == 0)
                pos.emplace(i, j);
    while (!pos.empty())
    {
        auto [x, y] = pos.front();
        pos.pop();
        for (int k = 0; k < 4; k++)
        {
            if (x + dr[k] <= 0 || x + dr[k] > r || y + dc[k] <= 0 || y + dc[k] > c)
                continue;
            if (height[x + dr[k]][y + dc[k]] > height[x][y])
            {
                dp[x + dr[k]][y + dc[k]]=max(dp[x][y]+1,dp[x + dr[k]][y + dc[k]]);
                ans=max(ans,dp[x + dr[k]][y + dc[k]]);
                indigree[x + dr[k]][y + dc[k]]--;
                if(indigree[x + dr[k]][y + dc[k]]==0)
                pos.emplace(x + dr[k],y + dc[k]);
            }
        }
    }
    if(!ans)cout<<"1";
    else cout<<ans;
}
```

- **细节讲解**
    -

- **思路**:
  - 1. 建图（这里用反图更方便）
  - 2. 计算入度
  - 3. 入度为0的点入队
  - 4. BFS：
  - 5. 答案 = max(dp[])

~~~ cpp
//BFS
   while (!q.empty()) {
       u = 出队
       for each v that u → v (原图：u 可以到达 v)
           dp[v] = max(dp[v], dp[u] + 1)
           inDegree[v]--
           if (inDegree[v] == 0) 入队
   }
~~~

#### BFS例题：P1443 马的遍历

- **题号**: P1443
- **链接**: [题目链接](https://www.luogu.com.cn/problem/P1443)
- **算法类型**: BFS
- **AC 代码**:

```cpp
nn[x][y]=0;
    queue<pair<int, int>> bfs; // 建立一个以点坐标为项目的队列
    bfs.emplace(x, y);
    while (!bfs.empty())
    {
        auto [h, w] = bfs.front();
        bfs.pop();
        for (int i = 0; i < 8; i++)
        {
            int hsh = h + dx[i];
            int ljl = w + dy[i];
            if (hsh < 1 || hsh > n || ljl < 1 || ljl > m || !nn[hsh][ljl])
                continue;
            nn[hsh][ljl] = 0;
            mp[hsh][ljl] = mp[h][w] + 1;
            bfs.emplace(hsh, ljl);
        }
    }
```

- **注意事项**:
  - 记得BFS不要漏了`bool visit`数组
  - 记得BFS状态转移（？）方程`mp[hsh][ljl] = mp[h][w] + 1;`
  - 最短路问题 不是“另一种算法”，它就是 DP 在无权图上的高效实现
- **改进思路**:
  - 考虑严格 cnt == k 的情况，调整 check 函数。

#### P1162 填涂颜色 提供深搜广搜两种做法

- **题号**: P1162
- **链接**: [题目链接](https://www.luogu.com.cn/problem/P1168)
- **算法类型**: 搜索板子
- **错误原因**:
  - 注意从四周寻找‘0’切入
- **AC 代码**广搜版:

```cpp
 vector<vector<int>> mp(35, vi(35));
    vector<vector<bool>> vis(35, vector<bool>(35, 1));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> mp[i][j];
        }
    }
    queue<pair<int, int>> bfs;
    //bfs.emplace(1, 1);
    for (int i = 1; i <= n; i++)
    {
        if (mp[1][i]==0) bfs.emplace(1, i);
        if (mp[i][1]==0) bfs.emplace(i, 1);
        if (mp[n][i]==0) bfs.emplace(n, i);
        if (mp[i][n]==0) bfs.emplace(i, n);
    }
    while (!bfs.empty())
    {
        auto [lg, cf] = bfs.front();
        bfs.pop();
        for (int i = 0; i < 4; i++)
        {
            int xlg = lg + dx[i];
            int xcf = cf + dy[i];
            if (xlg < 1 || xlg > n || xcf < 1 || xcf > n || !vis[xlg][xcf] || mp[xlg][xcf] == 1)
            {
                continue;
            }
            vis[xlg][xcf] = 0;
            mp[xlg][xcf] = -1;
            bfs.emplace(xlg, xcf);
        }
    }
```

- **AC 代码**深搜版:

```cpp
void dfs(int a, int b, vector<vector<int>> &mp)
{
    if (mp[a][b] != 0)
        return;
    if (mp[a][b] == 0)
        mp[a][b] = -1;
    for (int i = 0; i < 4; i++)
    {
        int xlg = a + dx[i];
        int xcf = b + dy[i];
       //dbg(xlg,xcf);
        if (xlg < 1 || xlg > n || xcf < 1 || xcf > n)
            continue;
        dfs(a + dx[i], b + dy[i], mp);
    }
    return;
}
//solve里面的
for (int i = 1; i <= n; i++)
    {
           dbg(i);
        dfs(i, 1, mp);
        dfs(1, i, mp);
        dfs(n, i, mp);
        dfs(i, n, mp);
    }
```

- **注意事项**:
  - 注意从四周引入点
  - 注意入队时机
- **改进思路**:
  - 学习两种搜索方式

#### P1088火星人

- **题号**: P1088
- **链接**: [题目链接](https://www.luogu.com.cn/problem/P1088)
- **算法类型**: 数学（没有stl的情况下手搓next_permutation）
- **错误原因**:
  - 不会，好难
- **AC 代码**:

```cpp
while (m)
{
    for (int j = nums.size() - 2; j >= 0; j--)
    {
        if (pron[j] < pron[j + 1])
        {
            for (int i = nums.size() - 1; i > j; i--)
            {
                if (pron[j] < pron[i])
                {
                    {
                        swap(pron[i], pron[j]);
                        m--;
                        reverse(pron.begin() + j + 1, pron.end());
                        break;
                    }
                }
            }
            break;
        }
    }
}
for (int i = 0; i < n; i++)
{
    cout << pron[i] << ' ';
}
```

- **注意事项**
  -

- **思路**:

1. 从右向左找第一个 `pron[j] < pron[j + 1]` 的位置 i
2. 若不存在 → 已是最大排列，返回 false
3. 从右向左找第一个 `pron[j] < pron[i]` 的 j
4. 交换 a[i] 和 a[j]
5. 反转区间 [i+1, n)
6. 返回 true。

#### P1825 [USACO11OPEN] Corn Maze S

- **题号**: P1825
- **链接**: [题目链接](https://www.luogu.com.cn/problem/P5678)
- **算法类型**: BFS
- **记录原因**:
  - AC了，终点看引参数进数组！不要天天被神秘UB卡住脑子
  - 这道题无非是标准BFS上面加了个规则函数：这道题放这里就是教你如何写有规则的搜索
- **AC 代码**:

```cpp
void goincsm(const vector<vector<int>> &mp, int &xx, int &yy)
{
    rep(i, 1, n)
    {
        rep(j, 1, m)
        {
            if (mp[i][j] == mp[xx][yy] && (i != xx || j != yy))
            {
                xx = i;
                yy = j;
                return;
            }
        }
    }
}
```

- **注意事项**:
  - 取地址代表可更改`int &xx`：适用于那些总是要更改的量
  - `const vector<vector<int>> &mp`既安全又高校的传图方式

#### P2895 [USACO08FEB] Meteor Shower S

- **题号**: P2895
- **链接**: [题目链接](https://www.luogu.com.cn/problem/P2895)
- **算法类型**: BFS
- **错误原因**:
  - 边界检查边界检查边界检查
  - 时间更新逻辑
  - vis数组限制逻辑（依旧时间更新逻辑）
- **AC 代码**:

```cpp
vi dx = {-1, 0, 1, 0};
vi dy = {0, 1, 0, -1};

struct flashlight
{
    int xi, yi, ti;
};

void solve()
{
    int m;
    cin >> m;
    vector<vector<bool>> vis(305, vector<bool>(305, 1));
    vector<vector<bool>> hited(305, vector<bool>(305, 1));
    vector<vector<int>> mp(305, vector<int>(305, INF));
    vector<flashlight> bar(m);
    vector<flashlight> safe;
    rep(i, 0, m - 1)
    {
        cin >> bar[i].xi >> bar[i].yi >> bar[i].ti;
        hited[bar[i].xi][bar[i].yi] = 0;
        rep(j, 0, 3)
        {
            int xd = bar[i].xi + dx[j];
            int yd = bar[i].yi + dy[j];
            if (xd < 0 || xd > 302 || yd < 0 || yd > 302)
                continue;
            hited[xd][yd] = 0;
        }
    }
    sort(bar.begin(), bar.end(), [](flashlight a, flashlight b)
         { return a.ti < b.ti; });
    rep(i, 0, 304)
    {
        rep(j, 0, 304)
        {
            if (hited[i][j] == 1 )
                safe.push_back({i, j, 0});
        }
    }

    queue<pii> pos;
    pos.emplace(0, 0);
    vis[0][0] = 0;
    int time = 0;
    while (!pos.empty())
    {
        int sz = SZ(pos); // 当前层有多少个点
        auto it = find_if(all(bar), [time](const flashlight &a)
                          { return a.ti == time+1; });
        while (it != bar.end())
        {
            int xo = it->xi;
            int yo = it->yi;
            vis[xo][yo] = 0;
            rep(i, 0, 3)
            {
                int xoo = xo + dx[i];
                int yoo = yo + dy[i];

                if (xoo < 0 || xoo > 302 || yoo < 0 || yoo > 302 || vis[xoo][yoo] == 0)
                    continue;
                vis[xoo][yoo] = 0;
            }
            it = std::find_if(++it, bar.end(),
                              [time](const flashlight &a)
                              { return a.ti == time+1; });
        }
        rep(layer, 0, sz - 1)
        {
            auto [x, y] = pos.front();
            pos.pop();

            rep(i, 0, 3)
            {
                int xx = x + dx[i];
                int yy = y + dy[i];
                if (xx < 0 || xx > 302 || yy < 0 || yy > 302 || vis[xx][yy] == 0)
                    continue;

                vis[xx][yy] = 0;
                mp[xx][yy] = time + 1;
                pos.emplace(xx, yy);
            }
        }
        time++;
    }
    int ans = INF;
    rep(i, 0, SZ(safe) - 1)
    {
        ans = min(ans, mp[safe[i].xi][safe[i].yi]);
    }
    if (ans == INF)
    {
        cout << "-1";
        return;
    }

    cout << ans;
}

```

- **注意事项**:
  - 注意：这道题没有规定地图大小，对于流星影响（限制点）最大可到301*301.所以我们的搜索应该开到303（最保险），包括continue地搜索限制
  - 注意time更新逻辑：lily只能在ti之前到达这个点，所以对于每个影响的点需要参考的是time+1；
  - 注意bfs每层地更新逻辑：每次入队都是time（i）时间点可到地所有点
- **结构体lambda搜索技巧**:

~~~cpp
  根据ti寻找bar中所需要地项，返回迭代器
  auto it = find_if(all(bar), [time](const flashlight &a)
                          { return a.ti == time+1; });
  直接从迭代器里面提取出来我们要的：->
  int xo = it->xi;
  int yo = it->yi;
  如果符合条件的项目存在
  while (it != bar.end())
  寻找下一个迭代器
  it = std::find_if(++it, bar.end(),
                              [time](const flashlight &a)
                              { return a.ti == time+1; });
~~~

---

## 赛后补题
>
>这里收录着各场比赛的赛后总结。或许有赛时代码优化掉落

### 2025年10月19日广东工业大学新生月赛

- **名次** A赛道第四，C赛道第一，总榜第十三（成功！第一次参加比赛结果还算可以）
- **存在问题** 码力羸弱，很多题都是用的巧法做。需补算法。心态不稳，乱交答案罚时爆炸痛失金牌

#### K最不上升也降序列

- **题号**: K
- **链接**: [题目链接](https://ac.nowcoder.com/acm/contest/119605/J)
- **算法类型**: 数学证明
- **错误原因**:
  - 不会
  - 都错题了（byd）题目中的LIS指的是**最长**单增子序列
- **题解思路**:

>LIS × LDS ≥ $n$ 是因为排列可以用 LIS 个下降子序列覆盖，每个长度 ≤ LDS，所以 $n \leq$ LIS × LDS。
>在最优构造中，我们让 LIS ≈ LDS ≈ $\sqrt{n}$，使乘积 ≈ $n$（或略大于），从而最小化 LIS + LDS ≈ $2\sqrt{n}$。
>不是“为什么等于 n”，而是“为什么至少 n”，最优构造接近这个下界。
>对于完全平方 n（如 n=9, k=3），乘积正好 =9；否则略大，但不影响。

- **AC 代码**:

```cpp

```

- **注意事项**:
  - 注意二分查找的左右边界初始化。
  - 确保 check 函数逻辑正确。

#### 切蛋糕

- **错误原因**:没有错，单纯想要记录天才异或dp
- **题解思路**:
  >建立二维数组，直接模拟遍历切蛋糕，通过队每个（i，j）进行异或运算来记录每个1，1 ->i,j的可行状态。由几何关系可知每个（i，j）的状态仅仅取决于（i-1，j）和（i，j-1）。虽然这道题很简单我的解法比dp更简单更省空间
  >>我想说的是：由一个状态继承过来的做法就可以叫做dp

### 10月22日 牛客练习（新生组）

-**成绩**  六出四（其实应该是我目前能力范围内尽力了）
-**存在问题** 不会快速幂，心态容易炸，时间不够，理论上三角形那题我能出

#### 数三角

- **链接**: [题目链接](https://ac.nowcoder.com/acm/contest/118653/D)
- **算法类型**: 模拟，数学,计算数学，模板
- **错误原因**:
  - 时间不够，这题不是我熟悉的形式，跳过这题
  - 忘记余弦定理了
  - 注意特判三点共线
  - 注意判断一下三条边三个角！！！
- **AC 代码**:

```cpp

bool cek(int i, int j, int k, const vi &x, const vi &y)
{
    int g1 = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
    int g2 = (x[i] - x[k]) * (x[i] - x[k]) + (y[i] - y[k]) * (y[i] - y[k]);
    int g3 = (x[k] - x[j]) * (x[k] - x[j]) + (y[k] - y[j]) * (y[k] - y[j]);
    int ck = (y[k] - y[i]) * (x[j] - x[i]) - (y[j] - y[i]) * (x[k] - x[i]);
    if (ck == 0)
        return 0;
    if (g1 + g2 - g3 < 0)return 1;
    if (g1 + g3 - g2 < 0) return true;
    if (g2 + g3 - g1 < 0) return true;   
    return 0;
    // ok根据余弦定理我们可以知道只要（a*a+b*b-c*c)*a*b>0就行
}

```

- **注意事项**:
  - 要不然你在开头先声明bool然后结尾在定义运算，要不然你就把数据导入进去，全局变量是坏的
- **改进思路**:
  >这是一种可以套模板的题目，详见以下
  数学公式：
  1，使用叉积公式：点 $(x_0, y_0)$ 到直线（由点 $(x_1, y_1)$ 和 $(x_2, y_2)$ 定义）的距离为：
$$\text{distance} = \frac{|(y_2 - y_1)(x_0 - x_1) - (y_0 - y_1)(x_2 - x_1)|}{\sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}}$$

```cpp
## 判断三角形类型 ##
bool isObtuse(int x1, int y1, int x2, int y2, int x3, int y3) {
    ll g1 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    ll g2 = (x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3);
    ll g3 = (x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3);
    //这里是叉积判断是否共线
    ll ck = (y3 - y1) * (x2 - x1) - (y2 - y1) * (x3 - x1);
    if (ck == 0) return false;
    return (g1 + g2 - g3 < 0 || g1 + g3 - g2 < 0 || g2 + g3 - g1 < 0);
    //这里是余弦定理返回钝角，直角就==0，锐角就>0
}

## 计算点到直线的距离 ##
double pointToLineDistance(int x0, int y0, int x1, int y1, int x2, int y2) {
    double cross = abs((y2 - y1) * (x0 - x1) - (y0 - y1) * (x2 - x1));
    double dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return cross / dist;
}//注意要用double


```

#### 判正误

- **链接**: [题目链接](https://ac.nowcoder.com/acm/contest/118653/C)
- **算法类型**: 快速幂模板速用
- **题目数据范围**

 >![alt text](image.png)

- **错误原因**:
  - 不会快速幂
- **AC 代码**:

```cpp
i64 qpow(i64 a, i64 b, i64 m)
{
    i64 res = 1; // 初始化结果为 1
    a %= m;      // 预先取模
    while (b > 0)
    { // 当 n > 0 时循环
        if (b & 1)
            res = res * a % m; // 如果 n 的最低位为 1，res = res * a % m
        a = a * a % m;         // a = a * a % m
        b>>= 1;               // n 右移一位
    }
    return res; // 返回 (a^n) % m
}

void solve()
{
i64 m1=1e9+7;
i64 m2=1e9+9;
i64 m3=1e9+21;

i64 a,b,c,d,e,f,g;
cin>>a>>b>>c>>d>>e>>f>>g;

i64 p1=qpow(a,d,m1)%m1+qpow(b,e,m1)%m1+qpow(c,f,m1)%m1;
i64 p2=qpow(a,d,m2)%m2+qpow(b,e,m2)%m2+qpow(c,f,m2)%m2;
i64 p3=qpow(a,d,m3)%m3+qpow(b,e,m3)%m3+qpow(c,f,m3)%m3;

if(p1==g&&p2==g&&p3==g)
{
    cout<<"Yes"<<'\n';
}
else cout<<"No"<<'\n';
}
```

- **注意事项**:
  -注意数据范围，记得开long long
- **改进思路**:
  >**常用模数**
  >i64 m1=1e9+7;
    i64 m2=1e9+9;
    i64 m3=1e9+21;
  >**简单快速幂**

  ~~~cpp
   i64 qpow(i64 a, i64 b, i64 m)
    {
    i64 res = 1; // 初始化结果为 1
    a %= m;      // 预先取模
    while (b > 0)
    { // 当 n > 0 时循环
        if (b & 1)
            res = res * a % m; // 如果 n 的最低位为 1，res = res * a % m
        a = a * a % m;         // a = a * a % m
        b>>= 1;               // n 右移一位
    }
    return res; // 返回 (a^n) % m
    }
  ~~~

  >**数据范围更大的快速幂**

  ~~~cpp
  using f80 = long double;  
  using u128 = unsigned __int128;  
  using i128 = __int128;  
  using u64 = unsigned long long;  
  using i64 = long long;  
  using u32 = unsigned;  
  i64 qmul(i64 x, i64 y, i64 m) {
    i64 z = (f80) x / m * y + 0.5L;
    u64 c = (u64) x * y - (u64) z * m;
    return c < m ? (i64) c : (i64) (c + m);
  }

  i64 qpow(i64 a, i64 n, i64 m) {
    i64 res = 1;
    while (n) {
        if (n & 1) res = res * a % m;
        a = a * a % m;
        n >>= 1;
    }
    return res;
  }
  ~~~

  >快速乘可避免模数大于 int 取值范围时溢出，可将快速幂中乘法替换为快速乘版本以避免乘法溢出。

### 2025年10月28日Div4

- **真tm想抽死自己**

#### D. Yet Another Array Problem

- **题号**: D
- **链接**: [题目链接](https://codeforces.com/contest/2167/problem/D)
- **算法类型**: 唐人暴力
- **错误原因**:
  - 脑子里没有明确的思路，多积累，多想
- **AC 代码**:

```cpp
for (int i = 2; i <= 1e9; i++)//我说白了i范围再[ 1 , 100 ]都能过
    {
        for (int j = 0; j < n; j++)
        {
            if (gcd(i, nums[j]) == 1)
            {
                ans = min(i, ans);
                hsh = 1;
                break;
            }
        }
        if (hsh == 1)
        {
            cout << ans << '\n';
            return;
        }
    }
```

- **Trick**:

>如果x是满足gcd(a[i],x)=1的最小值，则对每个2≤i<x都有gcd(a[i],x)≠1
考虑每个素数p，要满足对每个2≤p<x都有gcd(a[i],p)=p≠1
也就是每个满足2≤p<x的素数p都是a[i]的因数
那最坏情况就是2*3*5*7*11*13*17*...*p_max=a[i]
p_max也就前几十个素数  
对每个数a[i]，从小到大枚举x直到gcd(a[i],x)=1
也就是x其实贼啦小
很经典的
若干个数（大于1）乘起来大于n
数字个数是O(logn)

- **改进思路**:
  - 记得简单的循环走外面，我们要知道什么时候出循环，循环内外谁先走谁后走显得尤为重要

#### C. Isamatdin and His Magic Wand

- **题号**: C
- **链接**: [题目链接](https://codeforces.com/contest/2167/problem/C)
- **算法类型**: 字典序
- **错误原因**:
  - 一个序列 $p$ 字典序小于一个序列 $q$，如果存在一个索引 $i$，使得对于所有 $j < i$ 都有 $p_j = q_j$，并且 $p_i < q_i$。
  - lexicographically smallest：字典序最小时
  - 整数的字典序 = 数值大小顺序！
  字符串的字典序 = 字符ASCII顺序！
  - ==sort 默认行为字典序==
- **AC 代码**:

```cpp
sort
```

- **注意事项**:
  - 整数的字典序 = 数值大小顺序
  字符串的字典序 = 字符ASCII顺序
  - 长度不同，短的在前
  - sort 默认行为字典序！
- **改进思路**:
  - 考虑严格 cnt == k 的情况，调整 check 函数。

#### E. khba Loves to Sleep

- **题号**: E
- **链接**: [题目链接](https://codeforces.com/contest/2167/problem/E)
- **算法类型**: 二分，边界处理
- **错误原因**:
  - 边界处理
- **AC 代码**//只能放自己ac的代码！:

```cpp
bool cek(int a, const vi &pos)
{
    int cnt = 0;
    if (pos[1] - a >= 0)
    {
        cnt += pos[1] - a + 1;
    }
    for (int i = 1; i < n; i++)
    {
        if ((pos[i + 1] - pos[i]) / 2 >= a)
        {
            cnt += (pos[i + 1] - a) - (pos[i] + a)+1;
        }
    }
    if (pos[n] + a <= x)
    {
        cnt += x - (pos[n] + a) + 1;
    }
    return cnt >= k;
}

void findans(int d, const vi &pos, vi &ans)
{
    if(d==0)
    {
         for (int i = 0; i <= n; i++)
        {
            ans.push_back(i);
        }
        return;
    }
    if (pos[1] - d >= 0)
    {
        int ljl = 0;
        int hsh = pos[1] - d;
        for (int i = ljl; i <= hsh; i++)
        {
            ans.push_back(i);
        }
    }

    for (int i = 1; i <= n-1; i++)
    {
        if ((pos[i + 1] - pos[i]) / 2 >= d)
        {
            int ljl = pos[i] + d;
            int hsh = pos[i + 1] - d;
            for (int j = ljl; j <= hsh; j++)
            {
                ans.push_back(j);
                
            }
        }
     
    }
    if (pos[n] + d <= x)
    {
        int ljl = pos[n] + d;
        int hsh = x;
        for (int i = ljl; i <= hsh; i++)
        {
            ans.push_back(i);
        }
    }
}
```

- **注意事项**:
  - 边界处理
  - 如果要*修改答案数组*记得要**取地址**！
  - 以及输出记得要**输出到ans.size()**，要不然会ub（可能编译器一开始不管k在哪）

  ~~~
    for (int i = 0; i < ans.size(); i++)
    {
        if(i==k)break;
        cout << ans[i]<<' ';
    }
  ~~~

- **改进思路**:
  - 看到答案单调直接答案二分，这道题算法不难，只是一个锻炼码力的分类讨论比赛题

#### *G. Mukhammadali and the Smooth Array

###### 非常有意思的题目，请严肃学习1e9次题解

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
- **思路**:

### 10月31日牛客赛

- **名次** 两小时一题，这场比赛有很难崩的细节错误
- **存在问题** 逻辑不严密，要不然是考虑不周，要不然是知识盲区，依旧要练

#### B：Del

- **题号**: B
- **链接**: [题目链接](https://ac.nowcoder.com/acm/contest/119666/B)
- **算法类型**: 字符串处理，字典序，细节处理
- **错误原因**:
  - 我的赛时代码所有逻辑都是错的
  - **关于字典序** ：不是简单的删掉最大的字母就行的：
  >>反例：1 abcbd
    abbd
    abcb
  -
- **AC 代码**:

```cpp
void solve()
{
    int n;
    cin >> n;
    vector<string> arr;
    rep(i, 0, n)
    {
        string s;
        cin >> s;
        rep(j, 0, SZ(s) - 1)
        {
            if(s[j]>s[j+1]||j==s.size()-1)
            {
                s.erase(j,1);
                break;
            }
        }
        if (s.empty())
            continue;
        arr.push_back(s);
    }
    stable_sort(all(arr), [](const auto &a1, const auto &a2)
                { return a1 + a2 < a2 + a1; });
    string ans;
    rep(i, 0, SZ(arr) - 1)
    {
        ans+=arr[i];
    }
    cout<<ans<<endl;
}
```

- **需要了解的写法**:
  - `s.erase(j,1);`删除vector里面的其中一个元素
  - `size_t pos = s.find(max_char);`存放maxchar的迭代器
- **改进思路**:
  - 每个串删掉“第一个让它变大的字符”（或末尾），再按“谁放前面拼接更小”排序，得到的就是字典序最小的最终字符串。

#### C 丢手绢

- **题号**: C
- **链接**: [题目链接](https://ac.nowcoder.com/acm/contest/119666/C)
- **算法类型**: 圆环处理
- **题目**:

>给定一个长度为 $n$ 的数组 $\{a_1, a_2, \dots, a_n\}$，这些元素**围成一个圆**。第 $i$ 个元素与第 $i+1$ 个元素相邻，且第 $n$ 个元素与第 $1$ 个元素相邻。
我们从圆上任意选择**四个两两不同的位置** $i, j, k, l$，分别连线 $(i, j)$ 和 $(k, l)$。
**如果**这两条线恰好在圆内部相交（交点不在圆上）：
>
> - **权值定义：** 每条线的权值定义为其两个端点元素之和。
> - **价值定义：** 这两条相交线权值的乘积记为该对相交线的价值。
>求所有可能的两条相交的线中，**价值的最大值**。
>
- **AC 代码**:

```cpp
void solve()
{
    int n;
    cin>>n;
    vi nums(n);
    rep(i,0,n-1)
    {
        cin>>nums[i];
    }
    rotate(nums.begin(),max_element(all(nums)),nums.end());
    vi dx(n+1,0);
    //dx[n-1]=nums[n-1];
    for(int i=n-1;i>=0;i--)
    {
        dx[i]=max(nums[i],dx[i+1]);
    }  
    vi zx(n,0);
    zx[1]=nums[1];
    for(int i=2;i<=n-1;i++)
    {
        zx[i]=max(nums[i],zx[i-1]);
    } 
    ll sum=0;
    for(int i=2;i<n-1;i++)
    {
        sum=max(sum,(nums[0]+nums[i])*(zx[i-1]+dx[i+1]));
    }
    cout<<sum<<'\n';
}

```

- **注意事项**:
  - 对于由圆上点连成的线段(i,j)(k,l)来说，需要使他们相交的充要条件
   >$$\text{相交几何：} \quad 0 < k < i < l \quad (\text{在线性展开上})$$
  - `std::rotate( ForwardIt first, ForwardIt middle, ForwardIt last );`
  三个都是迭代器：第一个和最后一个是范围，中间是目标。简单来说，它将 middle 所指向的元素 变为新序列的 第一个元素。但是不改变序列里面每个元素之间的相对顺序
  >**常见用法一**：解决圆上排列问题： 当一个数组被视为一个圆（即首尾相连）时，通常需要检查所有可能的起始点（或某种特殊元素作为起点）的情况。
用法： 通过 std::rotate，可以将圆上的任意元素高效地移到数组的第一个位置（s[0]），从而将圆排列问题转化为标准的 线性数组问题 进行处理。
  >**常见用法二**： 模拟 $K$ 步旋转（数组旋转问题）这是 LeetCode 上的经典问题。如果要求将数组向左或向右旋转 $K$ 步，std::rotate 是最简洁高效的实现方式
  >**常见用法三**： 简化双指针或滑动窗口问题
在某些涉及双指针或滑动窗口的问题中，如果需要 周期性地 调整窗口的起始点，或者需要将数组的一个子序列移动到另一端来满足特定的结构要求，std::rotate 可以作为一种方便的工具。

  - **严重注意**：边界处理！！因为要保证元素顺序所以最后找i的循环起点是2终点是n-2!!

- **算法思路**:
  - **相交条件：** 四个点 $i, j, k, l$ 在圆上的顺序必须是交替的（如 $i \rightarrow k \rightarrow j \rightarrow l$）。
  - **优化：** 通过 `std::rotate` 将数组中的 **最大元素** 放置到 $s[0]$，简化为只需要考虑一条线段是 $(s[0], s[i])$ 的情况。
  - **$O(N)$ 计算：** 结合 **前缀最大值 (`px`)** 和 **后缀最大值 (`a[i+1]`)**，高效地找到分割线 $(s[0], s[i])$ 两侧的最佳配对元素 $s[k]$ 和 $s[l]$，从而最大化价值：
    $$\text{Max Value} = \max_{i} \left( (s[0] + s[i]) \times (\max_{k \in [1, i-1]} \{s[k]\} + \max_{l \in [i+1, n-1]} \{s[l]\}) \right)$$
- **详细做法和实现思路**
  - 实现寻找到最大元素S[i]：`rotate(s.begin(),max_element(s.begin(),s.end()),s.end());`
  - 实现维护区间[i+1,n-1]之间的最大数字（一个类似于前缀和标记的压缩数组）：注意他的实现方式：从后往前遍历

  ~~~cpp
  vector<ll>a(n+1,0);
    for(int i=n-1;i>=0;i--)
      a[i]=max(a[i+1],s[i]);
  ~~~

  - 维护前面最大值同理，甚至更加简单，可以直接用一个变量来维护。这个简单的代码做到了在寻找i的同时维护px。精妙至极。但是没有维护的实力就还是多开一个数组做把））

  ~~~cpp
  ll px=0;
  ll sum=0;
  for(ll i=2;i<n-1;i++)
  {
    px=max(px,s[i-1]);
    sum=max(sum,(s[0]+s[i])*(px+a[i+1]));
  }
  ~~~

---

## 杂谈

### 快速幂
>>
>>虽然说模板用的很溜但是还是得老老实实学一下二进制，万一涉及到大数据压缩呢

- **实现一**

~~~cpp
  int quickPower(int a, int b)//是求a的b次方
{
 int ans = 1, base = a;//ans为答案，base为a^(2^n)
 while(b > 0)//b是一个变化的二进制数，如果还没有用完
    {
  if(b & 1)//&是位运算，b&1表示b在二进制下最后一位是不是1，如果是：
   ans *= base;//把ans乘上对应的a^(2^n)
  
        base *= base;//base自乘，由a^(2^n)变成a^(2^(n+1))
  b >>= 1;//位运算，b右移一位，如101变成10（把最右边的1移掉了），10010变成1001。现在b在二进制下最后一位是刚刚的倒数第二位。结合上面b & 1食用更佳
 }
 return ans;
}
~~~

>简单来说就是通过位移让a^b=a^x1+a^x2+……

- **实现**

### 二进制转化器

~~~cpp
   int a, b;
    cin   >> b;
    string biob = "";
    int tp = b;
    while(tp>0){
        if(tp&1){biob = "1" + biob;}
        else{biob = "0" + biob;}
        tp/=2;
    }

cout<<biob;
~~~

### 乘法逆元

乘法逆元公式（基于费马小定理，适用于 \( p \) 是素数且 \( \gcd(a, p) = 1 \)）：

\[
a^{-1} \equiv a^{p-2} \pmod{p}
\]

因此，对 \( x / a \) 取模 \( p \) 的结果为：

\[
\frac{x}{a} \equiv x \cdot a^{-1} \equiv x \cdot a^{p-2} \pmod{p}
\]

**总结公式**：

\[
\boxed{\dfrac{x}{a} \equiv x \cdot a^{p-2} \pmod{p}}
\]

（使用快速幂算法计算 \( a^{p-2} \mod p \) 可高效求得逆元。）

## 教学

### 以滑雪为例题讲解BFS与拓扑DP

#### part1：建立反图（计算入度）
>
>“原图出度为 0 是起点，反图入度为 0 是终点”
  我们想从终点开始 DP → 必须用反图！

**场景,为什么用反图,例子**

  1. 拓扑排序 + DP（最长/最短路）,想从“终点”开始推 → 反图入度
  2. 求“前驱”而不是“后继”,原来求“能到达谁”，现在求“谁能到达我”,谁能影响到我
  3. 某些图算法需要逆向遍历,Tarjan、Kosaraju 求 SCC,强连通分量

  >元素,含义,代码表示
点（Node / Vertex）,问题中的“对象”,"int u, v 或 pair<int,int>"
边（Edge）,点之间的“关系”,u → v
权值（Weight）,边的“代价”或“长度”,w（有时没有）

**建图的步骤**

   1. 确定“点”是什么
   2. 确定“边”从哪到哪（方向 + 条件）
   3. 选择存储方式（邻接表 / 邻接矩阵）
   4. 遍历所有可能的边，加入图中

**计算入度**

~~~
if (height[r][c] > height[nr][nc])
    inDegree[r][c]++;  // 反图：(nr,nc) → (r,c)
~~~

这段代码并没有直接“建”反图的边，而是通过遍历网格时检查相反的条件来计算某个顶点的**入度** 。
这种结构的核心目的是将一个网格问题转化为一个有向无环图 (DAG)上的问题，从而利用拓扑排序或记忆化搜索/动态规划等高效的图算法来求解。

#### part2：BFS

- step1：入度为0的点加入队列(入度不入度的只是建边而已)

~~~cpp
queue<pair<int,int>> q;//建立一个以点坐标为项目的队列
for (int r = 0; r < R; ++r)
  for (int c = 0; c < C; ++c)
    if (in[r][c] == 0) q.emplace(r,c);
~~~

~~~cpp
while (!q.empty()) {//如果队列不空
  auto [r, c] = q.front();//1. 获取队首元素 (r, c) 对，并用结构化绑定解包到 r 和 c 两个变量中。
     q.pop();.// 2. 将队首元素从队列中移除。    

  for (int d = 0; d < 4; ++d) {//遍历邻居并更新 DP 和入度
    int nr = r + dr[d], nc = c + dc[d];
    if (nr>=0 && nr<R && nc>=0 && nc<C && height[nr][nc] > height[r][c]) {
      dp[nr][nc] = max(dp[nr][nc], dp[r][c] + 1);   // v → u
      if (--in[nr][nc] == 0) q.emplace(nr,nc);
    }
  }
}

~~~

`nr>=0 && nr<R && nc>=0 && nc<C`是检查邻居边界
`height[nr][nc] > height[r][c]`是检查是否可以滑行
`dp[nr][nc] = max(dp[nr][nc], dp[r][c] + 1);dp[x][y]` 是“从 (x,y) 出发”最长路径

>这里涉及到一些结构化绑定写法：

- q.front() 返回一个 std::pair<int, int> 类型的对象（或者一个包含两个 int 的自定义结构体）。
  auto [r, c] 告诉编译器：将这个对象解包，把它的第一个元素赋值给变量 r，第二个元素赋值给变量 c。
- 队列操作
**q.front()**,返回队列中最前面的元素的引用（但不移除它）。,auto pair_rc = q.front();
**q.pop()**,移除队列中最前面的元素（但不返回它）。,q.pop();
**q.empty()**,检查队列是否为空，返回 true 或 false。,while (!q.empty())
**q.emplace(...)**,在队列尾部原地构造并添加一个新元素。,"q.emplace(nr, nc);"

### 神秘UB记录点

### stl记录

- `string s = to_string(某个string数组)`
- `int hsh=*max_element(dp.begin()+1,dp.end());`找到最大的元素，返回迭代器，需要*取指针
- `auto it = find(v.begin(), v.end(), target);`返回迭代器，需要取指针。
- 提取下标：`(it - v.begin())`
- `gcd()`计算最大公约数
- `binary_search`在有序数列中寻找指定元素
- `next_permutation(a.begin(),a.end())`返回下一个全排列（字典序）

---

## 总结
