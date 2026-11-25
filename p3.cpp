#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll mod = 1000000007;

int id(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a';
    if (c >= 'A' && c <= 'Z')
        return 26 + c - 'A';
    return 52 + c - '0';
}
char chr(int i)
{
    if (i < 26)
        return 'a' + i;
    if (i < 52)
        return 'A' + i - 26;
    return '0' + i - 52;
}

void solve()
{
    int n;
    cin >> n;
    const int V = 62 * 62;
    vector<vector<int>> g(V);
    vector<int> in(V, 0), out(V, 0);
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        int a = id(s[0]) * 62 + id(s[1]);
        int b = id(s[1]) * 62 + id(s[2]);
        g[a].push_back(b);
        out[a]++;
        in[b]++;
    }
    int start = -1, cs = 0, ce = 0;
    for (int v = 0; v < V; v++)
    {
        int d = out[v] - in[v];
        if (d == 1)
        {
            cs++;
            start = v;
        }
        else if (d == -1)
            ce++;
        else if (d != 0)
        {
            cout << "NO\n";
            return;
        }
    }
    if (!((cs == 0 && ce == 0) || (cs == 1 && ce == 1)))
    {
        cout << "NO\n";
        return;
    }
    if (start == -1)
    {
        for (int v = 0; v < V; v++)
            if (out[v] > 0)
            {
                start = v;
                break;
            }
    }
    vector<int> st = {start}, path;
    while (!st.empty())
    {
        int v = st.back();
        if (g[v].empty())
        {
            path.push_back(v);
            st.pop_back();
        }
        else
        {
            int u = g[v].back();
            g[v].pop_back();
            st.push_back(u);
        }
    }
    reverse(path.begin(), path.end());
    if ((int)path.size() != n + 1)
    {
        cout << "NO\n";
        return;
    }
    string res;
    res += chr(path[0] / 62);
    res += chr(path[0] % 62);
    for (int i = 1; i < (int)path.size(); i++)
        res += chr(path[i] % 62);
    cout << "YES\n"
         << res << "\n";
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