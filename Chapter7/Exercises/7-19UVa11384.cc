/**
 * Title:   7-19UVa11384
 * Author:  InvisibleMan
 * Date:    2017-2-26
 * Time:    20ms
 */

#include <cstdio>

using namespace std;

int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        int ans = 1;
        while(n >> 1) {
            ans++;
            n = n >> 1;
        }
        printf("%d\n", ans);
    }
}
