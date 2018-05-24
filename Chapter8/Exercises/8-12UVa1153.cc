/**
 * Title:   8-12UVa1153
 * Author:  InvisibleMan
 * Date:    2017-4-20
 * Time:    220ms
 */

// tips: 注意看题目后面的提示

#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

struct Node{
    int cost, del;
    bool operator < (const Node &rhs) const {
        return del < rhs.del || (del == rhs.del && cost < rhs.cost);
    }
}data[800000];

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
            scanf("%d%d", &data[i].cost, &data[i].del);
        sort(data, data + n);
        priority_queue<int> q;
        int now = 0, cnt = 0;
        for(int i = 0; i < n; i++) {
            if(data[i].del - now >= data[i].cost) {
                cnt++, now += data[i].cost;
                q.push(data[i].cost);
            }
            else if(!q.empty() && data[i].cost < q.top()) {
                now -= q.top() - data[i].cost;
                q.pop();
                q.push(data[i].cost);
            }
        }
        printf("%d\n", cnt);
        if(T) printf("\n");
    }
    return 0;
}
