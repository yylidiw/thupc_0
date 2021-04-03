#include<bits/stdc++.h>
#define gc getchar()
#define pc putchar
#define li long long
using namespace std;
const int mo = 1004535809;
inline int read(){
	int x = 0,c = gc;
	while(c < '0' || c > '9') c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return x;
}
inline void print(int x){
	if(x >= 10) print(x / 10);
	pc(x % 10 + '0');
}
inline void file(char *s){
	char c[50];
	sprintf(c,"%s.in",s);
	freopen(c,"r",stdin);
	sprintf(c,"%s.out",s);
	freopen(c,"w",stdout);
}
int n,m,s,ks,a[140010],b[140010],bel[140010],fr[140010],xs[210][140010],len,tp[140010];
li f[140010],wn[17][140010],nwn[17][140010],t1[140010],t2[140010];
inline li ksm(li q,li w){
	li as = 1;
	while(w){
		if(w & 1) (as *= q) %= mo;
		(q *= q) %= mo;
		w >>= 1;
	}
	return as;
}
inline void qwq(li *q,int l,bool fg){
	register int i,j,k,p;
	li q1,*ww,q2;
	for(i = 1;i < l;++i) if(i < tp[i]) swap(q[i],q[tp[i]]);
	for(i = 1,p = 0;i < l;i <<= 1,++p){
		ww = (fg ? wn[p] : nwn[p]);
		for(j = 0;j < l;j += (i << 1)){
			for(k = j;k < j + i;++k){
				q1 = q[k + i] * ww[k - j] % mo;
				q2 = q[k];
				q[k + i] = q2 < q1 ? q2 - q1 + mo : q2 - q1;
				q[k] = q2 + q1 >= mo ? q2 + q1 - mo : q2 + q1;
			}
		}
	}
	if(!fg){
		li nn = ksm(l,mo - 2);
		for(i = 0;i < l;++i) (q[i] *= nn) %= mo;
	}
}
int main(){
	//file("a");
	int i,j,k,al,ar,bl,br;
	n = read();
	for(i = 1;i <= n;++i) a[i] = read();
	m = read();
	s = min((int)sqrtl(n) * 3 + 1,n);
	for(j = 0,len = 1;len < n + s;len <<= 1,++j);
	for(i = 1;i < len;++i) tp[i] = (tp[i >> 1] >> 1) | ((i & 1) << (j - 1));
	for(i = 1,j = 0;i < len;i <<= 1,++j){
		wn[j][0] = nwn[j][0] = 1;
		wn[j][1] = ksm(3,(mo - 1) / (i << 1));
		nwn[j][1] = ksm(3,mo - 1 - (mo - 1) / (i << 1));
		for(k = 2;k < i;++k){
			wn[j][k] = wn[j][k - 1] * wn[j][1] % mo;
			nwn[j][k] = nwn[j][k - 1] * nwn[j][1] % mo;
		}
	}
	for(i = 1,j = s,ks = 0;i <= n;++i){
		if(j == s) ++ks,j = 0,fr[i] = i;
		else fr[i] = fr[i - 1];
		bel[i] = ks;++j;
	}
	for(i = 1;i <= m;++i){
		al = read();ar = read();bl = read();ar = min(ar,n - bl + al);br = ar - al + bl;
		for(j = al,k = bl;j <= ar && bel[j] == bel[al];++j,++k) b[k] += a[j];
		if(j != n + 1) for(k = bel[j];k < bel[ar];++k,j += s) ++xs[k][j - al + bl - 1];
		if(bel[al] != bel[ar]) for(j = ar,k = br;bel[j] == bel[ar];--j,--k) b[k] += a[j];
	}
	for(i = 2;i < ks;++i){
		for(j = 0;j < s;++j) t1[j] = a[(i - 1) * s + j + 1];
		for(j = 0;j < n;++j) t2[j] = xs[i][j];
		qwq(t1,len,1);qwq(t2,len,1);for(j = 0;j < len;++j) (f[j] += t1[j] * t2[j]) %= mo;
		for(j = 0;j < len;++j) t1[j] = t2[j] = 0;
	}
	qwq(f,len,0);
	for(i = 1;i <= n;++i) b[i] += (int)f[i - 1];
	for(i = 1;i <= n;++i) print(b[i]),pc('\n');
	//cerr<<clock()<<endl;
	return 0;
}
