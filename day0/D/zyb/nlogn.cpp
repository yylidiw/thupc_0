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
int lst,qc[10000010],qd[10000010],tt[10000010];
inline void in(int x,int k){
	if(!x){
		if(k < 0) ans -= (p1[0] + 2 > -k);
		else ans += (p1[0] + 2 > k + 1);
	}
	else if(x == lst){
		if(k < 0) ans -= lst + 1 - tt[-k];
		else ans += lst + 1 - tt[k + 1];
	}
	else qc[x] = k,++qd[x];
}
int main(){
	int i,k,l,r;
	char ch;n = 0;lst = -1;
	fread(c,1,10000010,stdin);
	do{
		ch = c[n];
		++n;
		if(ch == '(') p1[n] = p3[n] = 1;
		else if(ch == ')') p1[n] = p3[n] = -1;
		else break;
		p1[n] += p1[n - 1];
		p2[n] = min(p2[n - 1],p1[n]);
		if(n > 1 && p2[n - 2] >= 0 && p2[n - 1] < 0) lst = n - 2;
	}while(1);
	if(lst == -1) lst = n - 2;
	--n;m = 0;
	for(i = n;i;--i) p3[i] = max(0,p3[i + 1] - p3[i]),m = max(m,p3[i] + 2);
	st[0] = -1;++ft;
	for(i = 0;i <= lst;++i) ++tt[p1[i] + 2];
	for(i = 1;i <= m;++i) tt[i] += tt[i - 1]; 
	for(i = 1;i < n;++i){
		r = min(lst,i - 1);
		while(ft && p1[st[ft]] >= p1[i]) --ft; 
		l = st[ft] + 1;
		st[++ft] = i;
		if(l <= r){
			if(l) in(l - 1,-p3[i + 1] - 1);
			in(r,p3[i + 1]);
		}
	}
	xg(p1[0] + 2);
	for(i = 1;i < lst;++i){
		xg(p1[i] + 2);
		if(!qd[i]) continue;
		k = qc[i];
		if(k < 0) ans -= 1ll * (i + 1 - cx(-k)) * qd[i];
		else ans += (i + 1 - cx(k + 1)) * qd[i];
	}
	cout<<ans<<'\n';
	//cerr<<clock()<<endl;
	return 0;
}
