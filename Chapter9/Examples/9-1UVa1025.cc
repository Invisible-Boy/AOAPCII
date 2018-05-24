/**
 * Title:   9-1UVa1025
 * Author:  InvisibleMan
 * Date:    2017-6-9
 * Time:    0ms
 */

#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

const int INF = 1e9;
const int Nmax = 55;
const int Tmax = 205;
int d[Tmax][Nmax], c[Nmax], allCost[Nmax], N, T;
set<int> P[Nmax], Q[Nmax];
typedef set<int>::iterator iter;

int dp(int now, int loc) {
    if(now > T) return INF;
    int &ans = d[now][loc];
    if(ans > -1) return ans;
    iter p = P[loc].lower_bound(now);
    if(loc < N - 1 && *p + allCost[loc] > T) return ans = INF;
    if(loc < N - 1)
        ans = *p - now + T - *p - allCost[loc];
    else
        ans = T - now;
    p = P[loc].lower_bound(now);
    while(*p < INF) {
        ans = min(ans, *p - now + dp(*p + c[loc], loc + 1));
        p++;
    }
    p = Q[loc].lower_bound(now);
    while(*p < INF) {
        ans = min(ans, *p - now + dp(*p + c[loc - 1], loc - 1));
        p++;
    }
    return ans;
}

int main() {
    int kase = 0;
    while(scanf("%d", &N) == 1 && N) {
        scanf("%d", &T);
        for(int i = 0; i < T; i++)
            for(int j = 0; j < N; j++)
                d[i][j] = -1;
        for(int i = 0; i < N - 1; i++)
            scanf("%d", &c[i]);
        allCost[N - 1] = 0;
        for(int i = N - 2; i > -1; i--)
            allCost[i] = allCost[i + 1] + c[i];
        for(int i = 0; i < N; i++) {
            P[i].clear();
            Q[i].clear();
            P[i].insert(INF);
            Q[i].insert(INF);
        }
        int m;
        scanf("%d", &m);
        for(int i = 0; i < m; i++) {
            int t;
            scanf("%d", &t);
            P[0].insert(t);
            for(int j = 1; j < N - 1; j++) {
                t += c[j - 1];
                P[j].insert(t);
            }
        }
        scanf("%d", &m);
        for(int i = 0; i < m; i++) {
            int t;
            scanf("%d", &t);
            Q[N - 1].insert(t);
            for(int j = N - 2; j > 0; j--) {
                t += c[j];
                Q[j].insert(t);
            }
        }
        printf("Case Number %d: ", ++kase);
        int t = dp(0, 0);
        if(t < INF) printf("%d\n", t);
        else printf("impossible\n");
    }
    return 0;
}
