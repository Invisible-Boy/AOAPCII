/**
 * Title:   8-2UVa1605
 * Author:  InvisibleMan
 * Date:    2017-3-13
 * Time:    0ms
 */

// tips: 与8-1相同，此题也是构造，没有最优性限制

#include <cstdio>
#define rep(p, q) for(int p = 0; p < q; p++)

int main() {
    int n, T = 0;
    while(scanf("%d", &n) == 1) {
        if(T++) printf("\n");
        printf("2 %d %d\n", n, n);
        rep(i, n) {
            rep(j, n) printf("%c", i < 26 ? 'A' + i : 'a' + i - 26);
            printf("\n");
        }
        printf("\n");
        rep(i, n) {
            rep(j, n) printf("%c", j < 26 ? 'A' + j : 'a' + j - 26);
            printf("\n");
        }
    }
}
