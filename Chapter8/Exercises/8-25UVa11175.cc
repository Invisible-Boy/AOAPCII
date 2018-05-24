/**
 * Title:   8-25UVa11175
 * Author:  InvisibleMan
 * Date:    2017-5-30
 * Time:    60ms
 */
#include <cstdio>

using namespace std;

const int Nmax = 300;

int main() {
    int T, nIn[Nmax], nOut[Nmax], in[Nmax][Nmax], out[Nmax][Nmax], temp[Nmax];
    bool edge[Nmax][Nmax];
    scanf("%d", &T);
    for(int t = 1; t <= T; t++) {
        int m, k;
        scanf("%d%d", &m, &k);
        for(int i = 0; i < m; i++) nIn[i] = 0, nOut[i] = 0;
        for(int i = 0; i < m; i++) for(int j = 0; j < m; j++) edge[i][j] = false;
        for(int i = 0; i < k; i++) {
            int t1, t2;
            scanf("%d%d", &t1, &t2);
            in[t2][nIn[t2]++] = t1;
            out[t1][nOut[t1]++] = t2;
            edge[t1][t2] = true;
        }
        bool flag = true;
        for(int i = 0; i < m && flag; i++) {
            int n = nIn[i];
            if(n > 1) {
                int mm = 0;
                bool vis[Nmax] = {0};
                for(int j = 0; j < n; j++) {
                    int tt = in[i][j], nn = nOut[tt];
                    for(int k = 0; k < nn; k++) {
                        int tout = out[tt][k];
                        if(!vis[tout]) {
                            temp[mm++] = tout;
                            vis[tout] = true;
                        }
                    }
                }
                for(int j = 0; j < n && flag; j++) {
                    int tt = in[i][j];
                    for(int k = 0; k < mm; k++)
                        if(!edge[tt][temp[k]]) {
                            flag = false;
                            break;
                        }
                }
            }
        }
        printf("Case #%d: %s\n", t, flag ? "Yes" : "No");
    }
    return 0;
}
