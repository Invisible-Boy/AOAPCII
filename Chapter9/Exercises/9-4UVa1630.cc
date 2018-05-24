/**
 *  Title:  9-4UVa1630
 *  Author: InvisibleMan
 *  Date:   2018/3/21
 *  Time:   0ms
 */

#include <cstdio>
#include <cstring>

using namespace std;

const int Nmax = 105;
char str[Nmax];
int pi[Nmax], dp[Nmax][Nmax], cost[Nmax][Nmax], next[Nmax][Nmax];

int kmp(int p, int q) {
    pi[0] = pi[1] = 0;
    int len = q - p;
    int t = 0;
    for(int i = 2; i <= len; i++) {
        while(t && str[p + i - 1] != str[p + t])
            t = pi[t];
        if(str[p + i - 1] == str[p + t]) t++;
        pi[i] = t;
    }
    if(len % (len - pi[len]) == 0)
        return len - pi[len];
    else return len;
}

inline int fun(int p, int q) {
    if(p >= q) return 0;
    int len = q - p, loop = dp[p][q], cnt = len / loop;
    if(cnt == 1) return len;
    int ans = cost[p][p + loop];
    while(cnt) {
        ans++;
        cnt /= 10;
    }
    ans += 2;
    return len < ans ? len : ans;
}

void print(int p, int q) {
    int mid = next[p][q], len = q - p;
    if(mid == q) {
        if(cost[p][q] == len)
            while(p < q) printf("%c", str[p++]);
        else {
            printf("%d(", len / dp[p][q]);
            print(p, p + dp[p][q]);
            printf(")");
        }
    }
    else {
        print(p, mid);
        print(mid, q);
    }
}

int main() {
    while(scanf("%s", str) == 1) {
        int len = strlen(str);
        for(int i = 0; i < len; i++)
            for(int j = i + 1; j <= len; j++)
                dp[i][j] = kmp(i, j);
        for(int i = 0; i <= len - 1; i++) {
            cost[i][i + 1] = 1;
            next[i][i + 1] = i + 1;
        }
        for(int l = 2; l <= len; l++)
            for(int i = 0; i <= len - l; i++) {
                int &nowNext = next[i][i + l], &nowCost = cost[i][i + l];
                nowNext = i + l; nowCost = fun(i, i + l);
                for(int j = i + 1; j < i + l; j++) {
                    int newCost = cost[i][j] + cost[j][i + l];
                    if(newCost < nowCost) {
                        nowNext = j;
                        nowCost = newCost;
                    }
                }
        }
        print(0, len);
        printf("\n");
    }
    return 0;
}
