/**
 * Title:   7-5UVa690-2
 * Author:  InvisibleMan
 * Date:    2017-1-31
 * Time:    90ms
 */

// tip：参考了网上的代码，使用位压缩状态，可以减少状态存储和返回所用的时间

#include <cstdio>
#include <cstring>

using namespace std;

int rese[5], n, ans, jump[21], cnt;

bool judge(int p1, int p2, int p3, int p4, int p5) {
    return !(p1 & rese[0]) && !(p2 & rese[1]) && !(p3 & rese[2]) && !(p4 & rese[3]) && !(p5 & rese[4]);
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
        if(judge(rese[0] << i, rese[1] << i, rese[2] << i, rese[3] << i, rese[4] << i))
            jump[cnt++] = i;
    }
}

void dfs(int p[], int now, int tAns) {
    if(now == 10) {
        for(int j = 0; j < cnt; j++)
            if(tAns + jump[j] < ans && judge(p[0] << jump[j], p[1] << jump[j], p[2] << jump[j], p[3] << jump[j], p[4] << jump[j])) {
                ans = tAns + jump[j];
                return;
            }
        return;
    }
    int p1[5];
    for(int i = 0; i < cnt; i++) {
        if(tAns + jump[0] * (10 - now) + jump[i] > ans || !judge(p[0] << jump[i], p[1] << jump[i], p[2] << jump[i], p[3] << jump[i], p[4] << jump[i])) continue;
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
                if(!judge(rese[0] << jump[i], rese[1] << jump[i], rese[2] << jump[i], rese[3] << jump[i], rese[4] << jump[i])) continue;
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
