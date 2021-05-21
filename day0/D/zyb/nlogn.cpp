#include<bits/stdc++.h>
using namespace std;
char c[10000010];
long long ans;
int n,m,p1[10000010],p2[10000010],p3[10000010],st[10000010],ft,t[10000010];
inline void xg(int x){
	for(int i = x;i <= m;i += i & -i) ++t[i];
} 
inline int cx(int x){
	int as = 0;
	for(int i = x;i;i -= i & -i) as += t[i];
	return as;
}
#define pb push_back
int qa[10000010],qb[10000010],qc[10000010],qd[10000010],cnt;
inline void in(int x,int y){
	qa[++cnt] = x;qb[cnt] = y;++qc[x];
}
int main(){
	int i,j,k,l,r;
	char ch;n = 0;
	fread(c,1,10000010,stdin);
	do{
		ch = c[n];
		++n;
		if(ch == '(') p1[n] = p3[n] = 1;
		else if(ch == ')') p1[n] = p3[n] = -1;
		else break;
		p1[n] += p1[n - 1];
		p2[n] = min(p2[n - 1],p1[n]);
	}while(1);
	--n;m = n / 2 + 2;
	for(i = n;i;--i) p3[i] = max(0,p3[i + 1] - p3[i]);
	st[0] = -1;++ft;
	int lst = -1;
	for(i = 1;i < n;++i){
		if(i > 1 && p2[i - 2] >= 0 && p2[i - 1] < 0) lst = i - 2;
		r = lst >= 0 ? lst : i - 1;
		while(ft && p1[st[ft]] >= p1[i]) --ft; 
		l = st[ft] + 1;
		st[++ft] = i;
		if(l <= r){
			if(l) in(l - 1,-p3[i + 1] - 1);
			in(r,p3[i + 1]);
		}
	}
	if(lst == -1) lst = n - 2;
	for(i = 1;i <= lst;++i) qc[i] += qc[i - 1];
	for(i = 1;i <= cnt;++i) qd[qc[qa[i]]--] = i; 
	for(i = 0,j = 1;i <= lst;++i){
		xg(p1[i] + 2);
		while(j <= cnt && qa[qd[j]] == i){
			k = qb[qd[j]];
			if(k < 0) ans -= i + 1 - cx(-k);
			else ans += i + 1 - cx(k + 1);
			++j;
		}
	}
	cout<<ans<<'\n';
	//cerr<<clock()<<endl;
	return 0;
}
