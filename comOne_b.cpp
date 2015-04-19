#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;
#define N 1010
#define MOD 100007
struct Node{
	int l, r, len;
	int ls, rs;
	int sum, add;
}nd[N * 3];
map<char, int>mp;
void update(int i){
	if(nd[i].l == nd[i].r)	return;
	nd[i].sum = nd[nd[i].ls].sum + nd[nd[i].ls].len * nd[nd[i].ls].add;
	nd[i].sum += nd[nd[i].rs].sum + nd[nd[i].rs].len * nd[nd[i].rs].add;
	nd[i].sum %= MOD;
}

void push(int i){
	if(nd[i].add){
		nd[i].sum += nd[i].add * nd[i].len;
		nd[i].sum %= MOD;
		if(nd[i].l != nd[i].r){
			nd[nd[i].ls].add += nd[i].add;
			nd[nd[i].rs].add += nd[i].add;
		}
		nd[i].add = 0;
	}
}

char str[N];
int ord[N][N];

void build(int l, int r, int i)
{
	if(l == r){
		nd[i].l = nd[i].r = l;
		nd[i].ls = nd[i].rs = -1;
		nd[i].len = 1;
		nd[i].sum = 0;
		nd[i].add = 0;
		return;
	}
	int mid = (l + r) >> 1;
	nd[i].ls = i << 1;
	nd[i].rs = (i << 1) | 1;
	nd[i].sum = 0;
	nd[i].add = 0;
	nd[i].l = l;
	nd[i].r = r;
	nd[i].len = (r - l) + 1;
	build(l, mid, nd[i].ls);
	build(mid + 1, r, nd[i].rs);
}

void add(int l, int r, int addn, int i)
{
	if(l <= nd[i].l && r >= nd[i].r){
		nd[i].add += addn;
		return;
	}
	int mid = (nd[i].l + nd[i].r) >> 1;
	push(i);
	if(mid >= r)	add(l, r, addn, nd[i].ls);
	else if(mid < l)	add(l, r, addn, nd[i].rs);
	else{
		add(l, mid, addn, nd[i].ls);
		add(mid + 1, r, addn, nd[i].rs);
	}
	update(i);
}

int get(int l, int r, int i)
{
	push(i);
	if(l <= nd[i].l && r >= nd[i].r){
		return nd[i].sum;
	}
	int mid = (nd[i].l + nd[i].r) >> 1;
	int res = 0;
	if(mid >= r)	res = get(l, r, nd[i].ls);
	else if(mid < l)	res = get(l, r, nd[i].rs);
	else{
		res = get(l, mid, nd[i].ls);
		res += get(mid + 1, r, nd[i].rs);
		res %= MOD;
	}
	update(i);
	return res;
}

void init(int n)
{
	for(int i = 0; i < N; i ++)	ord[i][0] = 0;
	build(0, n, 1);
}

int main()
{
	int T, cas, ans, len, i, j, k, sum;
	scanf("%d", &T);
	for(cas = 1; cas <= T; cas ++){
		scanf("%s", str);
		len = strlen(str);
		init(len);
		j = 0;
		mp.clear();
		for(i = 0; i < len; i ++){
			if(mp[str[i]] == 0) mp[str[i]] = ++ j;
			ord[mp[str[i]]][++ord[mp[str[i]]][0]] = i;
		}
		for(i = 0; i < len; i ++){
			j = mp[str[i]];
        //    printf("%d", j);
		//	printf("str[%d] = %c\n", i, str[i]);
			for(k = 1; k <= ord[j][0]; k ++){
				if(ord[j][k] > i)	break;
				if(ord[j][k] + 1 > i - 1){
					sum = 1;
				}else{
					sum = (get(ord[j][k] + 1, ord[j][k] + 1, 1) + 1) % MOD;
				}
		//		printf("ord = %d\tsum = %d\n", ord[j][k], sum);
				add(0, ord[j][k], sum, 1);
			}
		//	puts("");
		}
		//puts("");
		ans = get(0, 0, 1);
		printf("Case #%d: %d\n", cas, ans);
	}
    return 0;
}
