/**
 *  Title:  9-6UVa10723
 *  Author: InvisibleMan
 *  Date:   2018/3/26
 *  Time:   0ms
 *  Remark: hard LCS
 */
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int Nmax = 35;

char str1[Nmax], str2[Nmax];
int dp[Nmax][Nmax], cnt[Nmax][Nmax];

inline void getline(char str[]) {
    char t;
    while((scanf("%c", &t) == 1) && t != '\n')
        *str++ = t;
    *str = '\0';
}

int main() {
    int n;
    scanf("%d", &n); getchar();
    for(int k = 0; k < n;) {
        getline(str1);
        getline(str2);
        int len1 = strlen(str1);
        int len2 = strlen(str2);
        memset(dp, 0, sizeof(dp));
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i <= len1; i++) cnt[i][0] = 1;
        for(int i = 0; i <= len2; i++) cnt[0][i] = 1;
        for(int i = 1; i <= len1; i++)
            for(int j = 1; j <= len2; j++) {
                if(str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    cnt[i][j] = cnt[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    if(dp[i][j] == dp[i - 1][j])
                        cnt[i][j] += cnt[i - 1][j];
                    if(dp[i][j] == dp[i][j - 1])
                        cnt[i][j] += cnt[i][j - 1];
                }
            }
        printf("Case #%d: %d %d\n", ++k, len1 + len2 - dp[len1][len2], cnt[len1][len2]);
    }
    return 0;
}
