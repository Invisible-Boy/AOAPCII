/**
 * Title:   9-23UVa1204-2
 * Author:  InvisibleMan
 * Date:    2018-1-25
 * Time:    180ms
 */
#include <memory.h>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool cmp(const string &lhs, const string &rhs) {
    return lhs.length() < rhs.length();
}

int calOverlay(const string &lhs, const string &rhs) {
    int n = lhs.length(), m = rhs.length();
    for(int i = 1; i < m; i++) {
        if(i + n <= m) continue;
        int t1 = 0, t2 = i;
        while(t2 < m && lhs[t1] == rhs[t2]) t1++, t2++;
        if(t2 == m) return m - i;
    }
    return 0;
}

const int Nmax = 16;

int ans[1 << Nmax][Nmax][2], cost[Nmax][Nmax][2][2], len[Nmax];
string temp[Nmax], str[Nmax][2];

inline void update(int &lhs, int rhs) {
    if(lhs < 0 || lhs > rhs) lhs = rhs;
}

int main() {
    int n;
    while((cin >> n) && n) {
        int cnt = 0;
        for(int i = 0; i < n; i++)
            cin >> temp[i];
        sort(temp, temp + n, cmp);
        for(int i = 0; i < n; i++) {
            bool flag = true;
            str[cnt][0] = temp[i];
            reverse(temp[i].begin(), temp[i].end());
            len[cnt] = temp[i].length();
            str[cnt][1] = temp[i];
            for(int j = i + 1; j < n && flag; j++)
                flag = temp[j].find(str[cnt][0]) == string::npos && temp[j].find(str[cnt][1]) == string::npos;
            cnt += flag ? 1 : 0;
        }
        for(int i = 0; i < cnt; i++)
            for(int j = 0; j < cnt; j++)
                for(int k = 0; k < 2; k++)
                    for(int l = 0; l < 2; l++)
                        cost[i][j][k][l] = calOverlay(str[i][k], str[j][l]);
        memset(ans, -1, sizeof(ans));
        int full = (1 << cnt) - 1;
        ans[1][0][0] = len[0];
        for(int i = 1; i < full; i++) {
            for(int j = 0; j < cnt; j++) {
                for(int k = 0; k < 2; k++) {
                    if(ans[i][j][k] < 0) continue;
                    for(int l = 1; l < cnt; l++) {
                        if(!(i & (1 << l)))
                        for(int m = 0; m < 2; m++)
                            update(ans[i | (1 << l)][l][m], ans[i][j][k] + len[l] - cost[l][j][m][k]);
                    }
                }
            }
        }
        int answer = -1;
        for(int i = 0; i < cnt; i++)
            for(int k = 0; k < 2; k++)
                if(ans[full][i][k] > -1)
                    update(answer, ans[full][i][k] - cost[0][i][0][k]);
        cout << (answer > 2 ? answer : 2) << endl;
    }
    return 0;
}
