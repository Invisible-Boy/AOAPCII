/**
 * Title:   7-19UVa11384
 * Author:  InvisibleMan
 * Date:    2017-2-26
 * Time:    10ms
 */

#include <cstdio>

using namespace std;

int myfind(int n, int p, int q) {
    int mid = (p + q) >> 1;
    if(n >= (1 << mid + 1)) return myfind(n, mid + 1, q);
    if(n < (1 << mid)) return myfind(n, p, mid - 1);
    return mid + 1;
}

int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        printf("%d\n",myfind(n, 0, 30));
    }
}
