/**
 * Title:   7-12UVa1533
 * Author:  InvisibleMan
 * Date:    2017-2-20
 * Time:    30ms
 */

#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int StaMax = 1 << 15;
const int g[5][5] = {{1}, {2, 3}, {4, 5, 6}, {7, 8, 9, 10}, {11, 12, 13, 14, 15}};
const int id[16][2] = {{},{0, 0},{1, 0},{1, 1},{2, 0},{2, 1},{2, 2},{3, 0},{3, 1},{3, 2}
                      ,{3, 3},{4, 0},{4, 1},{4, 2},{4, 3},{4, 4}};
const int dx[6] = {-1, 0, -1, 1, 0, 1};
const int dy[6] = {-1, -1, 0, 0, 1, 1};
bool vis[StaMax];
int path[StaMax][2], fa[StaMax], cnt[StaMax];

bool judge(int id[2]) {
    return id[1] <= id[0] && id[0] > -1 && id[0] < 5 && id[1] > -1;
}

bool isok(int sta, int aim) {
    for(int i = 1; i < 16; i++)
        if(sta & (1 << (i - 1)) && i != aim) return false;
    return sta & (1 << (aim - 1));
}

int bfs(int n) {
    int nowSta = 0;
    for(int i = 1; i < 16; i++)
        if(i != n) nowSta |= 1 << (i - 1);
    vis[nowSta] = true;
    cnt[nowSta] = 0;
    fa[nowSta] = 0;
    queue<int> q;
    q.push(nowSta);
    while(!q.empty()) {
        nowSta = q.front();
        q.pop();
        for(int i = 1; i < 16; i++) {
            if(nowSta & (1 << (i - 1))) {
                int nowId[2] = {id[i][0], id[i][1]};
                for(int j = 0; j < 6; j++) {
                    int nextId[2] = {nowId[0] + dx[j], nowId[1] + dy[j]};
                    int nextSta = nowSta;
                    if(judge(nextId) && (nowSta & (1 << (g[nextId[0]][nextId[1]] - 1)))) {
                        nextSta &= ~(1 << (g[nextId[0]][nextId[1]] - 1));
                        nextId[0] = nextId[0] + dx[j];
                        nextId[1] = nextId[1] + dy[j];
                        while(judge(nextId)) {
                            if(nowSta & (1 << (g[nextId[0]][nextId[1]] - 1))) {
                                nextSta &= ~(1 << (g[nextId[0]][nextId[1]] - 1));
                                nextId[0] = nextId[0] + dx[j];
                                nextId[1] = nextId[1] + dy[j];
                            }
                            else {
                                nextSta |= (1 << (g[nextId[0]][nextId[1]] - 1));
                                nextSta &= ~(1 << (i - 1));
                                if(vis[nextSta]) break;
                                vis[nextSta] = true;
                                fa[nextSta] = nowSta;
                                cnt[nextSta] = cnt[nowSta] + 1;
                                path[nextSta][0] = i;
                                path[nextSta][1] = g[nextId[0]][nextId[1]];
                                if(isok(nextSta, n)) return nextSta;
                                q.push(nextSta);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void print(int sta) {
    if(fa[sta]) {
        print(fa[sta]);
        printf("%d %d ", path[sta][0], path[sta][1]);
    }
}

int main() {
    int T, n;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        memset(vis, false, sizeof(vis));
        int finalSta = bfs(n);
        if(finalSta) {
            printf("%d\n", cnt[finalSta]);
            print(fa[finalSta]);
            printf("%d %d\n", path[finalSta][0], path[finalSta][1]);
        }
        else printf("IMPOSSIBLE\n");
    }
    return 0;
}
