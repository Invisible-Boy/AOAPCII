/**
 *  Title:  UVa12099
 *  Author: InvisibleMan
 *  Date:   2018/3/15
    Time:   60ms
 */
#include <cstdio>
#include <algorithm>

using namespace std;

const int Nmax = 2105;

inline int min(int t1, int t2) {
    return t1 < t2 ? t1 : t2;
}

inline int max(int t1, int t2) {
    return t1 > t2 ? t1 : t2;
}

struct Node {
    int h, w;
    bool operator < (const Node &rhs) const {
        return h > rhs.h;
    }
}data[75];

int dp[Nmax][Nmax];

int main() {
    int tt;
    scanf("%d", &tt);
    while(tt--) {
        int m, wwmax = 0;
        scanf("%d", &m);
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &data[i].h, &data[i].w);
            wwmax += data[i].w;
        }
        sort(data, data + m);
        for(int i = 0; i <= wwmax; i++)
            for(int j = 0; j <= wwmax; j++)
                dp[i][j] = 1e9;
        dp[0][0] = 0;
        int wmax = 0, tw = data[0].w + 30; // 后两层的书厚度不能超过第一层厚度+30
        for(int i = 1; i < m; i++) {
            int addw = data[i].w, addh = data[i].h;
            wmax += addw; tw += addw;
            for(int j = wmax; j > -1; j--)
                for(int k = min(wmax - j, (tw - j) >> 1); k > -1; k--) { // 优化1和2
                    if(j >= tw - k - j) continue;
                    int &t = dp[j][k];
                    if(j >= addw)
                        t = min(t, dp[j - addw][k] + (j == addw ? addh : 0));
                    if(k >= addw)
                        t = min(t, dp[j][k - addw] + (k == addw ? addh : 0));
                }
        }
        int ans = 1e9, th = data[0].h;
        for(int i = 5; i <= wmax; i++)
            for(int j = 5; j <= i; j++) {
                if(dp[i][j] > 1e7) continue;
                int t = max(i, wwmax - i - j);
                ans = min(ans, t * (dp[i][j] + th));
            }
        printf("%d\n", ans);
    }
    return 0;
}
