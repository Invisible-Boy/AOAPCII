/**
 * Title:   8-22UVa1622
 * Author:  InvisibleMan
 * Date:    2017-5-21
 * Time:    0ms
 */

/**
 * 参考了网上的思路，先上下移动，然后再判断上下移动和左右移动那个更优
 * 最终左右移动之后，判断上下移动和左右移动哪个更优（此时两个方向都不能回头）
 * 此题也是采用了贪心的思路，保证每一步都尽量使下一步的损失最小，无法证明是最优解
 * 后面可能还需要再看
 */

#include <cstdio>
#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))
typedef long long LL;

LL find(LL N, LL M, LL nmin, LL nmax, LL wmin, LL wmax) {
    LL ans = 0;
    if(nmin > 0) {
        nmax -= nmin;
        ans += N * M; N--;
        nmin = (nmin << 1) - 1;
        ans += N * M * nmin;
        if(nmax > 0) {
            nmax--;
            ans += N * M;
        }
    }
    if(wmin > 0 && N > 0) {
        wmax -= wmin;
        if(wmax) {
            wmin <<= 1;
            wmax--;
        }
        else
            wmin -= 1;
        while(N >= M + wmin * (M - 1) && nmax > 0) {
            ans += N * M;
            nmax--;
            N--;
        }
        ans += N * M; M--;
        ans += N * M * wmin;
    }
    while((nmax > 0 || wmax > 0) && N > 0 && M > 0) {
        ans += N * M;
        if(nmax > 0 && (N > M || wmax == 0)) {
            N--;
            nmax--;
        }
        else {
            M--;
            wmax--;
        }
    }
    return ans;
}

int main() {
    int N, M, n, s, w, e, t = 0;
    while(scanf("%d%d", &N, &M) == 2 && N && M) {
        scanf("%d%d%d%d", &n, &s, &w, &e);
        LL ans = 0;
        LL nmin = min(n, s), nmax = max(n, s);
        LL wmin = min(w, e), wmax = max(w, e);
        LL ans1 = find(N, M, nmin, nmax, wmin, wmax);
        LL ans2 = find(M, N, wmin, wmax, nmin, nmax);
        printf("Case %d: %lld\n", ++t, max(ans1, ans2));
    }
    return 0;
}
