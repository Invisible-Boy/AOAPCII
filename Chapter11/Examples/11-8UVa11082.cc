/**
 *  Title:  11-8UVa11082
 *  Author: InvisibleMan
 *  Date:   2018/6/19
 */

#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

const int Nmax = 20;
const int Src = Nmax << 1;
const int Dst = Src + 1;
int cp[Dst + 1][Dst + 1], f[Dst + 1][Dst + 1];

void EdmonsKarp() {
    queue<int> q;
    int add[Dst + 1], p[Dst + 1];
    while(1) {
        memset(add, 0, sizeof(add));
        q.push(Src);
        add[Src] = 1e9;
        while(!q.empty() && !add[Dst]) {
            int now = q.front(); q.pop();
            for(int i = 0; i < Dst + 1; i++) {
                if(!add[i] && cp[now][i] > f[now][i]) {
                    add[i] = min(add[now], cp[now][i] - f[now][i]);
                    p[i] = now;
                    if(add[i]) q.push(i);
                }
            }
        }
        if(add[Dst] == 0) break;
        for(int i = Dst; i != Src;) {
            int pi = p[i];
            f[pi][i] += add[Dst];
            f[i][pi] -= add[Dst];
            i = pi;
        }
    }
}

int main() {
    int kase; 
    scanf("%d", &kase);
    for(int k = 0; k < kase;) {
        printf("Matrix %d\n", ++k);
        int n, m, t;
        memset(cp, 0, sizeof(cp));
        memset(f, 0, sizeof(f));
        scanf("%d%d", &n, &m);
        int last = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &t);
            cp[Src][i] = t - m - last;
            for(int j = Nmax; j < Nmax + m; j++)
                cp[i][j] = 19;
            last = t;
        }
        last = 0;
        for(int i = 0; i < m; i++) {
            scanf("%d", &t);
            cp[Nmax + i][Dst] = t - n - last;
            last = t;
        }
        EdmonsKarp();
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++)
                printf("%d ", f[i][Nmax + j] + 1);
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
