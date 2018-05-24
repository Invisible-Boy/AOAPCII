/**
 * Title:   8-19UVa1312-2
 * Author:  InvisibleMan
 * Date:    2017-5-10
 * Time:    0ms
 */

/**
 * 参考网上的代码，通过枚举y的间隔，同时判断是否有点落在矩形内，来更新最小值
 * 部分枚举，固定一个边来枚举另一个边
 */

#include <cstdio>
#include <algorithm>

using namespace std;

struct Node {
    int x, y;
    bool operator < (const Node &rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};

const int Nmax = 105;

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, w, h, uy[Nmax];
        Node node[Nmax];
        scanf("%d%d%d", &n, &w, &h);
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &node[i].x, &node[i].y);
            uy[i] = node[i].y;
        }
        sort(node, node + n);
        uy[n] = 0, uy[n + 1] = h;
        sort(uy, uy + n + 2);
        int ny = unique(uy, uy + n + 2) - uy;
        int ans = 0, ansx = 0, ansy = 0;
        for(int i = 0; i < ny; i++)
            for(int j = i + 1; j < ny; j++) {
                int temp = 0, maxy = uy[j], miny = uy[i], hh = maxy - miny;
                for(int k = 0; k < n; k++) {
                    if(node[k].y <= miny || node[k].y >= maxy) continue;
                    int ww = node[k].x - temp;
                    if(ans < min(ww, hh)) {
                        ans = min(ww, hh);
                        ansx = temp;
                        ansy = miny;
                    }
                    temp = node[k].x;
                }
                int ww = w - temp;
                if(ans < min(ww, hh)) {
                    ans = min(ww, hh);
                    ansx = temp;
                    ansy = miny;
                }
            }
        printf("%d %d %d\n", ansx, ansy, ans);
        if(T) printf("\n");
    }
    return 0;
}
