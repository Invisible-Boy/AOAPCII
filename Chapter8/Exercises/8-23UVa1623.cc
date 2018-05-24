/**
 * Title:   8-23UVa1623
 * Author:  InvisibleMan
 * Date:    2017-5-23
 * Time:    460ms
 */

#include <cstdio>
#include <map>

using namespace std;

const int Nmax = 1e6 + 5;

int main() {
    int T, n, m, ans[Nmax], vis[Nmax];
    bool flag;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        flag = true;
        // 使用一个map记录map[可以喝水的日子] = 第几个可以喝水的日子
        map<int, int> mp;
        int q = 0, t;
        for(int i = 1; i <= n; i++) vis[i] = -1;
        for(int i = 0; i < m; i++) {
            scanf("%d", &t);
            if(flag) {
                if(t == 0) mp[i] = q, ans[q++] = 0;
                else {
                    int lt = vis[t];
                    // 查找从上一次t湖水满到现在，是否有可以喝水的日子,并且尽量使用前面的日子（贪心）
                    map<int, int>::iterator p = mp.upper_bound(lt);
                    if(p != mp.end()) {
                        ans[p->second] = t;
                        mp.erase(p);
                    }
                    else flag = false;
                    vis[t] = i;
                }
            }
        }
        if(flag) {
            printf("YES\n%d", ans[0]);
            for(int i = 1; i < q; i++)
                printf(" %d", ans[i]);
        }
        else printf("NO");
        printf("\n");
    }
    return 0;
}
