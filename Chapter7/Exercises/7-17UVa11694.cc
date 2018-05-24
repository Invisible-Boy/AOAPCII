/**
 * Title:   7-17UVa11694
 * Author:  InvisibleMan
 * Date:    2017-2-28
 * Time:    30ms
 */

#include <cstdio>
#include <cstring>

using namespace std;

const int dx[] = {1, 1};
const int dy[] = {-1, 1};
int g[8][8], n, vis[8][8];
bool edge[8][8][2];
int aimx, aimy;

bool findPath(int x, int y, int fx, int fy) {
    for(int i = 0; i < 2; i++) {
        int nx, ny;
        if(edge[x][y][i]) {
            nx = x + dx[i], ny = y + dy[i];
            if((nx != fx || ny != fy) && nx >= 0 && nx <= n && ny >= 0 && ny <= n) {
                if(nx == aimx && ny == aimy) return true;
                if(findPath(nx, ny, x, y)) return true;
            }
        }
        nx = x - dx[i], ny = y - dy[i];
        if((nx != fx || ny != fy) && nx >= 0 && nx <= n && ny >= 0 && ny <= n) {
            if(edge[nx][ny][i]) {
                if(nx == aimx && ny == aimy) return true;
                if(findPath(nx, ny, x, y)) return true;
            }
        }
    }
    return false;
}

bool isok(int x, int y, int step) {
    int nx = x + dx[step], ny = y + dy[step];
    if(nx > n || ny > n || ny < 0) return false;
    if((g[x][y] >= 0 && vis[x][y] + 1 > g[x][y]) || (g[nx][ny] >= 0 && vis[nx][ny] + 1 > g[nx][ny]))
        return false;
    if((step || y == n) && (g[x][y] > 0 && vis[x][y] + 1 != g[x][y])) return false;
    if(step && y == n - 1 && g[x][n] >= 0 && vis[x][n] != g[x][n]) return false;
    if(step && x == n - 1 && g[n][y] >= 0 && vis[n][y] != g[n][y]) return false;
    if(!step && x == n - 1 && g[nx][ny] >= 0 && vis[nx][ny] + 1 != g[nx][ny]) return false;
    aimx = x, aimy = y;
    return !findPath(nx, ny, x, y);
}

bool dfs(int x, int y) {
    if(x == n - 1 && y == n - 1) {
        if(isok(x, y, 1) && (g[n][n] < 0 || g[n][n] == 1)) {
            edge[x][y][1] = true;
            return true;
        }
        if((g[x][y] < 0 || vis[x][y] == g[x][y])
           && isok(x, ++y, 0) 
           && g[n][n] <= 0) {
            edge[x][y][0] = true;
            return true;
        }
        return false;
    }
    if(isok(x, y, 1)) {
        int nx = x + 1, ny = y + 1;
        edge[x][y][1] = true;
        vis[x][y]++, vis[nx][ny]++;
        if(dfs(x + (y + 1) / n, (y + 1) % n)) return true;
        edge[x][y][1] = false;
        vis[x][y]--, vis[nx][ny]--;
    }
    if((g[x][y] < 0 || vis[x][y] == g[x][y]) && isok(x, ++y, 0)) {
        int nx = x + 1, ny = y - 1;
        edge[x][y][0] = true;
        vis[x][y]++, vis[nx][ny]++;
        if(dfs(x + y / n, y % n)) return true;
        edge[x][y][0] = false;
        vis[x][y]--, vis[nx][ny]--;
    }
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    for(int t = 0; t < T; t++) {
        scanf("%d\n", &n);
        memset(edge, false, sizeof(edge));
        memset(vis, 0, sizeof(vis));
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= n; j++)
                g[i][j] = getchar() - '0';
            getchar();
        }
        dfs(0, 0);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j <= n; j++) {
                if(edge[i][j][0]) printf("/");
                if(edge[i][j][1]) printf("\\");
            }
            printf("\n");
        }
    }
    return 0;
}
