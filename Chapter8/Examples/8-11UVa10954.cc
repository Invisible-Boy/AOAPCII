/**
 * Title:   8-11UVa10954
 * Author:  InvisibleMan
 * Date:    2017-3-22
 * Time:    0ms
 */

#include <cstdio>
#include <queue>

using namespace std;

int main() {
    int n;
    priority_queue<int, vector<int>, greater<int> > q;
    while(scanf("%d", &n) == 1 && n) {
        int t;
        while(n--) {
            scanf("%d", &t);
            q.push(t);
        }
        int sum = 0;
        while(1) {
            t = q.top(); q.pop();
            t += q.top(); q.pop();
            sum += t;
            if(q.empty()) break;
            q.push(t);
        }
        printf("%d\n", sum);
    }
    return 0;
}
