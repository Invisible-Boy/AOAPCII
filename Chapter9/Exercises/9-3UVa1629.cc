/**
 *  Title:  9-3UVa1629
 *  Author: InvisibleMan
 *  Date:   2018/3/20
 */

#include <iostream>

inline int min(int t1, int t2) {
    return t1 < t2 ? t1 : t2;
}

using namespace std;

const int Nmax = 21;

int n, m, k, dp[Nmax][Nmax][Nmax][Nmax], cnt[Nmax][Nmax][Nmax][Nmax];

int count(int x1, int y1, int x2, int y2) {
    int &ans = cnt[x1][y1][x2][y2];
    if(ans > -1 || (x1 == x2 && y1 == y2)){
        if(ans == -1) ans = 0;
        return ans;
    }
    for(int i = x1 + 1; i <= x2; i++)
        ans = count(x1, y1, i - 1, y2) + count(i, y1, x2, y2);
    for(int i = y1 + 1; i <= y2; i++)
        ans = count(x1, y1, x2, i - 1) + count(x1, i, x2, y2);
    return ans;
}

int dfs(int x1, int y1, int x2, int y2) {
    int &ans = dp[x1][y1][x2][y2], cnow = count(x1, y1, x2, y2);
    if(cnow == 1) ans = 0;
    else if(cnow == 0) ans = 1e7; // 至少有一个樱桃
    if(ans > -1) return ans;
    ans = 1e7;
    for(int i = x1 + 1; i <= x2; i++)
        ans = min(ans, dfs(x1, y1, i - 1, y2) + dfs(i, y1, x2, y2) + y2 - y1 + 1);
    for(int i = y1 + 1; i <= y2; i++)
        ans = min(ans, dfs(x1, y1, x2, i - 1) + dfs(x1, i, x2, y2) + x2 - x1 + 1);
    return ans;
}

int main() {
    int kase = 1;
    while(cin >> n >> m >> k) {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                for(int ii = i; ii < n; ii++)
                    for(int jj = j; jj < m; jj++)
                        dp[i][j][ii][jj] = cnt[i][j][ii][jj] = -1;
        while(k--) {
            int t1, t2;
            cin >> t1 >> t2;
            t1--, t2--;
            cnt[t1][t2][t1][t2] = 1;
        }
        cout << "Case " << kase++ << ": " << dfs(0, 0, n - 1, m - 1) << endl;
    }
    return 0;
}
