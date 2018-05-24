/**
 * Title:   7-4UVa818
 * Author:  InvisibleMan
 * Date:    2017-1-26
 * Time:    10ms
 */

/**
 * tips:整体思路是IDA*架构，每次选中一些珠子断开，判断剩余的珠子是否都是单链, 
 * 同时单链的数目比单个珠子个数至多多1个。
 * 在网上的代码中，很多人使用了二进制枚举断开珠子的情况，而没有采用IDA*,这样 
 * 需要把所有的2^15种情况全部枚举结束才能知道知道需要解开最少的个数，这样的反
 * 而复杂度比IDA*要复杂。
 */

#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

const int Nmax = 16;
bool ban[Nmax], vis[Nmax], flag;
set<int> edge[Nmax];  // 题目给出的边的关系可能有重复的，所以要用set存储
int n, ans, ans1, nodeNum, edgeNum;

void dfs(int index) {
    int cnt = 0;
    for(set<int>::iterator iter = edge[index].begin(); iter != edge[index].end() && flag; iter++) {
        int next = *iter;
        if(!ban[next]) {
            cnt++;
            if(cnt > 2) flag = false;
            edgeNum++;
            if(!vis[next]) {
                vis[next] = true;
                nodeNum++;
                dfs(next);
            }
        }
    }
}

void isok() {
    ans1 = 0;
    flag = true;
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= n && flag; i++)
        if(!vis[i] && !ban[i]) {
            nodeNum = 1;
            edgeNum = 0;
            vis[i] = true;
            dfs(i);
            ans1++;
            if((edgeNum >> 1) + 1 > nodeNum) flag = false;
        }
}

bool BAN(int now, int index) {
    if(now == ans) {
        isok();
        if(flag && ans1 <= ans + 1) return true;
        else return false;
    }
    for(int i = index; i <= n; i++) {
        ban[i] = true;
        if(BAN(now + 1, i + 1)) return true;
        ban[i] = false;
    }
    return false;
}

int main() {
    int cnt = 0;
    while(scanf("%d", &n) == 1 && n) {
        int t1, t2;
        ans = 0;
        memset(ban, 0, sizeof(ban));
        for(int i = 1; i <= n; i++) edge[i].clear();
        while(scanf("%d%d", &t1, &t2) == 2 && t1 > 0) {
            edge[t1].insert(t2);
            edge[t2].insert(t1);
        }
        while(ans < n) {
            if(BAN(0, 1)) break;
            ans++;
        }
        printf("Set %d: Minimum links to open is %d\n", ++cnt, ans);
    }
    return 0;
}
