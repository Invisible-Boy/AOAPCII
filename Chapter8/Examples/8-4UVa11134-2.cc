/**
 * Title:   8-4UVa11134
 * Author:  InvisibleMan
 * Date:    2017-3-14
 * Time:    0ms
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 5000;

int p[N], n, xl[N], yl[N], xr[N], yr[N], x[N], y[N];

bool cmp1(int t1, int t2) {
    return xr[t1] < xr[t2];
}

bool cmp2(int t1, int t2) {
    return yr[t1] < yr[t2];
}

bool fill(bool f, int a[], int b[], int aim[]) {
    if(f) sort(p, p + n, cmp1);
    else sort(p, p + n, cmp2);
    bool flag = true, vis[N] = {0};
    for(int i = 0; i < n && flag; i++) {
        int pp = p[i];
        flag = false;
        for(int j = a[pp] - 1; j < b[pp]; j++) {
            if(!vis[j]) {
                aim[pp] = j + 1;
                vis[j] = true;
                flag = true;
                break;
            }
        }
    }
    return flag;
}

int main() {
    while(scanf("%d", &n) == 1 && n) {
        for(int i = 0; i < n; i++) {
            scanf("%d%d%d%d", &xl[i], &yl[i], &xr[i], &yr[i]);
            p[i] = i;
        }
        if(fill(1, xl, xr, x) && fill(0, yl, yr, y))
            for(int i = 0; i < n; i++)
                printf("%d %d\n", x[i], y[i]);
        else printf("IMPOSSIBLE\n");
    }
    return 0;
}
