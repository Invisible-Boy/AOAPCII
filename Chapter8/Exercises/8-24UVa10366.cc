/**
 * Title:   8-24UVa10366
 * Author:  InvisibleMan
 * Date:    2017-5-26
 * Time:    0ms
 */

/**
 * 参考了网上的思路，先找到左边和右边的最大值，然后分情况讨论
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int Nmax = 1000;

int main() {
    int l, r, h[Nmax];
    while(scanf("%d%d", &l, &r) == 2 && l && r) {
        int n = ((r - l) >> 1) + 1, ln = (1 - l) >> 1, rn = (r + 1) >> 1;
        int lmax = 0, rmax = 0, lx, rx;
        for(int i = 0; i < ln; i++) {
            int t;
            scanf("%d", &t);
            h[i] = t;
            if(t >= lmax) lmax = t, lx = i;
        }
        for(int i = 0; i < rn; i++) {
            int t;
            scanf("%d", &t);
            h[i + ln] = t;
            if(t > rmax) rmax = t, rx = i + ln;
        }
        int ans = 0;
        if(lmax == rmax) {
            ans = lmax * (rx - lx);
            int t = h[n - 1], t1 = 0, t2 = 0;
            // 求右侧容量，很神奇的做法，画图才可以看懂
            for(int i = n - 1; i > rx; i--) {
                t1 += t;
                t = max(t, h[i - 1]);
            }
            t = h[0];
            // 求左侧容量，同上
            for(int i = 0; i < lx; i++) {
                t2 += t;
                t = max(t, h[i + 1]);
            }
            ans += min(t1, t2) << 1;
        }
        else if(lmax < rmax) {
            int t = h[0], t1 = 0, t2 = 0;
            for(int i = 0; i < lx; i++) {
                t1 += t;
                t = max(t, h[i + 1]);
            }
            int rx = lx + 1;
            while(rx < n && h[rx] < lmax) rx++;
            ans += (rx - lx) * lmax;
            if(h[rx] == lmax) {
                lx = rx;
                // 当右侧和左侧出现同一水平面时，水往左侧流的同时还会往右侧流，需要判断大小'
                while(rx < n && h[rx] <= lmax) rx++;
                t2 = (rx - lx) * lmax;
                ans += min(t1, t2);
            }
            ans += t1;
        }
        else {
            int t = h[n - 1], t1 = 0, t2 = 0;
            for(int i = n - 1; i > rx; i--) {
                t1 += t;
                t = max(t, h[i - 1]);
            }
            int lx = rx - 1;
            while(lx > -1 && h[lx] < rmax) lx--;
            ans += (rx - lx) * rmax;
            if(h[lx] == rmax) {
                rx = lx;
                while(lx > -1 && h[lx] <= rmax) lx--;
                t2 = (rx - lx) * rmax;
                ans += min(t1, t2);
            }
            ans += t1;
        }
        printf("%d\n", ans << 1);
    }
    return 0;
}
