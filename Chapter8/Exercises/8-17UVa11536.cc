/**
 * Title:   8-17UVa11536
 * Author:  InvisibleMan
 * Date:    2017-5-8
 * Time:    420ms
 */
#include <cstdio>
#define min(x, y) ((x) < (y) ? (x) : (y))

using namespace std;

const int Nmax = 1e6 + 1;
int main() {
    int T, n, m, k, d[Nmax], q[Nmax], num[101];
    scanf("%d", &T);
    for(int t = 1; t <= T; t++) {
        scanf("%d%d%d", &n, &m, &k);
        int ans = 1e8, cnt = 3;
        for(int i = 1; i <= k; i++) num[i] = 0;
        if(k < 4) ans = k, cnt = k;
        else {
            d[1] = 1, d[2] = 2, d[3] = 3;
            num[1]++, num[2]++, num[3]++;
            int front = 0, rear = 3;
            q[0] = 1, q[1] = 2, q[2] = 3;
            for(int i = 4; i <= n; i++) {
                d[i] = (d[i - 1] + d[i - 2] + d[i - 3]) % m + 1;
                if(d[i] <= k) {
                    num[d[i]]++;
                    q[rear++] = i;
                    if(num[d[i]] == 1) {
                        if(++cnt == k)
                            ans = min(ans, i - q[front] + 1);
                    }
                    // 注意此处的数组多层嵌套，需要小心理清关系
                    else if(d[i] == d[q[front]]) {
                        while(num[d[q[front]]] > 1) {
                            num[d[q[front]]]--;
                            front++;
                        }
                        if(cnt == k)
                            ans = min(ans, i - q[front] + 1);
                    }
                }
            }
        }
        printf("Case %d: ", t);
        if(cnt == k)
            printf("%d\n", ans);
        else printf("sequence nai\n");
    }
    return 0;
}
