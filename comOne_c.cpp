#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <map>
#include <utility>
#include <list>

using namespace std;

#define N 1500

int x[2][N], y[2][N];
int n, m, a, b;


int main()
{
	int T, cas, i;
	scanf("%d", &T);
	for(cas = 1; cas <= T; cas ++){
		scanf("%d%d%d%d", &n, &m, &a, &b);
		for(i = 0; i < a; i ++){
			scanf("%d", &x[0][i]);
			scanf("%d", &y[0][i]);
		}
		for(i = 0; i < b; i ++){
			scanf("%d", &x[1][i]);
			scanf("%d", &y[1][i]);
		}
		
	}
    return 0;
}
