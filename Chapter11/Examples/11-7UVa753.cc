/**
 * Title:   11-7UVa753
 * Author:  InvisibleMan
 * Date:    2018/6/19
 */
#include <iostream>
#include <string>
#include <unordered_map>
#include <cstring>
#include <queue>

using namespace std;

const int Nmax = 402;
const int INF = 100000;

inline int min(int t1, int t2) {
    return t1 < t2 ? t1 : t2;
}

struct Edge {
    int from, to, c, f, next;
}edge[Nmax << 1];

int tot, pEdge[Nmax];

void AddEdge(int from, int to, int c, int f) {
    edge[tot].from = from;
    edge[tot].to = to;
    edge[tot].c = c;
    edge[tot].f = f;
    edge[tot].next = pEdge[from];
    pEdge[from] = tot++;
}

unordered_map<string, int> mp;
int cnt = 0;

int getId(string &name) {
    if(!mp.count(name)) mp[name] = cnt++;;
    return mp[name];
}

int init() {
    memset(pEdge, -1, sizeof(pEdge)); tot = 0;
    mp.clear(); cnt = 2;
    int n;
    cin >> n;
    string name1, name2;
    while(n--) {
        cin >> name1;
        int id = getId(name1);
        AddEdge(id, 1, 1, 0);
        AddEdge(1, id, 0, 0);
    }
    cin >> n;
    int ans = n;
    while(n--) {
        cin >> name1 >> name2;
        int id = getId(name2);
        AddEdge(0, id, 1, 0);
        AddEdge(id, 0, 0, 0);
    }
    cin >> n;
    while(n--) {
        cin >> name1 >> name2;
        int id1 = getId(name1), id2 = getId(name2);
        AddEdge(id1, id2, INF, 0);
        AddEdge(id2, id1, 0, 0);
    }
    return ans;
}

int EdmondsKarp() {
    int a[Nmax], p[Nmax];
    int ans = 0;
    while(1) {
        queue<int> q;
        for(int i = 0; i < cnt; i++) a[i] = 0;
        q.push(0);
        a[0] = INF;
        p[0] = -1;
        while(!q.empty() && !a[1]) {
            int now = q.front(); q.pop();
            for(int t = pEdge[now]; t != -1; t = edge[t].next) {
                int to = edge[t].to;
                if(!a[to] && edge[t].c > edge[t].f) {
                    a[to] = min(a[now], edge[t].c - edge[t].f);
                    p[to] = t;
                    q.push(to);
                }
            }
        }
        if(a[1] == 0) break;
        for(int t = p[1]; t != -1; t = p[edge[t].from]) {
            edge[t].f += a[1];
            edge[t ^ 1].f -= a[1];
        }
        ans += a[1];
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    while(n--) {
        int ans = init();
        cout << ans - EdmondsKarp() << endl;
        if(n) cout << endl;
    }
    return 0;
}
