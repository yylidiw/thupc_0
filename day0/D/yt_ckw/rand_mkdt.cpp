#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
inline int getn(int a,int b) { return (rand()*32767+rand())%(b-a+1)+a; }
char s[10000010];
int main()
{
	FILE *fsd=fopen("seed.txt","r");unsigned int sd,ccc;fscanf(fsd,"%u%u",&sd,&ccc);
	FILE *gsd=fopen("seed.txt","w");sd+=12321,ccc+=1;fprintf(gsd,"%u\n%u\n",sd,ccc);
	freopen("data.in","w",stdout),srand((unsigned int)time(0)+sd);
	int n=getn(2,5);assert(n<=5000000);
	rep(i,1,n) s[i]='(',s[i+n]=')';
	random_shuffle(s+1,s+2*n+1);
	rep(i,1,n*2) printf("%c",s[i]);
	return !printf("\n");
}
