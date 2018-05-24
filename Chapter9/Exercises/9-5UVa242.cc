/**
 *  Title:  9-5UVa242
 *  Author: InvisibleMan
 *  Date:   2018/3/22
 *  Time:   10ms
 */
#include <memory.h>
#include <algorithm>
#include <cstdio>

using namespace std;

const int Nmax = 11;
const int Mmax = 105;

bool dp[Mmax * Nmax];
int data[Mmax], ans[Mmax];

inline bool judge() {
    int l1 = data[0], l2 = ans[0];
    if(l1 != l2) return l1 < l2;
    for(int i = l1 - 1; i > 0; i--)
        if(data[i] != ans[i]) return data[i] < ans[i];
    return false;
}

int main() {
    int s;
    while((scanf("%d", &s) == 1) && s) {
        int n; scanf("%d", &n);
        ans[0] = -1;
        for(int i = 0; i < n; i++) {
            int t; scanf("%d", &t);
            data[0] = ++t;
            memset(dp, 0, sizeof(dp));
            dp[0] = true;
            for(int j = 1; j < t; j++) {
                int tt;
                scanf("%d", &tt);
                data[j] = tt;
            }
            sort(&data[1], &data[t]);
            int max = data[t - 1];
            for(int l = 1; l <= s; l++)
                for(int now = max * l; now > 0; now--)
                    for(int dd = 1; dd < t && !dp[now] && now >= data[dd]; dd++)
                        dp[now] |= dp[now - data[dd]];
            int cnt = 1;
            while(dp[cnt]) cnt++;
            data[t] = --cnt;
            if(ans[0] < 0 || cnt > ans[ans[0]] || (cnt == ans[ans[0]] && judge()))
                memcpy(ans, data, sizeof(int) * (data[0] + 1));
        }
        int t = ans[0];
        printf("max coverage =%4d :", ans[t]);
        for(int i = 1; i < t; i++)
            printf("%3d", ans[i]);
        printf("\n");
    }
    return 0;
}
