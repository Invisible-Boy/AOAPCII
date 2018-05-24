/**
 * Title:   9-21UVa1336-2
 * Author:  InvisibleMan
 * Date:    2017-7-30
 * Time:    70ms
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Node {
    int loc, cost, inc;
    bool operator < (const Node &rhs) const {
        return loc < rhs.loc;
    }
};

const int Nmax = 1005;
const int INF = 1e9;
int n, start, kase = 0, vis[Nmax][Nmax][2] = {0}, inc[Nmax];
Node d[Nmax];
double dp[Nmax][Nmax][2], v;

int main() {
    while(scanf("%d%lf%d", &n, &v, &start) == 3 && n && v && start) {
        kase++;
        int cost = 0;
        inc[0] = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d%d%d", &d[i].loc, &d[i].cost, &d[i].inc);
            cost += d[i].cost;
        }
        sort(d + 1, d + n + 1);
        for(int i = 1; i <= n; i++)
            inc[i] = inc[i - 1] + d[i].inc;
        Node temp; temp.loc = start;
        int sta = lower_bound(d + 1, d + n + 1, temp) - d;
        dp[0][n][1] = INF; dp[1][n + 1][0] = INF;
        if(sta > 1) {
            dp[sta - 1][sta][0] = (start - d[sta - 1].loc) / v * inc[n];
            vis[sta - 1][sta][0] = kase;
        }
        if(sta <= n) {
            dp[sta - 1][sta][1] = (d[sta].loc - start) / v * inc[n];
            vis[sta - 1][sta][1] = kase;
        }
        for(int i = sta - 1; i > -1; i--)
            for(int j = sta; j <= n + 1; j++) {
                if(i + 1 < j && vis[i + 1][j][0] == kase) {
                    int tinc = inc[i] + inc[n] - inc[j - 1];
                    dp[i][j][0] = dp[i + 1][j][0] + (d[i + 1].loc - d[i].loc) / v * tinc;
                    dp[i][j][1] = dp[i + 1][j][0] + (d[j].loc - d[i + 1].loc) / v * tinc;
                    vis[i][j][0] = kase; vis[i][j][1] = kase;
                }
                if(j - 1 > i && vis[i][j - 1][1] == kase) {
                    int tinc = inc[i] + inc[n] - inc[j - 1];
                    double t1 = dp[i][j - 1][1] + (d[j - 1].loc - d[i].loc) / v * tinc;
                    double t2 = dp[i][j - 1][1] + (d[j].loc - d[j - 1].loc) / v * tinc;
                    if(vis[i][j][0] == kase)
                        dp[i][j][0] = min(dp[i][j][0], t1);
                    else dp[i][j][0] = t1, vis[i][j][0] = kase;
                    if(vis[i][j][1] == kase)
                        dp[i][j][1] = min(dp[i][j][1], t2);
                    else dp[i][j][1] = t2, vis[i][j][1] = kase;
                }
            }
        printf("%d\n", cost + (int)min(dp[0][n][1], dp[1][n + 1][0]));
    }
    return 0;
}
