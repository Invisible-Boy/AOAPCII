/**
 * Title:   7-16UVa11846
 * Author:  InvisibleMan
 * Date:    2017-3-7
 * Time:    0ms
 */

/**
 * tips参考了网上的题解，在最初的版本中，采用记录lead位置，
 * 然后遍历所有lead可能的矩形，这样做会导致在遍历后面的lead时，
 * 前面出现空隙，在最后的时候才会剪枝，导致超时。
 * 在这个版本中，根据每个空位进行便利，可以保证在遍历x,y时，x,y的左上方
 * 不会出现空隙，全部都安排了位置，剪枝效果比之前的策略要好很多
 */


#include <cstdio>

using namespace std;

int n, k;
char g[26][26], ans[26][26];

void era(int x, int y, int dx, int dy) {
    for(int i = x; i < dx; i++)
        for(int j = y; j < dy; j++)
            ans[i][j] = '.';
}

void write(int x, int y, int dx, int dy, char c) {
    for(int i = x; i < dx; i++)
        for(int j = y; j < dy; j++)
            ans[i][j] = c;
}

bool dfs(int nx, int ny, char c) {
    if(nx >= n || ny >= n) return true;
    if(ans[nx][ny] != '.') return dfs(nx + (ny + 1) / n, (ny + 1) % n, c);
    for(int dx = nx; dx < n && dx < nx + 9; dx++)
        for(int dy = ny; dy < n; dy++) {
            int cnt = 0, now = -1, s = (dx - nx + 1) * (dy - ny + 1);
            if(s > 9) break;
            bool flag = false;
            for(int ii = nx; ii <= dx; ii++) {
                for(int jj = ny; jj <= dy; jj++) {
                    if(g[ii][jj] != '.')
                        cnt++, now = g[ii][jj] - '0';
                    if(ans[ii][jj] != '.') {
                        flag = true;
                        break;
                    }
                }
                if(cnt > 1 || flag || (now != -1 && now != s)) break;
            }
            if(cnt == 1 && flag == false && now == s) {
                write(nx, ny, dx + 1, dy + 1, c);
                if(dfs(nx + (dy + 1) / n, (dy + 1) % n, c + 1)) return true;
                era(nx, ny, dx + 1, dy + 1);
            }
        }
    return false;
}

int main() {
    while(scanf("%d%d\n", &n, &k) == 2 && n && k) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++)
                g[i][j] = getchar(), ans[i][j] = '.';
            getchar();
        }
        dfs(0, 0, 'A');
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++)
                printf("%c", ans[i][j]);
            printf("\n");
        }
    }
    return 0;
}
