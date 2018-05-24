/*
 * Title:   7-10UVa11212.cc
 * Author:  InvisibleMan
 * Time:    2016-12-25
 */

#include <cstdio>

// 此版本没有使用memcpy,直接使用=，速度170ms，在数据量比较小的时候，直接赋值速度比memcpy要快
// 后续需要测试一下memcpy和赋值的速度差异

using namespace std;

const int Nmax = 9;
int n;
bool flag;

void dfs(int deep, int data[Nmax]) {
    int cnt = 0;
    for(int i = 1; i < n; i++)
        if(data[i] != data[i - 1] + 1)
            cnt++;
    if(cnt > 3 * deep) return;
    if(cnt == 0) {
        flag = true;
        return;
    }
    int data2[Nmax], data3[Nmax];
    for(int i = 1; i <= n / 2; i++)
        for(int j = 0; j <= n - i; j++) {
            cnt = 0;
            for(int k = 0; k < n; k++)
                if(k < j || k >= j + i) data2[cnt++] = data[k];
            for(int k = 0; k <= cnt; k++) {
                if(j == k) continue;
                int cnt2 = 0;
                for(int p = 0; p < k; p++) data3[cnt2++] = data2[p];
                for(int p = j; p < j + i; p++) data3[cnt2++] = data[p];
                for(int p = k; p < cnt; p++) data3[cnt2++] = data2[p];
                dfs(deep - 1, data3);
                if(flag) return;
            }
        }
}
int main() {
    int numCase = 0;
    int data[Nmax];
    while(scanf("%d", &n)  == 1 && n) {
        flag = false;
        int i;
        for(i = 0; i < n; i++)
            scanf("%d", &data[i]);
        for(i = 0; i < 5 && !flag; i++)
            dfs(i, data);
        printf("Case %d: %d\n", ++numCase, flag ? i - 1 : 5);
    }
    return 0;
}
