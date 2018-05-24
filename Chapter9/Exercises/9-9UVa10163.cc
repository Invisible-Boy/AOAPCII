/**
 * Title:   9-9UVa10163
 * Author:  InvisibleMan
 * Date:    2018/4/12
 * Time:    0ms
 * Remark:  两次0-1背包
 */

#include <cstdio>
#include <memory.h>

const int Nmax = 105, Mmax = 35;

int n, m, p[Nmax], cost[Nmax], data[Mmax];

inline int min(int t1, int t2) {
    return t1 < t2 ? t1 : t2;
}

inline int max(int t1, int t2) {
    return t1 > t2 ? t1 : t2;
}

int main() {
    while((scanf("%d%d", &n, &m) == 2) && n) {
        memset(p, 0, sizeof(p));
        p[0] = 1e9;
        for(int i = 0; i < m; i++) {
            scanf("%d", &data[i]);
            for(int j = n; j > 0; j--)
                for(int k = 1; k <= j; k++)
                    p[j] = max(p[j], min(data[i] / k, p[j - k]));
        }
        int ansp = p[n];
        if(ansp == 0) {
            printf("0 0\n");
            continue;
        }
        // 不能一边dp最大安全值，一边计算最小花费，因为最小花费时p[j - k]>=ansp,但可能不是max p[j - k]
        memset(cost, 0x3f, sizeof(cost));
        cost[0] = 0;
        for(int i = 0; i < m; i++) {
            int nowc = data[i];
            for(int j = n; j > 0; j--)
                for(int k = min(j, nowc / ansp); k > 0; k--) // 小心这里除0错误
                    cost[j] = min(cost[j], nowc + cost[j - k]);
        }
        printf("%d %d\n", ansp, cost[n]);
    }
    return 0;
}
