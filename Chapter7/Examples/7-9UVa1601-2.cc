/*
 * Title:	7-9UVa1601
 * Author:	InvisibleMan
 * Time:	2016-12-19
 */

// 使用双向bfs

#include <cstdio>
#include <queue>
#include <cstring>
#include <cctype>

using namespace std;
const int Nmax = 16;
const int stateMax = 256;
const int dy[] = {0, 1, -1, 0, 0};
const int dx[] = {0, 0, 0, -1, 1};

int w, h, n,
	s[3], d[3], id[Nmax][Nmax], G[stateMax][5], edgeN[stateMax], cost[2][stateMax][stateMax][stateMax];

int st(int a, int b, int c) {
	return (a << 16) + (b << 8) + c;
}

bool isok(int a, int newa, int b, int newb) {
	return newa != newb && (a != newb || b != newa);
}

void bfs() {
	cost[0][s[0]][s[1]][s[2]] = 0;
	cost[1][d[0]][d[1]][d[2]] = 0;
	queue<int> q[2];
	q[0].push(st(s[0], s[1], s[2]));
	q[1].push(st(d[0], d[1], d[2]));
	int t = 0, nowt[] = {0, 0};
	while(!q[t].empty()) {
		int a, b, c, state;
		state = q[t].front();
		a = state >> 16;
		b = (state >> 8) & 0xff;
		c = state & 0xff;
		if(cost[t][a][b][c] != nowt[t]) {
			t = 1 - t;
			nowt[t]++;
			continue;
		}
		q[t].pop();
		for(int i = 0; i < edgeN[a]; i++)
			for(int j = 0; j < edgeN[b]; j++) {
				int newa = G[a][i];
				int newb = G[b][j];
				if(isok(a, newa, b, newb)) {
					for(int k = 0; k < edgeN[c]; k++) {
						int newc = G[c][k];
						if(isok(a, newa, c, newc) && isok(b, newb, c, newc) && cost[t][newa][newb][newc] < 0) {
							cost[t][newa][newb][newc] = cost[t][a][b][c] + 1;
							if(cost[1 - t][newa][newb][newc] > -1) {
								printf("%d\n", cost[0][newa][newb][newc] + cost[1][newa][newb][newc]);
								return;
							}
							q[t].push(st(newa, newb, newc));
						}
					}
				}
			}
		
	}
}

int main() {
	char data[Nmax][Nmax];
	while(scanf("%d%d%d\n", &w, &h, &n) == 3 && w) {
		memset(cost, -1, sizeof(cost));
		for(int i = 0; i < h; i++) {
			for(int j = 0; j < w; j++)
				data[i][j] = getchar();
			getchar();
		}
		int cnt = 0;
		for(int i = 1; i < h - 1; i++)
			for(int j = 1; j < w - 1; j++) {
				char temp = data[i][j];
				if(islower(temp)) s[temp - 'a'] = cnt;
				if(isupper(temp)) d[temp - 'A'] = cnt;
				if(temp != '#') id[i][j] = cnt++;
			}

		for(int i = 1; i < h - 1; i++)
			for(int j = 1; j < w - 1; j++) {
				int ncnt = 0;
				if(data[i][j] != '#') {
					int index = id[i][j];
					for(int k = 0; k < 5; k++) {
						int neiy = i + dy[k];
						int neix = j + dx[k];
						if(data[neiy][neix] != '#')
							G[index][ncnt++] = id[neiy][neix];
					}
					edgeN[index] = ncnt;
				}
			}

		if(n < 3) {
			edgeN[cnt] = 1;
			G[cnt][0] = cnt;
			s[2] = d[2] = cnt++;
		}
		else if(n < 2) {
			edgeN[cnt] = 1;
			G[cnt][0] = cnt;
			s[1] = d[1] = cnt++;
		}
		if(s[0] == d[0] && s[1] == d[1] && s[2] == d[2])
			printf("0\n");
		else bfs();
	}
}
