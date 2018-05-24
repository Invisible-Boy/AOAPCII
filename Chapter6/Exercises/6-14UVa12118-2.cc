/*
 * Title:	6-14UVa12118
 * Author:	Invisible_Man
 * Time:	2016-11-16
 */

#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1001;

int v[MAXN], grpv[MAXN], edge[MAXN][MAXN];
bool vis[MAXN];
int m, n, t, result, caseNum = 1;

int DFS(int i) {
	int sum = 0;
	vis[i] = false;
	sum += v[i] % 2;
	for(int j = 0; j < v[i]; j++)
		if(vis[edge[i][j]])
			sum += DFS(edge[i][j]);
	return sum;
}

int main() {
	while((scanf("%d%d%d", &m, &n, &t) == 3) && (m || n || t)) {
		if(n == 0) result = 0;
		else{
			memset(v, 0, sizeof(v));
			memset(vis, 0, sizeof(vis));
			memset(edge, 0, sizeof(edge));
			for(int i = 0; i < n; i++) {
				int t1, t2;
				scanf("%d%d", &t1, &t2);
				edge[t1][v[t1]] = t2;
				edge[t2][v[t2]] = t1;
				v[t1]++, v[t2]++;
				vis[t1] = vis[t2] = true;
			}
			if(t == 0) result = 0;
			else {
				int len = 0;
				for(int i = 1; i <= m; i++)
					if(vis[i])
						grpv[len++] = DFS(i);
				if(len == 1) {
					if(grpv[0] <= 2) result = n;
					else result = ((grpv[0] - 1) >> 1) + n;
				}
				else {
					int sum = 0;
					sort(grpv, grpv + len);
					for(int i = len - 1; i > 1; i--)
						if(grpv[i] > 1)
							sum += grpv[i] - 2;
						else
							sum += grpv[i];
					for(int i = 0; i < 2; i++)
						if(grpv[i] > 0)
							sum += grpv[i] - 1;
						else
							sum += grpv[i] + 1;
					result = n + len - 1;
					if(sum > 2) result += (sum - 1) >> 1;
				}
 			}	
		}
		printf("Case %d: %d\n", caseNum++, result * t);
	}
	return 0;
}
