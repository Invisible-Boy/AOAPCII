/**
 * Title:   8-18UVa1442
 * Author:  InvisibleMan
 * Date:    2017-4-1
 * Time:    150ms
 */

#include <cstdio>

using namespace std;

#define min(x, y) ((x) < (y) ? (x) : (y))
const int Nmax = 1e6 + 1;

int T, n, floor[Nmax], ceil[Nmax];


int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
            scanf("%d", &floor[i]);
        for(int i = 0; i < n; i++)
            scanf("%d", &ceil[i]);
        floor[n] = 1001;
        int l = 0, r = 1, ans = 0, minCeil = ceil[0], maxFloor = floor[0], maxFl = l;
        while(r < n + 1) {
            if(floor[r] > minCeil || ceil[r] <= maxFloor) {
                int nowCeil;
                if(floor[r] > minCeil) nowCeil = minCeil, maxFl = r;
                else nowCeil = min(minCeil, maxFloor);
                for(int i = l; i < maxFl; i++)
                    ans += nowCeil - floor[i];
                if(floor[r] > minCeil) {
                    l = r;
                    minCeil = floor[r];
                    maxFloor = floor[l];
                }
                else {
                    l = maxFl + 1;
                    minCeil = min(ceil[l], maxFloor);
                    maxFloor = floor[l];
                }
                maxFl = l;
                r = l;
            }
            else {
                if(ceil[r] < minCeil)
                    minCeil = ceil[r];
                if(floor[r] >= maxFloor)
                    maxFloor = floor[r], maxFl = r;
            }
            r++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
