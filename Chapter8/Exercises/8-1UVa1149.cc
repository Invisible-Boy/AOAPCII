/**
 * Title:   8-1UVa1149.cc
 * Author:  InvisibleMan
 * Date:    2017-4-2
 * Time:    10ms
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int Nmax = 1e5;
int d[Nmax];

int main() {
    int T, n, b;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &b);
        for(int i = 0; i < n; i++)
            scanf("%d", &d[i]);
        sort(d, d + n);
        int l = 0, r = n, ans = 0;
        while(r > l) {
            if(d[l] + d[r - 1] <= b || l == r - 1)
                ++l;
            --r; ++ans;
        }
        printf("%d\n", ans);
        if(T) printf("\n");
    }
    return 0;
}
