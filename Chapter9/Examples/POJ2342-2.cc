/**
 * Title:   POJ2342-2
 * Author:  InvisibleMan
 * Date:    2017-7-6
 * Time:    157ms
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int Nmax = 6005;
int n, value[Nmax], ans[Nmax][2], p[Nmax];
vector<int> son[Nmax];
void dfs(int now) {
    int chNum = son[now].size();
    if(chNum > 0)
        for(int i = 0; i < chNum; i++)
            dfs(son[now][i]);
    int nowP = p[now], add = max(ans[now][0], ans[now][1]);
    if(nowP > -1 && add > 0) {
        ans[nowP][1] += add;
        nowP = p[nowP];
        if(nowP > -1)
            ans[nowP][0] += add;
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &value[i]);
        ans[i][0] = value[i] > 0 ? value[i] : 0;
        ans[i][1] = 0;
        //son[i].reserve(n);  如果提前分配会TLE
    }
    memset(p, -1, sizeof(p));
    for(int i = 1; i < n; i++) {
        int t1, t2;
        scanf("%d%d", &t1, &t2); t1--, t2--;
        son[t2].push_back(t1);
        p[t1] = t2;
    }
    int i; for(i = 0; i < n; i++)
        if(p[i] < 0) {
            dfs(i);
            break;
        }
    printf("%d\n", max(ans[i][0], ans[i][1]));
    return 0;
}
