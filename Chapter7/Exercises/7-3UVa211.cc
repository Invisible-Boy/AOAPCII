/**
 * Title:   7-3UVa211
 * Author:  InvisibleMan
 * Data:    2017-1-12
 * Time:    20ms
 */

// tips：注意看清题目的要求，是两片多米诺骨片，组成一个骨牌！

#include <cstdio>
#include <cstring>

using namespace std;

const int Nmax = 29, Rmax = 7, Cmax = 8;
const int dx[] = {0, 1}, dy[] = {1, 0};
const int state[7][7] = {
                            {1, 2, 3, 4, 5, 6, 7},
                            {2, 8, 9, 10, 11, 12, 13},
                            {3, 9, 14, 15, 16, 17, 18},
                            {4, 10, 15, 19, 20, 21, 22},
                            {5, 11, 16, 20, 23, 24, 25},
                            {6, 12, 17, 21, 24, 26, 27},
                            {7, 13, 18, 22, 25, 27, 28}
                        };
int data[Rmax][Cmax], ans[Rmax][Cmax], ansN;
bool vis[Nmax], gvis[Rmax][Cmax];

bool read() {
    for(int i = 0; i < Rmax; i++)
        for(int j = 0; j < Cmax; j++)
            if(scanf("%d", &data[i][j]) != 1) return false;
    return true;
}

void print(int data[][Cmax]) {
    for(int i = 0; i < Rmax; i++) {
        for(int j = 0; j < Cmax; j++)
            printf("%4d", data[i][j]);
        printf("\n");
    }
    printf("\n");
}

void dfs(int xx, int yy) {
    if(gvis[xx][yy]) {
        if(yy + 1 < Cmax) return dfs(xx, yy + 1);
        else return dfs(xx + 1, 0);
    }
    if(xx >= Rmax) {
        print(ans);
        printf("\n");
        ansN++;
        return;
    }
    gvis[xx][yy] = true;
    int t1 = data[xx][yy];
    for(int i = 0; i < 2; i++) {
        int nextx = xx + dx[i];
        int nexty = yy + dy[i];
        if(nextx >= Rmax || nexty >= Cmax) continue;
        int t2 = data[nextx][nexty];
        int tg = state[t1][t2];
        if(vis[tg] || gvis[nextx][nexty]) continue;
        ans[xx][yy] = ans[nextx][nexty] = tg;
        vis[tg] = true;
        gvis[nextx][nexty] = true;
        if(nexty + 1 < Cmax) dfs(xx, nexty + 1);
        else dfs(xx + 1, 0);
        gvis[nextx][nexty] = false;
        vis[tg] = false;
    }
    gvis[xx][yy] = false;
}

int main() {
    memset(vis, 0, sizeof(vis));
    memset(gvis, 0, sizeof(gvis));
    int cnt = 0;
    while(read()) {
        if(cnt) printf("\n\n\n\n\n");
        ansN = 0;
        printf("Layout #%d:\n\n\n", ++cnt);
        print(data);
        printf("Maps resulting from layout #%d are:\n\n\n", cnt);
        dfs(0, 0);
        printf("There are %d solution(s) for layout #%d.\n", ansN, cnt);
    }
    return 0;
}

