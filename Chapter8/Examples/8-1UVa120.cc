/**
 * Title:   8-1UVa120
 * Author:  InvisibleMan
 * Date:    2017-3-13
 * Time:    0ms
 */

// tips: 题目没有要求最小的次数，只是要求找到一种可行的方案

#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    int a[30], b[101], cnt = 0, t;
    while(scanf("%d", &t) == 1) {
        a[0] = t;
        b[t] = 0;
        cnt = 1;
        printf("%d", t);
        while(getchar() != '\n') {
            scanf("%d", &t);
            printf(" %d", t);
            a[cnt] = t;
            b[t] = cnt;
            cnt++;
        }
        printf("\n");
        sort(a, a + cnt, greater<int>());
        for(int i = 0; i < cnt; i++) {
            int temp = b[a[i]];
            if(temp != cnt - i - 1) {
                if(temp != 0) {
                    printf("%d ", cnt - temp);
                    for(int j = i; j < cnt; j++)
                        if(b[a[j]] <= temp)
                            b[a[j]] = temp - b[a[j]];
                }
                printf("%d ", i + 1);
                for(int j = i; j < cnt; j++)
                    if(b[a[j]] <= cnt - i - 1)
                        b[a[j]] = cnt - i - 1 - b[a[j]];
            }
        }
        printf("0\n");
    }
    return 0;
}
