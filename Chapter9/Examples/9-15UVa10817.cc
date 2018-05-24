/**
 * Title:   8-15UVa10817
 * Author:  InvisibleMan
 * Date:    2017-7-17
 * Time:    ms
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int Smax = 8;
const int Nmax = 105;
const int INF = 1e9;

int s, m, n, d[Nmax][1 << Smax][1 << Smax], c[Nmax], sta[Nmax];

int dfs(int i, int s1, int s2) {
    if(i == n) return (s2 == (1 << s) - 1) ? 0 : INF;
    int &ans = d[i][s1][s2];
    if(ans > -1) return ans;
    ans = dfs(i + 1, s1, s2);
    int ts1 = s1 & sta[i], ts2 = (~s1) & (~s2) & sta[i];
    s2 |= ts1;
    s1 ^= ts1;
    s1 |= ts2;
    ans = min(ans, dfs(i + 1, s1, s2) + c[i]);
    return ans;
}

int main() {
    while(scanf("%d%d%d\n", &s, &m, &n) == 3 && s > 0) {
        int ans = 0, s1 = 0, s2 = 0;
        memset(d, -1, sizeof(d));
        char t;
        for(int i = 0; i < m; i++) {
            int tc = 0;
            while((t = getchar()) && t != ' ')
                tc = tc * 10 + t - '0';
            ans += tc;
            while((t = getchar()) && t != '\n')
                if(t != ' ') {
                    tc = t - '0' - 1;
                    if(s1 & (1 << tc)) {
                        s2 |= 1 << tc;
                        s1 ^= 1 << tc;
                    }
                    else if(!(s2 & (1 << tc)))
                        s1 |= 1 << tc;
                }
        }
        for(int i = 0; i < n; i++) {
            int tc = 0;
            while((t = getchar()) && t != ' ')
                tc = tc * 10 + t - '0';
            c[i] = tc;
            int ss = 0;
            while((t = getchar()) && t != '\n')
                if(t != ' ') ss |= 1 << (t - '0' - 1);
            sta[i] = ss;
        }
        printf("%d\n", ans + dfs(0, s1, s2));
    }
    return 0;
}
