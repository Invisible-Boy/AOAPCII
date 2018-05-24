/**
 * Title:   7-10UVa11214-2
 * Author:  InvisibleMan
 * Date:    2017-2-16
 * Time:    180ms
 */

/**
 * tips: 在第一个版本中采用放置queue然后改变棋盘策略的方式，这样回溯的时候需要恢复棋盘，
 * 同时在改变棋盘的时候，需要将所有的横竖对角线都清楚，很复杂。
 * 在新的策略中，只是记录放置皇后之后，哪些横竖对角线被防守，不是真正的去改变棋盘，
 * 代码更加简洁且高效。
 */

#include <cstdio>
#include <cstring>

using namespace std;

bool sta[9][9], vis[4][18]; // vis用来存储横、竖、斜、反斜线是否已经有quue进行防守
int n, m, ans;

bool init() {
    scanf("%d%d\n", &n, &m);
    if(!n || !m) return false;
    memset(sta, false, sizeof(sta));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            if(getchar() == 'X') sta[i][j] = true;
        getchar();
    }
    return true;
}

bool judge() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(sta[i][j] && !vis[0][i] && !vis[1][j] && !vis[2][i + j] && !vis[3][9 + i - j]) return false;
    return true;
}

bool dfs(int now, int i, int j) {
    if(now == ans) return judge();
    while(i < n) {
        while(j < m) {
            bool s[4] = {vis[0][i], vis[1][j], vis[2][i + j], vis[3][9 + i - j]};
            vis[0][i] = vis[1][j] = vis[2][i + j] = vis[3][9 + i - j] = true;
            if(dfs(now + 1, i, j + 1)) return true;
            vis[0][i] = s[0];
            vis[1][j] = s[1];
            vis[2][i + j] = s[2];
            vis[3][9 + i - j] = s[3];
            j++;
        }
        j = 0, i++;
    }
    return false;
}

int main() {
    int cnt = 0;
    while(init()) {
        for(ans = 0; ans < 5; ans++) {
            memset(vis, false, sizeof(vis));
            if(dfs(0, 0, 0)) break;
        }
        printf("Case %d: %d\n", ++cnt, ans);
    }
    return 0;
}
