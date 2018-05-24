/**
 * Title:   9-22UVa12105-2
 * Author:  InvisibleMan
 * Date:    2017-9-1
 * Time:    100ms
 */

/**
 *  参考了lrj的代码，这个方法属于填表法
 */ 

#include <cstdio>

using namespace std;

const int Nmax = 105;
const int Mmax = 3005;
const int need[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int p[Nmax][Mmax], now[Nmax][Mmax];

int main() {
    int n, m, kase = 1;
    while(scanf("%d", &n) == 1 && n) {
        scanf("%d", &m);
        /**
         * 要从输出来理解这部分代码的作用，属于填表法。
         * 这部分的主要作用是去除当前选择的火柴之后，剩余的火柴是否还可以实现最后的功能。
         * 这样形成的p和now数组其实是最后输出的一个中间部分
         */
        for(int i = 0; i <= n; i++)
            for(int j = 0; j < m; j++) {
                int &ans = p[i][j];
                ans = now[i][j] = -1;
                if(j == 0) ans = 0;
                for(int d = 9; d > -1; d--) {
                    if(i >= need[d]) {
                        int t = p[i - need[d]][(j * 10 + d) % m];
                        if(t > -1 && t + 1 > ans) {
                            ans = t + 1;
                            now[i][j] = d;
                        }
                    }
                }
            }
        printf("Case %d: ", kase++);
        if(now[n][0] < 0) printf("-1");
        else {
            int j = 0;
            for(int d = now[n][j]; d > -1; d = now[n][j]) {
                printf("%d", d);
                j = (j * 10 + d) % m;
                n -= need[d];
            }
        }
        printf("\n");
    }
    return 0;
}
