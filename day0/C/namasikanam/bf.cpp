#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;

struct Monitor
{
    int id;
    int x;
    ll y;
}monitor[N];
int monitor_id;

bool is_prm[N];
int pd_cnt[N];
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    // 初始化
    memset(is_prm, true, sizeof(is_prm));
    is_prm[1] = false;
    for (int i = 2; i <= n; ++i)
        for (int j = 2 * i; j <= n; j += i)
            is_prm[j] = false;
    for (int i = 2; i <= n; ++i)
        if (is_prm[i])
            for (int j = i; j <= n; j += i)
                ++pd_cnt[j];
    
    // for (int i = 1; i <= n; ++i) printf("pd_cnt[%d] = %lld\n", i, pd_cnt[i]);

    int lastans = 0;
    vector<int> triggered;
    for (int i = 1; i <= m; ++i)
    {
        int op, x;
        ll y;
        scanf("%d%d%lld", &op, &x, &y);
        y ^= lastans;
        if (op == 0)
        {
            // printf("haunted %d %lld\n", x, y);

            for (int j = 1; j < i; ++j)
                if (monitor[j].y > 0)
                {
                    monitor[j].y -= pd_cnt[__gcd(x, monitor[j].x)] * y;

                    // printf("minus %d * %lld for monitor %d\n", pd_cnt[__gcd(x, monitor[j].x)], y, monitor[j].id);

                    if (monitor[j].y <= 0)
                    {
                        triggered.push_back(monitor[j].id);
                    }
                }
            printf("%u", (unsigned)triggered.size());
            for (int id: triggered) printf(" %d", id);
            puts("");
            lastans = triggered.size();
            triggered.clear();
        }
        else
        {
            monitor[i] = Monitor{
                .id = ++monitor_id,
                .x = x,
                .y = y
            };
            if (y == 0)
                triggered.push_back(monitor[i].id);
        }
    }
}
