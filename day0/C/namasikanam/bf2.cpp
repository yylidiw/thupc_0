#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;

bool is_prm[N];
list<int> prm_dvs[N];

struct Monitor
{
    int x;
    ll y;

    list<pair<int, list<int>::iterator> > submonitors;
} a[N];
int monitor_tot;

list<int> monitors[N];
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    // 初始化
    memset(is_prm, true, sizeof(is_prm));
    is_prm[1] = false;
    for (int i = 2; i <= n; ++i)
        if (is_prm[i])
        {
            for (int j = 2 * i; j <= n; j += i)
                is_prm[j] = false;
            for (int j = i; j <= n; j += i)
                prm_dvs[j].push_back(i);
        }

    ll lastans = 0;
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

            for (int p: prm_dvs[x])
                for (int monitor_id: monitors[p])
                    if (a[monitor_id].y > 0) {
                        if ((a[monitor_id].y -= y) <= 0) {
                            triggered.push_back(monitor_id);
                        }
                    }
            
            // remove triggered monitors
            for (int monitor_id: triggered)
                for (auto pair: a[monitor_id].submonitors)
                    monitors[pair.first].erase(pair.second);
            
            sort(triggered.begin(), triggered.end());
            printf("%u", (unsigned)triggered.size());
            for (int monitor_id: triggered)
                printf(" %d", monitor_id);
            puts("");
            lastans = triggered.size();
            triggered.clear();
        }
        else
        {
            ++monitor_tot;
            a[monitor_tot] = Monitor{x, y};
            
            if (y == 0)
                triggered.push_back(monitor_tot);
            else
            {
                for (int p: prm_dvs[x])
                {
                    monitors[p].push_back(monitor_tot);
                    auto it = --monitors[p].end();
                    a[monitor_tot].submonitors.push_back(make_pair(p, it));
                }
            }
        }
    }
}
