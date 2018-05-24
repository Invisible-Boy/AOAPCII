/**
 * Title:   8-26UVa12559
 * Author:  InvisibleMan
 * Date:    2017-6-1
 * Time:    100ms
 */

#include <cstdio>
#include <cstring>
#include <cmath>

#define min(x, y) ((x) < (y) ? (x) : (y))
using namespace std;

struct Node {
    int r, x, y;
};

const int Nmax = 101;
bool g[Nmax][Nmax];
int w, h;
Node ans[Nmax];

bool judge(int y, int x, int r) {
    int cnt = 0;
    for(int i = 0; i <= r; i++) {
        int dy = (int)(sqrt(r * r - i * i) + 0.5);
        if(!g[x - i][y + dy]) cnt++;
        if(!g[x + i][y + dy]) cnt++;
        if(!g[x - i][y - dy]) cnt++;
        if(!g[x + i][y - dy]) cnt++;
    }
    return cnt < 5;
}

int main() {
    int T;
    scanf("%d\n", &T);
    for(int t = 1; t <= T; t++) {
        memset(g, 0, sizeof(g));
        scanf("%d%d\n", &w, &h);
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                g[i][j] = getchar() - '0';
            }
            getchar();
        }
        int num = 0, rmax = min(w, h) >> 1;
        for(int r = 5; r < rmax; r++)
            for(int i = r; i < w - r; i++)
                for(int j = r; j < h - r; j++) {
                    if(judge(i, j, r)) {
                        ans[num].r = r, ans[num].x = i, ans[num].y = j;
                        num++;
                    }
                }
        printf("Case %d: %d", t, num);
        for(int i = 0; i < num; i++)
            printf(" (%d,%d,%d)", ans[i].r, ans[i].x, ans[i].y);
        printf("\n");
    }
    return 0;
}
