/**
 * Title:   7-2UVa225
 * Author:  InvisibleMan
 * Data:    2017-1-6
 * Time:    1210ms
 */

// tips:题目隐含了同一个城市不能多次访问，因此需要记录访问过的城市的坐标

#include <cstdio>
#include <set>
#include <cstdlib>
#include <cstring>

using namespace std;

const int Nmax = 500;
const char dir[] = {'e', 'n', 's', 'w'};
const int dx[] = {1, 0, 0, -1};
const int dy[] = {0, 1, -1, 0};
const int edge[4][2] = {{1, 2}, {0, 3}, {0, 3}, {1, 2}};
struct postion {
    int mx, my;
    postion(int xx = 0, int yy = 0) : mx(xx), my(yy) {}
    bool operator < (const postion &rth) const {
        return mx < rth.mx || (mx == rth.mx && my < rth.my);
    }
};
int n, numW;
char way[21];
set<postion> ban;
bool vis[Nmax][Nmax];

void print() {
    for(int i = 1; i < n; i++)
        printf("%c", way[i]);
}

bool isok(postion &now, int nn, int d) {
    for(int i = 1; i <= nn; i++)
        if(ban.count(postion(now.mx + dx[d] * i, now.my + dy[d] * i))) return false;
    return true;
}

void dfs(int nn, int d, postion now) {
    if(nn == n) {
        if(!now.mx && abs(now.my) == n && d != 1 && d != 2) {
            for(int i = 1; i < 3; i++)
                if(!(now.my + dy[i] * n) && isok(now, n, i)) {
                    print();
                    printf("%c\n", dir[i]);
                    numW++;
                    break;
                }
        }
        else if(!now.my && abs(now.mx) == n && d != 0 && d != 3) {
            for(int i = 0; i < 5; i += 3)
                if(!(now.mx + dx[i] * n) && isok(now, n, i)) {
                    print();
                    printf("%c\n", dir[i]);
                    numW++;
                    break;
                }
        }
        return;
    }
    for(int i = 0; i < 2; i++) {
        int dd = edge[d][i];
        way[nn] = dir[dd];
        if(isok(now, nn, dd)) {
            postion next(now.mx + dx[dd] * nn, now.my + dy[dd] * nn);
            if(!vis[next.mx + 250][next.my + 250]) {
                vis[next.mx + 250][next.my + 250] = true;
                dfs(nn + 1, dd, next);
                vis[next.mx + 250][next.my + 250] = false;
            }
        }
    }
}

int main() {
    int num;
    memset(vis, 0, sizeof(vis));
    vis[250][250] = true;
    scanf("%d", &num);
    for(int j = 0; j < num; j++) {
        int m;
        numW = 0;
        ban.clear();
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; i++) {
            int tx, ty;
            scanf("%d%d", &tx, &ty);
            ban.insert(postion(tx, ty));
        }
        if(n < 7) {
            printf("Found 0 golygon(s).\n\n");
            continue;
        }
        for(int i = 0; i < 4; i++) {
           way[1] = dir[i];
           if(ban.count(postion(dx[i], dy[i]))) continue;
           dfs(2, i, postion(dx[i], dy[i]));
        }
        printf("Found %d golygon(s).\n\n", numW);
    }
    return 0;
}
