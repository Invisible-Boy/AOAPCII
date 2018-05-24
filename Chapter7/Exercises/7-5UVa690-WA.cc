/**
 * Title:   7-5UVa690
 * Author:  InvisibleMan
 * Date:    2017-1-28
 * Time:    TLEms
 */

// tip: 在状态存储和返回花费了太多的时间

#include <cstdio>
#include <cstring>

using namespace std;

const int Nmax = 201;
bool used[5][Nmax], ban[21];
int n, ans, tAns, rese[5][20], num[5], jump;

bool judge() {
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < num[i]; j++)
            if(!used[i][tAns + rese[i][j]])
                used[i][tAns + rese[i][j]] = true;
            else {
                for(int ii = 0; ii < i; ii++)
                    for(int jj = 0; jj < num[ii]; jj++)
                        used[ii][tAns + rese[ii][jj]] = false;
                for(int jj = 0; jj < j; jj++) used[i][tAns + rese[i][jj]] = false;
                return false;
            }
    return true;
}

void rev() {
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < num[i]; j++) 
            used[i][tAns + rese[i][j]] = false;
}

void dfs(int now) {
    if(now == 8) {
        if(tAns >= ans) return;
        for(int i = 1; i <= n; i++) {
            if(ban[i]) continue;
            tAns += i;
            if(judge()) {
                ans = tAns < ans ? tAns : ans;
                rev();
                tAns -= i;
                return;
            }
            tAns -= i;
        }
    }
    for(int i = 1; i <= n; i++) {
        if(ban[i]) continue;
        tAns += i;
        if(tAns + jump * (8 - now) < ans && judge()) {
            dfs(now + 1);
            rev();
        }
        tAns -= i;
    }
}

int main() {
    while(scanf("%d\n", &n) == 1 && n) {
        memset(used, 0, sizeof(used));
        memset(ban, 0, sizeof(ban));
        ans = n * 9;
        char temp;
        for(int i = 0; i < 5; i++) {
            num[i] = 0;
            for(int j = 0; j < n; j++)
                if(scanf("%c", &temp) == 1 && temp == 'X') {
                    rese[i][num[i]++] = j;
                    used[i][j] = true;
                }
            getchar();
        }
        for(int i = 0; i < 5; i++) 
            for(int j = 0; j < num[i]; j++)
                for(int k = j + 1; k < num[i]; k++)
                    ban[rese[i][k] - rese[i][k - 1]] = true;
        for(int i = 1; i <= n; i++)
            if(!ban[i]) {
                jump = i;
                break;
            }
        if(jump == n) {
            printf("%d\n", ans + n);
            continue;
        }
        for(int i = 1; i < n; i++) {
            if(ban[i]) continue;
            tAns = i;
            if(judge()) {
                dfs(1);
                rev();
            }
        }
        printf("%d\n", ans + n);
    }
    return 0;
}
