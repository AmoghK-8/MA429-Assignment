#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll mod = 1000000007;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

bool ok(ll v, ll X, ll o)
{
    return ((v & X) == o) || ((v | X) == o);
}

void solve()
{
    const ll M = (1LL << 30) - 1;
    const ll X = 0x15555555LL; // 15 set bits, all < 2^30
    cout << X << endl;
    ll o;
    cin >> o;
    if (o == -1)
        exit(0);
    ll D = rng() & M;
    if (!(D & X))
        D |= 1;
    if (!(D & (M ^ X)))
        D |= 2;
    ll m0 = 0, m1 = D;
    cout << m0 << " " << m1 << endl;
    ll r;
    cin >> r;
    if (r == -1)
        exit(0);
    bool a = ok(r ^ m0, X, o), b = ok(r ^ m1, X, o);
    int ans;
    if (a && !b)
        ans = 0;
    else if (b && !a)
        ans = 1;
    else
        ans = rng() & 1;
    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}