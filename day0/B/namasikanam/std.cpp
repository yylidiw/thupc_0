#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = 1e5 + 5, S = M * 18 * 4;

int stot = 1;
int root[M];
int ls[S], rs[S];
ll segt[S]; // 主席树的节点上放的是“标记”

void add(int &node, int old_node, int l, int r, int L, int R, int x)
{
    node = stot++;
    segt[node] = segt[old_node];
    ls[node] = ls[old_node], rs[node] = rs[old_node];

    if (L <= l && r <= R)
        segt[node] += x;
    else
    {
        if (L <= l + r >> 1)
            add(ls[node], ls[old_node], l, l + r >> 1, L, R, x);
        if (R > l + r >> 1)
            add(rs[node], rs[old_node], (l + r >> 1) + 1, r, L, R, x);
    }
}

ll query(int node, int l, int r, int i)
{
    ll ans = segt[node];
    if (i <= l + r >> 1)
    {
        if (ls[node])
            ans += query(ls[node], l, l + r >> 1, i);
    }
    else
    {
        if (rs[node])
            ans += query(rs[node], (l + r >> 1) + 1, r, i);
    }
    return ans;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int j = 1; j <= m; ++j)
    {
        int op;
        scanf("%d", &op);
        if (op == 0)
        {
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            add(root[j], root[j - 1], 1, n, l, r, x);
        }
        else
        {
            int i;
            scanf("%d", &i);
            root[j] = root[j - 1];

            ll s = query(root[j], 1, n, i) + 1 >> 1;
            int l = -1, r = j - 1; // l < ans <= r
            while (r - l > 1)
            {
                int m = l + r >> 1;
                if (query(root[m], 1, n, i) >= s)
                    r = m;
                else
                    l = m;
            }

            printf("%d\n", j - r);
        }
    }
}