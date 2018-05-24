/*
 * Title:	6-14UVa12118
 * Author:	Invisible_Man
 * Time:	2016-11-16
 */

#include <cstdio>
#include <cstring>

using namespace std;

// tip度数为奇数的节点数目必定为偶数

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
				int sum = 0;
				for(int i = 0; i < len; i++)
				// 节点度为奇数的点作为对外联系的节点，当奇数度节点个数小于2时，放置两个虚拟节点，作为该group与其他group联系的节点
					sum += grpv[i] > 2 ? grpv[i] : 2;
				result = n + ((sum - 2) >> 1);
 			}	
		}
		printf("Case %d: %d\n", caseNum++, result * t);
	}
	return 0;
}
