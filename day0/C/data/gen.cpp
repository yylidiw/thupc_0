// should be run directly in the directory of data

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

unsigned rand32()
{
    return rand() << 1 ^ rand();
}

const int N = 1e5 + 5, M = 1e5 + 5;

bool is_prm[N];
vector<int> prm_dvs[N];

struct Monitor
{
    int x;
    ll y;
    vector<int> heap_pos;
} monitors[M]; // (0, monitor_tot]
int monitor_tot;

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
    assert(heap[i].dvs_id < monitors[heap[i].monitor_id].heap_pos.size());
    assert(heap[j].dvs_id < monitors[heap[j].monitor_id].heap_pos.size());

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
    // printf("remove %d(%d)\n", monitor_id, monitors[monitor_id].x);
    for (int dvs_id = 0; dvs_id < prm_dvs[monitors[monitor_id].x].size(); ++dvs_id)
    {
        int p = prm_dvs[monitors[monitor_id].x][dvs_id];
        int pos = monitors[monitor_id].heap_pos[dvs_id];

        // printf("remove %d from %d\n", p, monitors[monitor_id].x);

        monitors[monitor_id].y -= accumulated[p] - heaps[p][pos].now;

        swap(heaps[p], pos, heaps[p].size() - 1);
        heaps[p].pop_back();
        if (pos < heaps[p].size())
            down(heaps[p], up(heaps[p], pos));
    }
}

// int tot = 0;
void add(int monitor_id)
{
    assert(monitors[monitor_id].y > 0);
    ll alarm = (monitors[monitor_id].y + prm_dvs[monitors[monitor_id].x].size() - 1) / prm_dvs[monitors[monitor_id].x].size();

    monitors[monitor_id].heap_pos.clear();
    for (int dvs_id = 0; dvs_id < prm_dvs[monitors[monitor_id].x].size(); ++dvs_id)
    {
        // printf("add %d of %d\n", prm_dvs[monitors[monitor_id].x][dvs_id], monitors[monitor_id].x);

        int p = prm_dvs[monitors[monitor_id].x][dvs_id];

        // printf("heaps[%d]:", p);
        // for (int i = 1; i < heaps[p].size(); ++i)
        //     printf(" %d(%d)", heaps[p][i].monitor_id, monitors[heaps[p][i].monitor_id].x);
        // puts("");

        heaps[p].push_back(Alarm{
            .now = accumulated[p],
            .alarm = alarm + accumulated[p],
            .monitor_id = monitor_id,
            .dvs_id = dvs_id});

        monitors[monitor_id].heap_pos.push_back(heaps[p].size() - 1);
        up(heaps[p], heaps[p].size() - 1);

        // printf("heaps[%d]:", p);
        // for (int i = 1; i < heaps[p].size(); ++i)
        //     printf(" %d(%d)", heaps[p][i].monitor_id, monitors[heaps[p][i].monitor_id].x);
        // puts("");

        // ++tot;
    }
}

ll lastans;
vector<int> triggered;

void work(int op, int x, ll y, FILE *fout)
{
    if (op == 0)
    {
        for (int p : prm_dvs[x])
        {
            accumulated[p] += y;
            while (heaps[p].size() > 1 && heaps[p][1].alarm <= accumulated[p])
            {
                int monitor_id = heaps[p][1].monitor_id;

                // printf("heaps[%d]:", p);
                // for (int i = 1; i < heaps[p].size(); ++i)
                //     printf(" %d(%d)", heaps[p][i].monitor_id, monitors[heaps[p][i].monitor_id].x);
                // puts("");

                remove(monitor_id);

                // printf("heaps[%d]:", p);
                // for (int i = 1; i < heaps[p].size(); ++i)
                //     printf(" %d(%d)", heaps[p][i].monitor_id, monitors[heaps[p][i].monitor_id].x);
                // puts("");

                if (monitors[monitor_id].y <= 0)
                    triggered.push_back(monitor_id);
                else
                    add(monitor_id);
            }
        }
        lastans = triggered.size();
        sort(triggered.begin(), triggered.end());
        fprintf(fout, "%lld", lastans);
        for (int monitor_id : triggered)
            fprintf(fout, " %d", monitor_id);
        fprintf(fout, "\n");
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
}

int n, m;
void gen_testcase(int idx, function<void(FILE *, FILE *)> generator)
{
    FILE *fin = fopen((to_string(idx) + ".in").c_str(), "w");
    FILE *fout = fopen((to_string(idx) + ".ans").c_str(), "w");
    fprintf(fin, "%d %d\n", n, m);
    lastans = 0;
    triggered.clear();
    for (int i = 1; i <= n; ++i)
    {
        init(heaps[i]);
        assert(heaps[i].size() == 1);
    }
    monitor_tot = 0;
    memset(accumulated, 0, sizeof(accumulated));
    generator(fin, fout);
    fclose(fin);
    fclose(fout);
}

int main()
{
    // initialize the primality
    memset(is_prm, true, sizeof(is_prm));
    is_prm[1] = false;
    for (int i = 2; i < N; ++i)
        if (is_prm[i])
        {
            for (int j = i + i; j < N; j += i)
                is_prm[j] = false;
            for (int j = i; j < N; j += i)
                prm_dvs[j].push_back(i);
        }

    // testcase 1: sample
    system("cp ../down/1.in .");
    system("cp ../down/1.ans .");

    // testcase 2: small & random
    n = 5000, m = 5000;
    auto testcase2 = [=](FILE *fin, FILE *fout) {
        for (int i = 1; i <= m; ++i)
        {
            // printf("%d\n", i);

            int op = rand() & 1;
            int x = rand() % (n - 1) + 2;
            ll y = rand32();
            fprintf(fin, "%d %d %lld\n", op, x, y ^ lastans);
            work(op, x, y, fout);
        }
    };
    gen_testcase(2, testcase2);

    // testcase 3: large & random
    n = 1e5, m = 1e5;
    auto testcase3 = [=](FILE *fin, FILE *fout) {
        for (int i = 1; i <= m; ++i)
        {
            int op = rand() & 1;
            int x = rand() % (n - 1) + 2;
            ll y = rand32();
            fprintf(fin, "%d %d %lld\n", op, x, y ^ lastans);
            work(op, x, y, fout);
        }
    };
    gen_testcase(3, testcase3);

    // testcase 4: 现在 [n/2 + 1, n] 的位置均匀排布监控，再随机地闹鬼
    n = 1e5, m = 1e5;
    auto testcase4 = [=](FILE *fin, FILE *fout) {
        for (int i = 1; i <= n / 2; ++i)
        {
            int x = n - i + 1;
            ll y = rand32();
            fprintf(fin, "1 %d %lld\n", x, y ^ lastans);
            work(1, x, y, fout);
        }
        for (int i = n / 2 + 1; i <= m; ++i)
        {
            int x = rand() % (n - 1) + 2;
            ll y = rand32() / 1000; // TODO: need to be adjusted
            fprintf(fin, "0 %d %lld\n", x, y ^ lastans);
            work(0, x, y, fout);
        }
    };
    gen_testcase(4, testcase4);

    // testcase 5: 一开始有一大堆监控，然后再一点一点闹鬼，恰好在最后一个一起完成监控
    n = 1e5, m = 1e5;
    auto testcase5 = [=](FILE *fin, FILE *fout) {
        assert(n == m);
        for (int i = 1; i <= m / 2; ++i)
        {
            int x = i << 1;
            ll y = m / 2;
            fprintf(fin, "1 %d %lld\n", x, y ^ lastans);
            work(1, x, y, fout);
        }
        for (int i = m / 2 + 1; i <= m; ++i)
        {
            ll y = 1;
            fprintf(fin, "0 %d %lld\n", 2, y ^ lastans);
            work(0, 2, y, fout);
        }
    };
    gen_testcase(5, testcase5);

    // testcase 6: 每一个监控都要么阈值是 0，要么会紧跟一个跟它有公因子的，会帮它立刻把监控消掉
    n = 1e5, m = 1e5;
    auto testcase6 = [=](FILE *fin, FILE *fout) {
        for (int i = 1; i <= m;)
            if (rand() % 10000 != 0 && i < m)
            {
                int x = rand() % (n - 1) + 2;
                ll y = rand32();
                fprintf(fin, "1 %d %lld\n", x, y ^ lastans);
                work(1, x, y, fout);

                int x1 = prm_dvs[x][rand() % prm_dvs[x].size()];
                ll y1 = (y + prm_dvs[x1].size() - 1) / prm_dvs[x1].size();
                x1 = (rand32() % (n / x1) + 1) * x1;
                fprintf(fin, "0 %d %lld\n", x1, y1 ^ lastans);
                work(0, x1, y1, fout);

                i += 2;
            }
            else
            {
                int x = rand() % (n - 1) + 2;
                fprintf(fin, "1 %d %lld\n", x, 0 ^ lastans);
                work(1, x, 0, fout);

                ++i;
            }
    };
    gen_testcase(6, testcase6);

    // testcase 7: 一组极限数据
    n = 1e5, m = 1e5;
    auto testcase7 = [=](FILE *fin, FILE *fout) {
        int x = 1;
        int k = 0;
        for (int i = 2; i <= n; ++i)
            if (is_prm[i])
                if (x * i <= n)
                {
                    x *= i;
                    ++k;
                }
                else
                    break;
        ll y = (1ll << 32) - 1;

        int i = 1;
        for (; i <= m - 200; ++i)
        {
            fprintf(fin, "1 %d %lld\n", x, y);
            work(1, x, y, fout);
        }
        for (; y > 0; ++i)
        {
            fprintf(fin, "0 4 %lld\n", (y + k - 1) / k ^ lastans);
            work(0, 4, (y + k - 1) / k, fout);
            y -= (y + k - 1) / k;
        }

        for (; i <= m; ++i)
        {
            int op = rand() & 1;
            int x = rand() % (n - 1) + 2;
            ll y = rand32();
            fprintf(fin, "%d %d %lld\n", op, x, y ^ lastans);
            work(op, x, y, fout);
        }
    };
    gen_testcase(7, testcase7);
}