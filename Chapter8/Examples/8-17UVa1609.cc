/**
 * Title:   8-17UVa1609
 * Author:  InvisibleMan
 * Date:    2017-3-31
 * Time:    ms
 */

#include <cstdio>

using namespace std;

int n, p[2][1025], q[2][1025];
char g[1025][1026];
int main() {
    while(scanf("%d\n", &n) == 1) {
        for(int i = 1; i <= n; i++) scanf("%s", g[i] + 1);
        p[0][0] = 0; q[0][0] = 0;
        for(int i = 2; i <= n; i++) {
            if(g[1][i] == '0')
                q[0][i] = q[0][0], q[0][0] = i;
            else
                p[0][i] = p[0][0], p[0][0] = i;
        }
        int f = 0;
        while(n > 1) {
            q[1 - f][0] = p[1 - f][0] = 0;
            int li = 0;
            for(int i = q[f][0]; i > 0; i = q[f][i]) {
                int lj = 0, j = p[f][0];
                for(; j > 0; j = p[f][j]) {
                    if(g[i][j] == '0') {
                        printf("%d %d\n", j, i);
                        p[1 - f][j] = p[1 - f][0];
                        p[1 - f][0] = j;
                        q[f][li] = q[f][i];
                        p[f][lj] = p[f][j];
                        break;
                    }
                    lj = j;
                }
                if(j == 0) li = i;
            }
            printf("1 %d\n", p[f][0]);
            p[f][0] = p[f][p[f][0]];
            int i = q[f][0], j = p[f][0];
            while(i > 0 && q[f][i] > 0) {
                int ii = q[f][i];
                if(g[i][ii] == '1') {
                    q[1 - f][i] = q[1 - f][0], q[1 - f][0] = i;
                    printf("%d %d\n", i, ii);
                }
                else {
                    q[1 - f][ii] = q[1 - f][0], q[1 - f][0] = ii;
                    printf("%d %d\n", ii, i);
                }
                i = q[f][ii];
            }
            while(j > 0 && p[f][j] > 0) {
                int jj = p[f][j];
                if(g[j][jj] == '1') {
                    p[1 - f][j] = p[1 - f][0], p[1 - f][0] = j;
                    printf("%d %d\n", j, jj);
                }
                else {
                    p[1 - f][jj] = p[1 - f][0], p[1 - f][0] = jj;
                    printf("%d %d\n", jj, j);
                }
                j = p[f][jj];
            }
            if(i > 0) {
                if(g[i][j] == '1') {
                    q[1 - f][i] = q[1 - f][0], q[1 - f][0] = i;
                    printf("%d %d\n", i, j);
                }
                else {
                    p[1 - f][j] = p[1 - f][0], p[1 - f][0] = j;
                    printf("%d %d\n", j, i);
                }
            }
            f = 1 - f;
            n = n >> 1;
        }
    }
    return 0;
}
