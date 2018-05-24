/**
 * Title:   9-8UVa1625
 * Author:  InvisibleMan
 * Date:    2017-6-17
 * Time:    0ms
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int Nmax = 5005;

int ans[Nmax], p1[26], p2[26], q1[26], q2[26];

int main() {
    int t;
    char s1[Nmax], s2[Nmax];
    scanf("%d", &t);
    while(t--) {
        int n, m;
        scanf("%s%s", s1 + 1, s2 + 1);
        n = strlen(s1 + 1) + 1;
        m = strlen(s2 + 1) + 1;
        memset(p1, 0x3f, sizeof(p1));
        memset(p2, 0x3f, sizeof(p2));
        memset(q1, -1, sizeof(q1));
        memset(q2, -1, sizeof(q2));
        for(int i = 1; i < n; i++) {
            int index = s1[i] - 'A';
            p1[index] = min(p1[index], i);
            q1[index] = max(q1[index], i);
        }
        for(int i = 1; i < m; i++) {
            int index = s2[i] - 'A';
            p2[index] = min(p2[index], i);
            q2[index] = max(q2[index], i);
        }
        memset(ans, 0, sizeof(ans));
        for(int j = 1; j < m; j++) {
            int t = 0;
            for(int k = 0; k < 26; k++)
                if((p1[k] <= 0 || p2[k] <= j - 1) && (q1[k] > 0 || q2[k] > j - 1))
                    t++;
            ans[j] = ans[j - 1] + t;
        }
        for(int i = 1; i < n; i++) {
            for(int j = 0; j < m; j++) {
                int t1 = 0, t2 = 0;
                for(int k = 0; k < 26; k++) {
                    if((p1[k] <= i - 1 || p2[k] <= j) && (q1[k] > i - 1 || q2[k] > j))
                        t1++;
                    if((p1[k] <= i || p2[k] <= j - 1) && (q1[k] > i || q2[k] > j - 1))
                        t2++;
                }
                ans[j] += t1;
                if(j > 0)
                    ans[j] = min(ans[j], ans[j - 1] + t2);
            }
        }
        printf("%d\n", ans[m - 1]);
    }
    return 0;
}
