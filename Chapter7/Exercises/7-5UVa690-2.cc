/**
 * Title:   7-5UVa690-2
 * Author:  InvisibleMan
 * Date:    2017-1-30
 * Time:    110ms
 */

// tip：参考了网上的代码，使用位压缩状态，可以减少状态存储和返回所用的时间
// tip: 在virtual judge上还有一个代码与这个代码类似，但是一直WA,目前原因未知

#include <cstdio>
#include <cstring>

using namespace std;

int rese[5], n, ans, jump[21], cnt;

bool judge(int p[], int move) {
    for(int i = 0; i < 5; i++)
        if((p[i] << move) & rese[i]) return false;
    return true;
}

void init() {
    memset(rese, 0, sizeof(rese));
    char temp;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%c", &temp);
            if(temp == 'X') rese[i] |= (1 << j);
        }
        getchar();
    }
    ans = n * 9;
    cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(judge(rese, i))
            jump[cnt++] = i;
    }
}

void dfs(int p[], int now, int tAns) {
    if(now == 10) {
        for(int j = 0; j < cnt; j++)
            if(tAns + jump[j] < ans && judge(p, jump[j])) {
                ans = tAns + jump[j];
                return;
            }
        return;
    }
    int p1[5];
    for(int i = 0; i < cnt; i++) {
        if(tAns + jump[0] * (10 - now) + jump[i] > ans || !judge(p, jump[i])) continue;
        for(int j = 0; j < 5; j++)
            p1[j] = (p[j] << jump[i]) | rese[j];
        dfs(p1, now + 1, tAns + jump[i]);
    }
}

int main() {
    while(scanf("%d\n", &n) == 1 && n) {
        init();
        if(cnt > 1) {
            for(int i = 0; i < cnt; i++) {
                if(!judge(rese, jump[i])) continue;
                int p[5];
                for(int j = 0; j < 5; j++)
                    p[j] = (rese[j] << jump[i]) | rese[j];
                dfs(p, 3, jump[i]);
            }
        }
        printf("%d\n", ans + n);
    }
    return 0;
}
