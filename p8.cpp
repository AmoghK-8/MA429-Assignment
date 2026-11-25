#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll mod = 1000000007;

int n, q;
vector<int> pr, sz, pa, stk;
vector<vector<pair<int, int>>> seg;
vector<int> ans;

pair<int, int> fnd(int x)
{
    int p = 0;
    while (pr[x] != x)
    {
        p ^= pa[x];
        x = pr[x];
    }
    return {x, p};
}
bool unite(int u, int v)
{
    auto p1 = fnd(u) ; int ru = p1.first , pu = p1.second ;
    auto p2 = fnd(v) ; int rv = p2.first , pv = p2.second ;
    if (ru == rv)
        return pu != pv;
    if (sz[ru] < sz[rv])
        swap(ru, rv);
    pr[rv] = ru;
    pa[rv] = pu ^ pv ^ 1;
    sz[ru] += sz[rv];
    stk.push_back(rv);
    return true;
}
void rollback(size_t to)
{
    while (stk.size() > to)
    {
        int rv = stk.back();
        stk.pop_back();
        int ru = pr[rv];
        sz[ru] -= sz[rv];
        pr[rv] = rv;
        pa[rv] = 0;
    }
}
void add(int node, int l, int r, int ql, int qr, pair<int, int> e)
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
    bool ok = true;
    for (auto &e : seg[node])
        if (!unite(e.first, e.second))
        {
            ok = false;
            break;
        }
    if (!ok)
    {
        for (int i = l; i <= r; i++)
            ans[i] = 0;
    }
    else if (l == r)
        ans[l] = 1;
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
    cin >> n >> q;
    pr.resize(n + 1);
    iota(pr.begin(), pr.end(), 0);
    sz.assign(n + 1, 1);
    pa.assign(n + 1, 0);
    seg.assign(4 * q + 4, {});
    ans.assign(q, 0);
    map<pair<int, int>, int> open;
    for (int i = 0; i < q; i++)
    {
        int x, y;
        cin >> x >> y;
        auto key = make_pair(x, y);
        auto it = open.find(key);
        if (it == open.end())
            open[key] = i;
        else
        {
            add(1, 0, q - 1, it->second, i - 1, key);
            open.erase(it);
        }
    }
    for (auto &p : open){
        auto key = p.first ; 
        auto st = p.second ;
        add(1, 0, q - 1, st, q - 1, key);
    }
        
    dfs(1, 0, q - 1);
    for (int i = 0; i < q; i++)
        cout << (ans[i] ? "YES" : "NO") << "\n";
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