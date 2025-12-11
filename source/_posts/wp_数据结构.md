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
