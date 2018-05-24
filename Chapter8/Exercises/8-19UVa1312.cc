/**
 * Title:   8-19UVa1312
 * Author:  InvisibleMan
 * Date:    2017-5-10
 * Time:    0ms
 */

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int Nmax = 105;
int main() {
    int T, w, h, n, ux[Nmax], uy[Nmax];
    scanf("%d", &T);
    while(T--) {
        vector<int> height[10001];
        int x, y;
        scanf("%d%d%d", &n, &w, &h);
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &x, &y);
            ux[i] = x, uy[i] = y;
            height[x].push_back(y);
        }
        ux[n] = 0; ux[n + 1] = w;
        uy[n] = 0;
        sort(ux, ux + n + 2);
        int nx = unique(ux, ux + n + 2) - ux;
        sort(uy, uy + n + 1);
        int ny = unique(uy, uy + n + 1) - uy;
        for(int i = 0; i < nx; i++)
            sort(height[ux[i]].begin(), height[ux[i]].end());
        int ans = 0, ansx = 0, ansy = 0;
        for(int i = 0; i < nx - 1; i++) {
            for(int j = 0; j < ny; j++) {
                int lower_h = h;
                for(int k = i + 1; k < nx; k++) {
                    int tAns = min(lower_h - uy[j], ux[k] - ux[i]);
                    if(tAns > ans) {
                        ans = tAns;
                        ansx = ux[i];
                        ansy = uy[j];
                    }
                    if(lower_h - uy[j] <= ans)
                        break;
                    vector<int> &t = height[ux[k]];
                    vector<int>::iterator p = upper_bound(t.begin(), t.end(), uy[j]);
                    if(p != t.end()) lower_h = min(*p, lower_h);
                }
            }
        }
        printf("%d %d %d\n", ansx, ansy, ans);
        if(T) printf("\n");
    }
    return 0;
}
