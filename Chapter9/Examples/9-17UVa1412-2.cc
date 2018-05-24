/**
 * Title:   9-17UVa1412
 * Author:  InvisibleMan
 * Date:    2017-7-21
 * Time:    440ms
 */

// 填表法

#include <cstdio>
#include <vector>
#include <map>

using namespace std;

const int Nmax = 8;
const int Mmax = 105;
const int NState = 15000;

vector<vector<int> > state;
map<vector<int>, int> ID;
int m, n, kk, k[Nmax], sell[NState][Nmax], buy[NState][Nmax], opt[Mmax][NState], pre[Mmax][NState];
double c, price[Nmax][Mmax], d[Mmax][NState];
char name[Nmax][10];

void dfs(vector<int> &sta, int tot) {
    ID[sta] = state.size();
    state.push_back(sta);
    if(tot == kk) return;
    for(int i = 0; i < n; i++) {
        if(sta[i] < k[i]) {
            sta[i]++;
            if(!ID.count(sta))
                dfs(sta, tot + 1);
            sta[i]--;
        }
    }
}

inline bool init() {
    if(scanf("%lf%d%d%d", &c, &m, &n, &kk) != 4) return false;
    ID.clear(); state.clear();
    for(int i = 0; i < n; i++) {
        int t;
        scanf("%s%d%d", name[i], &t, &k[i]);
        for(int j = 0; j < m; j++) {
            scanf("%lf", &price[i][j]);
            price[i][j] *= t;
        }
    }
    vector<int> sta(n, 0);
    dfs(sta, 0);
    for(int i = 0; i < state.size(); i++)
        for(int j = 0; j < n; j++) sell[i][j] = buy[i][j] = -1;
    for(int i = 0; i < state.size(); i++) {
        for(int j = 0; j <= m; j++) d[j][i] = -1;
        int tot = 0;
        for(int j = 0; j < n; j++) tot += state[i][j];
        for(int j = 0; j < n; j++) {
            if(state[i][j] > 0) {
                state[i][j]--;
                sell[ID[state[i]]][j] = i;
                state[i][j]++;
            }
            if(tot < kk && state[i][j] < k[j]) {
                state[i][j]++;
                buy[ID[state[i]]][j] = i;
                state[i][j]--;
            }
        }
    }
    return true;
}

double dp(int now, int id) {
    double &ans = d[now][id];
    if(ans > -1 || now == 0) return ans;
    ans = -0.5;
    if(dp(now - 1, id) > ans) {
        ans = d[now - 1][id];
        pre[now][id] = id; opt[now][id] = 0;
    }
    for(int i = 0; i < n; i++) {
        if(buy[id][i] > -1) {
            double newc = dp(now - 1, buy[id][i]) - price[i][now - 1];
            if(newc > ans && newc >= 0) {
                ans = newc;
                pre[now][id] = buy[id][i];
                opt[now][id] = i + 1;
            }
        }
        if(sell[id][i] > -1) {
            double newc = dp(now - 1, sell[id][i]) + price[i][now - 1];
            if(newc > ans && newc >= price[i][now - 1]) {
                ans = newc;
                pre[now][id] = sell[id][i];
                opt[now][id] = -i - 1;
            }
        }
    }
    return ans;
}

void print(int now, int id) {
    if(now > 0) {
        print(now - 1, pre[now][id]);
        int op = opt[now][id];
        if(op > 0)
            printf("BUY %s\n", name[op - 1]);
        else if(op < 0)
            printf("SELL %s\n", name[-op - 1]);
        else
            printf("HOLD\n");
    }
}

int main() {
    int kase = 0;
    while(init()) {
        if(kase++) printf("\n");
        d[0][0] = c; pre[0][0] = -1;
        printf("%.2lf\n", dp(m, 0));
        print(m, 0);
    }
    return 0;
}
