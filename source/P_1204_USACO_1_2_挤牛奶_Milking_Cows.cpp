// Time: 2025-11-22 18:28:24 (周六)

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define int long long  // 慎开！大数爆 int 时再开

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

void solve()
{
    int n;
    cin >> n;
    vi tm(1e6 + 100);
    int mx = -1;
    ll mn =LINF;
    rep(i, 1, n)
    {
        int q, w;
        cin >> q >> w;
        mn = min(mn, q);
        mx = max(mx, w);
        tm[q] += 1;
        tm[w] -= 1;
    }

    rep(i, mn, mx + 1)
    {
        if (!i)
            continue;
        tm[i] += tm[i - 1];
    }
    //cerr<<tm[1200]<<' '<<tm[1500];
    ll ans1 = 0;
    ll ans2 = 0;
    ll cnt1 = 0;
    ll cnt2 = 0;
    rep(i, mn, mx-1)
    {
        if (tm[i])
        {
            cnt1++;
            cnt2 = 0;
        }
        else
        {
            cnt2++;
            cnt1 = 0;
        }
        ans2 = max(cnt2, ans2);
        ans1 = max(cnt1, ans1);
    }
    cout << ans1 << ' ' << ans2;
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