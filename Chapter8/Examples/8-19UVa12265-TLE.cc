/**
 * Title:   8-19UVa12265
 * Author:  InvisibleMan
 * Date:    2017-4-2
 * Time:    TLE
 */

#include <cstdio>

using namespace std;

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))
const int Nmax = 1001;

int T, n, m, rMax[Nmax][Nmax], cMax[Nmax][Nmax], ans[Nmax << 1];
char data[Nmax][Nmax];

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d\n", &n, &m);
        for(int i = 1; i <= n; ++i) scanf("%s", data[i] + 1);
        for(int i = 1; i <= m; ++i) rMax[i][0] = 0;
        for(int i = 1; i <= n; ++i) cMax[0][i] = 0;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) {
                rMax[i][j] = data[i][j] == '#' ? 0 : rMax[i][j - 1] + 1;
                cMax[i][j] = data[i][j] == '#' ? 0 : cMax[i - 1][j] + 1;
            }
        for(int i = 2; i <= n + m; ++i)
            ans[i] = 0;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) {
                if(data[i][j] == '#') continue;
                int nowAns, nowC, nowR;
                // 此处，对于每个节点找到最大的矩形需要O(m)的时间，太慢了
                // 参考别人的代码，使用单调栈来维护
                if(rMax[i][j] > cMax[i][j]) {
                    nowR = rMax[i][j], nowAns = 1 + nowR;
                    int Cmax = cMax[i][j];
                    for(int c = 1; c < Cmax && nowR + Cmax > nowAns; ++c) {
                        nowR = min(nowR, rMax[i - c][j]);
                        nowAns = max(nowAns, c + 1 + nowR);
                    }
                }
                else {
                    nowC = cMax[i][j], nowAns = 1 + nowC;
                    int Rmax = rMax[i][j];
                    for(int r = 1; r < Rmax && nowC + Rmax > nowAns; ++r) {
                        nowC = min(nowC, cMax[i][j - r]);
                        nowAns = max(nowAns, r + 1 + nowC);
                    }
                }
                ++ans[nowAns];
            }
        for(int i = 2; i <= n + m; ++i)
            if(ans[i] > 0)
                printf("%d x %d\n", ans[i], i << 1);
    }
    return 0;
}
