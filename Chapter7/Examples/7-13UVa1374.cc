/**
 * Title:   7-13UVa1374
 * Author:  InvisibleMan
 * Data:    2017-1-3
 * Time:    ms
 */

// tips: IDA*

#include <cstdio>
#include <cstring>

using namespace std;

const int Nmax = 10001;
int aim, temp[Nmax];
bool vis[Nmax];

bool dfs(int deep, int Dmax, int begin, int end) {
    int tMax = 0;
    for(int i = 0; i < end; i++)
        if(temp[i] > tMax) tMax = temp[i];
    if(tMax << (Dmax - deep) < aim) return false;
    if(deep == Dmax - 1) {
        for(int i = 0; i < end; i++) {
            int tt = aim - temp[i];
            if(tt < 0) tt = -tt;
            if(vis[tt])
                return true;
        }
        return false;
    }
    for(int i = begin; i < end; i++)
        for(int j = 0; j < end; j++) {
            int t1 = temp[i] + temp[j];
            int t2 = temp[i] - temp[j];
            if(t2 < 0) t2 = -t2;
            if(t1 < Nmax && !vis[t1]) {
                temp[end] = t1;
                vis[t1] = true;
                if(dfs(deep + 1, Dmax, end, end + 1)) return true;
                vis[t1] = false;
            }
            if(t2 < Nmax && !vis[t2]) {
                temp[end] = t2;
                vis[t2] = true;
                if(dfs(deep + 1, Dmax, end, end + 1)) return true;
                vis[t2] = false;
            }
        }
    return false;
}

int main() {
    freopen("ans", "w", stdout);
    temp[0] = 1;
    int cnt = 0;
    while(scanf("%d", &aim) == 1 && aim) {
        if(aim == 1) printf("0\n");
        else {
            memset(vis, 0, sizeof(vis));
            vis[1] = true;
            for(int i = 0; ; i++)
                if(dfs(0, i, 0, 1)) {
                    printf("%2d, ", i);
                    cnt++;
                    if(cnt % 25 == 0) printf("\n"); 
                    break;
                }
        }
    }
    return 0;
}
