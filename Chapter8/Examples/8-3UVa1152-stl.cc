/**
 * Title:   8-3UVa1152
 * Authoe:  InvisibleMan
 * Date:    2017-3-13
 * Time:    ms
 */

// tips: 使用stl超时

#include <cstdio>
#include <set>

using namespace std;

int main() {
    int T, n, num[4][4000];
    scanf("%d", &T);
    for(int t = 0; t < T; t++) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < 4; j++)
                scanf("%d", &num[j][i]);
        set<int> s;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                s.insert(num[0][i] + num[1][j]);
        int cnt = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(s.count(- num[2][i] - num[3][j])) cnt++;
        if(t) printf("\n");
        printf("%d\n", cnt);
    }
    return 0;
}
