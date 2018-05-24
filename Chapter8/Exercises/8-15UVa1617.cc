/**
 * Title:   8-15UVa1617
 * Author:  InvisibleMan
 * Date:    2017-5-12
 * Time:    0ms
 */

#include <cstdio>
#include <algorithm>

using namespace std;

struct Node {
    int l, r;
    bool operator < (const Node &rhs) const {
        return r < rhs.r || (r == rhs.r && l < rhs.l);
    }
};

const int Nmax = 1e5 + 5;
Node node[Nmax];

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
            scanf("%d%d", &node[i].l, &node[i].r);
        sort(node, node + n);
        int ans = -1, nowl = -1, nowr = -1;
        for(int i = 0; i < n; i++) {
            int tl = node[i].l, tr = node[i].r;
            if(tl > nowr) {
                ans++;
                nowl = tr - 1;
                nowr = tr;
            }
            /*else if(nowr + 1 > tr)
                nowl--;
            else
                nowr++;
            */
            // 上述可以贪心为,即不需要记录左端点，因为题目的限制，肯定可以把每个线段都在其deadline之前放进去
            else if(nowr + 1 <= tr)
                nowr++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
