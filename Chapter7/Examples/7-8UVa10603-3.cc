/*
 * Title:   7-8UVa10603.cc
 * Author:  InvisibleMan
 * Time:    2016-12-18
 */

// 没有使用STL存储状态，使用自己写的hash同时使用stdio,没有使用iostream,时间为0ms

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

typedef int State[3];
const int Smax = 65536;
int d1, d, stdv[3], result, cost[Smax];
State st[Smax];

int myhash(State &now) {
	return (now[0] << 8) + now[1];
}

void changeresult(State &now, int nowtotal) {
    for(int i = 0; i < 3; i++)
		if(now[i] <= d && now[i] > d1) {
			result = nowtotal;
			d1 = now[i];
		}
		else if(now[i] == d1 && nowtotal < result)
			result = nowtotal;
}

void bfs(State &now) {
	queue<int*> q;
	q.push(&now[0]);
	State next;
	while(!q.empty()) {
		memcpy(now, q.front(), sizeof(now)); q.pop();
		int total = cost[myhash(now)];
		for(int i = 0; i < 3; i++)
			if(now[i] != stdv[i])
				for(int j = 0; j < 3; j++)
					if(now[j] && i != j) {
						int change = min(stdv[i] - now[i], now[j]);
						for(int k = 0; k < 3; k++)
							if(k == i)
								next[k] = now[k] + change;
							else if(k == j)
								next[k] = now[k] - change;
							else
								next[k] = now[k];
						int nextTotal = total + change;
						int index = myhash(next);
						if(nextTotal < cost[index]) {
							memcpy(st[index], next, sizeof(next));
							changeresult(next, nextTotal);
							cost[index] = nextTotal;
							q.push(&st[index][0]);
						}
					}
	}
}

int main() {
    int n;
    scanf("%d", &n);
    while(n--) {
        memset(cost, 0x7f, sizeof(cost));
		d1 = 0;
		result = 0;
		scanf("%d%d%d%d", &stdv[0], &stdv[1], &stdv[2], &d);
        if(d >= stdv[2]) {
            printf("0 %d\n", stdv[2]);
            continue;
        }
        State now = {0, 0, stdv[2]};
		cost[0] = 0;
        bfs(now);
		printf("%d %d\n", result, d1);
    }
    return 0;
}
