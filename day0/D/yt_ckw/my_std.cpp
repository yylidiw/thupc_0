#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define lint long long
using namespace std;
const int N=10000010;
struct Arrar{
	int a[N<<1],n;inline int _init(int _n) { return memset(a,0,sizeof(int)*(2*n+5)),n=_n; }
	inline int& operator[](int i) { return a[i+n]; }
}nxt;
struct Black_Box{
	Arrar cnt;int s,ans;inline int _init(int _s,int n) { return ans=0,cnt._init(n),s=_s; }
	inline int ask(int x) { while(s<x) ans-=cnt[s++];while(s>x) ans+=cnt[--s];return ans; }
	inline int upd(int x,int v) { return cnt[x]+=v,ans+=v*(x>=s); }
}b;
struct edges{ int to,pre; }e[N<<1];int h[N],etop,a[N],s[N],T[N],ok[N];char S[N];lint ans=0;
inline int add_edge(int u,int v) { return e[++etop].to=v,e[etop].pre=h[u],h[u]=etop; }
int dfs(int x) { for(int i=h[x],l;i;i=e[i].pre) (ok[l=e[i].to]?ans+=b.ask(-s[l-1]):0),b.upd(T[l],1),dfs(l),b.upd(T[l],-1);return 0; }
int main()
{
	freopen("data.in","r",stdin);
	scanf("%s",S+1);int n=(int)strlen(S+1);
	assert(n>=1&&n<=10000000),nxt._init(n);
	rep(i,1,n) assert(S[i]=='('||S[i]==')');
	rep(i,1,n) if(S[i]=='(') a[i]=1;else a[i]=-1;
	rep(i,1,n) s[i]=s[i-1]+a[i];assert(!s[n]);
	for(int l=n,r;l;nxt[s[l]]=l,l--)
		if(a[l]<0) add_edge(l+1,l);
		else r=nxt[s[l-1]],add_edge((r?r:n)+1,l);
	for(int i=n;i;i--) T[i]=min(0,T[i+1]+a[i]);int mint=0,tot=0;
	rep(i,1,n) ok[i]=(mint>=0),mint=min(mint,tot+=a[i]);
	b._init(0,n),dfs(n+1);return !printf("%lld\n",ans);
}
