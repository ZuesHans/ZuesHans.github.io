// Time: 2026-01-12 16:54:12 (周一)
// Author:  Keronshans

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define all(x) (x).begin(), (x).end()
//#define int long long

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000007;
const double EPS = 1e-9;

/* ======================================== */
const int NN = 1e7 + 10;
void solve()
{
    int n;
    cin >> n;
    vector<pii> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i].first;
        nums[i].second = i + 1;
    }
    sort(all(nums));
    bitset<NN> vis;
    pii ans;
    int ans1 = INF;
    int y;
    for (int i = 0; i < n; i++)
    {
        for (int j = nums[i].first; j < NN; j += nums[i].first)
        {
            if (vis[j])
            {
                if (j <= ans1)
                {
                    ans.first = nums[i].second;
                    ans1 = j;
                    y = ans1 / nums[i].first;
                }
            }
            vis[j] = 1;
        }
    }

    bool fd = 0;
    for (int i = 0; i < n; i++)
    {
        if (nums[i].first == y)
        {
            fd = 1;
            ans.second = nums[i].second;
        }
    }
    if (!fd)
    {
        for (int i = 0; i < n; i++)
        {
            if (ans1 % nums[i].first == 0 && ans.first != nums[i].second)
            {
                ans.second = nums[i].second;
            }
        }
    }
    cout << min(ans.second, ans.first) << ' ' << max(ans.first, ans.second);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 1;
    // cin >> T;  // 多组数据时取消注释

    while (T--)
    {
        solve();
    }

    return 0;
}