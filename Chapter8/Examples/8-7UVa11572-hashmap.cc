/**
 * Title:   8-7UVa11572
 * Author:  InvisibleMan
 * Date:    2017-3-18
 * Time:    180ms
 */

#include <cstdio>
#define max(x, y) ((x) > (y) ? (x) : (y))

using namespace std;

const int N = 1000003;

struct Hash {
    int p[N], q[N];
    void clear() {
        for(int i = 0; i < N; i++) {
            p[i] = -1;
            q[i] = -1;
        }
    }
    int& operator[] (int t) {
        int i;
        for(i = t % N; p[i] >-1 && p[i] != t; i = (i + 1) % N);
        return q[i];
    }
}hash;

int main() {
    int T, n;
    scanf("%d", &T);
    while(T--) {
        hash.clear(); 
        int t, start = 0, ans = 0;
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &t);
            int &p = hash[t];
            if(p >= start) {
                ans = max(ans, i - start);
                start = p + 1;
            }
            p = i;
        }
        printf("%d\n", max(ans, n - start));
    }
    return 0;
}
