#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5, M = 1e5 + 5;

bool is_prm[N];
vector<int> prm_dvs[N];

struct Monitor
{
    int x;
    ll y;
    vector<int> heap_pos;
} monitors[M]; // (0, monitor_tot]
int monitor_tot = 0;

struct Alarm
{
    ll now, alarm;
    int monitor_id; // 是哪一个 monitor 的 alarm
    int dvs_id;     // 是其 monitor 的哪一个 divisor 的 alarm
};

vector<Alarm> heaps[N];
void init(vector<Alarm> &heap)
{
    heap.clear();
    heap.push_back(Alarm{0, 0});
}

void swap(vector<Alarm> &heap, int i, int j)
{
    swap(monitors[heap[i].monitor_id].heap_pos[heap[i].dvs_id], monitors[heap[j].monitor_id].heap_pos[heap[j].dvs_id]);
    swap(heap[i], heap[j]);
}

int down(vector<Alarm> &heap, int node)
{
    for (int next = node << 1; next < heap.size(); node = next, next <<= 1)
    {
        if (next + 1 < heap.size() && heap[next + 1].alarm < heap[next].alarm)
            ++next;
        if (heap[node].alarm > heap[next].alarm)
            swap(heap, node, next);
        else
            break;
    }
    return node;
}
int up(vector<Alarm> &heap, int node)
{
    for (int next = node >> 1; next && heap[next].alarm > heap[node].alarm; node = next, next >>= 1)
        swap(heap, node, next);
    return node;
}

ll accumulated[N];

void remove(int monitor_id)
{
    for (int dvs_id = 0; dvs_id < prm_dvs[monitors[monitor_id].x].size(); ++dvs_id)
    {
        int p = prm_dvs[monitors[monitor_id].x][dvs_id];
        int pos = monitors[monitor_id].heap_pos[dvs_id];

        monitors[monitor_id].y -= accumulated[p] - heaps[p][pos].now;

        swap(heaps[p], pos, heaps[p].size() - 1);
        heaps[p].pop_back();
        if (pos < heaps[p].size())
            down(heaps[p], up(heaps[p], pos));
    }
}

void add(int monitor_id)
{
    assert(monitors[monitor_id].y > 0);
    ll alarm = (monitors[monitor_id].y + prm_dvs[monitors[monitor_id].x].size() - 1) / prm_dvs[monitors[monitor_id].x].size();
    monitors[monitor_id].heap_pos.clear();
    for (int dvs_id = 0; dvs_id < prm_dvs[monitors[monitor_id].x].size(); ++dvs_id)
    {
        int p = prm_dvs[monitors[monitor_id].x][dvs_id];
        heaps[p].push_back(Alarm{
            .now = accumulated[p],
            .alarm = alarm + accumulated[p],
            .monitor_id = monitor_id,
            .dvs_id = dvs_id});
        monitors[monitor_id].heap_pos.push_back(heaps[p].size() - 1);
        up(heaps[p], heaps[p].size() - 1);
    }
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    // 初始化质因子相关的东西
    memset(is_prm, true, sizeof(is_prm));
    is_prm[1] = false;
    for (int i = 2; i <= n; ++i)
        if (is_prm[i])
        {
            for (int j = i + i; j <= n; j += i)
                is_prm[j] = false;
            for (int j = i; j <= n; j += i)
                prm_dvs[j].push_back(i);
        }

    // let's dance!
    ll lastans = 0;
    for (int i = 1; i <= n; ++i)
        init(heaps[i]);
    vector<int> triggered;
    for (int i = 1; i <= m; ++i)
    {
        int op;
        int x;
        ll y;
        scanf("%d%d%lld", &op, &x, &y);
        y ^= lastans;

        // printf("==== %d %d %lld ======\n", op, x, y);

        if (op == 0)
        {
            for (int p : prm_dvs[x])
            {
                accumulated[p] += y;
                while (heaps[p].size() > 1 && heaps[p][1].alarm <= accumulated[p])
                {
                    int monitor_id = heaps[p][1].monitor_id;
                    remove(monitor_id);

                    if (monitors[monitor_id].y <= 0)
                        triggered.push_back(monitor_id);
                    else
                        add(monitor_id);
                }
            }
            lastans = triggered.size();
            printf("%lld", lastans);
            for (int monitor_id : triggered)
                printf(" %d", monitor_id);
            puts("");
            triggered.clear();
        }
        else
        {
            monitors[++monitor_tot] = Monitor{x, y};
            if (y == 0)
                triggered.push_back(monitor_tot);
            else
                add(monitor_tot);
        }

        // for (int i = 1; i <= n; ++i)
        //     if (heaps[i].size() > 1)
        //     {
        //         printf("[%d: %lld]\n", i, accumulated[i]);
        //         for (int j = 1; j < heaps[i].size(); ++j)
        //             printf("\t%d: alarm = %lld, monitor_id = %d\n", j, heaps[i][j].alarm, heaps[i][j].monitor_id);
        //     }
    }
}