/**
 * Title:   8-7UVa11572
 * Author:  InvisibleMan
 * Date:    2017-3-18
 * Time:    490ms
 */

#include <cstdio>
#include <map>
#define max(x, y) ((x) > (y) ? (x) : (y))

using namespace std;

int main() {
    int T, n;
    scanf("%d", &T);
    while(T--) {
        map<int, int> hash;
        int t, start = 0, ans = 0;
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &t);
            if(hash.count(t) && hash[t] >= start) {
                ans = max(ans, i - start);
                start = hash[t] + 1;
            }
            hash[t] = i;
        }
        printf("%d\n", max(ans, n - start));
    }
    return 0;
}
