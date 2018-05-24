/**
 * Title:   AntsUVa1411
 * Author:  InvisibleMan
 * Date:    2017-3-11
 * Time:    0ms
 */

// tips: 巨人与鬼，算法参考AOAPCII上的解法

#include <cstdio>
#include <algorithm>

using namespace std;

struct Node {
    int x, y, connect;
    Node(int _x = 0, int _y = 0, int _connect = -1) : x(_x), y(_y), connect(_connect) {}
};

Node ant[200];
int n, indx[200];

bool init() {
    if(scanf("%d", &n) == 1) {
        int tx, ty;
        for(int i = 0; i < n << 1; i++) {
            scanf("%d%d", &tx, &ty);
            ant[i].x = ty, ant[i].y = tx;
            indx[i] = i;
        }
        return true;
    }
    return false;
}

int nowx, nowy;

bool cmp1(int i, int j) { // 按照坐标进行排序
    Node *p1 = &ant[i], *p2 = &ant[j];
    return p1->x < p2->x || (p1->x == p2->x && p1->y < p2->y);
}

bool cmp2(int i, int j) { // 在选定根点之后，按照角度大小进行排序
    int dx1, dx2, dy1, dy2;
    dx1 = ant[i].x - nowx;
    dx2 = ant[j].x - nowx;
    dy1 = ant[i].y - nowy;
    dy2 = ant[j].y - nowy;
    return dy1 * dx2 > dy2 * dx1;
}

void slove(int p, int q) {
    if(q - p < 2) return;
    sort(indx + p, indx + q, cmp1);
/*    
    printf("p = %d q = %d\n", p, q);
    for(int i = 0; i < n << 1; i++) {
        printf("%d %d\n", ant[indx[i]].x, ant[indx[i]].y);
    }
    printf("------------\n");
*/
    nowx = ant[indx[p]].x;
    nowy = ant[indx[p]].y;
    sort(indx + p + 1, indx + q, cmp2);
    int cnt[2] = {0};
    cnt[indx[p] / n]++;
    for(int i = p + 1; i < q; i++) {
        cnt[indx[i] / n]++;
        if(cnt[0] == cnt[1]) {
            ant[indx[p]].connect = indx[i];
            ant[indx[i]].connect = indx[p];
            slove(p + 1, i);
            slove(i + 1, q);
            return;
        }
    }
}

int main() {
    int T = 0;
    while(init()) {
        
        if(T++) printf("\n");
        slove(0, n << 1);
        for(int i = 0; i < n; i++)
            printf("%d\n", ant[i].connect - n + 1);
    }
    return 0;
}
