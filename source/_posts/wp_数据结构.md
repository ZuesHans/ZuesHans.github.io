---
title: wp_数据结构
date: 2025-12-10
tags:
    - 算法
cover: /img/cover/default.png
---


### 并查集

#### [家谱](https://www.luogu.com.cn/problem/P2814)

- **核心模型**:题目要求给出一个父亲的名字，以及他的儿子们。接下来进行若干次查询，查询一个人的祖宗
- **思维误区 (Bug)**:套用dsu模板，但是模板默认有启发式合并
- **修正逻辑 (Patch)**:这道题强制要求了父亲与儿子的关系，所以删掉启发式合并，把father放在前面son放在后面（模板默认后面的往前面合并）
- **关键代码**:

>DSU（并查集）里的启发式合并
>在并查集中，启发式合并通常被称为 “按秩合并” (Union by Rank) 或 “按大小合并” (Union by Size)。
>
>它的目的是 防止树退化成链，从而保证查询速度。
>
>1. 没有启发式合并：如果每次都固定把 $Y$ 接在 $X$ 下面，而在极端数据下（比如 $1 \to 2, 2 \to 3, \dots, N-1 \to N$），并查集会变成一条长长的“链表”。查找一次祖先需要 $O(N)$ 的时间。
>2. 有启发式合并：我们维护每棵树的 size（节点数）或 rank（高度）。永远把更小（或更矮）的那棵树，接到更大（或更高）的那棵树下面。

```cpp
struct DSU
{
    std::vector<int> fa, sz;
    int count; // 连通块数量

    // 初始化：传入点数 n (支持 0~n 或 1~n)
    DSU(int n) : fa(n + 1), sz(n + 1, 1), count(n)
    {
        std::iota(fa.begin(), fa.end(), 0); // 0, 1, 2...
    }

    // 查找 + 路径压缩
    int find(int x)
    {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    // 合并 x 和 y
    // 返回 true 表示合并成功（原来不连通）
    // 返回 false 表示原来就是连通的
    bool merge(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY)
            return false;

        // 启发式合并：把小的树接到大的树下面
        // if (sz[rootX] < sz[rootY])
        //     std::swap(rootX, rootY);

        fa[rootY] = rootX;      // Y 认 X 做爹
        sz[rootX] += sz[rootY]; // X 吸收 Y 的人口
        count--;                // 连通块少一个
        return true;
    }

    // 判断是否连通
    bool same(int x, int y)
    {
        return find(x) == find(y);
    }

    // 获取 x 所在连通块的大小
    int size(int x)
    {
        return sz[find(x)];
    }
};
```

---

### 优先队列

#### [P7913 [CSP-S 2021] 廊桥分配]([题目URL](https://www.luogu.com.cn/problem/P7913))

- **核心模型**:优先队列模拟，读错题
- **思维误区 (Bug)**:wronganser1：贪心分配航道逻辑错了。wronganser2：没有释放完他的航道(while写成if)
- 注意重复调用的函数写成lambda
  实现小技巧：可以前缀和过去on查询航道占用（贪心序号最小，也就是尽可能地再前面的航道放更多地飞机）
- **修正逻辑 (Patch)**:
- **关键代码**:

```cpp
struct tim
{
    int l, r;
};

void solve()
{
    int n, m1, m2;
    cin >> n >> m1 >> m2;

    vector<tim> gn(m1);
    vector<tim> gw(m2);

    rep(i, 0, m1 - 1) cin >> gn[i].l >> gn[i].r;
    rep(i, 0, m2 - 1) cin >> gw[i].l >> gw[i].r;

    auto px = [&](vector<tim> &a,vi &pre) -> void
    {
        priority_queue<pii, vector<pii>, greater<pii>> man;
        priority_queue<int, vi, greater<>> xian;

        vi cnt(n + 2, 0);
        int idx = 0;
        for (auto it : a)
        {
            while(!man.empty() && it.l > man.top().first)
            {
                xian.push(man.top().second);
                man.pop();
            }

            int now=0;
            if(!xian.empty())
            {
                now=xian.top();
                xian.pop();
            }
            else 
            {
                idx++;
                now=idx;
            }
            if(now<=n)
            {
                cnt[now]++;
                man.push({it.r,now});

            }

        }

        for(int i=1;i<=n;i++)
        {
            pre[i]=cnt[i]+pre[i-1];
        }
    };

    sort(all(gn), [&](tim a, tim b)
         { return a.l < b.l; });
    sort(all(gw), [&](tim a, tim b)
         { return a.l < b.l; });

    vi pre1(n+2);
    vi pre2(n+2);

    px(gn,pre1);
    px(gw,pre2);

    ll ans=-1;
    for(int i=0;i<=n;i++)
    {
        ans=max(ans,(ll)pre1[i]+pre2[n-i]);
    }
cout<<ans<<'\n';

}

```

---

### 单调栈

#### [玉蟾宫](https://www.luogu.com.cn/problem/P4147)

- **核心模型**:单调栈求最大矩形面积，找到以每一行为底的高度（直接累加，线性处理）
- **思维误区 (Bug)**:单调栈方向反了，以及单调栈里面留下的最后一个元素是最远阻挠元素，我们的通行范围是阻挠元素往里面一点的那一段
- **修正逻辑 (Patch)**:记得检查数据范围
- **一些思维上的疑惑**：
  - 中间消失的那些元素，一定比栈里留下的元素“高”或者“等高”
  - 计算合法的原因是因为维护的左边和右边由于他的特性一定是匹配的两个
  - 单调栈的特性：找到最近的那一个，因为元素是有序的所以可以保证逻辑是线性的；
  - 这份代码里面的单调栈查找逻辑：对于每个点（这一行）维护他的往左区间，**所以更新在emplace前更新（注意更新时间）**由于单调栈的线性逻辑特性top永远是最近的。
- **关键代码**:

```cpp
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vi> mp(n, vi(m, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char d;
            cin >> d;
            if (d == 'F')
                mp[i][j] = 1;
        }
    }

    vi h(m);
    vi l(m), r(m);
    ll ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mp[i][j])
            {
                h[j]++;
            }
            else
                h[j] = 0;
        }

        stack<int> stk;
        for (int j = 0; j < m; j++)
        {
            while (!stk.empty() && h[stk.top()] >= h[j])
            {
                stk.pop();
            }

            if (stk.empty())
            {
                l[j] = 0;
            }
            else
            {
                l[j] = stk.top()+1;
            }

            stk.emplace(j);
        }

        stack<int> stk1;
        for (int j = m - 1; j >= 0; j--)
        {
            while (!stk1.empty() && h[stk1.top()] >= h[j])
            {
                stk1.pop();
            }

            if (stk1.empty())
            {
                r[j] = m-1;
            }
            else
            {
                r[j] = stk1.top() -1;
            }

            stk1.emplace(j);
        }

        for (int j = 0; j < m; j++)
            ans = max(ans, (ll)(r[j] - l[j] + 1) * h[j]);
    }
    cout << ans * 3;
}
```

#### [ImbalancedArray](https://codeforces.com/problemset/problem/817/D)

- **核心模型**:推式子模拟计算
- **思维误区 (Bug)**:**记得计算贡献的时候，左闭右闭区间看的是点不是长度！所以要+1**.以及你的操作是左维护一个值右边维护一个值，记得有一个区间开一个区间闭！以下提供ac代码的完美的去重逻辑

- **修正逻辑 (Patch)**
  - 要求区间最大值和最小值的差。进行简单的数学划分就能划出来->sum={min}+{max}.
  - 对于每个数来说，计算他能影响到的区间，也就是他可以给总结果的贡献
  - 根据乘法原理可以算出一个数字他可以贡献的价值为nums[i]，他贡献的次数是他作为最大值/最小值出现在某个区间的组合种类数->ans +=(ll) (nums[i] x (i - le[i]+1) X (ri[i] - i+1));（乘法原理）
  - **单调栈就是用来维护这种**==最近区间==的
- **关键代码**:

```cpp
void solve()
{
    int n;
    cin >> n;
    vi nums(n + 1);
    rep(i, 1, n)
    {
        cin >> nums[i];
    }

    vi le(n + 1);
    vi ri(n + 1);
    //-------------维护最大值-------------------//

    stack<int> stkl;
    for (int i = 1; i <= n; i++)
    {
        while (!stkl.empty() && nums[stkl.top()] <= nums[i])//区间闭
        {
            stkl.pop();
        }
        if (stkl.empty())
        {
            le[i] = 1;
        }
        else
        {
            le[i] = stkl.top() + 1;
        }
        stkl.emplace(i);
    }
    stack<int> stkr;
    for (int i = n; i >= 1; i--)
    {
        while (!stkr.empty() && nums[stkr.top()] < nums[i])//区间开
        {
            stkr.pop();
        }
        if (stkr.empty())
        {
            ri[i] = n;
        }
        else
        {
            ri[i] = stkr.top() - 1;
        }
        stkr.emplace(i);
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i) // 计算贡献
        ans +=(ll) (nums[i] * (i - le[i]+1) * (ri[i] - i+1));
    //-------------维护最小值-------------------//

    vi l(n + 1);
    vi r(n + 1);
    stack<int> stl;
    for (int i = 1; i <= n; i++)
    {
        while (!stl.empty() && nums[stl.top()] >= nums[i])
        {
            stl.pop();
        }
        if (stl.empty())
        {
            l[i] = 1;
        }
        else
        {
            l[i] = stl.top() + 1;
        }
        stl.emplace(i);
    }
    stack<int> str;
    for (int i = n; i >= 1; i--)
    {
        while (!str.empty() && nums[str.top()] > nums[i])
        {
            str.pop();
        }
        if (str.empty())
        {
            r[i] = n;
        }
        else
        {
            r[i] = str.top() - 1;
        }
        str.emplace(i);
    }
    
    for (int i = 1; i <= n; ++i) // 计算贡献
        ans -= (ll)(nums[i] * (i - l[i]+1) * (r[i] - i+1));

    cout << ans << '\n';
}
```

#### [良好的感觉](https://www.luogu.com.cn/problem/P2422)

- **核心模型**:单调栈维护某个最小值的“生效区间”
- **思维误区 (Bug)**:单调栈的边界判断-悬线法
- **修正逻辑 (Patch)**:左边边界收缩（+1）一点，右边边界收缩（-1）一点
- **单调栈逻辑**：维护最小值堆里面留下大的，维护最大值堆里面留下小的
- **关键代码**:

```cpp
void solve()
{
    int n;
    cin >> n;
    int d;
    vi qzh(n + 1);
    vi nms(n + 1);
    rep(i, 1, n)
    {
        cin >> d;
        nms[i] = d;
        qzh[i] = qzh[i - 1] + d;
    }

    vi l(n + 1);
    vi r(n + 1);
    stack<int> stl;
    for (int i = 1; i <= n; i++)
    {
        while (!stl.empty() && nms[stl.top()] >= nms[i])
        {
            stl.pop();
        }
        if (stl.empty())
        {
            l[i] = 1;
        }
        else
        {
            l[i] = stl.top() +1;
        }
        stl.emplace(i);
    }
    stack<int> str;
    for (int i = n; i >= 1; i--)
    {
        while (!str.empty() && nms[str.top()] > nms[i])
        {
            str.pop();
        }
        if (str.empty())
        {
            r[i] = n;
        }
        else
        {
            r[i] = str.top()-1;
        }
        str.emplace(i);
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ll sumq = qzh[r[i]] - qzh[l[i]-1];
        ll qq = nms[i];
       // cerr<<sumq<<' '<<qq<<' '<<nms[i]<<"sss"<<l[i]<<' '<<r[i]<<'\n';
        ans = max(ans, sumq * qq);
    }
    cout<<ans;
}

```

---

---

---
