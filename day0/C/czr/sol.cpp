#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define pi pair<ll,int>
#define fi first
#define se second
using namespace std;
const int N=100000;
const int P=10000;
vector <int> vec[N+5];
int sz[N+5],cnt[N+5],pri[P+5],d[N+5],tot,n,T,lst,num,ct;
int ans[N+5],co[N+5],o;
ll ts[P+5];
bool ins[6*N+5];
struct node
{int x,t[7];
ll y,rec[7],lst[7];
}m[N+5];
pair<ll,int> val[6*N+5];
int lc[6*N+5],rc[6*N+5],fa[6*N+5],dis[6*N+5],rt[P+5],cot;
int que[25];
inline bool cmp(pi a,pi b)
{return ((a.fi==b.fi) ? (a.se>b.se):(a.fi>b.fi));} 
inline int merge(int x,int y)
{int o=0;
while (x&&y)
{if (cmp(val[x],val[y])) swap(x,y);
que[++o]=x;x=rc[x];
}
int lst=x+y,no;
for (int i=o;i>=1;i--)
{no=que[i];fa[lst]=no;rc[no]=lst;
if (dis[lc[no]]<dis[rc[no]]) swap(lc[no],rc[no]);
dis[no]=dis[rc[no]]+1;lst=no;
}
return lst;
}
inline void del(int o,int id)
{int t=merge(lc[id],rc[id]);
int u=fa[id];fa[t]=u;ins[id]=0;
if (u!=-1)
{if (lc[u]==id) {lc[u]=t;}
else {rc[u]=t;}
while (u!=-1) 
{if (dis[lc[u]]<dis[rc[u]]) swap(lc[u],rc[u]);
dis[u]=dis[rc[u]]+1;u=fa[u];
}
return;
}
rt[o]=t;
return;
}
inline void insert(int o,int id,pi tp)
{val[id]=tp;fa[id]=-1;lc[id]=rc[id]=dis[id]=0;ins[id]=1;
rt[o]=merge(id,rt[o]);
}
inline pi top(int id)
{return val[rt[id]];}
inline void pop(int id)
{int qwq=rt[id],t=merge(lc[qwq],rc[qwq]);
ins[qwq]=0;rt[id]=t;fa[t]=-1;
}
inline void init()
{for (int i=2;i<=N;i++)
{if (sz[i]) continue;
pri[++tot]=i;d[i]=tot;
for (int j=i;j<=N;j+=i) sz[j]++;
}
for (int i=1;i<=N;i++) vec[i].resize(sz[i]+1);
for (int i=2;i<=N;i++)
{if (!d[i]) continue; 
for (int j=i;j<=N;j+=i) vec[j][++cnt[j]]=d[i];
}
memset(fa,-1,sizeof(fa));
tot=0;
}
int qwq=0;
inline void alarm(int id,int x,ll y)
{ll thr=(y-1)/cnt[x]+1;
for (int i=1;i<=cnt[x];i++) 
{if (m[id].lst[i]==ts[vec[x][i]]+thr) continue;
if (m[id].t[i]) 
{if (ins[m[id].t[i]]) del(vec[x][i],m[id].t[i]);
}
else {m[id].t[i]=++cot;}
m[id].lst[i]=ts[vec[x][i]]+thr;
insert(vec[x][i],m[id].t[i],mp(m[id].lst[i],id));
}
}
inline void moni(int x,ll y)
{if (!y) {ans[++o]=++num;return;}
m[++num].x=x;m[num].y=y;
for (int i=1;i<=cnt[x];i++)
{m[num].rec[i]=ts[vec[x][i]];
m[num].lst[i]=-1;
}
alarm(num,x,y);
}
inline void solve(int id)
{while (rt[id]) 
{pi tp=top(id);
if (tp.fi>ts[id]) break;
pop(id);
if (co[tp.se]==-1) continue;
int x=m[tp.se].x;
ll y=m[tp.se].y,nw=0;
for (int i=1;i<=cnt[x];i++)
{nw+=(ts[vec[x][i]]-m[tp.se].rec[i]);}
if (nw>=y) {ans[++o]=tp.se;co[tp.se]=-1;}
else {alarm(tp.se,x,y-nw);}
}
}
inline void add(int x,ll y)
{for (int i=1;i<=cnt[x];i++)
{ts[vec[x][i]]+=y;solve(vec[x][i]);}
sort(ans+1,ans+o+1);
printf ("%d",o);
for (int i=1;i<=o;i++) printf (" %d",ans[i]);
puts("");lst=o;o=0; 
}
int main (){
	int i,j,op,x;
	ll y;init();
	scanf ("%d%d",&n,&T);
	for (i=1;i<=T;i++)
	{scanf ("%d%d%lld",&op,&x,&y);
	y^=lst;
	if (!op) {add(x,y);}
	else {moni(x,y);}
	}
	return 0;
}
