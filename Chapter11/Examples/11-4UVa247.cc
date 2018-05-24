/**
 * Title:   11-4UVa247
 * Author:  InvisibleMan
 * Date:    2018/5/16
 * Time:    40ms
 */

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>

using namespace std;

map<string, int> mp;
vector<string> name;
const int Nmax = 30;
bool edge[Nmax][Nmax];
int n, m;

inline int addName(string &s) {
    if(mp.count(s)) return mp[s];
    int ans = mp[s] = name.size();
    name.push_back(s);
    return ans;
}

void init() {
    memset(edge, 0, sizeof(edge));
    name.clear();
    mp.clear();
    for(int i = 0; i < m; i++) {
        string s;
        cin >> s;
        int t1 = addName(s);
        cin >> s;
        int t2 = addName(s);
        edge[t1][t2] = true;
    }
}

bool flag[Nmax][Nmax];

void floyd() {
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                edge[i][j] = edge[i][j] || (edge[i][k] && edge[k][j]);
    memset(flag, 0, sizeof(flag));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            flag[i][j] = edge[i][j] && edge[j][i];
}

bool vis[Nmax];

inline void printg(int now) {
    vis[now] = true;
    cout << name[now];
    for(int i = 0; i < n; i++)
        if(flag[now][i] && i != now) {
            vis[i] = true;
            cout << ", " << name[i];
        }
    cout << endl;
}

int main() {
    int kase = 0;
    while((cin >> n >> m) && n && m) {
        if(kase) cout << endl;
        init();
        floyd();
        for(int i = 0; i < n; i++) vis[i] = false;
        cout << "Calling circles for data set " << ++kase << ':' << endl;
        for(int i = 0; i < n; i++)
            if(!vis[i]) printg(i);
    }
    return 0;
}
