#include<bits/stdc++.h>

int read(int L,int R){
	int x;
	assert(scanf("%d",&x)==1);
	assert(L<=x&&x<=R);
	return x;
}

const int N=1.1e6+7;
int a[N],b[N],t[N],B,n,m;

void add(int l1,int r1,int l2,int sgn){
	int r2=l2+(r1-l1);
	if(l2<0)l1+=0-l2,l2=0;
	if(r2>n)r1-=r2-n,r2=n;
	if(sgn==1){
		for(int i=l1;i<r1;++i)b[l2++]+=a[i];
	}else if(sgn==-1){
		for(int i=l1;i<r1;++i)b[l2++]-=a[i];
	}
}

struct Q{
	int L,R,o;
	bool operator<(const Q& w)const{return o<w.o;}
	void init(){
		int l1=read(1,n),r1=read(l1,n);
		int l2=read(1,n-(r1-l1));
		--l1;--l2;
		int r2=l2+(r1-l1);
		o=l2-l1;
		L=l1/B,R=r1/B;
		int lm=l1%B,rm=r1%B;
		if(L==R)add(l1,r1,l2,1);
		else{
			if(lm<B/2)add(L*B,l1,l2-lm,-1);
			else add(l1,(++L)*B,l2,1);
			if(rm<B/2)add(R*B,r1,r2-rm,1);
			else add(r1,(++R)*B,r2,-1);
		}
	}
}qs[N];

int c[N];

namespace FFT{
typedef long long i64;
typedef unsigned long long u64;
const int P=479<<21|1,I2=(P+1)/2,R=1<<30,R1=R-1,iP=1004535807,RR=473382811,iR=939790336;
inline int fix1(int x){return x<P?x:x-P;}
inline int fix2(int x){return x<0?x+P:x;}
inline int mulmod(unsigned a,unsigned b){
	unsigned m=u64(a)*b*iP&R1;
	int t=u64(a)*b+u64(m)*P>>30;
	return fix1(t);
}
#define $(x) mulmod(x,RR)
i64 pw(int a,int n){
	if(n<0)n+=P-1;
	int v=$(1);
	for(;n;n>>=1,a=mulmod(a,a))if(n&1)v=mulmod(v,a);
	return v;
}
int N,K,r[1<<21|111],A[1<<21|111],B[1<<21|111],*Es[2][25];
int tts=0;
void pre(int n){
	for(N=2,K=0;N<n;N<<=1,++K);
	for(int i=1;i<N;++i)r[i]=r[i>>1]>>1|(i&1)<<K;
}
void ntt(int*a,int t){
	for(int i=1;i<N;++i)if(i<r[i])std::swap(a[i],a[r[i]]);
	for(int i=1,z=0;i<N;i<<=1,++z){
		if(!Es[t==1][z]){
			int*E=Es[t==1][z]=new int[i+1];
			E[0]=$(1);
			E[1]=pw($(3),t*(P-1)/(i<<1));
			for(int j=2;j<i;++j)E[j]=mulmod(E[1],E[j-1]);
		}
		int*E=Es[t==1][z];
		for(int j=0;j<N;j+=i<<1){
			int*b=a+j,*c=b+i;
			for(int k=0;k<i;++k){
				int x=b[k],y=mulmod(c[k],E[k]);
				b[k]=fix1(x+y);
				c[k]=fix2(x-y);
			}
		}
	}
	if(t==-1){
		int I=pw($(N),P-2);
		for(int i=0;i<N;++i)a[i]=mulmod(a[i],I);
	}
}

void mul(int*a,int*b){
	for(int i=0;i<N;++i)a[i]=mulmod(a[i],b[i]);
}

void f1(int *b,int n){
	memset(B,0,sizeof(int)*N);
	for(int i=0;i<n;++i)B[i]=$(b[i]);
	ntt(B,1);
}
void f2(int *a,int n,int *c){
	memset(A,0,sizeof(int)*N);
	for(int i=0;i<n;++i)A[i]=$(a[i]);
	ntt(A,1);
	mul(A,B);
	ntt(A,-1);
	for(int i=0;i<n*2;++i)c[i]=mulmod(A[i],1);
}
}

double cost(int i){
	return 1.*((n>>i)+1)*(m+n*i*16)+1.*m*(1<<i);
	// mn/B + n2logB/B + mB
	// n/B (m + nlogn) + mB
	// sqrt(nm(m+nlogn))
}

int main(){
	//freopen( "1.in" , "r" , stdin );
	//freopen( "1.out" , "w" , stdout );
	n=read(1,1e6);
	for(int i=0;i<n;++i)a[i]=read(1,1e3);
	m=read(1,1e6);
	B=0;
	for(int i=0;i<20;++i)if(cost(i)<cost(B))B=i;
	B=1<<B;
	//fprintf(stderr,"B = %d\n",B);
	FFT::pre(B*2);
	for(int i=0;i<m;++i)qs[i].init();
	std::sort(qs,qs+m);
	for(int i=0;i<=n/B;++i){
		int l=i*B,r=std::min(n,l+B);
		memset(t,0,sizeof(t[0])*(n+B*3+1));
		for(int j=0;j<m;++j)if(qs[j].L<=i&&i<qs[j].R){
			++t[l+qs[j].o+B];
		}
		FFT::f1(a+l,B);
		for(int j=0;j<=n/B+1;++j){
			FFT::f2(t+j*B,B,c);
			for(int k=(j==0?B:0);k<B*2;++k)b[(j-1)*B+k]+=c[k];
		}
	}
	for(int i=0;i<n;++i)printf("%d\n",b[i]);
	return 0;
}

