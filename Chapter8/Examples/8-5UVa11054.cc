/**
 * Title:   8-5UVa11054
 * Author:  InvisibleMan
 * Date:    2017-3-14
 * Time:    40ms
 */

#include <cstdio>

int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        long ans = 0, l = 0, t;
        for(int i = 0; i < n; i++) { 
            scanf("%ld", &t);
            l += t;
            ans += l > 0 ? l : -l;
        }
        printf("%ld\n", ans);
    }
    return 0;
}
