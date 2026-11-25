#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll mod = 1000000007;

vector<int> pr, sz, stk;
vector<vector<int>> seg;
vector<array<int, 2>> edges;
vector<int> qz, res;

int fnd(int x)
{
    while (pr[x] != x)
        x = pr[x];
    return x;
}
void unite(int u, int v)
{
    u = fnd(u);
    v = fnd(v);
    if (u == v)
        return;
    if (sz[u] < sz[v])
        swap(u, v);
    pr[v] = u;
    sz[u] += sz[v];
    stk.push_back(v);
}
void rollback(size_t to)
{
    while (stk.size() > to)
    {
        int v = stk.back();
        stk.pop_back();
        sz[pr[v]] -= sz[v];
        pr[v] = v;
    }
}
void add(int node, int l, int r, int ql, int qr, int e)
{
    if (ql > r || qr < l)
        return;
    if (ql <= l && r <= qr)
    {
        seg[node].push_back(e);
        return;
    }
    int m = (l + r) / 2;
    add(2 * node, l, m, ql, qr, e);
    add(2 * node + 1, m + 1, r, ql, qr, e);
}
void dfs(int node, int l, int r)
{
    size_t save = stk.size();
    for (int e : seg[node])
        unite(edges[e][0], edges[e][1]);
    if (l == r)
        res[l] = sz[fnd(qz[l])];
    else
    {
        int m = (l + r) / 2;
        dfs(2 * node, l, m);
        dfs(2 * node + 1, m + 1, r);
    }
    rollback(save);
}

void solve()
{
    int n, q, k;
    cin >> n >> q >> k;
    vector<int> eS, eD; // start (type-2 count), day
    vector<int> endCnt; // endCnt[j] = type-2 count at the j-th type-3 (1-indexed)
    endCnt.push_back(0);
    int cnt2 = 0, day = 0;
    for (int i = 0; i < q; i++)
    {
        int ty;
        cin >> ty;
        if (ty == 1)
        {
            int x, y;
            cin >> x >> y;
            edges.push_back({x, y});
            eS.push_back(cnt2);
            eD.push_back(day);
        }
        else if (ty == 2)
        {
            int z;
            cin >> z;
            qz.push_back(z);
            cnt2++;
        }
        else
        {
            day++;
            endCnt.push_back(cnt2);
        }
    }
    int m2 = cnt2;
    if (m2 == 0)
        return;
    pr.resize(n + 1);
    iota(pr.begin(), pr.end(), 0);
    sz.assign(n + 1, 1);
    seg.assign(4 * m2 + 4, {});
    res.assign(m2, 0);
    for (int e = 0; e < (int)edges.size(); e++)
    {
        int s = eS[e];
        int expire = eD[e] + k;
        int en = (expire <= day) ? endCnt[expire] : m2;
        if (s < en)
            add(1, 0, m2 - 1, s, en - 1, e);
    }
    dfs(1, 0, m2 - 1);
    for (int i = 0; i < m2; i++)
        cout << res[i] << "\n";
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