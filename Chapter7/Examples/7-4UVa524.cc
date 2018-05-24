/*
 * Title:	7-5UVa524.cc
 * Author:	InvisibleMan
 * Time:	2016-12-11
 */

#include <cstdio>
#include <cstring>

using namespace std;

const int Nmax = 20;

int n, result[Nmax];
bool isPrime[Nmax << 1];
bool vis[Nmax];

void serach(int cur) {
	if(cur == n) {
		printf("%d", result[0]);
		for(int i = 1; i < n; i++)
			printf(" %d", result[i]);
		printf("\n");
		return;
	}
	for(int i = 2; i <= n; i++) {
		int t = result[cur - 1];
		if(!vis[i] && isPrime[t + i])
			if(cur != n - 1 || (cur == n - 1 && isPrime[1 + i])) {
				vis[i] = true;
				result[cur] = i;
				serach(cur + 1);
				vis[i] = false;
			}
	}
}

int main() {
	int caseNum = 0;
	memset(isPrime, false, sizeof(isPrime));
	isPrime[2] = isPrime[3] = isPrime[5] = isPrime[7] = isPrime[11] =
	isPrime[13] = isPrime[17] = isPrime[19] = isPrime[23] = isPrime[29] =
	isPrime[31] = true;
	while(scanf("%d", &n) == 1) {
		if(caseNum++) printf("\n");
		printf("Case %d:\n", caseNum);
		memset(vis, false, sizeof(vis));
		result[0] = 1;
		serach(1);
	}
	return 0;
}
