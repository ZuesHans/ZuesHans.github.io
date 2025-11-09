//Time: 2025-11-09 23:38:28 (周日)

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
    int n,q;
    map<int,map<int,int>> box;
    cin>>n>>q;
    rep(i,0,q-1)
    {
        int cz,q,w,k;
        cin>>cz;
        if(cz==1)
        {
            cin>>q>>w>>k;
            if(k!=0)
            {
                box[q][w]+=k;
            }
            else box[q][w]=0;
        }
         if(cz==2)
        {
            cin>>q>>w;
            cout<<box[q][w]<<'\n';
        }
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