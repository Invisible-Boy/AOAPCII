/**
 * Title:   8-13UVa10570
 * Author:  InvisibleMan
 * Date:    2017-4-26
 * Time:    160ms
 */
#include <cstdio>

using namespace std;

int cw(int dt[], int start, int n, int nowAns) {
    int d[500];
    for(int i = 0; i < n; i++)
        d[i] = dt[i];
    int ans = 0;
    for(int i = 0; i < n && ans < nowAns; i++) {
        int now = (start + i) % n;
        if(d[now] != i + 1) {
            int t = d[now], aim = (start + t - 1) % n;
            d[now] = d[aim];
            d[aim] = t;
            i--;
            ans++;
        }
    }
    return ans;
}

int acw(int dt[], int start, int n, int nowAns) {
    int d[500];
    for(int i = 0; i < n; i++)
        d[i] = dt[i];
    int ans = 0;
    for(int i = 0; i < n && ans < nowAns; i++) {
        int now = (start - i + n) % n;
        if(d[now] != i + 1) {
            int t = d[now], aim = (start - t + n + 1) % n;
            d[now] = d[aim];
            d[aim] = t;
            i--;
            ans++;
        }
    }
    return ans;
}

int main() {
    int n, d[501];
    while(scanf("%d", &n) == 1 && n) {
        for(int i = 0; i < n; i++)
            scanf("%d", &d[i]);
        int ans = 1000;
        for(int i = 0; i < n; i++) {
            ans = cw(d, i, n, ans);
            ans = acw(d, i, n, ans);
        }
        printf("%d\n", ans);
    }
    return 0;
}
