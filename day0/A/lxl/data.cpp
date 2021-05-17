#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#define MAXN 100010

using namespace std;

int n , m , A[ MAXN ] , a = 10 , b = 5 , c = 100000;

int main()
{
	freopen( "data34.in" , "w" , stdout );
	srand( time( 0 ) );
	n = 100000 - rand() % 1000 , m = 500000 - rand() % 1000;
	cout << n << endl;
	for( int i = 1 ; i <= n ; i++ ) A[i] = i;
	random_shuffle( A + 1 , A + n + 1 );
	for( int i = 1 ; i <= n ; i++ )
		if( rand() % a < b )
		{
			//A[i] = rand() % c + 1;
			A[i] = 1;
			while( rand() % 10 < 8 ) A[i] <<= 1;
			if( A[i] == 0 ) A[i] = n;
			A[i] = rand() % A[i] + 1;
			if( A[i] > n ) A[i] = n;
		}
	for( int i = 1 ; i <= n ; i++ )
		cout << A[i] << ( i == n ? '\n' : ' ' );
	cout << m << endl;
	while( m-- )
	{
		int l = ( rand() * 100 + rand() % 100 ) % n + 1 , r = ( rand() * 100 + rand() % 100 ) % n + 1;
		if( l > r ) swap( l , r );
		cout << l << " " << r << endl;
	}
	return 0;
}
