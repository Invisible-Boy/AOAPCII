/**
 * Title:   7-11UVa12569
 * Author:  InvisibleMan
 * Date:    2017-2-18
 * Time:    ms
 */

/** 
 * tips: 参考了网上的代码，最开始的代码把每个状态看作一个整体，
 * 在内部记录走过的所有路径，运算时间很长。在网上的代码中，
 * 采用了和例题7-8相同的思路，使用数组记录所有的状态，并使用一个
 * fa[]数组，记录各个状态之间的关系，相当于建立了一个隐式链表，
 * 从而记录出所有的路径，最后通过递归输出所求的路径。
 */
 
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int StaMax = 1 << 19;
int n, m, ob[15], t, cnt[StaMax], fa[StaMax], path[StaMax][2];
bool vis[StaMax], edge[16][16];

bool move(int s, int d, int nowSta, int &newSta) {
    if(!edge[s][d] || (nowSta & (1 << (d - 1)))) return false;
    newSta = nowSta & ~(1 << (s - 1));
    newSta |= 1 << (d - 1);
    newSta &= (1 << 15) - 1;
    newSta |= d << 15;
    if(vis[newSta]) return false;
    vis[newSta] = true;
    fa[newSta] = nowSta;
    cnt[newSta] = cnt[nowSta] + 1;
    path[newSta][0] = s;
    path[newSta][1] = d;
    return true;
}

int bfs() {
    int nowSta = ob[0] << 15;
    for(int i = 0; i <= m; i++)
        nowSta |= 1 << (ob[i] - 1);
    vis[nowSta] = true;
    cnt[nowSta] = 0;
    fa[nowSta] = 0;
    queue<int> q;
    q.push(nowSta);
    while(!q.empty()) {
        nowSta = q.front();
        q.pop();
        int s = nowSta >> 15;
        int newSta;
        if(move(s, t, nowSta, newSta))
            return newSta;
        for(int i = 1; i <= n; i++) {
            if(move(s, i, nowSta, newSta))
                q.push(newSta);
        }
        for(int i = 1; i <= n; i++) {
            if(i == s) continue;
            if(nowSta & (1 << (i - 1)))
                for(int j = 1; j <= n; j++) {
                    if(j != s && edge[i][j] && !(nowSta & (1 << (j - 1)))) {
                        newSta = nowSta & ~(1 << (i - 1));
                        newSta |= 1 << (j - 1);
                        if(vis[newSta]) continue;
                        vis[newSta] = true;
                        fa[newSta] = nowSta;
                        cnt[newSta] = cnt[nowSta] + 1;
                        path[newSta][0] = i;
                        path[newSta][1] = j;
                        q.push(newSta);
                    }
                }
        }
    }
    return 0;
}

void print(int sta) {
    if(fa[sta] > 0) {
        print(fa[sta]);
        printf("%d %d\n", path[sta][0], path[sta][1]);
    }

}

int main() {
    int T;
    scanf("%d", &T);
    cnt[0] = -1, cnt[1] = 0;
    fa[0] = fa[1] = -1;
    for(int i = 1; i <= T; i++) {
        scanf("%d%d%d%d", &n, &m, &ob[0], &t);
        memset(edge, false, sizeof(edge));
        for(int i = 1; i <= m; i++)
            scanf("%d", &ob[i]);
        for(int i = 1; i < n; i++) {
            int t1, t2;
            scanf("%d%d", &t1, &t2);
            edge[t1][t2] = edge[t2][t1] = true;
        }
        int finalSta = 0;
        if(ob[0] == t) finalSta = 1;
        else {
            memset(vis, false, sizeof(vis));
            finalSta = bfs();
        }
        printf("Case %d: %d\n", i, cnt[finalSta]);
        if(fa[finalSta] > 0)
            print(finalSta);
    }
    return 0;
}
