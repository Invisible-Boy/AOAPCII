/**
 * Title:   7-18UVa10384
 * Author:  InvisibleMan
 * Date:    2017-3-1
 * Time:    0ms
 */

#include <cstdio>
#include <cstdlib>

using namespace std;

const int Nmax = 1000;
char ans[Nmax];
int fin[20], finNum, cnt;

int find(int x, int y) {
    int ans = 1000;
    for(int i = 0; i < finNum; i++) {
        int aimx = fin[i] / 6, aimy = fin[i] % 6;
        int t = abs(aimx - x) + abs(aimy - y);
        if(t < ans) ans = t;
    }
    return ans;
}

bool dfs(int x, int y, int sta1, int sta2, int vis, int now) {
    if(now == cnt)
        return x < 0 || x > 3 || y < 0 || y > 5;
    if(find(x, y) + now + 1 > cnt) return false;
    
    if(!(sta1 & (1 << (x * 6 + y)))) {
        int nextVis = x * 6 + y;
        if((x - 1) * 6 + y != vis) {
            ans[now] = 'N';
            if(dfs(x - 1, y, sta1, sta2, nextVis, now + 1)) return true;
        }
    }
    else if(x > 0 && !(sta1 & (1 << ((x - 1) * 6 + y)))) {
        int nextSta1 = sta1 | (1 << ((x - 1) * 6 + y));
        nextSta1 &= ~(1 << (x * 6 + y));
        ans[now] = 'N';
        if(dfs(x - 1, y, nextSta1, sta2, 1000, now + 1)) return true;
    }
    
    if(!(sta1 & (1 << ((x + 1) * 6 + y)))) {
        int nextVis = x * 6 + y;
        if((x + 1) * 6 + y != vis) {
            ans[now] = 'S';
            if(dfs(x + 1, y, sta1, sta2, nextVis, now + 1)) return true;
        }
    }
    else if(x < 3 && !(sta1 & (1 << ((x + 2) * 6 + y)))) {
        int nextSta1 = sta1 | (1 << ((x + 2) * 6 + y));
        nextSta1 &= ~(1 << ((x + 1) * 6 + y));
        ans[now] = 'S';
        if(dfs(x + 1, y, nextSta1, sta2, 1000, now + 1)) return true;
    }

    if(!(sta2 & (1 << (y * 4 + x)))) {
        int nextVis = x * 6 + y;
        if(x * 6 + y - 1 != vis) {
            ans[now] = 'W';
            if(dfs(x, y - 1, sta1, sta2, nextVis, now + 1)) return true;
        }
    }
    else if(y > 0 && !(sta2 & (1 << ((y - 1) * 4 + x)))) {
        int nextSta2 = sta2 | (1 << ((y - 1) * 4 + x));
        nextSta2 &= ~(1 << (y * 4 + x));
        ans[now] = 'W';
        if(dfs(x, y - 1, sta1, nextSta2, 1000, now + 1)) return true;
    }
    
    if(!(sta2 & (1 << ((y + 1) * 4 + x)))) {
        int nextVis = x * 6 + y;
        if(x * 6 + y + 1 != vis) {
            ans[now] = 'E';
            if(dfs(x, y + 1, sta1, sta2, nextVis, now + 1)) return true;
        }
    }
    else if(y < 5 && !(sta2 & (1 << ((y + 2) * 4 + x)))) {
        int nextSta2 = sta2 | (1 << ((y + 2) * 4 + x));
        nextSta2 &= ~(1 << ((y + 1) * 4 + x));
        ans[now] = 'E';
        if(dfs(x, y + 1, sta1, nextSta2, 1000, now + 1)) return true;
    }
    return false;
}

int main() {
    int x, y;
    while(scanf("%d%d", &y, &x) == 2 && x && y) {
        int t, sta1 = 0, sta2 = 0;
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 6; j++) {
                scanf("%d", &t);
                if(t & 1) sta2 |= 1 << (j * 4 + i);
                if(t & 2) sta1 |= 1 << (i * 6 + j);
                if(t & 4) sta2 |= 1 << ((j + 1) * 4 + i);
                if(t & 8) sta1 |= 1 << ((i + 1) * 6 + j);
            }
        finNum = 0;
        for(int i = 0; i < 6; i++) {
            if(!(sta1 & (1 << i)))
                fin[finNum++] = i;
            if(!(sta1 & (1 << (24 + i))))
                fin[finNum++] = 18 + i;
        }
        for(int i = 0; i < 4; i++) {
            if(!(sta2 & (1 << i)))
                fin[finNum++] = i * 6;
            if(!(sta2 & (1 << (24 + i))))
                fin[finNum++] = i * 6 + 5;
        }
        cnt = 1;
        --x, --y;
        while(cnt < 1000) {
            if(dfs(x, y, sta1, sta2, 1000, 0)) break;
            cnt++;
        }
        for(int i = 0; i < cnt; i++)
            printf("%c", ans[i]);
        printf("\n");
    }
    return 0;
}
