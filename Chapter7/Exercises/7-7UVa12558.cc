/**
 * Title:   7-7UVa12558
 * Author:  InvisibleMan
 * Date:    2017-2-4
 * Time:    290ms
 */

#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

const int INF = 0x7fffffff;
int ans[100], tAns[100];
set<int> ban;

int gcd(int a, int b) {
    return a == 0 ? b : gcd(b % a, a);
}

bool isok(int max) {
    for(int i = max; i >= 0; i--)
        if(tAns[i] == ans[i]) continue;
        else if(tAns[i] < ans[i]) {
            for(int j = 0; j <= max; j++)
                ans[j] = tAns[j];
            return true;
        }
        else return false;
    return true;
}

bool dfs(int now, int m_max, int a, int b) {
    if(now == m_max) {
        tAns[now] = b;
        return a == 1 && !ban.count(b) && tAns[now - 1] < b && isok(m_max);
    }
    int sta = (b + a - 1) / a; 
    if(now)
        sta = max(tAns[now - 1] + 1, sta);
    bool flag = false;
    for(int i = sta; i <= INF / b; i++) {
        if((m_max - now + 1) * b < a * i) break;
        if(ban.count(i)) continue;
        tAns[now] = i;
        int newA = a * i - b;
        int newB = b * i;
        int m = gcd(newA, newB);
        if(dfs(now + 1, m_max, newA / m, newB / m)) flag = true;
    }
    return flag;
}

int main() {
    int n, a, b, k;
    scanf("%d", &n);
    for(int i = 1; i <=n; i++) {
        scanf("%d%d%d", &a, &b, &k);
        ban.clear();
        memset(ans, 0x7f, sizeof(ans));
        int t, j;
        for(j = 0; j < k; j++) {
            scanf("%d", &t);
            ban.insert(t);
        }
        for(j = 1; ; j++)
            if(dfs(0, j, a, b)) break;
        printf("Case %d: %d/%d=1/%d", i, a, b, ans[0]);
        for(int k = 1; k <= j; k++)
            printf("+1/%d", ans[k]);
        printf("\n");
    }
    return 0;
}
