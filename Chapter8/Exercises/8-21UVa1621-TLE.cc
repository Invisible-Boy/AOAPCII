/**
 * Title:   8-21UVa1621
 * Author:  InvisibleMan
 * Date:    2017-5-14
 * Time:    TLE
 */

// 使用dfs莫名WA,感觉应该是RE或者TLE才对，目前原因未知
// 在UVaLive中是TLE,目测是UVa的评测机制出了问题

#include <cstdio>

using namespace std;

const int Nmax = 15000 + 5;
int aim, ans[Nmax];
bool vis[Nmax];

bool dfs(int a, int b, int c, int now, int i) {
    if(i == aim) return true;
    if(c > 0) {
        if(now + 3 <= aim && !vis[now + 3]) {
            vis[now + 3] = true;
            ans[i] = now + 3;
            if(dfs(a, b, c - 1, now + 3, i + 1)) return true;
            vis[now + 3] = false;
        }
        if(now - 3 > 0 && !vis[now - 3]) {
            vis[now - 3] = true;
            ans[i] = now - 3;
            if(dfs(a, b, c - 1, now - 3, i + 1)) return true;
            vis[now - 3] = false;
        }
    }
    if(b > 0) {
        if(now + 2 <= aim && !vis[now + 2]) {
            vis[now + 2] = true;
            ans[i] = now + 2;
            if(dfs(a, b - 1, c, now + 2, i + 1)) return true;
            vis[now + 2] = false;
        }
        if(now - 2 > 0 && !vis[now - 2]) {
            vis[now - 2] = true;
            ans[i] = now - 2;
            if(dfs(a, b - 1, c, now - 2, i + 1)) return true;
            vis[now - 2] = false;
        }
    }
    if(a > 0) {
        if(now + 1 <= aim && !vis[now + 1]) {
            vis[now + 1] = true;
            ans[i] = now + 1;
            if(dfs(a - 1, b, c, now + 1, i + 1)) return true;
            vis[now + 1] = false;
        }
        if(now - 1 > 0 && !vis[now - 1]) {
            vis[now - 1] = true;
            ans[i] = now - 1;
            if(dfs(a - 1, b, c, now - 1, i + 1)) return true;
            vis[now - 1] = false;
        }
    }
    return false;
}

int main() {
    int T;
    vis[0] = true;
    while(scanf("%d", &T) == 1) while(T--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        aim = a + b + c;
        printf("0");
        for(int i = 1; i <= aim; i++) vis[i] = false;
        dfs(a, b, c, 0, 0);
        for(int i = 0; i < aim; i++)
            printf(" %d", ans[i]);
        printf("\n");
    }
    return 0;
}
