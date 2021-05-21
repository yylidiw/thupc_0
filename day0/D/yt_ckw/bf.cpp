#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
#define ull unsigned lint
#define db long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define gc getchar()
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
inline int inn()
{
	int x,ch;while((ch=gc)<'0'||ch>'9');
	x=ch^'0';while((ch=gc)>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch^'0');return x;
}
const int N=10000010;char s[N];int a[N];
inline int check(int l,int r,int n)
{
	int t=0,s=0;
	rep(i,1,l-1) t=min(t,s+=a[i]);
	rep(i,r+1,n) t=min(t,s+=a[i]);
	rep(i,l,r) t+=min(t,s+=a[i]);
//	if(t>=0) debug(l)sp,debug(r)ln;
	return t>=0;
}
int main()
{
	freopen("data.in","r",stdin);
	scanf("%s",s+1);int n=(int)strlen(s+1);lint ans=0;
	rep(i,1,n) if(s[i]=='(') a[i]=1;else a[i]=-1;
	rep(l,1,n) rep(r,l,n-1) ans+=check(l,r,n);
	return !printf("%lld\n",ans);
}
