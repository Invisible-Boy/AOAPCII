/**
 *  Title:  9-7UVa1631
 *  Author: InvisibleMan
 *  Date:   2018/3/29
 *  Remark: Error idea
 */

#include <cstdio>
#include <cstring>
#include <queue>

const int Nmax = 1005, INF = 1e9;
const int dx[][3] = {{0, 0, 1},
                     {0, 0, 9},
                     {0, 1, 0},
                     {0, 9, 0},
                     {1, 0, 0},
                     {9, 0, 0},
                     {0, 1, 1},
                     {0, 9, 9},
                     {1, 1, 0},
                     {9, 9, 0},
                     {1, 1, 1},
                     {9, 9, 9}};

inline int min(int t1, int t2) {
    return t1 < t2 ? t1 : t2;
}

inline int atoi(char *temp, int size) {
    int ans = 0;
    while(size--) ans = ans * 10 + *temp++ - '0';
    return ans;
}

int predp[Nmax][Nmax];

int slove(int x, int y) {
    if(x == y) predp[x][y] = 0;
    if(predp[x][y] > -1) return predp[x][y];
    if(predp[x][y] == -1 && predp[y][x] > -1) return predp[y][x];
    std::queue<int> que;
    que.push(y);
    predp[y][y] = 0;
    while(!que.empty()) {
        int now = que.front();
        que.pop();
        int t1 = now % 10;
        int t2 = (now / 10) % 10;
        int t3 = now / 100;
        int nowcnt = predp[now][y];
        for(int i = 0; i < 12; i++) {
            int newnow = (t1 + dx[i][0]) % 10 + (t2 + dx[i][1]) % 10 * 10 + (t3 + dx[i][2]) % 10 * 100;
            if(predp[newnow][y] == -1) {
                predp[newnow][y] = nowcnt + 1;
                que.push(newnow);
            }
        }
    }
    return predp[x][y];
}

int main() {
    char str1[Nmax], str2[Nmax];
    int dp[Nmax][Nmax];
    memset(predp, -1, sizeof(predp));
    while(scanf("%s%s", str1, str2) == 2) {
        int len = strlen(str1);
        for(int l = 1; l < 4; l++)
            for(int i = 0; i <= len - l; i++)
                dp[i][i + l] = slove(atoi(str1 + i, l), atoi(str2 + i, l));
        for(int l = 4; l <= len; l++)
            for(int i = 0; i <= len - l; i++) {
                dp[i][i + l] = INF;
                for(int j = i + 1; j < i + l; j++)
                    dp[i][i + l] = min(dp[i][i + l], dp[i][j] + dp[j][i + l]);
            }
        printf("%d\n", dp[0][len]);
    }
    return 0;
}
