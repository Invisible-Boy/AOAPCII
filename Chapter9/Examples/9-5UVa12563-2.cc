/**
 * Title:   9-5UVa12563-2
 * Author:  InvisibleMan
 * Date:    2017-6-13
 * Time:    0ms
 */

#include <cstdio>

using namespace std;

const int Tmax = 9005;
const int Nmax = 55;

int main() {
    int T, d[Nmax], ans[Nmax][Tmax][2];
    scanf("%d", &T);
    for(int kase = 1; kase <= T; kase++) {
        int n, t;
        scanf("%d%d", &n, &t);
        if(t > Tmax) t = Tmax;
        for(int i = 0; i < n; i++)
            scanf("%d", &d[i]);
        for(int i = 0; i < t; i++)
            ans[n][i][0] = ans[n][i][1] = 0;
        for(int i = n - 1; i > -1; i--)
            for(int j = 0; j < t; j++) {
                ans[i][j][0] = ans[i + 1][j][0];
                ans[i][j][1] = ans[i + 1][j][1];
                if(j >= d[i] && (ans[i][j][0] < ans[i + 1][j - d[i]][0] + 1 || (ans[i][j][0] == ans[i + 1][j - d[i]][0] + 1 && ans[i][j][1] < ans[i + 1][j - d[i]][1] + d[i]))) {
                    ans[i][j][0] = ans[i + 1][j - d[i]][0] + 1;
                    ans[i][j][1] = ans[i + 1][j - d[i]][1] + d[i];
                }
            }
        printf("Case %d: %d %d\n", kase, ans[0][t - 1][0] + 1, ans[0][t - 1][1] + 678);
    }
    return 0;
}
