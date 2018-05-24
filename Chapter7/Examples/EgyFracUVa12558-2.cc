/*
 * Title:   Egyptian Fractions(UVa12558)
 * Author:  InvisibleMan
 * Time:    2016-12-19
 */

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

typedef long long LL;
bool ban[1005], flag;
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

bool isbetter(int n) {
    for(int i = n - 1; i > -1; i--)
        if(ans[i] == ansT[i]) continue;
        else if(ans[i] > ansT[i]) return true;
        else return false;
    return false;
}

void dfs(int now, int deep, LL a, LL b) {
    if(now == deep) {
        if(a == 0 && (!flag || isbetter(now))) {
            ans = ansT;
            flag = true;
        }
        return;
    }
    LL nowMin = (b + a - 1) / a;
    if(now)
        nowMin = nowMin > ansT[now - 1] ? nowMin : ansT[now - 1] + 1;
    for(LL i = nowMin; i * a <= (deep - now) * b; i++) {
        if(i < 1005 && ban[i]) continue;
        ansT[now] = i;
        LL aa = a * i - b;
        LL bb = b * i;  // 此处增加溢出判断，可以剪枝
        if(aa) gcd(aa, bb);
        dfs(now + 1, deep, aa, bb);
    }
}

int main() {
    LL a, b;
    int n, k, temp; cin >> n;
    for(int i = 0; i < n; i++) {
        memset(ban, false, sizeof(ban));
        flag = false;
        cin >> a >> b >> k;
        for(int j = 0; j < k; j++) {
            cin >> temp;
            ban[temp] = true;
        }
        for(int deep = 2; !flag; deep++) {
            ans.resize(deep);
            ansT.resize(deep);
            dfs(0, deep, a, b);
        }
        cout << "Case " << i + 1 << ": " << a << '/' << b << '=';
        for(int i = 0; i < (int)ans.size(); i++) {
            if(i) cout << '+';
            cout << "1/" << ans[i];
        }
        cout << endl;
    }
    return 0;
}
