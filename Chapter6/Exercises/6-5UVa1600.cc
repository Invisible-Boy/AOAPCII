/*
 * Title:   6-5UVa1600
 * Author:  Invisible_Man
 * Time:    2016-10-5
 */

#include <iostream>
#include <cstring>
#include <queue>
#include <cmath>

using namespace std;

const int MAXN = 21;
const int INF = 1000000;

int m, n, k;
bool vis[MAXN][MAXN], data[MAXN][MAXN];
int K[MAXN][MAXN];

struct Node {
    int x, y, num;
    Node(int x, int y, int num) : x(x), y(y), num(num) {}
};

bool isLegal(int x, int y) {
    return x >= 1 && x <= m && y >= 1 && y <= n;
}

int BFS() {
    if(m == 1 && n == 1) return 0;
    queue<Node> q[2];
    q[0].push(Node(1, 1, 0));
    vis[1][1] = true;
    K[1][1] = 0;
    int layer = 0;
    while(!q[layer].empty()) {
        while(!q[layer].empty()) {
            int nowX = q[layer].front().x;
            int nowY = q[layer].front().y;
            int nowNum = q[layer].front().num;
            if(nowX == m && nowY == n) return nowNum;
            q[layer].pop();
            for(int i = -1; i < 2; i+=2) {
                if(isLegal(nowX + i, nowY)) {
                    if(data[nowX + i][nowY])
                        K[nowX + i][nowY] = min(K[nowX][nowY] + 1, K[nowX + i][nowY]);
                    else K[nowX + i][nowY] = 0;
                    if(K[nowX + i][nowY] <= k && !vis[nowX + i][nowY]) {
                        q[1 - layer].push(Node(nowX + i, nowY, nowNum + 1));
                        vis[nowX + i][nowY] = true;
                    }
                }
                if(isLegal(nowX, nowY + i)) {
                    if(data[nowX][nowY + i])
                        K[nowX][nowY + i] = min(K[nowX][nowY] + 1, K[nowX][nowY + i]);
                    else K[nowX][nowY + i] = 0;
                    if(K[nowX][nowY + i] <= k && !vis[nowX][nowY + i]) {
                        q[1 - layer].push(Node(nowX, nowY + i, nowNum + 1));
                        vis[nowX][nowY + i] = true;
                    }
                }
            }
        }
        layer = 1 - layer;
    }
    return -1;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        memset(vis, 0, sizeof(vis));
        memset(K, 1, sizeof(K));
        cin >> m >> n >> k;
        for(int i = 1; i <= m; i++)
            for(int j = 1; j <= n; j++)
                cin >> data[i][j];
        cout << BFS() << endl;
    }
    return 0;
}
