/*
 * Title:	7-1UVa725
 * Author:	Invisible_Man
 * Time:	2016-11-17
 */

#include <cstdio>
#include <cstring>

using namespace std;

int main() {
	int n, caseNum = 0;;
	bool vis[10], flag, flag_r;
	while(scanf("%d", &n) == 1 && n) {
		if(caseNum++) printf("\n");
		int t1 = 1234, t2 = t1 * n;
		flag_r = true;
		while(t2 < 99999) {
			memset(vis, 0, sizeof(vis));
			flag = true;
			int i = 0, tt1 = t1, tt2 = t2;
			if(t1 < 10000) i = 1;
			while(tt1) {
				vis[tt1 % 10] = true;
				tt1 /= 10;
			}
			while(tt2) {
				vis[tt2 % 10] = true;
				tt2 /= 10;
			}
			for(; i < 10; i++)
				if(!vis[i]) flag = false;
			if(flag) {
				flag_r = false;
				printf("%05d / %05d = %d\n", t2, t1, n);
			}
			t1++, t2 = t1 * n;
		}
		if(flag_r) printf("There are no solutions for %d.\n", n);
	}
	return 0;
}
