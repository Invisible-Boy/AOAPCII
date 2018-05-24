/**
 * Title:   8-6UVa1606
 * Author:  InvisibleMan
 * Time:    2017-3-17
 * Date:    940ms
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int N = 10000;

int n, lx[N], ly[N], type[N], ind[N], ox[N], oy[N];
double plor[N];

bool cmp(int t1, int t2) {
    return plor[t1] < plor[t2];
}

bool left(int t1, int t2) {
    return ox[t1] * oy[t2] >= ox[t2] * oy[t1];
}

int main() {
    while(scanf("%d", &n) == 1 && n) {
        int ans = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d%d%d", &lx[i], &ly[i], &type[i]);
            ind[i] = i;
        }
        for(int i = 0; i < n; i++) {
            int cnt = 0;
            for(int j = 0; j < n; j++) {
                if(i != j) {
                    ind[cnt] = cnt;
                    ox[cnt] = lx[j] - lx[i];
                    oy[cnt] = ly[j] - ly[i];
                    if(type[j]) ox[cnt] = -ox[cnt], oy[cnt] = -oy[cnt];
                    plor[cnt] = atan2(oy[cnt], ox[cnt]);
                    cnt++;
                }
            }
            sort(ind, ind + cnt, cmp);
            int l = 0, r = 0, tAns = 2;
            while(l < cnt) {
                if(l == r) tAns++, r = (r + 1) % cnt;
                while(l != r && left(ind[l], ind[r]))
                    tAns++, r = (r + 1) % cnt;
                tAns--;
                ans = max(ans, tAns);
                l++;
            }
        }   
        printf("%d\n", ans);
    }
    return 0;
}
