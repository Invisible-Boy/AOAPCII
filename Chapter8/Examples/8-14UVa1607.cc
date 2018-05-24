/**
 * Title:   8-14UVa1607.cc
 * Author:  InvisibleMan
 * Date:    2017-3-25
 * Time:    100ms
 */

#include <cstdio>
#include <utility>

using namespace std;

pair<int, int> connect[200000]; 
char inVal[100000];
bool outVal[200000];
int n, m;

inline bool func(int in1, int in2) {
    return !(in1 < 0 ? inVal[-(in1 + 1)] - '0' : outVal[in1 - 1]) || 
    !(in2 < 0 ? inVal[-(in2 + 1)] - '0' : outVal[in2 - 1]);
}

bool fun(int l, int r, int x) {
    for(int i = l; i < r; i++)
        inVal[i] = '0' + x;
    for(int i = 0; i < m; i++)
        outVal[i] = func(connect[i].first, connect[i].second);
    return outVal[m - 1];
}

int main() {
    int T;
    scanf("%d", &T);
    for(int t = 0; t < T; t++) {
        scanf("%d%d", &n, &m);
        for(int j = 0; j < m; j++)
            scanf("%d%d", &connect[j].first, &connect[j].second);
        bool flag[2] = {fun(0, n, 0), fun(0, n, 1)};
        if(flag[0] == flag[1]) {
            for(int i = 0; i < n; i++)
                printf("0");
            printf("\n");
            continue;
        }
        int l = 0, r = n, f = 0;
        while(l < r - 1) {
            int mid = (l + r) >> 1;
            if(fun(l, mid, f) != flag[f])
                l = mid;
            else {
                r = mid;
                f = 1 - f;
            }
        }
        inVal[l] = 'x';
        for(int i = 0; i < n; i++)
            printf("%c", inVal[i]);
        printf("\n");
    }
    return 0;
}
