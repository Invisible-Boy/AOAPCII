/*
 * Title:	EightQueen.cc
 * Author:	InvisibleMan
 * Time:	2016-12-11
 */

#include <iostream>

using namespace std;

const int Nmax = 20;

int n, tot, c[Nmax];
bool vis[3][Nmax * 2] = {0};

void search(int cur) {
	if(cur == n) {
		tot++;
		return;
	}
	for(int i = 0; i < n; i++)
		if(!vis[0][i] && !vis[1][cur + i] && !vis[2][n + i - cur]) {
			c[cur] = i;
			vis[0][i] = vis[1][cur + i] = vis[2][n + i - cur] = true;
			search(cur + 1);
			vis[0][i] = vis[1][cur + i] = vis[2][n + i - cur] = false;
	}
}

int main() {
	cin >> n;
	tot = 0;
	search(0);
	cout << tot;	
	return 0;
}
