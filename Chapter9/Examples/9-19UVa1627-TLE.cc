/**
 * Title:   9-19UVa1627
 * Author:  InvisbleMan
 * Date:    2017-7-25
 * Time:    TLE
 */

#include <cstdio>
#include <queue>
#include <cstring>
#include <cstdlib>

using namespace std;

const int Nmax = 105;
const int Shift = 50;

struct State {
    unsigned long long sta[2][2], id[2][2];
    int num[2];
};

int n;
unsigned long long edge[Nmax][2];


int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            edge[i][0] = 0, edge[i][1] = 0;
            unsigned int t = 0;
            while(scanf("%u", &t) == 1 && t) {
                if(t > Shift) {
                    t -= Shift;
                    edge[i][1] |= 1 << t;
                }
                else
                    edge[i][0] |= 1 << t;
            }
        }
        queue<State> q;
        State start;
        memset(start.sta, 0xff, sizeof(start.sta));
        memset(start.id, 0, sizeof(start.id));
        start.num[0] = start.num[1] = 0;
        q.push(start);
        for(int i = 0; i < n; i++) {
            int j = q.size();
            while(j--) {
                for(int k = 0; k < 2; k++) {
                    State now = q.front();
                    int s = i / Shift;
                    int ss = (i + 1) - Shift * s;
                    if((now.sta[k][s] & (1 << ss)) &&
                       ((now.id[k][0] & (~edge[i][0])) == 0) && 
                       ((now.id[k][1] & (~edge[i][1])) == 0)) {
                        now.sta[k][0] &= edge[i][0];
                        now.sta[k][1] &= edge[i][1];
                        now.id[k][s] |= 1 << ss;
                        now.num[k]++;
                        q.push(now);
                    }
                }
                q.pop();
            }
        }
        if(q.empty()) printf("No solution\n");
        else {
            start = q.front(); q.pop();
            while(!q.empty()) {
                State now = q.front(); q.pop();
                if(abs(now.num[0] - now.num[1]) < abs(start.num[0] - start.num[1]))
                    start = now;
            }
            for(int k = 0; k < 2; k++) {
                printf("%d", start.num[k]);
                for(int kk = 1; kk <= n; kk++) {
                    int s = (kk - 1) / Shift;
                    int ss = kk - Shift * s;
                    if(start.id[k][s] & (1 << ss))
                        printf(" %d", kk);
                }
                printf("\n");
            }
        }
        if(T) printf("\n");
    }
    return 0;
}
