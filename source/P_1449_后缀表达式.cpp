// Time: 2025-11-09 23:44:58 (周日)

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
//#define int long long  // 慎开！大数爆 int 时再开

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
    string s;
    cin >> s;
    stack<int> cul;

    stack<char> sz;
    rep(i, 0, s.size())
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            sz.emplace(s[i]);
        }
        if (s[i] == '.')
        {
            int x = 1;
            int num = 0;
            while (!sz.empty())
            {
                auto hsh = sz.top();
                sz.pop();
                num += (hsh - '0') * x;
                x *= 10;
            }
 
            cul.emplace(num);
        }
        if (s[i] == '-')
        {
            int ans = 0;
            auto ljl = cul.top();
            cul.pop();
            auto hsh = cul.top();
            cul.pop();
            ans = (hsh - ljl);
            cul.emplace(ans);
        }
        if (s[i] == '+')
        {
            int ans = 0;
            auto ljl = cul.top();
            cul.pop();
            auto hsh = cul.top();
            cul.pop();
            ans += (hsh + ljl);
            cul.emplace(ans);
        }
        if (s[i] == '*')
        {
            int ans = 0;
            auto ljl = cul.top();
            cul.pop();
            auto hsh = cul.top();
            cul.pop();
            ans += (hsh * ljl);
            cul.emplace(ans);
        }
        if (s[i] == '/')
        {
            int ans = 0;
            auto ljl = cul.top();
            cul.pop();
            auto hsh = cul.top();
            cul.pop();
            ans = hsh/ljl;
            cul.emplace(ans);
        }
    }
    cout<<cul.top();
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