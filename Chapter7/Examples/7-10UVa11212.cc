/*
 * Title:   7-10UVa11212.cc
 * Author:  InvisibleMan
 * Time:    2016-12-23
 */

#include <cstdio>
#include <cstring>

// 此版本没有经过优化，速度2070ms，后面还需要调整

using namespace std;
const int Nmax = 10;
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
            memcpy(data2, data, sizeof(int) * j);
            memcpy(data2 + j, data + j + i, sizeof(int) * (n - j - i));
            for(int k = 0; k <= n - i; k++) {
                if(j == k) continue;
                memcpy(data3, data2, sizeof(int) * (k));
                memcpy(data3 + k, data + j, sizeof(int) * (i));
                memcpy(data3 + k + i, data2 + k, sizeof(int) * (n - i - k));
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
}
