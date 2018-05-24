/**
 * Title:   9-6UVa11400
 * Author:  InvisibleMan
 * Date:    2017-6-15
 * Time:    60ms
 */

#include <cstdio>
#include <algorithm>

using namespace std;

struct lamp {
    int V, K, C, L;
    bool operator < (const lamp &rhs) const {
        return V < rhs.V;
    }
};

const int Nmax = 1005;

int main() {
    int n;
    lamp d[Nmax];
    while(scanf("%d", &n) == 1 && n) {
        for(int i = 1; i <= n; i++)
            scanf("%d%d%d%d", &d[i].V, &d[i].K, &d[i].C, &d[i].L);
        sort(d + 1, d + n + 1);
        int s[Nmax], ans[Nmax];
        s[0] = 0; ans[0] = 0;
        for(int i = 1; i <= n; i++) {
            s[i] = s[i - 1] + d[i].L;
            ans[i] = ans[i - 1] + d[i].K + d[i].C * d[i].L;
        }
        for(int i = 1; i <= n; i++)
            for(int j = 0; j < i; j++)
                ans[i] = min(ans[j] + (s[i] - s[j]) * d[i].C + d[i].K, ans[i]);
        printf("%d\n", ans[n]);
    }
    return 0;
}
