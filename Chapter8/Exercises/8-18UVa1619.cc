/**
 * Title:   8-18UVa1619
 * Author:  InvisibleMan
 * Date:    2017-5-9
 * Time:    150ms
 */

/**
 * 参考了网上的思路，采用滑动窗口算法，维护一个单调序列
 */

#include <cstdio>

using namespace std;

const int Nmax = 1e5 + 5;
int d[Nmax], l[Nmax], r[Nmax], q[Nmax];
long long sum[Nmax];

int main() {
    int n, T = 0;
    while(scanf("%d", &n) == 1) {
        long long t = 0;
        sum[0] = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d", &d[i]);
            t += d[i];
            sum[i] = t;
        }
        d[0] = -2, d[n + 1] = -1;
        int rear = 0;
        q[0] = 0;
        for(int i = 1; i <= n + 1; i++) {
            while(d[i] <= d[q[rear]])
                r[q[rear--]] = i - 1;
            l[i] = q[rear];
            q[++rear] = i;
        }
        long long ans = -1;
        int ansl, ansr;
        for(int i = 1; i <= n; i++) {
            long long temp = d[i] * (sum[r[i]] - sum[l[i]]);
            if(temp > ans)
                ansl = l[i], ansr = r[i], ans = temp;
        }
        if(T++) printf("\n");
        printf("%lld\n%d %d\n", ans, ansl + 1, ansr);
    }
    return 0;
}
