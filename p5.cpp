#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll mod = 1000000007;

void solve()
{
    int n;
    string t;
    cin >> n >> t;
    int m;
    cin >> m;
    vector<string> words(m);
    vector<array<int, 26>> trie;
    trie.reserve(1000002);
    vector<int> wid;
    wid.reserve(1000002);
    array<int, 26> emptyNode;
    emptyNode.fill(0);
    trie.push_back(emptyNode);
    wid.push_back(-1);
    for (int i = 0; i < m; i++)
    {
        cin >> words[i];
        string w = words[i];
        for (auto &ch : w)
            ch = tolower(ch);
        reverse(w.begin(), w.end());
        int node = 0;
        for (char ch : w)
        {
            int c = ch - 'a';
            if (!trie[node][c])
            {
                trie.push_back(emptyNode);
                wid.push_back(-1);
                trie[node][c] = trie.size() - 1;
            }
            node = trie[node][c];
        }
        if (wid[node] == -1)
            wid[node] = i;
    }
    vector<char> can(n + 1, 0);
    vector<int> choice(n + 1, -1), nxt(n + 1, -1);
    can[n] = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        int node = 0;
        for (int p = i; p < n; p++)
        {
            node = trie[node][t[p] - 'a'];
            if (!node)
                break;
            if (wid[node] != -1 && can[p + 1])
            {
                can[i] = 1;
                choice[i] = wid[node];
                nxt[i] = p + 1;
                break;
            }
        }
    }
    int i = 0;
    bool first = true;
    while (i < n)
    {
        if (!first)
            cout << " ";
        cout << words[choice[i]];
        first = false;
        i = nxt[i];
    }
    cout << "\n";
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