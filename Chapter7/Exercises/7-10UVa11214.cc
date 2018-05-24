/**
 * Title:   7-10UVa11214
 * Author:  InvisibleMan
 * Date:    2017-2-16
 * Time:    ms
 */

#include <cstdio>
#include <cstring>

using namespace std;

int n, m, cnt;
bool sta[9][9];

bool init() {
    scanf("%d%d\n", &n, &m);
    if(!n || !m) return false;
    memset(sta, 0, sizeof(sta));
    cnt = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
           if(getchar() == 'X') cnt++, sta[i][j] = true;
        getchar();
    }
    return true;
}

int judge(int i, int j, bool s[][9]) {
    int nn = 0;
    for(int ii = 0; ii < n; ii++)
        if(s[ii][j]) nn++;
    for(int jj = 0; jj < m; jj++)
        if(s[i][jj]) nn++;
    for(int ii = i + 1, jj = j + 1; ii < n && jj < m; ii++, jj++)
        if(s[ii][jj]) nn++;
    for(int ii = i + 1, jj = j - 1; ii < n && jj > -1; ii++, jj--)
        if(s[ii][jj]) nn++;
    for(int ii = i - 1, jj = j - 1; ii > -1 && jj > -1; ii--, jj--)
        if(s[ii][jj]) nn++;
    for(int ii = i - 1, jj = j + 1; ii > -1 && jj < m; ii--, jj++)
        if(s[ii][jj]) nn++;
    return s[i][j] ? nn - 1 : nn;
}

void clear(int i, int j, bool s[][9]) {
    for(int ii = 0; ii < n; ii++)
        s[ii][j] = false;
    for(int jj = 0; jj < m; jj++)
        s[i][jj] = false;
    for(int ii = i + 1, jj = j + 1; ii < n && jj < m; ii++, jj++)
        s[ii][jj] = false;
    for(int ii = i + 1, jj = j - 1; ii < n && jj > -1; ii++, jj--)
        s[ii][jj] = false;
    for(int ii = i - 1, jj = j - 1; ii > -1 && jj > -1; ii--, jj--)
        s[ii][jj] = false;
    for(int ii = i - 1, jj = j + 1; ii > -1 && jj < m; ii--, jj++)
        s[ii][jj] = false;
}

bool dfs(int now, int deep, int ii, int jj, bool s[][9]) {
    if(now == deep) {
        return !cnt;
    }
    int i = ii, j = jj;
    for(; i < n; i++, j = 0)
        for(; j < m; j++) {
            int nn = judge(i, j, s);
            if(!nn) continue;
            cnt -= nn;
            bool ss[9][9];
            for(int i = 0; i < n; i++)
                for(int j = 0; j < m; j++)
                    ss[i][j] = s[i][j];
            clear(i, j, ss);
            if(dfs(now + 1, deep, i + (j + 1) / m, (j + 1) % m, ss)) return true;
            cnt += nn;
        }
    return false;
}

int main() {
    int T = 0;
    while(init()) {
        int i = 0;
        if(cnt) {
            for(i = 1; i < 5; i++)
                if(dfs(0, i, 0, 0, sta)) break;
        }
        printf("Case %d: %d\n", ++T, i);
    }
    return 0;
}
