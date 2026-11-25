#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll mod = 1000000007;

int query(int c, int r)
{
    cout << "? " << c << " " << r << endl;
    int h;
    cin >> h;
    if (h == -1)
        exit(0);
    return h;
}

void solve()
{
    int n;
    cin >> n;
    int x = query(n, 1); // lies on a cycle
    int B = 1;
    while ((ll)B * B < n)
        B++;
    vector<int> pos(n + 1, -1);
    pos[x] = 0;
    int cur = x;
    for (int j = 1; j < B; j++)
    {
        cur = query(1, cur);
        pos[cur] = j; // larger j overwrites
    }
    int L = -1;
    int g = x;
    for (int t = 1;; t++)
    {
        g = query(B, g);
        if (pos[g] != -1)
        {
            L = t * B - pos[g];
            break;
        }
    }
    int m = (L - x % L) % L;
    int r = x;
    if (m != 0)
        r = query(m, x);
    cout << "! " << x << " " << r << endl;
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