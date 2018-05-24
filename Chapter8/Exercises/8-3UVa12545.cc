/**
 * Title:   8-3UVa12545
 * Author:  InvisibleMan
 * Date:    2017-4-5
 * Time:    0ms
 */

#include <cstdio>
#include <cstring>

char s[101], t[101];

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        printf("Case %d: ", i);
        scanf("%s%s", s, t);
        int len = strlen(s), ns = 0, nt = 0, mt = 0, ms = 0, nd = 0;
        for(int j = 0; j < len; j++) {
            if(s[j] == '1') ns++;
            if(t[j] == '1') nt++;
            if(s[j] == '?') {
                if(t[j] == '1') mt++;
                ms++;
            }
            else if(s[j] != t[j]) nd++;
        }
        if(ns > nt) printf("-1\n");
        else {
            int t = nt - ns - mt;
            if(t > 0) printf("%d\n", ms + t + (nd - t) / 2);
            else printf("%d\n", (nd - t) / 2 + ms);
        }
    }
    return 0;
}
