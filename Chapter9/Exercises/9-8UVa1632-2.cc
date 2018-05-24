/**
 *  Title:  9-8UVa1632
 *  Author: InvisibleMan
 *  Date:   2018/4/12
 *  Time:   300ms
 *  remark: reference online answer
 */

#include <cstdio>

const int Nmax = 10010;
const int INF = 1 << 30;
int n, d[Nmax][2], dp[2][Nmax][2];

inline int min(int t1, int t2) {
    return t1 < t2 ? t1 : t2;
}

int main() {
    while(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &d[i][0], &d[i][1]);
            dp[0][i][0] = dp[0][i][1] = 0;
        }
        int cur = 0;
        for(int l = 1; l < n; l++) {
            cur ^= 1;
            for(int i = 0; i < n - l; i++) {
                dp[cur][i][0] = min(dp[cur ^ 1][i + 1][0] + d[i + 1][0] - d[i][0], dp[cur ^ 1][i + 1][1] + d[i + l][0] - d[i][0]);
                if(dp[cur][i][0] >= d[i][1]) dp[cur][i][0] = INF;
                dp[cur][i][1] = min(dp[cur ^ 1][i][1] + d[i + l][0] - d[i + l - 1][0], dp[cur ^ 1][i][0] + d[i + l][0] - d[i][0]);
                if(dp[cur][i][1] >= d[i + l][1]) dp[cur][i][1] = INF;
            }
        }
        int ans = min(dp[cur][0][0], dp[cur][0][1]);
        if(ans < INF)
            printf("%d\n", ans);
        else
            printf("No solution\n");
    }
    return 0;
}
