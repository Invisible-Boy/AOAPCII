/**
 * Title:   8-7UVa11572
 * Author:  InvisibleMan
 * Date:    2017-3-18
 * Time:    80ms
 */

// tips: 这个解法实际上是不对的，因为题目说每个数的范围是1-1e9，但是实际上数据范围只达到了1e6

#include <cstdio>
#include <cstring>
#define max(x, y) ((x) > (y) ? (x) : (y))

using namespace std;

const int Nmax = 1e6 + 5;

int main() {
    int T, n;
    scanf("%d", &T);
    while(T--) {
        int hash[Nmax];
        memset(hash, -1, sizeof(hash));
        int t, start = 0, ans = 0;
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &t);
            if(hash[t] > -1 && hash[t] >= start) {
                ans = max(ans, i - start);
                start = hash[t] + 1;
            }
            hash[t] = i;
        }
        printf("%d\n", max(ans, n - start));
    }
    return 0;
}
