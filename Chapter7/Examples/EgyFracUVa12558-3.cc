/*
 * Title:   Egyptian Fractions(UVa12558)
 * Author:  InvisibleMan
 * Time:    2016-12-20
 */

// 参考了Egypt-reference.cc, 但运行效率比其更高

#include <cstdio>
#include <cstring>

using namespace std;

const int INF = 0x7fffffff;
bool ban[1005], flag;
const int Nmax = 20000;
int ans[Nmax], ansT[Nmax];

void gcd(int &a, int &b) {
    int aa = a, bb = b;
    while(bb % aa) {
        bb = bb % aa;
        int temp = aa;
        aa = bb; 
        bb = temp;
    }
    a /= aa;
    b /= aa;
}

bool isbetter(int n) {
    for(int i = n - 1; i > -1; i--)
        if(ans[i] != ansT[i]) return ansT[i] < ans[i];
    return false;
}

void dfs(int now, int deep, int a, int b) {
    if(now == deep - 1) {  // 这个解法的精髓所在，不是判断最后一个，而是直接默认判断倒数第二个，因为越往后分母越大，在最后一个判断分子是不是1，可以显著的降低复杂度和避免溢出，相当于减掉了一层，最下面一层分支最多。
        if(a == 1 && b > ansT[now - 1] && (b >= 1005 || (b < 1005 && !ban[b]))) {
            ansT[now++] = b;
            a = 0;
        }
        if(a == 0 && (!flag || isbetter(now))) {
            memcpy(ans, ansT, sizeof(int) * deep);
            flag = true;
        }
        return;
    }
    int nowMin = (b + a - 1) / a;
    if(now)
        nowMin = nowMin > ansT[now - 1] ? nowMin : ansT[now - 1] + 1;
    for(int i = nowMin;i <= INF / b && i * a<= (deep - now) * b; i++) {
        if(i < 1005 && ban[i]) continue;
        ansT[now] = i;
        int aa = a * i - b;
        int bb = b * i;
        if(aa < 0) continue;
        if(aa) gcd(aa, bb);
        dfs(now + 1, deep, aa, bb);
    }
}

int main() {
    int a, b;
    int n, k, temp; scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        memset(ban, false, sizeof(ban));
        flag = false;
        scanf("%d%d%d", &a, &b, &k);
        for(int j = 0; j < k; j++) {
            scanf("%d", &temp);
            ban[temp] = true;
        }
        int deep;
        for(deep = 2; !flag; deep++)
            dfs(0, deep, a, b);
        printf("Case %d: %d/%d=", i + 1, a, b);
        for(int i = 0; i < deep - 1; i++) {
            if(i) printf("+"); 
            printf("1/%d", ans[i]);
        }
        printf("\n");
    }
    return 0;
}
