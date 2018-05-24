/**
 * Title:   9-12UVa12186
 * Author:  InvisibleMan
 * Date:    2017-7-6
 * Time:    40ms
 */

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int Nmax = 100005;

vector<int> son[Nmax];
int d[Nmax];

bool cmp(const int x, const int y) {
    return d[x] < d[y];
}

int main() {
    int n, t;
    while((scanf("%d%d", &n, &t) == 2) && n && t) {
        for(int i = 0; i <= n; i++) son[i].clear();
        for(int i = 1; i <= n; i++) {
            int temp;
            scanf("%d", &temp);
            son[temp].push_back(i);
        }
        for(int i = n; i > -1; i--) {
            d[i] = 0;
            int num = son[i].size();
            if(num == 0) d[i] = 1;
            else {
                sort(son[i].begin(), son[i].end(), cmp);
                num = (t * num - 1) / 100 + 1;
                for(int j = 0; j < num; j++)
                    d[i] += d[son[i][j]];
            }
        }
        printf("%d\n", d[0]);
    }
    return 0;
}
