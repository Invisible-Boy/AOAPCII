/*
 * Title:	6-12UVa810
 * Author:	Invisible_Man
 * Time:	2016-11-14
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 11;
const int sideNum = 7;
// oppent[i] = 7 - i;
const int aid[3][4] = {{2, 3, 5, 4}, {4, 6, 3 ,1}, {6, 5, 1, 2}};
const int detR[4] = {1, -1, 0, 0};
const int detC[4] = {0, 0, -1, 1};

struct Node {
	int r, c, f, t;
	Node(int r = 0, int c = 0, int f = 0, int t = 0) : r(r), c(c), f(f), t(t) {}
};

bool vis[MAXN][MAXN][sideNum][sideNum];
Node p[MAXN][MAXN][sideNum][sideNum];
int maze[MAXN][MAXN];
int right[sideNum][sideNum];
int r, c, sr, sc, st, sf;

bool hasEdge(Node &temp, int i, Node &newTemp) {
	newTemp.r = temp.r + detR[i];
	newTemp.c = temp.c + detC[i];
	if(newTemp.r < 1 || newTemp.r > r || newTemp.c < 1 || newTemp.c > c)
		return false;
	if(maze[newTemp.r][newTemp.c] != -1 && maze[newTemp.r][newTemp.c] != temp.t)
		return false;
	if(i == 0) {
		newTemp.t = 7 - temp.f;
		newTemp.f = temp.t;
	}
	else if(i == 1) {
		newTemp.t = temp.f;
		newTemp.f = 7 - temp.t;
	}
	else if(i == 2) {
		newTemp.f = temp.f;
		newTemp.t = right[temp.f][7 - temp.t];
	}
	else if(i == 3) {
		newTemp.f = temp.f;
		newTemp.t = 7 - right[temp.f][7 - temp.t];
	}
	if(vis[newTemp.r][newTemp.c][newTemp.f][newTemp.t]) return false;
	vis[newTemp.r][newTemp.c][newTemp.f][newTemp.t] = true;
	p[newTemp.r][newTemp.c][newTemp.f][newTemp.t] = temp;
	return true;
}

bool BFS() {
	bool flag = false;
	queue<Node> q;
	q.push(Node(sr, sc, sf, st));
	Node temp, newTemp;
	while(!flag && !q.empty()) {
		temp = q.front();
		q.pop();
		for(int i = 0; i < 4; i++) {
			if(hasEdge(temp, i, newTemp)) {
				if(newTemp.r == sr && newTemp.c == sc) {
					flag = true;
					break;
				}
				else q.push(newTemp);
			}
		}
	}
	return flag;
}

int main() {
	char name[25];
	for(int i = 0; i < 4; i++) {
		right[1][aid[0][i]] = aid[0][(i + 1) % 4];
		right[6][aid[0][i]] = 7 - aid[0][(i + 1) % 4];
		right[2][aid[1][i]] = aid[1][(i + 1) % 4];
		right[5][aid[1][i]] = 7 - aid[1][(i + 1) % 4];
		right[3][aid[2][i]] = aid[2][(i + 1) % 4];
		right[4][aid[2][i]] = 7 - aid[2][(i + 1) % 4];
	}
	while(scanf("%s", name) == 1 && strcmp(name, "END")) {
		printf("%s", name);
		memset(vis, 0, sizeof(vis));
		memset(p, 0, sizeof(p));
		scanf("%d%d%d%d%d%d", &r, &c, &sr, &sc, &st, &sf);
		for(int i = 1; i <= r; i++)
			for(int j = 1; j <= c; j++)
				scanf("%d", &maze[i][j]);
		if(BFS()){
			vector<Node> ans;
			for(int i = 1; i < sideNum; i++)
				for(int j = 1; j < sideNum; j++)
					if(vis[sr][sc][i][j]) {
						Node u(sr, sc, i, j);
						ans.push_back(u);
						u = p[sr][sc][i][j];
						while(true) {
							ans.push_back(u);
							if(u.r == sr && u.c == sc) break;
							u = p[u.r][u.c][u.f][u.t];
						}
						break;
					}
			int cnt = 0;
			vector<Node>::reverse_iterator p = ans.rbegin();
			vector<Node>::reverse_iterator q = ans.rend() - 1;
			for(; p != q; p++, cnt++) {
				if(cnt % 9 == 0) printf("\n  ");
				printf("(%d,%d),", p->r, p->c);
			}
			if(cnt % 9 == 0) printf("\n  ");
			printf("(%d,%d)\n", sr, sc);
		}
		else
			printf("\n  No Solution Possible\n");
	}
	return 0;
}
