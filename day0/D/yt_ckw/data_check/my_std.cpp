#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define lint long long
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
const int N=10000010;int st,Ans,n,cnt[N<<1],nxt[N<<1];char S[N];lint ans=0;
struct edges{ int to,pre; }e[N<<1];int h[N],etop,a[N],s[N],T[N],ok[N];
inline int add_edge(int u,int v) { return e[++etop].to=v,e[etop].pre=h[u],h[u]=etop; }
/*int dfs(int x)
{
	for(int i=h[x],l;i;i=e[i].pre)
	{
		if(ok[l=e[i].to])
		{
			int q=-s[l-1];
			while(st<q) Ans-=cnt[n+(st++)];
			while(st>q) Ans+=cnt[n+(--st)];
			ans+=Ans;
		}
		cnt[n+T[l]]++;if(T[l]>=st) Ans++;
		dfs(l);
		cnt[n+T[l]]--;if(T[l]>=st) Ans--;
	}
	return 0;
}*/
int xs[N],cur[N];
int dfs(int S)
{
	int c=1;xs[1]=S;
	rep(i,1,S) cur[i]=h[i];
	while(c)
	{
		int x=xs[c],&i=cur[x];
		if(!i)
		{
			if(x!=S)
			{
				cnt[n+T[x]]--;
				if(T[x]>=st) Ans--;
			}
			c--;
			continue;
		}
		int l=e[i].to;i=e[i].pre;
		xs[++c]=l,cur[l]=h[l];
		if(ok[l])
		{
			int q=-s[l-1];
			while(st<q) Ans-=cnt[n+(st++)];
			while(st>q) Ans+=cnt[n+(--st)];
			ans+=Ans;
		}
		cnt[n+T[l]]++;if(T[l]>=st) Ans++;
	}
	return 0;
}
int main()
{
//	freopen("data.in","r",stdin);
	scanf("%s",S+1),n=(int)strlen(S+1);
//	n=10000000;rep(i,1,n) if(i&1) S[i]='(';else S[i]=')';
	assert(n>=1&&n<=10000000);
	rep(i,1,n) assert(S[i]=='('||S[i]==')');
	rep(i,1,n) if(S[i]=='(') a[i]=1;else a[i]=-1;
	rep(i,1,n) s[i]=s[i-1]+a[i];assert(!s[n]);
	for(int l=n,r;l;nxt[n+s[l]]=l,l--)
		if(a[l]<0) add_edge(l+1,l);
		else r=nxt[n+s[l-1]],add_edge((r?r:n)+1,l);
	for(int i=n;i;i--) T[i]=min(0,T[i+1]+a[i]);int mint=0,tot=0;
	rep(i,1,n) ok[i]=(mint>=0),mint=min(mint,tot+=a[i]);
	dfs(n+1);return !printf("%lld\n",ans);
}
