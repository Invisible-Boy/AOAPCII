/*
 * Title:	7-2UVa11059
 * Author:	Invisible_Man
 * Time:	2016-11-17
 */

#include <cstdio>

using namespace std;

typedef long long LL;

int main() {
	int n, caseNum = 0;
	int data[18];
	while(scanf("%d", &n) == 1) {
		for(int i = 0; i < n; i++)
			scanf("%d", &data[i]);
		LL result = 0;
		for(int i = 0; i < n; i++)
			for(int j = i; j < n; j++) {
				LL now = 1;
				for(int k = i; k <= j; k++)
					now *= data[k];
				if(now > result)  result = now;
			}
		printf("Case #%d: The maximum product is %lld.\n\n", ++caseNum, result);
	}
	return 0;
}
