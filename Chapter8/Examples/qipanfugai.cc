/**
 * Title:   棋盘覆盖问题
 * Author:  InvisibleMan
 * Date:    2017-3-10
 */

#include <cstdio>
#include <cstring>

using namespace std;

const int Nmax = 1 << 10; // 规定最大不能超过n x n的方格，n最大不能超过1024

int g[Nmax][Nmax], c; 

int location(int midx, int midy, int x, int y) {
    int ans = 0;
    if(x >= midy) ans++;
    if(y >= midx) ans += 2;
    return ans;
}

void cover(int px, int qx, int py, int qy, int xx, int yy) { // 此处可以优化，不用传入上下左右4个坐标，
                                                             // 只传入一个角的坐标和矩形的边长即可
    if(qx - px == 2) {
        for(int i = px; i < qx; i++)
            for(int j = py; j < qy; j++)
                if(g[i][j] == 0) g[i][j] = c;
        c++;
        return;
    }
    int midx = (px + qx) >> 1;
    int midy = (py + qy) >> 1;
    int lx[] = {midx - 1, midx - 1, midx, midx};
    int ly[] = {midy - 1, midy, midy - 1, midy};
    int l = location(midx, midy, xx, yy);
    for(int i = 0; i < 4; i++)
        if(i != l)
            g[lx[i]][ly[i]] = c;
    ++c;
    if(l != 0)                                      // 此处可以讲坐标存入数组，采用循环减少代码长度
        cover(px, midx, py, midy, lx[0], ly[0]);
    else
        cover(px, midx, py, midy, xx, yy);
    if(l != 1)
        cover(px, midx, midy, qy, lx[1], ly[1]);
    else
        cover(px, midx, midy, qy, xx, yy);
    if(l != 2)
        cover(midx, qx, py, midy, lx[2], ly[2]);
    else
        cover(midx, qx, py, midy, xx, yy);
    if(l != 3)
        cover(midx, qx, midy, qy, lx[3], ly[3]);
    else
        cover(midx, qx, midy, qy, xx, yy);
}

int main() {
    int k, x, y, T = 1;
    while(scanf("%d%d%d", &k, &x, &y) == 3) {
        x--, y--;
        memset(g, 0, sizeof(g));
        g[x][y] = -1;
        c = 1;
        cover(0, k, 0, k, x, y);
        printf("Case %d:\n", T++);
        for(int i = 0; i < k; i++) {
            for(int j = 0; j < k; j++)
                printf("%4d ", g[i][j]);
            printf("\n");
        }
        printf("\n");
    };

    return 0;
}
