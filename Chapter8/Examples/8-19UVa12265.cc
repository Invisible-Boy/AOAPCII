/**
 * Title:   8-19UVa12265
 * Author:  InvisibleMan
 * Date:    2017-4-2
 * Time:    40ms
 */

// tips: 使用一个单调栈来维护最大的h - c(思路详见紫书p251)

#include <cstdio>

using namespace std;

// 此处使用自己定义的数据结构会比pair<int, int>效率高10ms
struct Pair {
    int c, h;
    Pair(int _c = 0, int _h = 0) : c(_c), h(_h) {}
};

const int Nmax = 1001;

int T, n, m, h[Nmax], ans[Nmax << 1];
Pair sta[Nmax];
char d[Nmax][Nmax];

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++) scanf("%s", d[i]);
        for(int i = 0; i < m; i++) h[i] = 0;
        for(int i = 2; i <= n + m; i++) ans[i] = 0;
        for(int i = 0; i < n; i++) {
            int top = -1;
            for(int j = 0; j < m; j++) {
                if(d[i][j] == '#') {
                    h[j] = 0;
                    top = -1;
                }
                else {
                    Pair now = Pair(j, ++h[j]);
                    while(top > -1 && sta[top].h > h[j]) now.c = sta[top--].c;
                    while(top < 0 || now.h - now.c > sta[top].h - sta[top].c) sta[++top] = now;
                    ++ans[j - sta[top].c + 1 + sta[top].h];
                }
            }
        }
        for(int i = 2; i <= n + m; i++)
            if(ans[i] > 0) printf("%d x %d\n", ans[i], i << 1);
    }
    return 0;
}
