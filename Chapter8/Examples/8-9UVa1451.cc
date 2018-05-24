/**
 * Title:   8-9UVa1451
 * Author:  InvisibleMan
 * Date:    2017-3-22
 * Time:    ms
 */

// tips: 参考了lrj的代码，对于上凸队列的理解还需要加强

#include <cstdio>

using namespace std;

int T, n, l, p[100001], index[100001];

int cmp(int x1, int x2, int x3, int x4) {
    return (p[x2] - p[x1 - 1]) * (x4 - x3 + 1) - (p[x4] - p[x3 - 1]) * (x2 - x1 + 1);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d\n", &n, &l);
        p[0] = 0;
        for(int i = 1, cnt = 0; i <= n; i++) {
            cnt += getchar() - '0';
            p[i] = cnt;
        }
        int ansL = 1, ansR = l, p = 0, q = 0;
        for(int t = l; t <= n; t++) {
            /* 为什么这里是 t-l 而不是 t-l+1 ？
               目测是因为求斜率时是x1和x2-1，所以真正在运算的是t-l，而不是t-l+1，因此要用t-l来判断是否新加入的点是上凸点
            */
            while(q - p > 1 && cmp(index[q - 2], t - l, index[q - 1], t - l) >= 0) --q;
            index[q++] = t - l + 1; // 由于cmp的书写，这里放入的点反而是t-l+1，而不是t - l
            while(q - p > 1 && cmp(index[p + 1], t, index[p], t) >= 0) ++p;
            int tt = cmp(index[p], t, ansL, ansR);
            if(tt > 0 || tt == 0 && t - index[p] < ansR - ansL)
                ansL = index[p], ansR = t;
        }
        printf("%d %d\n", ansL, ansR);
    }
    return 0;
}
