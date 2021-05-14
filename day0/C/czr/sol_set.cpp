#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
using namespace std;
const int N=100000;
const int P=10000;
vector <int> vec[N+5];
int sz[N+5],cnt[N+5],pri[P+5],d[N+5],tot,n,T,lst,num,ct;
int ans[N+5],co[N+5],o;
ll ts[P+5];
set <pair<ll,int> > q[P+5]; 
set <pair<ll,int> >::iterator it;
struct node
{int x;
ll y,rec[7],lst[7];
}m[N+5];
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
}
inline void alarm(int id,int x,ll y)
{ll thr=(y-1)/cnt[x]+1;co[id]=++ct;
for (int i=1;i<=cnt[x];i++) 
{if (m[id].lst[i]!=-1) q[vec[x][i]].erase(q[vec[x][i]].lower_bound(make_pair(m[id].lst[i],id)));
m[id].lst[i]=ts[vec[x][i]]+thr;
q[vec[x][i]].insert(make_pair(m[id].lst[i],id));
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
{for (it=q[id].begin();it!=q[id].end();it=q[id].begin()) 
{pair <ll,int> tp=(*it);
if (tp.fi>ts[id]) break;
if (co[tp.se]==-1) continue;
int x=m[tp.se].x;
ll y=m[tp.se].y,nw=0;
for (int i=1;i<=cnt[x];i++)
{nw+=(ts[vec[x][i]]-m[tp.se].rec[i]);}
if (nw>=y) 
{ans[++o]=tp.se;co[tp.se]=-1;
for (int j=1;j<=cnt[x];j++) 
{q[vec[x][j]].erase(q[vec[x][j]].lower_bound(make_pair(m[tp.se].lst[j],tp.se)));}
}
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
