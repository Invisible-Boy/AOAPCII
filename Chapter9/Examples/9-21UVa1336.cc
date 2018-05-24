/**
 * Title:   9-21UVa1336
 * Author:  InvisibleMan
 * Date:    2017-7-30
 * Time:    170ms
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
int n, start, kase = 0, vis[Nmax][Nmax][2] = {0};
Node d[Nmax];
double dp[Nmax][Nmax][2], v;

double dfs(int p, int q, int k, int inc) {
    if(vis[p][q][k] == kase) return dp[p][q][k];
    vis[p][q][k] = kase;
    double &ans = dp[p][q][k];
    ans = INF;
    if(k) {
        if(p > 0)
            ans = min(ans, dfs(p, q + 1, 0, inc - d[p].inc) + (d[q].loc - d[p].loc) / v * inc);
        if(q < n)
            ans = min(ans, dfs(p, q + 1, 1, inc - d[q + 1].inc) + (d[q + 1].loc - d[q].loc) / v * inc);
        else if(p < 1) ans = 0;
    }
    else {
        if(q <= n)
            ans = min(ans, dfs(p - 1, q, 1, inc - d[q].inc) + (d[q].loc - d[p].loc) / v * inc);
        if(p > 1)
            ans = min(ans, dfs(p - 1, q, 0, inc - d[p - 1].inc) + (d[p].loc - d[p - 1].loc) / v * inc);
        else if(q > n) ans = 0;
    }
    return ans;
}

int main() {
    while(scanf("%d%lf%d", &n, &v, &start) == 3 && n && v && start) {
        kase++;
        int cost = 0, inc = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d%d%d", &d[i].loc, &d[i].cost, &d[i].inc);
            cost += d[i].cost;
            inc += d[i].inc;
        }
        sort(d + 1, d + n + 1);
        Node temp; temp.loc = start;
        int sta = lower_bound(d + 1, d + n + 1, temp) - d;
        int ans1 = INF, ans2 = INF;
        if(sta > 1)
            ans1 = dfs(sta - 1, sta, 0, inc - d[sta - 1].inc) + (start - d[sta - 1].loc) / v * inc;
        if(sta <= n)
            ans2 = dfs(sta - 1, sta, 1, inc - d[sta].inc) + (d[sta].loc - start) / v * inc;
        printf("%d\n", cost + min(ans1, ans2));
    }
    return 0;
}
