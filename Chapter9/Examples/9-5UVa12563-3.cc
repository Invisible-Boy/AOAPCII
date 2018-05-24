/**
 * Title:   9-5UVa12563-3
 * Author:  InvisibleMan
 * Date:    2017-6-13
 * Time:    0ms
 */

#include <cstdio>

using namespace std;

const int Tmax = 9005;
const int Nmax = 55;

int main() {
    int T, d, ans[Nmax][Tmax][2];
    scanf("%d", &T);
    for(int kase = 1; kase <= T; kase++) {
        int n, t;
        scanf("%d%d", &n, &t);
        if(t > Tmax) t = Tmax;
        scanf("%d", &d);
        for(int i = 0; i < t; i++)
            if(i >= d) ans[0][i][0] = 1, ans[0][i][1] = d;
            else ans[0][i][0] = ans[0][i][1] = 0;
        for(int i = 1; i < n; i++) {
            scanf("%d", &d);
            for(int j = 0; j < t; j++) {
                ans[i][j][0] = ans[i - 1][j][0], ans[i][j][1] = ans[i - 1][j][1];
                if(j >= d && (ans[i][j][0] < ans[i - 1][j - d][0] + 1 || (ans[i][j][0] == ans[i - 1][j - d][0] + 1 && ans[i][j][1] < ans[i - 1][j - d][1] + d)))
                    ans[i][j][0] = ans[i - 1][j - d][0] + 1, ans[i][j][1] = ans[i - 1][j - d][1] + d;
            }
        }
        printf("Case %d: %d %d\n", kase, ans[n - 1][t - 1][0] + 1, ans[n - 1][t - 1][1] + 678);
    }
    return 0;
}
