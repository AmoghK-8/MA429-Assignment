#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll mod = 1000000007;

static short par_[3001][3001], sub_[3001][3001];
static ll dp[3001][3001];
vector<int> adj[3001];

ll go(int u, int v)
{
    if (u == v)
        return 0;
    ll &r = dp[u][v];
    if (r != -1)
        return r;
    r = (ll)sub_[v][u] * sub_[u][v] + max(go(par_[v][u], v), go(u, par_[u][v]));
    return r;
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int root = 1; root <= n; root++)
    {
        vector<int> order;
        order.reserve(n);
        order.push_back(root);
        par_[root][root] = 0;
        for (int i = 0; i < (int)order.size(); i++)
        {
            int u = order[i];
            sub_[root][u] = 1;
            for (int w : adj[u])
                if (w != par_[root][u])
                {
                    par_[root][w] = u;
                    order.push_back(w);
                }
        }
        for (int i = n - 1; i > 0; i--)
        {
            int u = order[i];
            sub_[root][par_[root][u]] += sub_[root][u];
        }
    }
    memset(dp, -1, sizeof dp);
    ll ans = 0;
    for (int u = 1; u <= n; u++)
        for (int v = u + 1; v <= n; v++)
            ans = max(ans, go(u, v));
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