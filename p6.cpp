#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll mod = 1000000007;

int dp[101][2601];

void precompute()
{
    dp[0][0] = 1;
    for (int l = 1; l <= 100; l++)
        for (int s = 0; s <= 2500; s++)
        {
            ll v = 0;
            for (int c = 0; c <= 25 && c <= s; c++)
                v += dp[l - 1][s - c];
            dp[l][s] = v % mod;
        }
}

void solve()
{
    string w;
    cin >> w;
    int s = 0;
    for (char c : w)
        s += c - 'a';
    cout << ((dp[w.size()][s] - 1) % mod + mod) % mod << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    precompute();
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}