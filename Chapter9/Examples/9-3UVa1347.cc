/**
 * Title:   9-3UVa1347
 * Author:  InvisibleMan
 * Date:    2017-6-11
 * Time:    0ms
 */

// 参考了紫书上的思路

#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int Nmax = 1e3;
double dist[Nmax][Nmax], ans[Nmax][Nmax];

int main() {
    int n, d[Nmax][2];
    while(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; i++)
            scanf("%d%d", &d[i][0], &d[i][1]);
        for(int i = 0; i < n; i++)
            for(int j = i + 1; j < n; j++) {
                int dx = d[i][0] - d[j][0], dy = d[i][1] - d[j][1];
                dist[i][j] = sqrt((double)(dx * dx + dy * dy));
            }
        for(int i = 0; i < n - 1; i++)
            ans[n - 1][i] = dist[i][n - 1];
        for(int i = n - 2; i > 0; i--)
            for(int j = i - 1; j > -1; j--)
                ans[i][j] = min(dist[i][i + 1] + ans[i + 1][j], dist[j][i + 1] + ans[i + 1][i]);
        printf("%.2f\n", dist[0][1] + ans[1][0]); // 第一步必定是从第一个点走到第二个点
    }
    return 0;
}
