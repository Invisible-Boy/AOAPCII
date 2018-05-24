/**
 * Title:   9-5UVa12563
 * Author:  InvisibleMan
 * Date:    2017-6-13
 * Time:    ms
 */

#include <cstdio>
#include <cstring>

using namespace std;

const int Tmax = 9005;

int main() {
    int T, ans[Tmax][2];
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) {
        int n, t;
        scanf("%d%d", &n, &t);
        if(t >= Tmax) t = Tmax;
        memset(ans, 0, sizeof(ans));
        for(int i = 0; i < n; i++) {
            int l;
            scanf("%d", &l);
            for(int j = t - 1; j > -1; j--) {
                if(j >= l) {
                    if(ans[j - l][0] + 1 > ans[j][0] || (ans[j - l][0] + 1 == ans[j][0] && ans[j - l][1] + l > ans[j][1]))
                        ans[j][0] = ans[j - l][0] + 1, ans[j][1] = ans[j - l][1] + l;
                }
            }
        }
        printf("Case %d: %d %d\n", i, ans[t - 1][0] + 1, ans[t - 1][1] + 678);
    }
    return 0;
}
