/**
 * Title:   7-2UVa225-2
 * Author:  InvisibleMan
 * Data:    2017-1-6
 * Time:    140ms
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

const int Nmax = 222, O = 105;   // 优化点
const char dir[] = {'e', 'n', 's', 'w'};
const int dx[] = {1, 0, 0, -1};
const int dy[] = {0, 1, -1, 0};
const int edge[4][2] = {{1, 2}, {0, 3}, {0, 3}, {1, 2}};
int n, numW, sum[21];
char way[21];
bool vis[Nmax][Nmax], ban[Nmax][Nmax];

void print() {
    for(int i = 1; i < n; i++)
        printf("%c", way[i]);
}

bool isok(int nowx, int nowy, int nn, int d) {
    for(int i = 1; i <= nn; i++)
        if(ban[nowx + dx[d] * i + O][nowy + dy[d] * i + O]) return false;
    return true;
}

void dfs(int nn, int d, int nowx, int nowy) {
    if(nn == n) {
        if(!nowx && abs(nowy) == n && d != 1 && d != 2) {
            for(int i = 1; i < 3; i++)
                if(!(nowy + dy[i] * n) && isok(nowx, nowy, n, i)) {
                    print();
                    printf("%c\n", dir[i]);
                    numW++;
                    break;
                }
        }
        else if(!nowy && abs(nowx) == n && d != 0 && d != 3) {
            for(int i = 0; i < 5; i += 3)
                if(!(nowx + dx[i] * n) && isok(nowx, nowy, n, i)) {
                    print();
                    printf("%c\n", dir[i]);
                    numW++;
                    break;
                }
        }
        return;
    }
    for(int i = 0; i < 2; i++) {
        int dd = edge[d][i];
        way[nn] = dir[dd];
        if(isok(nowx, nowy, nn, dd)) {
            int nextx = nowx + dx[dd] * nn;
            int nexty = nowy + dy[dd] * nn;
            if(abs(nextx) + abs(nexty) <= sum[n] - sum[nn] && !vis[nextx + O][nexty + O]) {   // 优化点
                vis[nextx + O][nexty + O] = true;
                dfs(nn + 1, dd, nextx, nexty);
                vis[nextx + O][nexty + O] = false;
            }
        }
    }
}

int main() {
    int num;
    memset(vis, 0, sizeof(vis));
    vis[O][O] = true;
    scanf("%d", &num);
    sum[0] = 0;
    for(int i = 1; i < 21; i++) // 优化点
        sum[i] = sum[i - 1] + i;
    for(int j = 0; j < num; j++) {
        int m;
        numW = 0;
        memset(ban, 0, sizeof(ban));
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; i++) {
            int tx, ty;
            scanf("%d%d", &tx, &ty);
            if(tx < Nmax && ty < Nmax) // 优化点
                ban[tx + O][ty + O] = true;
        }
        if(n < 7) {
            printf("Found 0 golygon(s).\n\n");
            continue;
        }
        for(int i = 0; i < 4; i++) {
           way[1] = dir[i];
           if(ban[dx[i] + O][dy[i] + O]) continue;
           dfs(2, i, dx[i], dy[i]);
        }
        printf("Found %d golygon(s).\n\n", numW);
    }
    return 0;
}
