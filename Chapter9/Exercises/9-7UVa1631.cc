/**
 *  Title:  9-7UVa1631
 *  Author: InvisibleMan
 *  Date:   2018/4/10
 *  Time:   40ms
 *  Remark: referenced online answer
 */
#include <cstdio>
#include <cstring>

const int Nmax = 1005;
const int INF = 0x3f3f3f3f;
char s1[Nmax], s2[Nmax];
int dp[Nmax][10][10];

inline int min(int t1, int t2) {
    return t1 < t2 ? t1 : t2;
}

int main() {
    while(scanf("%s%s", s1, s2) == 2) {
        int len = strlen(s1);
        s1[len] = s2[len] = '0';
        s1[len + 1] = '0'; s2[len + 1] = '0';
        memset(dp, 0x3f, sizeof(dp));
        dp[0][s1[0] - '0'][s1[1] - '0'] = 0;
        for(int i = 0; i < len; i++)
            for(int j = 0; j < 10; j++)
                for(int k = 0; k < 10; k++)
                    if(dp[i][j][k] < INF) {
                        int max = (s2[i] - '0' - j + 10) % 10;
                        int newj = k, newk = s1[i + 2] - '0';
                        int newans = dp[i][j][k] + max;
                        for(int ii = 0; ii <= max; ii++)
                            for(int jj = 0; jj <= ii; jj++)
                                dp[i + 1][(newj + ii) % 10][(newk + jj) % 10] = min(dp[i + 1][(newj + ii) % 10][(newk + jj) % 10], newans);
                        max = (j - s2[i] + '0' + 10) % 10;
                        newans = dp[i][j][k] + max;
                        for(int ii = 0; ii <= max; ii++)
                            for(int jj = 0; jj <= ii; jj++)
                                dp[i + 1][(newj - ii + 10) % 10][(newk - jj + 10) % 10] = min(dp[i + 1][(newj - ii + 10) % 10][(newk - jj + 10) % 10], newans);
                    }
        printf("%d\n", dp[len][0][0]);
    }
    return 0;
}
