/**
 * Title:   9-16UVa1252
 * Author:  InvisibleMan
 * Date:    2017-7-20
 * Time:    110ms
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int Mmax = 11;
const int Nmax = 128;

int n, m, cnt[1 << Mmax][1 << Mmax], sta[Nmax], d[1 << Mmax][1 << Mmax];

int dp(int s, int a) {
    if(cnt[s][a] < 2) return 0;
    int &ans = d[s][a];
    if(ans > -1) return ans;
    ans = Nmax;
    for(int i = 0; i < m; i++)
        if((s & (1 << i)) == 0)
            ans = min(ans, max(dp(s | (1 << i), a), dp(s | (1 << i), a | (1 << i))) + 1);
    return ans;
}

int main() {
    while(scanf("%d%d\n", &m, &n) == 2 && n && m) {
        memset(cnt, 0, sizeof(cnt));
        memset(d, -1, sizeof(d));
        for(int i = 0; i < n; i++) {
            int t = 0;
            for(int j = 0; j < m; j++)
                t |= (getchar() - '0') << j;
            scanf("\n");
            for(int s = (1 << m) - 1; s > -1; s--)
                cnt[s][s & t]++;
        }
        printf("%d\n", dp(0, 0));
    }
    return 0;
}
