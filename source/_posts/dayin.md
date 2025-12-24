## 离散化

- **离散化点**

```cpp
// 1. 复制一份用来查表
vector<int> b = a; 

// 2. 排序 + 去重
sort(b.begin(), b.end());
b.erase(unique(b.begin(), b.end()), b.end());

// 3. 直接修改原数组 a
for (int i = 1; i <= n; i++) {
    // 这里的 +1 是为了适配树状数组下标从1开始
    a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
}

// 现在 a[i] 已经是 1 ~ N 的小整数了，直接用
```

- **离散化区间**

#### 区间离散化裸题

核心模型:离散化
思维误区 (Bug):记住离散化的前缀和是只用给pre[r]–，因为是把距离压缩到前面那个点
修正逻辑 (Patch):使用erase和uniqe，记得erase需要nums.end(*)

```cpp
void solve()
{
    int n;
    cin >> n;
    vector<int> arr = {(int)-1e18,(int)1e18};
    vector<int> bg(n);
    vector<int> ed(n);
    for (int i = 0; i < n; i++)
    {
        cin >> bg[i] >> ed[i];
        arr.push_back(bg[i]);
        arr.push_back(ed[i]);
    }
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()));
    int m = arr.size();
    vector<int> pre(m + 2);
    for (int i = 0; i < n; i++)
    {
        int l = lower_bound(arr.begin(), arr.end(), bg[i]) - arr.begin();
        int r = lower_bound(arr.begin(), arr.end(), ed[i]) - arr.begin();
        pre[l]++;
        pre[r]--;
    }

    int ans = 0;
    for (int i = 1; i < m + 1; i++)
    {
        pre[i] = pre[i] + pre[i - 1];
    }
    bool ok = true;
    for(int i=0;i<m-1;++i)
    {
        if(pre[i])
        {
            ans+=arr[i+1]-arr[i];
        }
    }
    cout << ans;
}


```
