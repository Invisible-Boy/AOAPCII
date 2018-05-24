/*
 * Title:	7-9UVa1601
 * Author:	InvisibleMan
 * Time:	2016-12-19
 */

// 参考了很多刘汝佳的代码，后续还需要继续改进

#include <cstdio>
#include <queue>
#include <cstring>
#include <cctype>

using namespace std;
const int Nmax = 17;
const int stateMax = 17 * 17;
const int dy[] = {0, 1, -1, 0, 0};
const int dx[] = {0, 0, 0, -1, 1};

int w, h, n,
	s[3], d[3], id[Nmax][Nmax], G[Nmax * Nmax][5], edgeN[Nmax * Nmax], cost[stateMax][stateMax][stateMax];

int st(int a, int b, int c) {
	return (a << 16) + (b << 8) + c;
}

bool isok(int a, int newa, int b, int newb) {
	return newa != newb && (a != newb || b != newa);
}

void bfs() {
	cost[s[0]][s[1]][s[2]] = 0;
	queue<int> q;
	q.push(st(s[0], s[1], s[2]));
	while(!q.empty()) {
		int a, b, c, state;
		state = q.front(); q.pop();
		a = state >> 16;
		b = (state >> 8) & 0xff;
		c = state & 0xff;
		for(int i = 0; i < edgeN[a]; i++)
			for(int j = 0; j < edgeN[b]; j++) {
				int newa = G[a][i];
				int newb = G[b][j];
				if(isok(a, newa, b, newb)) {
					for(int k = 0; k < edgeN[c]; k++) {
						int newc = G[c][k];
						if(isok(a, newa, c, newc) && isok(b, newb, c, newc) && cost[newa][newb][newc] < 0) {
							cost[newa][newb][newc] = cost[a][b][c] + 1;
							if(newa == d[0] && newb == d[1] && newc == d[2]) {
								printf("%d\n", cost[newa][newb][newc]);
								return;
							}
							q.push(st(newa, newb, newc));
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
				if(islower(data[i][j])) s[data[i][j] - 'a'] = cnt;
				if(isupper(data[i][j])) d[data[i][j] - 'A'] = cnt;
				if(data[i][j] != '#') id[i][j] = cnt++;
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
