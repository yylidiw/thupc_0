#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;

struct Monitor
{
    int id;
    int x;
    ll y;

    bool operator< (const Monitor &o) const {
        return id < o.id;
    }
};
list<Monitor> monitors;
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

    ll lastans = 0;
    vector<Monitor> triggered;
    for (int i = 1; i <= m; ++i)
    {
        int op, x;
        ll y;
        scanf("%d%d%lld", &op, &x, &y);
        y ^= lastans;
        if (op == 0)
        {
            // printf("haunted %d %lld\n", x, y);

            for (auto it = monitors.begin(); it != monitors.end();)
                if (it->y > 0)
                {
                    it->y -= pd_cnt[__gcd(x, it->x)] * y;

                    // printf("minus %d * %lld for monitor %d\n", pd_cnt[__gcd(x, monitor[j].x)], y, monitor[j].id);

                    if (it->y <= 0)
                    {
                        triggered.push_back(*it);
                        monitors.erase(it++);
                    }
                    else ++it;
                }
                else ++it;
            sort(triggered.begin(), triggered.end());
            printf("%u", (unsigned)triggered.size());
            for (Monitor monitor: triggered)
                printf(" %d", monitor.id);
            puts("");
            lastans = triggered.size();
            triggered.clear();
        }
        else
        {
            Monitor monitor = Monitor{
                .id = ++monitor_id,
                .x = x,
                .y = y};
            
            if (y == 0)
                triggered.push_back(monitor);
            else
                monitors.push_back(monitor);
        }
    }
}
