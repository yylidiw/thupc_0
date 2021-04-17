#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5, M = 1e5 + 5;

struct Update
{
    int l, r, x;
    int j;
};
vector<Update> updates;

ll a[N];

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

            for (int i = l; i <= r; ++i)
                a[i] += x;

            updates.push_back(Update{l, r, x, j});
        }
        else
        {
            int i;
            scanf("%d", &i);

            if (a[i] == 0)
            {
                printf("%d\n", j);
            }
            else
            {
                ll s = a[i] + 1 >> 1;
                for (Update update : updates)
                    if (update.l <= i && i <= update.r && (s -= update.x) <= 0)
                    {
                        printf("%d\n", j - update.j);
                        break;
                    }
            }
        }
    }
}