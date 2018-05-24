/*
 * Title:   Egyptian Fractions(UVa12558)
 * Author:  InvisibleMan
 * Time:    2016-12-19
 */

#include <cstdio>
#include <cstring>
#include <vector>

// 这个版本是错误的，因为题目的意思是循环比较，最小的分数要最大，如果最小的相等那就比较次最小以此类推；

using namespace std;

typedef long long LL;
bool ban[1001], flag;
vector<LL> ans, ansT;

void gcd(LL &a, LL &b) {
    LL aa = a, bb = b;
    while(bb % aa) {
        bb = bb % aa;
        LL temp = aa;
        aa = bb;
        bb = temp;
    }
    a /= aa;
    b /= aa;
}

void dfs(int now, int deep, LL a, LL b) {
    if(now == deep) {
        if(a == 0 && (ansT[deep - 1] < ans[deep - 1] || (ansT[deep - 1] == ans[deep - 1] && ansT[deep - 2] < ans[deep - 2]))) {
            ans = ansT;
            flag = true;
        }
        return;
    }
    LL nowMin = b / a + ((b % a) + a - 1) / a;
    if(now)
        nowMin = nowMin > ansT[now - 1] ? nowMin : ansT[now - 1] + 1;
    for(LL i = nowMin; i * a <= (deep - now) * b; i++) {
        if(i < 1001 && ban[i]) continue;
        ansT[now] = i;
        LL aa = a * i - b;
        LL bb = b * i;
        if(aa) gcd(aa, bb);
        dfs(now + 1, deep, aa, bb);
    }
}

int main() {
    LL a, b;
    int n, k, temp; scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        memset(ban, false, sizeof(ban));
        flag = false;
        scanf("%lld%lld%d", &a, &b, &k);
        for(int j = 0; j < k; j++) {
            scanf("%d", &temp);
            ban[temp] = true;
        }
        for(int deep = 2; !flag; deep++) {
            ans.resize(deep);
            ansT.resize(deep);
            ans[deep - 1] = 1 << 30;
            dfs(0, deep, a, b);
        }
        printf("Case %d: %lld/%lld=", i + 1, a, b);
        for(int i = 0; i < (int)ans.size(); i++) {
            if(i) printf("+");
            printf("1/%lld", ans[i]);
        }
        printf("\n");
    }
    return 0;
}
