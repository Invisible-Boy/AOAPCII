/**
 * Title:   8-10UVa1614
 * Author:  InvisibleMan
 * Date:    2017-4-13
 * Time:    120ms
 */

// tips: 可以用数学归纳法证明，1-i之间的数字可以组成1~sum(i)(前i个数之和)任意一个数字

#include <cstdio>

int main() {
    int n, ans[100000], d[100000];
    while(scanf("%d", &n) == 1) {
        long long sum = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &d[i]);
            sum += d[i];
            ans[i] = 1;
        }
        if((sum & 1) == 0) {
            sum = sum >> 1;
            for(int i = n - 1; i > -1 && sum; i--)
                if(sum >= d[i]) {
                    ans[i] = -1;
                    sum -= d[i];
                }
            printf("Yes\n%d", ans[0]);
            for(int i = 1; i < n; i++)
                printf(" %d", ans[i]);
            printf("\n");
        }
        else
            printf("No\n");
    }
    return 0;
}
