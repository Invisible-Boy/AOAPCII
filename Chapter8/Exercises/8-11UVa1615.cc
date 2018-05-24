/**
 * Title:   8-11UVa1615
 * Author:  InvisibleMan
 * Date:    2017-4-20
 * Time:    0ms
 */

#include <cstdio>
#include <algorithm>
#include <cmath>

// 在algorithm中定义了max和min，使用的是模版类
// 在cmath中定义了fmax(double, double),没有max,和min
//#define max(x, y) ((x) > (y) ? (x) : (y))
//#define min(x, y) ((x) < (y) ? (x) : (y))

using namespace std;

const int Nmax = 1e5;

struct Node{
    double b, e;
    bool operator < (const Node &rhs) const {
        return e < rhs.e;
    }
};

Node seg[Nmax];

int main() {
    double L, D;
    while(scanf("%lf%lf", &L, &D) == 2) {
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            double tx, ty, dist;
            scanf("%lf%lf", &tx, &ty);
            dist = sqrt(D * D - ty * ty);
            // 使用库函数中的max和min时，传入的参数类型必须一致
            seg[i].b = max(0.0, tx - dist);
            seg[i].e = min(L, tx + dist);
        }
        sort(seg, seg + n);
        int cnt = 0, i = 0, now;
        while(i < n) {
            now = seg[i].e;
            cnt++, i++;
            while(i < n && seg[i].b <= now)
                ++i;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
