/**
 * Title:   Coin (NYOJ-995)
 * Author:  InvisibleMan
 * Date:    2017-6-8
 * Time:    128ms
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int Cmax = 1e5 + 5;
const int Nmax = 55;
const int INF = 1e9; // 因为这个值后面要参与计算，所以不要取的太极端,免得溢出

int main() {
    int n, aim, d[Cmax], c[Nmax];
    while(scanf("%d%d", &n, &aim) == 2 && (n || aim)) {
        for(int i = 0; i < n; i++)
            scanf("%d", &c[i]);
        sort(c, c + n);
        d[0] = 0;
        for(int i = 1; i <= aim; i++)
            d[i] = INF;
        for(int i = 1; i <= aim; i++)
            for(int j = 0; j < n && c[j] <= i; j++)
                d[i] = min(d[i], d[i - c[j]] + 1);
        for(int i = aim; i > -1; i--) {
            if(d[i] < INF) {
                printf("%d\n", d[i]);
                break;
            }
        }
    }
    return 0;
}
