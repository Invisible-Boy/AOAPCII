/**
 *  Title:  9-8UVa1632
 *  Author: InvisibleMan
 *  Date:   2018/4/11
 *  Time:   TLEms
 *  Remark: The reason of TLE still unknow, reference online answer.
 */

#include <cstdio>

const int Nmax = 10010;
const int INF = 1 << 30;
int n, d[Nmax][2], dp[Nmax][Nmax][2];

inline int min(int t1, int t2) {
    return t1 < t2 ? t1 : t2;
}

int main() {
    while(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &d[i][0], &d[i][1]);
            dp[i][i][0] = dp[i][i][1] = 0;
        }
        for(int l = 1; l < n; l++)
            for(int i = 0; i < n - l; i++) {
                dp[i][i + l][0] = min(dp[i + 1][i + l][0] + d[i + 1][0] - d[i][0], dp[i + 1][i + l][1] + d[i + l][0] - d[i][0]);
                if(dp[i][i + l][0] >= d[i][1]) dp[i][i + l][0] = INF;
                dp[i][i + l][1] = min(dp[i][i + l - 1][1] + d[i + l][0] - d[i + l - 1][0], dp[i][i + l - 1][0] + d[i + l][0] - d[i][0]);
                if(dp[i][i + l][1] >= d[i + l][1]) dp[i][i + l][1] = INF;
            }
        int ans = min(dp[0][n - 1][0], dp[0][n - 1][1]);
        if(ans < INF)
            printf("%d\n", ans);
        else
            printf("No solution\n");
    }
    return 0;
}
