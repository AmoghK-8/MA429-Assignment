#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll mod = 1000000007;

ll pw(ll b, ll e)
{
    ll r = 1;
    b %= mod;
    while (e)
    {
        if (e & 1)
            r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}

vector<int> p;
int fnd(int x)
{
    while (p[x] != x)
    {
        p[x] = p[p[x]];
        x = p[x];
    }
    return x;
}

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<ll> c(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    vector<array<ll, 3>> e(m);
    for (auto &x : e)
    {
        ll u, v;
        cin >> u >> v;
        x = {c[u] ^ c[v], u, v};
    }
    sort(e.begin(), e.end());
    vector<ll> pow2(n + 1);
    pow2[0] = 1;
    for (int i = 1; i <= n; i++)
        pow2[i] = pow2[i - 1] * 2 % mod;
    p.resize(n + 1);
    iota(p.begin(), p.end(), 0);
    ll ans = 0, cntKeys = 0;
    for (int i = 0; i < m;)
    {
        int j = i;
        int merges = 0;
        vector<int> touched;
        while (j < m && e[j][0] == e[i][0])
        {
            int u = e[j][1], v = e[j][2];
            touched.push_back(u);
            touched.push_back(v);
            int a = fnd(u), b = fnd(v);
            if (a != b)
            {
                p[a] = b;
                merges++;
            }
            j++;
        }
        ans = (ans + pow2[n - merges]) % mod;
        cntKeys++;
        for (int x : touched)
            p[x] = x;
        i = j;
    }
    ll rest = ((pw(2, k) - cntKeys % mod) % mod + mod) % mod;
    ans = (ans + rest * pow2[n]) % mod;
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}