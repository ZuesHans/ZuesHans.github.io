```cpp
vi LIS_nlogn(vector<int> &a)
{
if (a.empty()) return {};
    vector<int> low;
    vector<int> low_idx;
    vector<int> pre(a.size(), -1);
    for (int i = 0; i < a.size(); i++)
    {
        if (low.empty() || a[i] >= low.back())
        {
            if (!low_idx.empty())
                pre[i] = low_idx.back();
            low.push_back(a[i]);
            low_idx.push_back(i);
        }

        else
        {
            auto it = upper_bound(low.begin(), low.end(), a[i]);
            *it = a[i];
            int p = it - low.begin();
            low_idx[it - low.begin()] = i;
            if (p > 0)
                pre[i] = low_idx[p - 1];
        }
    }

    vi res;
    for (int i = low_idx.back(); i != -1; i = pre[i])
    {
        res.push_back(i + 1); // 1 开始
    }
    reverse(all(res));
    return res;
}

```

- 狄尔沃斯定理结论：
将一个序列划分为最少数量的 $X$ 子序列，其最少数量等于该序列最长 $Y$ 子序列的长度。（$X$ 和 $Y$ 互为“反面”）
  - 最少【上升】子序列个数 == 最长【不上升】子序列长度
  - 最少【不下降】子序列个数 == 最长【严格下降】子序列长度

```cpp
struct DSU
{
    vector<int> f, siz;
    int cnt;

    DSU(int n) : f(n), siz(n, 1), cnt(n)
    {
        iota(f.begin(), f.end(), 0);
    }
    // DSU(int n) : fa(n + 1), sz(n + 1, 1), count(n) 
    // {
    //     std::iota(fa.begin(), fa.end(), 0);
    // }

    int find(int x)
    {
        while (x != f[x])
            x = f[x] = f[f[x]];
        return x;
    }

    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        // if (siz[x] < siz[y]) swap(x, y);
        siz[x] += siz[y];
        f[y] = x;
        cnt--;
        return true;
    }

    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) { return siz[find(x)]; }
};
```

```cpp
struct Vector2D {
    int x;
    int y;

    // 构造函数
    Vector2D(int x = 0, int y = 0) : x(x), y(y) {}

    // 1. 重载加号 (+): 两个结构体相加
    // 注意后尾的 const：这表示该运算不会修改原结构体的值
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(this->x + other.x, this->y + other.y);
    }

    // 2. 重载判等 (==): 判断两个结构体是否一样
    bool operator==(const Vector2D& other) const {
        return this->x == other.x && this->y == other.y;
    }

    // 3. 重载小于 (<): 定义排序规则
    // 极其重要！如果你想把这个 struct 塞进 std::map、std::set，或者用 std::sort，必须重载这个
    bool operator<(const Vector2D& other) const {
        if (this->x != other.x) {
            return this->x < other.x; // 先按 x 从小到大排
        }
        return this->y < other.y;     // 如果 x 相同，按 y 从小到大排
    }
};

// 4. 【额外奉送】重载输出流 (<<) 
// 注意：这个必须写在 struct 外面！这样你就可以直接 cout 打印结构体了
std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

```
