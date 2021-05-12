#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l,i##_r=r;i<i##_r;++i)
#define clr(x) memset(x,0,sizeof(x))
const int N=500007,sN=750,ssN=32;

int n,m,B,B2,B3;

const int BUF_SZ=1e6;

char ib[BUF_SZ],*ip=ib+BUF_SZ,ob[1<<23],*op=ob;
int read(int L,int R){
	size_t n=ib+BUF_SZ-ip;
	if(n<100){
		memcpy(ib,ip,n);
		fread(ib+n,1,BUF_SZ-n,stdin)[ib+n]=0;
		ip=ib;
	}
	int x=0;
	while(*ip<48)++ip;
	while(*ip>47)x=x*10+*ip++-48;
	assert(L<=x&&x<=R);
	return x;
}
void print(long long x){
	char ss[20];
	int sp=0;
	do ss[sp++]=x%10+48;while(x/=10);
	while(sp)*op++=ss[--sp];
	*op++=10;
}

struct Q{
	int l,r,w;
	bool operator<(const Q&q)const{
		int d=l/B-q.l/B;
		if(d)return d<0;
		return (l/B&1)?r<q.r:r>q.r;
	}
}qs[N];

struct Pos{
	int x,y;
	bool operator<(const Pos&w)const{return y!=w.y?y>w.y:x>w.x;}
}ps[N];

struct Seg{int l,r,w,sgn;};

int a[N],ys[N],pv[N],nx[N];
long long ans[N];

std::vector<Seg> m1[N],m2[N];

int sx[N],s33[ssN][ssN],s22[sN][sN],s23[sN][ssN],s32[ssN][sN];

int rev(int x){return n-1-x;}

struct Bi{
	int x2,y2,x3,y3;
}bs[N];

void inc(int x,int sgn){
	int y=ys[x];
	int x2=bs[x].x2,x3=bs[x].x3;
	int y2=bs[x].y2,y3=bs[x].y3;
	#define Fi3 F(i,0,x3)
	#define Fi2 F(i,x3*B,x2)
	#define Fj3 F(j,0,y3)
	#define Fj2 F(j,y3*B,y2)
	Fi3 Fj3 s33[i][j]+=sgn;
	Fi2 Fj2 s22[i][j]+=sgn;
	Fi2 Fj3 s23[i][j]+=sgn;
	Fi3 Fj2 s32[i][j]+=sgn;
	F(i,x2*B2,x)if(ys[i]<y2*B2)sx[i]+=sgn;
	F(j,y2*B2,y)if(ps[j].x<x)sx[ps[j].x]+=sgn;
}

int sum(int x){
	int x2=bs[x].x2,x3=bs[x].x3;
	int y2=bs[x].y2,y3=bs[x].y3;
	int s=sx[x]+s22[x2][y2]+s33[x3][y3]+s23[x2][y3]+s32[x3][y2];
	return s;
}

void calc(std::vector<Seg> *ms){
	F(i,0,n)ps[i]=Pos{i,a[i]};
	std::sort(ps,ps+n);
	F(i,0,n)ys[ps[i].x]=i;
	F(x,0,n){
		int y=ys[x];
		bs[x]={x/B2,y/B2,x/B3,y/B3};
	}
	F(i,0,n)pv[i]=-1,nx[i]=n;
	F(i,1,n)if(ps[i].y==ps[i-1].y){
		pv[ps[i-1].x]=ps[i].x;
		nx[ps[i].x]=ps[i-1].x;
	}
	clr(s22),clr(s23),clr(s32),clr(s33),clr(sx);
	F(i,0,n){
		if(pv[i]!=-1)inc(pv[i],-1);
		inc(i,1);
		for(Seg &s:ms[i]){
			long long d=0;
			F(j,s.l,s.r+1){
				int j2=nx[j];
				int d0=0;
				if(j2<i)d0-=sum(j2)*s.sgn;
				d0+=sum(j)*s.sgn;
				d+=d0;
			}
			ans[s.w]+=d;
		}
	}
}

int main(){
	n=read(1,5e5);
	F(i,0,n)a[i]=read(1,n)-1;
	m=read(1,5e5);
	F(i,0,m){
		qs[i].l=read(1,n)-1;
		qs[i].r=read(qs[i].l+1,n)-1;
		qs[i].w=i;
	}
	B=n/sqrt(m)+1;
	std::sort(qs,qs+m);
	B=pow(n,0.25)+1;
	B2=B*B;
	B3=B*B*B;
	int L=0,R=0;
	F(i,0,m){
		int l=qs[i].l,r=qs[i].r,w=qs[i].w;
		if(R<r)m1[rev(L)].push_back({rev(r),rev(R+1),w,1}),R=r;
		if(L>l)m2[R].push_back({l,L-1,w,1}),L=l;
		if(R>r)m1[rev(L)].push_back({rev(R),rev(r+1),w,-1}),R=r;
		if(L<l)m2[R].push_back({L,l-1,w,-1}),L=l;
	}
	calc(m2);
	std::reverse(a,a+n);
	F(i,0,n)a[i]=rev(a[i]);
	calc(m1);
	F(i,1,m)ans[qs[i].w]+=ans[qs[i-1].w];
	F(i,0,m)print(ans[i]);
	fwrite(ob,1,op-ob,stdout);
	return 0;
}
