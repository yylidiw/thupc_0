#include<cstdio>
#include<iostream>
#define rep(i,j,k) for(int i = j; i <= k; i++)
#define dow(i,j,k) for(int i = j; i >= k; i--)
#define ll long long
using namespace std;

int read() {
    int s = 0, t = 1; char c = getchar();
    while( !isdigit(c) ) { if( c == '-' ) t = -1; c = getchar(); }
    while( isdigit(c) ) s = s * 10 + c - 48, c = getchar();
    return s * t;
}

const int N = 1e5+5, M = N * 100;
int rt[N], lc[M], rc[M], tot = 0, ql, qr, d;
ll add[M];

void Add(int l,int r, int& k,const int pre) {
    k = ++tot;
    add[k] = add[pre];
    lc[k] = lc[pre], rc[k] = rc[pre];
    if( ql <= l && r <= qr ) {
        add[k] += d;
        return;
    }
    int mid = (l + r) >> 1;
    if( ql <= mid ) Add(l, mid, lc[k], lc[pre]);
    if( qr > mid ) Add(mid+1, r, rc[k], rc[pre]);
}

ll query(int l,int r,const int k) {
    if( !k ) return 0;
    if( l == r ) return add[k];
    int mid = (l + r) >> 1;
    if( d <= mid ) return query(l, mid, lc[k]) + add[k];
    else return query(mid+1, r, rc[k]) + add[k];
}

int main() {
    int n = read(), m = read();
    rep(i,1,m) {
        int flag = read();
        if( flag == 0 ) {
            ql = read(), qr = read(), d = read();
            Add(1,n,rt[i], rt[i-1]);
        } else {
            d = read();
            rt[i] = rt[i-1];
            ll v = query(1,n,rt[i]);
            int l = 0, r = i - 1;
            while( l < r ) {
                int mid = (l + r) >> 1;
                if( query(1, n, rt[mid]) * 2 >= v ) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            printf("%d\n", i - l);
        }
    }
    return 0;
}