/**
 * Title:   9-4UVa116
 * Author:  InvisibleMan
 * Date:    2017-6-12
 * Time:    ms
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int Nmax = 10;
const int Mmax = 100;

int main() {
    int n, m, d[Nmax][Mmax], ans[Nmax][Mmax], answer, next[Nmax][Mmax];
    while(scanf("%d%d", &n, &m) == 2) {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                scanf("%d", &d[i][j]);
        for(int i = 0; i < n; i++)
            ans[i][m - 1] = d[i][m - 1];
        for(int i = m - 2; i > -1; i--)
            for(int j = 0; j < n; j++) {
                int tindex = j;
                for(int k = -1; k < 2; k++) {
                    int index = (j + k + n) % n;
                    int ans1 = ans[tindex][i + 1], ans2 = ans[index][i + 1];
                    if(ans2 < ans1 || (ans2 == ans1 && index < tindex))
                        tindex = index;
                }
                ans[j][i] = ans[tindex][i + 1] + d[j][i];
                next[j][i] = tindex;
            }
        int answer = 0;
        for(int i = 1; i < n; i++)
            if(ans[i][0] < ans[answer][0])
                answer = i;
        int nowx = answer, nowy = 0;
        printf("%d", answer + 1);
        while(nowy < m - 1) {
            printf(" %d", next[nowx][nowy] + 1);
            nowx = next[nowx][nowy];
            nowy++;
        }
        printf("\n%d\n", ans[answer][0]);
    }
    return 0;
}
