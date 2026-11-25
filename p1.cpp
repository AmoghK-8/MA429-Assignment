#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll mod = 1000000007;

void solve()
{
    int n, k, l;
    cin >> n >> k >> l;
    vector<int> s(n + 2, 0);
    for (int i = 0; i < k; i++)
    {
        int x;
        cin >> x;
        s[x] = 1;
    }
    vector<int> pts;
    for (int i = 0; i <= n; i++)
        if (s[i] ^ s[i + 1])
            pts.push_back(i);
    vector<int> a(l);
    for (auto &x : a)
        cin >> x;
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    int m = pts.size();
    const int INF = 1e9;
    vector<vector<int>> dist(m, vector<int>(m, INF));
    for (int i = 0; i < m; i++)
    {
        vector<int> d(n + 1, -1);
        queue<int> q;
        d[pts[i]] = 0;
        q.push(pts[i]);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int x : a)
            {
                if (u + x <= n && d[u + x] == -1)
                {
                    d[u + x] = d[u] + 1;
                    q.push(u + x);
                }
                if (u - x >= 0 && d[u - x] == -1)
                {
                    d[u - x] = d[u] + 1;
                    q.push(u - x);
                }
            }
        }
        for (int j = 0; j < m; j++)
            if (d[pts[j]] != -1)
                dist[i][j] = d[pts[j]];
    }
    vector<int> dp(1 << m, INF);
    dp[0] = 0;
    for (int mask = 0; mask < (1 << m) - 1; mask++)
    {
        if (dp[mask] >= INF)
            continue;
        int i = 0;
        while (mask >> i & 1)
            i++;
        for (int j = i + 1; j < m; j++)
        {
            if (mask >> j & 1 || dist[i][j] >= INF)
                continue;
            int nm = mask | (1 << i) | (1 << j);
            dp[nm] = min(dp[nm], dp[mask] + dist[i][j]);
        }
    }
    int res = dp[(1 << m) - 1];
    cout << (res >= INF ? -1 : res) << "\n";
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