#include<bits/stdc++.h>
//#define gc getchar()
char buf[100000],*buff = buf + 100000;
#define gc ((buff == buf + 100000 ? (fread(buf,1,100000,stdin),buff = buf) : 0),*(buff++))
//#define pc putchar
char bfu[10000000],*bfuu = bfu;
#define pc(x) (*(bfuu++) = x)
#define li long long
#define pb push_back
using namespace std;
inline li read(){
	li x = 0;
	int y = 0,c = gc;
	while(c < '0' || c > '9') y = c,c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return y == '-' ? -x : x;
}
inline void prt(li x){
	if(x >= 10) prt(x / 10);
	pc(x % 10 + '0');
}
inline void print(li x){
	if(x < 0) pc('-'),x = -x;
	prt(x);
}
int n,m,a[100010],sz,sz1,sz2,tta;
li ans[500010];
struct qry{
	int l,r,id;
}p[500010];
inline bool operator < (qry q,qry w){
	return q.l / sz == w.l / sz ? ((q.l / sz & 1) ? q.r > w.r : q.r < w.r) : q.l < w.l;
}
struct lsh{
	int a,id;
}aa[100010];
inline bool operator < (lsh x,lsh y){
	return x.a < y.a;
}
struct caoz{
	int l,r,fg,id;
	inline caoz(int _l,int _r,int _fg,int _id){
		l = _l;r = _r;fg = _fg;id = _id;
	}
};

vector<caoz> cz[100010];
int ton[100010],pm[100010],nxt[100010],pre[100010],wz[100010],lst[100010];
#define clr(x) memset((x),0,sizeof(x))
int s1[35][35],s2[510][35],s3[35][510],s4[510][510],s5[100010];
int bel1[100010],bel2[100010],beg1[510],beg2[35];
void xg(int x,int fg){
	int y = pm[x];
	int x1 = bel1[x],x2 = bel2[x],y1 = bel1[y],y2 = bel2[y];
	int px = beg2[x2],py = beg2[y2],qx = beg1[x1],qy = beg1[y1];
	register int i,j;
	for(i = 1;i < x2;++i) for(j = 1;j < y2;++j) s1[i][j] += fg;
	for(i = px;i < x1;++i) for(j = 1;j < y2;++j) s2[i][j] += fg;
	for(i = 1;i < x2;++i) for(j = py;j < y1;++j) s3[i][j] += fg;
	for(i = px;i < x1;++i) for(j = py;j < y1;++j) s4[i][j] += fg;
	for(i = qx;i < x;++i) if(pm[i] < qy) s5[i] += fg;
	for(j = qy;j < y;++j) if(wz[j] < x) s5[wz[j]] += fg;
}
inline int cx(int x){
	int y = pm[x];
	int x1 = bel1[x],x2 = bel2[x],y1 = bel1[y],y2 = bel2[y];
	return s1[x2][y2] + s2[x1][y2] + s3[x2][y1] + s4[x1][y1] + s5[x];
}
void wk(){
	clr(ton);
	int i,j,k,l,r,fg,id;
	for(i = 1;i <= n;++i) ++ton[a[i]];
	for(i = 1;i <= n;++i) ton[i] += ton[i - 1];
	for(i = 1;i <= n;++i) pm[i] = ton[a[i]]--,wz[pm[i]] = i;
	clr(lst);
	for(i = 1;i <= n;++i) pre[i] = lst[a[i]],lst[a[i]] = i;
	clr(lst);
	for(i = n;i;--i) nxt[i] = lst[a[i]],lst[a[i]] = i;
	clr(s1),clr(s2);clr(s3);clr(s4);clr(s5);
	for(i = 1;i <= n;++i){
		if(pre[i]) xg(pre[i],-1);
		xg(i,1);
		for(j = 0;j < cz[i].size();++j){
			l = cz[i][j].l;r = cz[i][j].r;
			fg = cz[i][j].fg;id = cz[i][j].id;
			li tmp = 0;
			for(k = l;k <= r;++k){
				if(nxt[k] < i) tmp -= cx(nxt[k]);
				tmp += cx(k);
			}
			ans[id] += tmp * fg;
		} 
	}
}
int main(){
	int i,j;
	n = read();
	for(i = 1;i <= n;++i) aa[i].a = read(),aa[i].id = i;
	sort(aa + 1,aa + n + 1);
	aa[0].a = aa[1].a - 1;
	tta = 0;
	for(i = 1;i <= n;++i){
		if(aa[i].a != aa[i - 1].a) ++tta;
		a[aa[i].id] = tta;
	}
	m = read();
	for(i = 1;i <= m;++i){
		p[i].l = read();p[i].r = read();p[i].id = i;
	}
	sz = n / (sqrtl(m) + 1) + 1;
	sort(p + 1,p + m + 1);
	sz = sqrtl(sqrtl(n)) + 1;
	sz1 = sz * sz;sz2 = sz1 * sz;
	for(i = 1;i <= n;++i) bel1[i] = (i - 1) / sz1 + 1,bel2[i] = (i - 1) / sz2 + 1;
	for(i = n;i;--i) beg1[bel1[i]] = i,beg2[bel2[i]] = bel1[i];
	int nl = 1,nr = 0;
	for(i = 1;i <= m;++i){
		int al = p[i].l,ar = p[i].r,ai = p[i].id;
		if(nr < ar) nr = ar;
		if(nl > al) cz[nr].pb(caoz(al,nl - 1,1,ai)),nl = al;
		if(nr > ar) nr = ar;
		if(nl < al) cz[nr].pb(caoz(nl,al - 1,-1,ai)),nl = al;
	}
	for(i = 1;i <= n;++i) a[i] = tta - a[i] + 1;
	wk(); 
	for(i = 1,j = n;i < j;++i,--j) swap(a[i],a[j]);
	for(i = 1;i <= n;++i) a[i] = tta - a[i] + 1;
	for(i = 1;i <= n;++i) cz[i].clear();
	nl = 1;nr = 0;
	for(i = 1;i <= m;++i){
		int al = p[i].l,ar = p[i].r,ai = p[i].id;
		if(nr < ar) cz[n - nl + 1].pb(caoz(n - ar + 1,n - nr,1,ai)),nr = ar;
		if(nl > al) nl = al;
		if(nr > ar) cz[n - nl + 1].pb(caoz(n - nr + 1,n - ar,-1,ai)),nr = ar;
		if(nl < al) nl = al;
	}
	wk();
	for(i = 2;i <= m;++i) ans[p[i].id] += ans[p[i - 1].id];
	for(i = 1;i <= m;++i) print(ans[i]),pc('\n');
	fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}
