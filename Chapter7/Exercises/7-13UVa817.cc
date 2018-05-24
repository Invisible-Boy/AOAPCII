/**
 * Title:   7-13UVa817
 * Author:  InvisibleMan
 * Date:    2017-2-20
 * Time:    460ms
 */

// tips:简单的dfs，注意至少需要插入一个符号，否则报错

#include <cstdio>
#include <stack>

using namespace std;

int n, ans;
char sta[10], oper[9];

bool init() {
    ans = 0;
    for(n = 0; n < 10; n++) {
        sta[n] = getchar();
        if(sta[n] == '=') break;
    }
    oper[n - 1] = '+';
    while(getchar() != '\n');
    return n;
}

bool isok(int now) {
    int p = now;
    while(p - 1 > -1 && oper[p - 1] == (char)0)
        p--;
    return p == now || sta[p] - '0';
}

bool judge() {
    stack<int> s;
    int flag = 0;
    int now = 0, bef = 0;
    for(int i = 0; i < n; i++) {
        now = now * 10 + sta[i] - '0';
        if(oper[i] != 0) {
            flag++;
            if(i == 0) s.push(now);
            else if(oper[bef] == '*') {
                int now1 = now * s.top();
                s.pop();
                s.push(now1);
            }
            else if(oper[bef] == '-')
                s.push(-now);
            else s.push(now);
            bef = i;
            now = 0;
        }
    }
    now = 0;
    while(!s.empty()) {
        now += s.top();
        s.pop();
    }
    return flag > 1 && now == 2000;
}

void dfs(int now) {
    if(now == n - 1) {
        if(judge()) {
            ans++;
            printf("  ");
            for(int i = 0; i <= n; i++) {
                printf("%c", sta[i]);
                if(i < n - 1 && oper[i]) printf("%c", oper[i]);
            }
            printf("\n");
        }
        return;
    }
    if(isok(now)) {
        oper[now] = (char)0;
        dfs(now + 1);
        oper[now] = '*';
        dfs(now + 1);
        oper[now] = '+';
        dfs(now + 1);
        oper[now] = '-';
        dfs(now + 1);
    }
}

int main() {
    int cnt = 1;
    while(init()) {
        printf("Problem %d\n", cnt++);
        dfs(0);
        if(!ans) printf("  IMPOSSIBLE\n");
    }
    return 0;
}
