/*
 * Title:	7-3UVa10976
 * Author:	Invisible_Man
 * Time:	2016-11-17
 */

#include <cstdio>
#include <utility>

using namespace std;

int main() {
	pair<int, int> result[10001];
	int k;
	while(scanf("%d", &k) == 1) {
		int len = 0;
		for(int i = k + 1; i <= (k << 1); i++) {
			int t1 = i * k, t2 = i - k;
			if(t1 % t2 == 0)
				result[len++] = pair<int, int>(t1 / t2, i);
		}
		printf("%d\n", len);
		for(int i = 0; i < len; i++)
			printf("1/%d = 1/%d + 1/%d\n", k, result[i].first, result[i].second);
	}
	return 0;
}
