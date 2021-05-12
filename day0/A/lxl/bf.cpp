#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l;i<r;++i)
const int N=500007;

int n,m,a[N];

int read(int L,int R){
	int x;
	assert(scanf("%d",&x)==1);
	assert(L<=x&&x<=R);
	return x;
}

std::pair<int,int> ps[1000000];
int pp;

int main(){
	freopen( "1.in" , "r" , stdin );
	freopen( "test.out" , "w" , stdout );
	n=read(1,1000);
	F(i,1,n+1)a[i]=read(1,n);
	m=read(1,5e5);
	F(_,0,m){
		int l=read(1,n),r=read(l,n);
		pp=0;
		F(i,l,r+1)F(j,i+1,r+1){
			if(a[i]>a[j])ps[pp++]=std::make_pair(a[i],a[j]);
		}
		std::sort(ps,ps+pp);
		int ans=std::unique(ps,ps+pp)-ps;
		printf("%d\n",ans);
	}
	return 0;
}
