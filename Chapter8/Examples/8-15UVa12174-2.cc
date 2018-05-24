/**
 * Title:   8-15UVa12174
 * Author:  InvisibleMan
 * Date:    2017-3-28
 * Time:    20ms
 */

// tips:参考了lrj的代码，之前的思路想错了，如果采用之前的代码，复杂度最多为O(n * s)
// 采用这种策略，复杂度为O(n)

#include <cstdio>

using namespace std;

const int Nmax = 1e5 + 1;

int main() {
    int T, s, n, cnt[Nmax], x[3 * Nmax];
    bool div[Nmax << 1];
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &s, &n);
        for(int i = 0; i <= s; i++)
            cnt[i] = 0, x[i] = x[i + n + s] = -1;
        for(int i = 0; i < n + s; i++)
            div[i] = false;
        for(int i = s; i < n + s; i++) scanf("%d", &x[i]);
        int tot = 0, ans = s;    // 当前窗口中互异元素个数
        for(int i = 0; i < n + s; i++) {
            if(tot == s) div[i] = true;
            if(i < s && tot == i) div[i] = true;
            if(i > n && tot == s + n - i) div[i] = true;
            if(x[i] > 0 && --cnt[x[i]] == 0) --tot;  // 精髓
            if(x[i + s] > 0 && cnt[x[i + s]]++ == 0) tot++;  // 精髓
        }
        for(int i = 0; i < s; i++) {
            for(int j = i; j < n + s; j += s)
                if(!div[j]) { --ans; break; }
        }
        if(ans >= n) ans = s;
        printf("%d\n", ans);
    }
    return 0;
}
