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
priority_queue <pair<ll,pair<int,int> > > q[P+5]; 
struct node
{int x;
ll y,rec[7];
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
for (int i=1;i<=cnt[x];i++) q[vec[x][i]].push(make_pair(-(ts[vec[x][i]]+thr),make_pair(id,ct)));
}
inline void moni(int x,ll y)
{if (!y) {ans[++o]=++num;return;}
m[++num].x=x;m[num].y=y;
for (int i=1;i<=cnt[x];i++)
{m[num].rec[i]=ts[vec[x][i]];}
alarm(num,x,y);
}
inline void solve(int id)
{pair<ll,pair<int,int> > tp;
while (!q[id].empty())
{tp=q[id].top();
if (-tp.fi>ts[id]) break;
q[id].pop();
if (co[tp.se.fi]!=tp.se.se) continue;
int x=m[tp.se.fi].x;
ll y=m[tp.se.fi].y,nw=0;
for (int i=1;i<=cnt[m[tp.se.fi].x];i++)
{nw+=(ts[vec[x][i]]-m[tp.se.fi].rec[i]);}
if (nw>=y) {ans[++o]=tp.se.fi;co[tp.se.fi]=-1;}
else {alarm(tp.se.fi,x,y-nw);}
}
}
inline void add(int x,int y)
{for (int i=1;i<=cnt[x];i++)
{ts[vec[x][i]]+=y;solve(vec[x][i]);}
sort(ans+1,ans+o+1);
printf ("%d",o);
for (int i=1;i<=o;i++) printf (" %d",ans[i]);
puts("");lst=o;o=0; 
}
int main (){
	int i,j,op,x;
	int y;init();
	scanf ("%d%d",&n,&T);
	for (i=1;i<=T;i++)
	{scanf ("%d%d%d",&op,&x,&y);
	y^=lst;
	if (!op) {add(x,y);}
	else {moni(x,y);}
	}
	return 0;
}
