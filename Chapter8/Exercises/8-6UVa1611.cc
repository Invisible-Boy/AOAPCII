/**
 * Title:   8-6UVa1611
 * Author:  InvisibleMan
 * Date:    2017-4-8
 * Time:    300ms
 */

// tips:根据提示，最多需要2n次调整

#include <cstdio>

using namespace std;

int d[10001], l[10001], mv[20002][2], cnt;

void move(int p, int q) {
    int len = (q - p) >> 1;
    for(int i = 0; i < len; i++) {
        int &t1 = d[p + i], &t2 = d[p + i + len], t = t1;
        l[t1] = p + i + len;
        l[t2] = p + i;
        t1 = t2;
        t2 = t;
    }
}

int main() {
    int T, n;
    scanf("%d", &T);
    while(T--) {
        cnt = 0;
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &d[i]);
            l[d[i]] = i;
        }
        for(int i = 1; i < n; i++) {
            if(l[i] != i) {
                // 如果 a----b----------n b到n的距离比a到b的距离大，则1步就可以将b换到a
                int aim = (l[i] << 1) - i;
                if(aim <= n + 1) {
                    mv[cnt][0] = i;
                    mv[cnt++][1] = aim - 1;
                    move(i, aim);
                }
                // 否则 a-------m-----b-n 将b先换到a和n的中点m，再从m换到a
                else {
                    int mid = (i + n) >> 1;
                    int aim = (mid << 1) - l[i] + 1;
                    mv[cnt][0] = aim;
                    mv[cnt++][1] = l[i];
                    move(aim, l[i] + 1);
                    mv[cnt][0] = i;
                    aim = (mid << 1) - i - 1;
                    mv[cnt++][1] = aim;
                    move(i, aim + 1);
                }
            }
        }
        printf("%d\n", cnt);
        for(int i = 0; i < cnt; i++)
            printf("%d %d\n", mv[i][0], mv[i][1]);
    }
    return 0;
}
