/**
 * Title:   8-4UVa11491
 * Author:  InvisibleMan
 * Date:    2017-4-6
 * Time:    0ms
 */
#include <cstdio>

const int Nmax = 1e5 + 1;

char str[Nmax];
// 维护了一个单调队列
int stk[Nmax << 1];

int main() {
    int n, d;
    while(scanf("%d%d\n", &n, &d) == 2 && n) {
        d = n - d;
        scanf("%s", str);
        int p = n - d - 1, head = Nmax, tail = Nmax;
        while(p > -1) {
            if(head <= tail || str[p] - '0' >= stk[head - 1]) stk[head++] = str[p] - '0';
            p--;
        }
        for(int i = n - d; i < n; i++) {
            if(head <= tail || str[i] - '0' > stk[head - 1]) {
                printf("%s", &str[i]);
                break;
            }
            else {
                printf("%d", stk[--head]);
                while(tail < head && str[i] - '0' > stk[tail]) ++tail;
                stk[--tail] = str[i] - '0';
            }
        }
        printf("\n");
    }
    return 0;
}
