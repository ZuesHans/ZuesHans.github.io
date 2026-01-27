//Time: 2026-01-12 16:27:32 (周一)
//Author:  Keronshans

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define all(x) (x).begin(), (x).end()
// #define int long long 

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
const int NB=1e6+10;
void solve()
{

    vi mp(NB);

    for(int i=1;i<NB;i++)
    {
        for(int j=i;j<NB;j+=i)
        {
            mp[j]++;
        }
    }
    
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int q;
        cin>>q;
        cout<<mp[q]<<'\n';
    }
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