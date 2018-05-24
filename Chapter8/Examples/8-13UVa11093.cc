/**
 * Title:   8-13UVa11093
 * Aurhor:  InvisibleMan
 * Date:    2017-3-23
 * Time:    140ms
 */

/* tips: 贪心算法，当汽车从i->j停下时，从i->j-1的车站都不能当作起点，因为都会在j站通不过
         原因是，前面的车站越多，只会对通过后面的车站提供有利的影响，当钱买呢车站多的时候通不过，后面车站更通不过
*/

#include <cstdio>

using namespace std;

int main() {
    int T, n, p[100001], q[100001];
    scanf("%d", &T);
    for(register int t = 1; t <= T; t++) {
        scanf("%d", &n);
        for(register int i = 0; i < n; i++)
            scanf("%d", &p[i]);
        for(register int i = 0; i < n; i++)
            scanf("%d", &q[i]);
        register int l = 0, ll = 0;
        bool flag = true;
        while(l < n) {
            int sum = 0;
            do {
                sum += p[ll] - q[ll];
                ll = (ll + 1) % n;
            }while(sum >= 0 && ll != l);
            if(ll > l) l = ll;
            else {
                flag = !(sum >= 0 && ll == l);
                break;
            }
        }
        printf("Case %d: ", t);
        if(flag) printf("Not possible\n");
        else printf("Possible from station %d\n", l + 1);
    }
    return 0;
}
