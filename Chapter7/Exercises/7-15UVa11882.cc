/**
 * Title:   7-15UVa11882
 * Author:  InvisibleMan
 * Date:    2017-2-25
 * Time:    350ms
 */

#include <cstdio>
#include <cstring>

using namespace std;

const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};
bool vis[15][15];
int g[15][15], r, c, ans[30], tAns[30], cnt, ansCnt, ansL[30][2], tAnsL[30][2];

bool init() {
    scanf("%d%d\n", &r, &c);
    if(!r || !c) return false;
    cnt = 0;
    ansCnt = 0;
    memset(vis, false, sizeof(vis));
    memset(ans, 0, sizeof(ans));
    char t;
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            t = getchar();
            if(t != '#') {
                g[i][j] = t - '0';
                cnt++;
            }
            else g[i][j] = 0;
        }
        getchar();
    }
    return true;
}

bool pass(int now, int li, int lj) {
    if(ansCnt == 0) return false;
    if(ansCnt == cnt) {
        int i;
        for(i = 0; i < now; i++)
            if(ans[i] > tAns[i]) return true;
            else if(ans[i] < tAns[i]) break;
        if(i == now && ans[now] > g[li][lj]) return true;
    }
    if(!now || ansL[now][0] != li || ansL[now][1] != lj) return false;
    for(int i = 0; i < now; i++) 
        if(!vis[ansL[i][0]][ansL[i][1]]) return false;
    for(int i = 0; i < now; i++) {
        if(ans[i] > tAns[i]) return true;
        else if(ans[i] < tAns[i]) {
            for(i = 0; i < now; i++) {
                ans[i] = tAns[i];
                ansL[i][0] = tAnsL[i][0];
                ansL[i][1] = tAnsL[i][1];
            }
        }
    }
    return true;
}

void dfs(int i, int j, int now) {
    if(pass(now, i, j)) return;
    vis[i][j] = true;
    tAns[now] = g[i][j];
    tAnsL[now][0] = i;
    tAnsL[now][1] = j;
    int newi, newj;
    bool flag = true;
    for(int k = 0; k < 4; k++) {
        newi = i + dx[k];
        newj = j + dy[k];
        if(newi < 0 || newi >= r || newj < 0 || newj >= c || vis[newi][newj] || !g[newi][newj]) continue;
        flag = false;
        dfs(newi, newj, now + 1);
    }
    if(flag) {
        if(now + 1 > ansCnt) {
            ansCnt = now + 1;
            for(int ii = 0; ii < ansCnt; ii++) {
                ans[ii] = tAns[ii];
                ansL[ii][0] = tAnsL[ii][0];
                ansL[ii][1] = tAnsL[ii][1];
            }
        }
        if(now + 1 == ansCnt) {
            for(int ii = 0; ii < ansCnt; ii++)
                if(ans[ii] > tAns[ii]) break;
                else if(ans[ii] < tAns[ii]) {
                    for(ii = 0; ii < ansCnt; ii++) {
                        ans[ii] = tAns[ii];
                        ansL[ii][0] = tAnsL[ii][0];
                        ansL[ii][1] = tAnsL[ii][1];
                    }
                }
        }
    }
    vis[i][j] = false;
}

int main() {
    while(init()) {
        for(int i = 0; i < r; i++)
            for(int j = 0; j < c; j++)
                if(g[i][j] && !vis[i][j])
                    dfs(i, j, 0);
        for(int i = 0; i < ansCnt; i++)
            printf("%d", ans[i]);
        printf("\n");
    }
    return 0;
}
