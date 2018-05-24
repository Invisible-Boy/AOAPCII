/**
 * Title:   7-6UVa12113
 * Author:  InvisibleMan
 * Date:    2016-2-3
 * Time:    10ms
 */

#include <cstdio>
#include <cstring>

using namespace std;

char row[5], col[5];
bool vis[9];

bool init() {
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    char temp;
    scanf("%c", &temp);
    if(temp == '0') return false;
    for(int j = 1; j < 9; j++) {
        scanf("%c", &temp);
        if(temp == '_') row[0] |= 1 << ((j - 1) >> 1);
    }
    getchar(); getchar();
    for(int i = 1; i < 5; i++) {
        for(int j = 0; j < 9; j++) {
            scanf("%c", &temp);
            if(temp == '_') row[i] |= 1 << ((j - 1) >> 1);
            else if(temp == '|') col[j >> 1] |= 1 << (i - 1);
        }
        getchar(); getchar();
    }
    return true;
}

bool judge(char tRow[], char tCol[]) {
    for(int i = 0; i < 5; i++)
        if(row[i] != tRow[i] || col[i] != tCol[i])
            return false;
    return true;
}

bool dfs(int now, char tRow[], char tCol[]) {
    if(judge(tRow, tCol)) return true;
    if(now == 6) return false;
    char ttRow[5] = {0};
    char ttCol[5] = {0};
    for(int i = 0; i < 9; i++)
        if(!vis[i]) {
            vis[i] = true;
            for(int j = 0; j < 5; j++)
                ttRow[j] = tRow[j], ttCol[j] = tCol[j];
            int numRow = i / 3;
            int numCol = i % 3;
            ttRow[numRow] |= 3 << numCol;
            ttRow[numRow + 2] |= 3 << numCol;
            ttCol[numCol] |= 3 << numRow;
            ttCol[numCol + 2] |= 3 << numRow;
            ttRow[numRow + 1] &= ~(3 << numCol);
            ttCol[numCol + 1] &= ~(3 << numRow);
            if(dfs(now + 1, ttRow, ttCol))
                return true;
            vis[i] = false;
        }
    return false;
}

int main() {
    int cnt = 0;
    char tRow[5] = {0};
    char tCol[5] = {0};
    while(init()) {
        memset(vis, 0, sizeof(vis));
        printf("Case %d: %s\n", ++cnt, dfs(0, tRow, tCol) ? "Yes" : "No");
    }
    return 0;
}
