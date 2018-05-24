/**
 * Title:   8-4UVa11134
 * Author:  InvisibleMan
 * Date:    2017-3-14
 * Time:    0ms
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Node {
    int xl, yl, xr, yr, x, y;
};

Node rook[5010];

bool cmp1(int t1, int t2) {
    return rook[t1].xr < rook[t2].xr;
}

bool cmp2(int t1, int t2) {
    return rook[t1].yr < rook[t2].yr;
}

int main() {
    int p[5010], n, xl, yl, xr, yr;
    while(scanf("%d", &n) == 1 && n) {
        for(int i = 0; i < n; i++) {
            scanf("%d%d%d%d", &xl, &yl, &xr, &yr);
            rook[i].xl = xl, rook[i].yl = yl;
            rook[i].xr = xr, rook[i].yr = yr;
            p[i] = i;
        }
        sort(p, p + n, cmp1);
        bool flag = true, vis[5010] = {0};
        for(int i = 0; i < n && flag; i++) {
            int index = p[i];
            flag = false;
            for(int j = rook[index].xl - 1; j < rook[index].xr; j++) {
                if(!vis[j]) {
                    rook[index].x = j + 1;
                    vis[j] = true;
                    flag = true;
                    break;
                }
            }
        }
        if(flag) {
            sort(p, p + n, cmp2);
            memset(vis, 0, sizeof(vis));
        }
        for(int i = 0; i < n && flag; i++) {
            int index = p[i];
            flag = false;
            for(int j = rook[index].yl - 1; j < rook[index].yr; j++) {
                if(!vis[j]) {
                    rook[index].y = j + 1;
                    vis[j] = true;
                    flag = true;
                    break;
                }
            }
        }
        if(flag)
            for(int i = 0; i < n; i++)
                printf("%d %d\n", rook[i].x, rook[i].y);
        else printf("IMPOSSIBLE\n");
    }
    return 0;
}
