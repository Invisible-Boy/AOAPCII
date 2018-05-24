/**
 * Title:   8-16UVa1608
 * Author:  InvisibleMan
 * Date:    2017-3-29
 * Time:    200ms
 */

#include <cstdio>
#include <map>

using namespace std;

const int Nmax = 200001;
int d[Nmax], p[Nmax], n[Nmax];

bool isBoring(int l, int r) {
    if(l > r - 2) return false;
    if(l == r - 2) return d[l] == d[l + 1];
    // 必须从两边往中间搜索，
    // 否则当唯一元素始终只在最前面或最后嘛出现的时候会导致复杂度变成o(n^2)
    for(int i = 0; i <= (r - l) >> 1; i++) { 
        if(p[l + i] < l && n[l + i] >= r)
            return isBoring(l, l + i) || isBoring(l + i + 1, r);
        if(p[r - i - 1] < l && n[r - i - 1] >= r)
            return isBoring(l, r - i - 1) || isBoring(r - i, r);
    }
    return true;
}

int main() {
    int T, m;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &m);
        map<int, int> myMap;
        for(int i = 0; i < m; i++) {
            scanf("%d", &d[i]);
            if(myMap.count(d[i])) {
                int t = myMap[d[i]];
                p[i] = t; n[t] = i; n[i] = Nmax;
            }
            else
                p[i] = -1, n[i] = Nmax;
            myMap[d[i]] = i;
        }
        if(isBoring(0, m)) printf("boring\n");
        else printf("non-boring\n");
    }
    return 0;
}
