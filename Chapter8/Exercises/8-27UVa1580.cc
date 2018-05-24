/**
 * Title:   8-27UVa1580
 * Author:  InvisibleMan
 * Date:    2017-6-4
 * Time:    0ms
 */

/**
 * 参考了网上的代码，居然是暴力过。
 */
#include <cstdio>
#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

using namespace std;

const int Nmax = 500;
const int INF = 1e9;

int main() {
    int a, b, n, m, d[Nmax][Nmax];
    while(scanf("%d%d%d%d", &a, &b, &n, &m) == 4) {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                scanf("%d", &d[i][j]);
        if(a > b) {
            int t = a;
            a = b;
            b = t;
        }
        int min[Nmax];  // 保存每一列的最小值
        long long ans = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++)
                min[j] = INF;
            for(int r = i; r < n; r++) {  // 注意此处r 和 j的顺序不能变，否则不能满足后面min[]矩阵要保持的性质
                if(r - i + 1 > b) break;
                for(int j = 0; j < m; j++) {
                    int h = INF;
                    for(int c = j; c < m; c++) {
                        if(c - j + 1 > b) break;
                        min[c] = min(min[c], d[r][c]);
                        h = min(h, min[c]);
                        int bb = r - i + 1;
                        int aa = c - j + 1;
                        if(aa > bb) {
                            int t = aa;
                            aa = bb;
                            bb = t;
                        }
                        if(aa <= a && bb <= b) {
                            long long t = (long long)aa * bb * h;
                            long long tans = aa * bb * (t / (m * n - aa * bb) + h - (t % (m * n - aa * bb) == 0));
                            ans = max(ans, tans);
                        }
                        else if(aa > a)
                            break;
                    }
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
