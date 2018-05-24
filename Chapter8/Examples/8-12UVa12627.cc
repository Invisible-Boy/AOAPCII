/**
 * Title:   8-12UVa12627
 * Author:  InvisibleMan
 * Date:    2017-3-25
 * Time:    0ms
 */

// tips:这里不能直接递归，要转化成一个完整的子问题，否则就变成了递归树
// 自己之前就没有转化成f(k, b) - f(k, a - 1)导致超时，值得借鉴和深思

#include <cstdio>

long long r[30];

long long ans(int k, int a) {
    if(a < 1) return 0;
    if(k == 0) return 1;
    int mid = 1 << k - 1;
    if(a > mid)
        return ans(k - 1, a - mid) + (r[k - 1] << 1);
    return ans(k - 1, a) << 1;
}

int main() {
    int T;
    scanf("%d", &T);
    r[0] = 1;
    for(int i = 1; i < 30; i++)
        r[i] = r[i - 1] * 3;
    for(int i = 1; i <= T; i++) {
        int k, a, b;
        scanf("%d%d%d", &k, &a, &b);
        printf("Case %d: %lld\n", i, ans(k, b) - ans(k, a - 1));
    }
    return 0;
}
