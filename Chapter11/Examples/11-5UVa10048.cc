/**
 * Title:   11-5UVa10048
 * Author:  InvisibleMan
 * Date:    2018/5/16
 * Time:    0ms
 */

#include <iostream>

using namespace std;

const int Nmax = 105;
int edge[Nmax][Nmax], n, m, q;

inline void init() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            edge[i][j] = -1;
    while(m--) {
        int t1, t2, cost;
        cin >> t1 >> t2 >> cost;
        if(edge[--t1][--t2] == -1)
            edge[t1][t2] = edge[t2][t1] = cost;
        else if(cost < edge[t1][t2])
            edge[t1][t2] = edge[t2][t1] = cost;
    }
}

inline int min(int t1, int t2) {
    return t1 < t2 ? t1 : t2;
}

inline int max(int t1, int t2) {
    return t1 > t2 ? t1 : t2;
}

inline void floyd() {
    for(int k = 0; k < n; k++)
    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
        if(edge[i][k] > -1 && edge[k][j] > -1) {
            int newVal = max(edge[i][k], edge[k][j]);
            edge[i][j] = edge[i][j] == -1 ? newVal : min(edge[i][j], newVal);
        }
}

int main() {
    int kase = 0;
    while((cin >> n >> m >> q) && n && m && q) {
        if(kase) cout << endl;
        cout << "Case #" << ++kase << endl;
        init();
        floyd();
        while(q--) {
            int t1, t2;
            cin >> t1 >> t2;
            if(edge[--t1][--t2] > -1)
                cout << edge[t1][t2] << endl;
            else cout << "no path" << endl;
        }
    }
}
