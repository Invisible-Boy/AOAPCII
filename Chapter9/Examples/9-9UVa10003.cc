/**
 * Title:   9-9UVa10003
 * Author:  InvisibleMan
 * Date:    2017-6-28
 * Time:    20ms
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

const int Nmax = 55;

int main() {
    int l, d[Nmax], ans[Nmax][Nmax];
    while(scanf("%d", &l) == 1 && l) {
        int n;
        scanf("%d", &n);
        d[0] = 0; d[n + 1] = l; n += 2;
        for(int i = 1; i < n - 1; i++)
            scanf("%d", &d[i]);
        memset(ans, 0, sizeof(ans));
        for(int i = 2; i < n; i++) {
            for(int j = 0; j < n - i; j++) {
                ans[j][j + i] = ans[j][j + 1] + ans[j + 1][j + i];
                for(int k = j + 2; k < j + i; k++)
                    ans[j][j + i] = std::min(ans[j][j + i], ans[j][k] + ans[k][j + i]);
                ans[j][j + i] += d[j + i] - d[j];
            }
        }
        printf("The minimum cutting is %d.\n", ans[0][n - 1]);
    }
    return 0;
}
