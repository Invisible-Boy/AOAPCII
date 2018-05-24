/**
 * Title:   9-1UVa1025
 * Author:  InvisibleMan
 * Date:    2017-6-11
 * Time:    0ms
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int Nmax = 55;
const int Tmax = 205;
const int INF = 1e9;

int main() {
    int N, T, c[Nmax], allC[Nmax], kase = 0, ans[Nmax][Tmax];
    bool p[Nmax][Tmax], q[Nmax][Tmax];
    while(scanf("%d", &N) == 1 && N) {
        scanf("%d", &T);
        for(int i = 0; i < N - 1; i++)
            scanf("%d", &c[i]);
        c[N - 1] = 0; allC[N - 1] = 0;
        for(int i = N - 2; i > -1; i--)
            allC[i] = c[i] + allC[i + 1];
        int m;
        for(int i = 0; i < N; i++)
            for(int j = 0; j < T; j++) p[i][j] = false, q[i][j] = false;
        scanf("%d", &m);
        for(int i = 0; i < m; i++) {
            int t;
            scanf("%d", &t);
            for(int i = 0; i < N - 1 && t < Tmax; i++) {
                p[i][t] = true;
                t += c[i];
            }
        }
        scanf("%d", &m);
        for(int i = 0; i < m; i++) {
            int t;
            scanf("%d", &t);
            for(int i = N - 1; i > 0 && t < Tmax; i--) {
                q[i][t] = true;
                t += c[i - 1];
            }
        }
        for(int i = 0; i < N - 1; i++) ans[i][T] = INF;
        ans[N - 1][T] = 0;
        for(int i = T - 1; i > -1; i--)
            for(int j = N - 1; j > -1; j--) {
                int &tans = ans[j][i];
                tans = ans[j][i + 1] + 1; // 等1分钟
                if(j < N - 1 && p[j][i] && i + allC[j] <= T)
                    tans = min(tans, ans[j + 1][i + c[j]]);
                if(j > 0 && q[j][i] && i + c[j - 1] + allC[j - 1] <= T)
                    tans = min(tans, ans[j - 1][i + c[j - 1]]);
            }
        printf("Case Number %d: ", ++kase);
        if(ans[0][0] < INF) printf("%d\n", ans[0][0]);
        else printf("impossible\n");
    }
    return 0;
}
