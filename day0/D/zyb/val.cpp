#include<bits/stdc++.h>
#define gc getchar()
using namespace std;
int a = 0,b = 0; 
int main(){
	char c;
	do{
		c = gc;
		if(c == '(') ++a;
		else if(c == ')') ++b;
		else assert(c == '\n' || c == '\r' || c == ' ' || c == -1);
	}while(c == '(' || c == ')');
	assert(a && a == b && a + b <= 1e7);
	do{
		c = gc;
		assert(c == -1 || c == ' ' || c == '\n' || c == '\r');			
	}while(c != -1);
	return 0;
}
