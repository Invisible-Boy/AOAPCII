/**
 * Title:   9-22UVa12105
 * Author:  InvisibleMan
 * Date:    2017-8-19
 * Time:    60ms
 */

#include <cstdio>

using namespace std;

const int Nmax = 105;
const int Mmax = 3005;
const int cost[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int n, m, kase = 1;
int vis[Nmax][Mmax] = {0}, ans[Nmax >> 1][Mmax], re[Nmax >> 1][10];

int main() {
    while(scanf("%d%d", &n, &m) == 2 && n) {
        vis[0][0] = kase; ans[0][0] = 0;
        for(int i = 0; i < (n >> 1); i++) {
            for(int j = 0; j < m; j++) {
                if(vis[i][j] == kase) {
                    for(int k = 0; k < 10; k++) {
                        int newCost = ans[i][j] + cost[k];
                        if(newCost <= n) {
                            int newRe = (j * 10 + k) % m;
                            if(vis[i + 1][newRe] != kase) {
                                vis[i + 1][newRe] = kase;
                                ans[i + 1][newRe] = newCost;
                            }
                            else if(newCost < ans[i + 1][newRe])
                                ans[i + 1][newRe] = newCost;
                        }
                    }
                }
            }
        }
        int ansI = n >> 1;
        while(ansI) {
            if(vis[ansI][0] == kase)
                break;
            ansI--;
        }
        printf("Case %d: ", kase);
        if(ansI) {
            for(int i = 1; i < 10; i++) re[1][i] = i % m;
            for(int i = 2; i <= ansI; i++)
                for(int j = 1; j < 10; j++)
                    re[i][j] = (re[i - 1][j] * 10) % m;
            int pre = 0;
            for(int i = ansI; i > 0; i--) {
                for(int j = 9; j > -1; j--) {
                    int need = (m - (re[i][j] + pre) % m) % m;
                    if(vis[i - 1][need] == kase && cost[j] + ans[i - 1][need] <= n) {
                        printf("%d", j);
                        n -= cost[j];
                        pre = (pre + re[i][j]) % m;
                        if(i == ansI && j == 0) i = -1;
                        break;
                    }
                }
            }
        }
        else printf("-1");
        printf("\n");
        kase++;
    }
    return 0;
}
