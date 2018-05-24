/**
 *  Title:  9-1UVa10285
 *  Author: InvisibleMan
 *  Date:   2018-3-19
 *  Time:   20ms
 */

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

const int Nmax = 105;
const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
int r, c, data[Nmax][Nmax], dp[Nmax][Nmax], ans;

bool check(int x, int y, int now) {
    return x > -1 && x < r && y > -1 && y < c && now > data[x][y];
}

int dfs(int x, int y) {
    int &tans = dp[x][y], now = data[x][y];
    if(tans > -1) return tans;
    tans = 1;
    for(int i = 0; i < 4; i++)
        if(check(x + dx[i], y + dy[i], now)) tans = max(tans, dfs(x + dx[i], y + dy[i]) + 1);
    ans = max(ans, tans);
    return tans;
}

int main() {
    int kase;
    cin >> kase;
    while(kase--) {
        string name;
        cin >> name >> r >> c;
        for(int i = 0; i < r; i++)
            for(int j = 0; j < c; j++) {
                cin >> data[i][j];
                dp[i][j] = -1;
            }
        ans = -1;
        for(int i = 0; i < r; i++)
            for(int j = 0; j < c; j++)
                if(dp[i][j] < 0) dfs(i, j);
        cout << name << ": " << ans << endl;
    }
    return 0;
}
