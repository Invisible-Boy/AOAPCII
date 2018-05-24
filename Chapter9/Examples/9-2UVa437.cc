/**
 * Title:   9-2UVa437
 * Author:  InvisibleMan
 * Date:    2017-6-12
 * Time:    0ms
 */

#include <cstdio>
#include <algorithm>

using namespace std;

struct Node{
    int l, w, h;
    bool operator < (const Node &rhs) const {
        if(l != rhs.l) return l < rhs.l;
        if(w != rhs.w) return w < rhs.w;
        return h < rhs.h;
    }
    bool operator == (const Node &rhs) const {
        return l == rhs.l && w == rhs.w && h == rhs.h;
    }
};

const int Nmax = 90;

int main() {
    Node d[Nmax];
    int n, kase = 0;
    while(scanf("%d", &n) == 1 && n) {
        int nn = 0;
        for(int i = 0; i < n; i++) {
            int t1, t2, t3;
            scanf("%d%d%d", &t1, &t2, &t3);
            int l, w, h;
            d[nn].l = max(t1, t2), d[nn].w = min(t1, t2), d[nn].h = t3; nn++;
            d[nn].l = max(t1, t3), d[nn].w = min(t1, t3), d[nn].h = t2; nn++;
            d[nn].l = max(t2, t3), d[nn].w = min(t2, t3), d[nn].h = t1; nn++;
        }
        sort(d, d + nn);
        nn = unique(d, d + nn) - d;
        int ans[Nmax], tans = 0;
        for(int i = nn - 1; i > -1; i--) {
            ans[i] = d[i].h;
            for(int j = i + 1; j < nn; j++) {
                if(d[i].l < d[j].l && d[i].w < d[j].w)
                    ans[i] = max(ans[i], ans[j] + d[i].h);
            }
            tans = max(tans, ans[i]);
        }
        printf("Case %d: maximum height = %d\n", ++kase, tans);
    }
    return 0;
}
