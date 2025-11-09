// Time: 2025-11-09 13:07:39 (周日)

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
    cin >> n;
    map<int, bool> cek;
    stack<int> zhan;
    rep(i, 1, n )
    {
        int d;
        cin >> d;
        if (cek.empty())
        {
            zhan.emplace(d);
            cek[d] = true;
            continue;
        }
        else if (!cek.empty() && cek.find(d) == cek.end())
        {
            zhan.emplace(d);
            cek[d] = true; 
            continue;
        }

        else if (!cek.empty() &&cek[d] == 0)
        {
            zhan.emplace(d);
            cek[d] = true ;
            continue;
        }
        else if (!cek.empty() &&cek[d] == 1)
        {
            int p;
            p = zhan.top();
            while (p != d)
            {
                zhan.pop();
                    cek[p] = 0;
                p = zhan.top();
            
            }
            zhan.pop();
            cek[d] = 0;
            continue;
        }
    }
    cout << zhan.size();
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