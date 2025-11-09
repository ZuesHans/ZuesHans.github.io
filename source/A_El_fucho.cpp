//Time: 2025-11-09 14:30:18 (周日)

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
// #define int long long  // 慎开！大数爆 int 时再开

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
    cin>>n;
    int wi=n;
    int lo=0;
    int ans=0;

    while(wi!=1||lo!=1)
    {
        lo=wi/2;
        wi=(wi+1)/2;
        ans+=lo*2;
     // cerr<<lo<<' '<<wi<<' '<<ans<<endl;
    }
    cout<<ans<<'\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 1;
    cin >> T;  // 多组数据时取消注释

    while (T--)
    {
        solve();
    }

    return 0;
}