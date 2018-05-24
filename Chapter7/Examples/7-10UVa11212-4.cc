/*
 * Title:   7-10UVa11212i-4.cc
 * Author:  InvisibleMan
 * Time:    2016-12-25
 */

// 不要破坏一个排好的序列，同时利用每次只能减少3个不合顺序的排列剪枝，时间为0ms

#include <cstdio>
#include <cstring>

using namespace std;

const int Nmax = 9;
int n, data[Nmax];
bool flag;

void dfs(int deep) {
    int cnt = 0;
    for(int i = 0; i < n - 1; i++)
        if(data[i] != data[i + 1] - 1)
            cnt++;
    if(data[n - 1] != n) cnt++;
    if(cnt > 3 * deep) return;
    if(cnt == 0) {
        flag = true;
        return;
    }
    int tempData[Nmax], oldData[Nmax];
    memcpy(oldData, data, sizeof(data));
    // 在这一部分使用了定序，每次只能向切割位置的后面插入，进一步降低复杂度
    for(int i = 0; i < n; i++)
        for(int j = i; j < n; j++) {
            if((i > 0 && oldData[i - 1] + 1 == oldData[i]) || ((j < n - 1) && oldData[j] + 1 == oldData[j + 1])) continue;  //不要破坏一个排好序的组合
            cnt = 0;
            for(int k = 0; k < n; k++)
                if(k < i || k > j) tempData[cnt++] = oldData[k];
            for(int k = i + 1; k <= cnt; k++) {
                int cnt2 = 0;
                for(int p = 0; p < k; p++) data[cnt2++] = tempData[p];
                for(int p = i; p <= j; p++) data[cnt2++] = oldData[p];
                for(int p = k; p < cnt; p++) data[cnt2++] = tempData[p];
                dfs(deep - 1);
                if(flag) return;
            }
        }
}
int main() {
    int numCase = 0;
    while(scanf("%d", &n) == 1 && n) {
        flag = false;
        int i, oldData[Nmax];
        for(i = 0; i < n; i++)
            scanf("%d", &oldData[i]);
        for(i = 0; i < 5 && !flag; i++) {
            memcpy(data, oldData, sizeof(data));
            dfs(i);
        }
        printf("Case %d: %d\n", ++numCase, flag ? i - 1 : 5);
    }
    return 0;
}
