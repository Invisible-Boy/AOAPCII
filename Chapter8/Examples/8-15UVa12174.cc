/**
 * Title:   8-15UVa12174
 * Author:  InvisibleMan
 * Date:    2017-3-28
 * Time:    870ms
 */

// tips: 复杂度略高，为O(n*s)

#include <cstdio>

using namespace std;

const int Nmax = 1e5 + 1;

int main() {
    int T, s, n, lo[Nmax];
    bool div[Nmax];
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &s, &n);
        for(int i = 0; i <= s; i++)
            div[i] = true, lo[i] = -1;
        int t, cnt = s;
        for(int i = 0; i < n; i++) {
            scanf("%d", &t);
            if(lo[t] >= 0 && lo[t] > i - s) {
                for(int ii = i; ii < lo[t] + s; ii++)
                    if(div[ii % s]) div[ii % s] = false, --cnt;
                for(int ii = lo[t] - 1; ii > -1 && ii >= i - s; ii--)
                    if(div[ii % s]) div[ii % s] = false, --cnt;
            }
            lo[t] = i;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
