#include<bits/stdc++.h>

int read(int L,int R){
	int x;
	assert(scanf("%d",&x)==1);
	assert(L<=x&&x<=R);
	return x;
}

const int N=1e6+7;
int a[N],b[N];

int main(){
	int n=read(1,1e6);
	for(int i=1;i<=n;++i)a[i]=read(1,1e3);
	int m=read(1,1e6);
	for(int i=1;i<=m;++i){
		int l1=read(1,n),r1=read(l1,n);
		int l2=read(1,n-(r1-l1));
		for(int j=l1;j<=r1;++j)b[l2++]+=a[j];
	}
	for(int i=1;i<=n;++i)printf("%d\n",b[i]);
	return 0;
}
