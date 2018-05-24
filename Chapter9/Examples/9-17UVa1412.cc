/**
 * Title:   9-17UVa1412
 * Author:  InvisibleMan
 * Date:    2017-7-21
 * Time:    280ms
 */

// 刷表法

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
    for(int i = 0; i < state.size(); i++) {
        for(int j = 0; j <= m; j++) d[j][i] = -1.0;
        int tot = 0;
        for(int j = 0; j < n; j++) tot += state[i][j];
        for(int j = 0; j < n; j++) {
            sell[i][j] = buy[i][j] = -1;
            if(state[i][j] > 0) {
                state[i][j]--;
                sell[i][j] = ID[state[i]];
                state[i][j]++;
            }
            if(tot < kk && state[i][j] < k[j]) {
                state[i][j]++;
                buy[i][j] = ID[state[i]];
                state[i][j]--;
            }
        }
    }
    return true;
}

inline void update(int now, int id1, int id2, double v, int o) {
    if(v > d[now + 1][id2]) {
        d[now + 1][id2] = v;
        pre[now + 1][id2] = id1;
        opt[now + 1][id2] = o;
    }
}

inline void dp() {
    pre[0][0] = -1;
    d[0][0] = c;
    for(int i = 0; i < m; i++)
    for(int j = 0; j < state.size(); j++)
    if(d[i][j] > -0.5) {
        double nowc = d[i][j];
        update(i, j, j, nowc, 0);
        for(int tk = 0; tk < n; tk++) {
            if(nowc >= price[tk][i] && buy[j][tk] > -1)
                update(i, j, buy[j][tk], nowc - price[tk][i], tk + 1);
            if(sell[j][tk] > -1)
                update(i, j, sell[j][tk], nowc + price[tk][i], -tk - 1);
        }
    }
}

void print(int now, int id) {
    if(pre[now][id] > -1) {
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
        dp();
        printf("%.2lf\n", d[m][0]);
        print(m, 0);
    }
    return 0;
}
