/**
 * Title:   9-16UVa1252
 * Author:  InvisibleMan
 * Date:    2017-7-18
 * Time:    TLE
 */

/**
 * 起初想着给问问题定序，按顺序问问题，先考虑问不问第i个问题再考虑问不问第i+1个问题
 * 这种方案可以解决一部分问题，不能解决全部的情况。后面考虑遍历所有的问问题的顺序，
 * 理所当然的TLE
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int Nmax = 128;

int m, n, sta[Nmax], id[Nmax];

int dp(int s, int p, int q) {
    if(q - p < 2) return 0;
    int tt = 0;
    for(int i = 0; i < m; i++) if((s & (1 << i)) == 0) tt++;
    if(s == (1 << m) - 1 || q - p > (1 << tt)) return Nmax;
    int ans = Nmax;
    for(int i = 0; i < m; i++) {
        if((s & (1 << i)) == 0) {
            ans = min(ans, dp(s | (1 << i), p, q));
            int pp = p, qq = q - 1;
            while(qq >= pp) {
                while(pp <= qq && ((sta[id[pp]] & (1 << i)) == 0))
                    pp++;
                while(qq >= pp && (sta[id[qq]] & (1 << i)))
                    qq--;
                if(pp < qq) {
                    int t = id[pp];
                    id[pp] = id[qq];
                    id[qq] = t;
                }
            }
            if(pp != p && pp != q)
                ans = min(ans, max(dp(s | (1 << i), p, pp), dp(s | (1 << i), pp, q)) + 1);
        }
    }
    return ans;
}

int main() {
    while(scanf("%d%d\n", &m, &n) == 2 && m && n) {
        for(int i = 0; i < n; i++) {
            int t = 0;
            for(int j = 0; j < m; j++)
                t |= ((getchar() - '0') << j);
            sta[i] = t;
            id[i] = i;
            scanf("\n");
        }
        printf("%d\n", dp(0, 0, n));
    }
    return 0;
}
