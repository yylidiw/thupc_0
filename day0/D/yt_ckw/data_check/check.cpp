#include<bits/stdc++.h>
using namespace std;
char s[100000];
int main()
{
	for(int i=1;i<=36;i++)
		sprintf(s,"my_std.exe < %d.in > my_std.out",i),system(s),
		sprintf(s,"fc my_std.out %d.ans",i),system(s);
	return 0;
}
