/*
 * Title:   7-10UVa11212-2.cc
 * Author:  InvisibleMan
 * Time:    2016-12-23
 */

#include <cstdio>
#include <cstring>

// 企图用连续的段减轻复杂度，但不理想

using namespace std;
const int Nmax = 10;
bool flag;

void dfs(int deep, int data[Nmax], int n) {
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
        for(int j = 0; j <= n - i; j++)
            for(int k = 0; k <= n - i; k++) {
                if(j == k) continue;
                memcpy(data2, data, sizeof(int) * j);
                memcpy(data2 + j, data + j + i, sizeof(int) * (n - j - i));
                memcpy(data3, data2, sizeof(int) * (k));
                memcpy(data3 + k, data + j, sizeof(int) * (i));
                memcpy(data3 + k + i, data2 + k, sizeof(int) * (n - i - k));
                int nn = 0;
                for(int ii = 0; ii < n; ii++) {
                    while(ii + 1 < n)
                        if(data3[ii + 1] == data3[ii] + 1)
                            ii++;
                        else {
                            data2[nn++] = data3[ii];
                            break;
                        }
                    if(ii == n - 1)
                        data2[nn++] = data3[ii];
                }
                memset(data3, 0, sizeof(data3));
                for(int kk = 0; kk < nn; kk++)
                    data3[data2[kk]] = 1;
                for(int kk = 1; kk < 10; kk++)
                    data3[kk] += data3[kk - 1];
                for(int kk = 0; kk < nn; kk++)
                    data2[kk] = data3[data2[kk]];
                dfs(deep - 1, data2, nn);
                if(flag) return;
            }
}
int main() {
    int n, numCase = 0;
    int data[Nmax];
    while(scanf("%d", &n)  == 1 && n) {
        flag = false;
        int i;
        for(i = 0; i < n; i++)
            scanf("%d", &data[i]);
        for(i = 0; i < n && !flag; i++)
            dfs(i, data, n);
        printf("Case %d: %d\n", ++numCase, i - 1);
    }
}
