/*
 * Title:	6-14UVa12118
 * Author:	Invisible_Man
 * Time:	2016-11-16
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1001;

vector<int> grpv;
vector<vector<int> > edge;
vector<bool> vis;

int DFS(int i) {
	int sum = 0;
	vis[i] = false;
	int len = edge[i].size();
	sum += len % 2;
	for(int j = 0; j < len; j++)
		if(vis[edge[i][j]])
			sum += DFS(edge[i][j]);
	return sum;
}

int main() {
	int m, n, t, result, caseNum = 1;
	while((cin >> m >> n >> t) && (m || n || t)) {
		if(n == 0) result = 0;
		else{
			vis.clear(); vis.resize(m + 1, 0);
			edge.clear(); edge.resize(m + 1);
			grpv.clear();
			for(int i = 0; i < n; i++) {
				int t1, t2;
				cin >> t1 >> t2;
				edge[t1].push_back(t2);
				edge[t2].push_back(t1);
				vis[t1] = vis[t2] = true;
			}
			if(t == 0) result = 0;
			else {
				for(int i = 1; i <= m; i++)
					if(vis[i])
						grpv.push_back(DFS(i));
				int len = (int)grpv.size();
				if(len == 1) {
					if(grpv[0] <= 2) result = n;
					else result = ((grpv[0] - 1) >> 1) + n;
				}
				else {
					int sum = 0;
					sort(grpv.begin(), grpv.end());
					for(int i = len - 1; i > 1; i--)
						if(grpv[i] > 1)
							sum += grpv[i] - 2;
						else
							sum += grpv[i];
					for(int i = 0; i < 2; i++)
						if(grpv[i] > 0)
							sum += grpv[i] - 1;
						else
							sum += grpv[i] + 1;
					result = n + len - 1;
					if(sum > 2) result += (sum - 1) >> 1;
				}
 			}
			
		}
		cout << "Case " << caseNum++ << ": " << result * t << endl;
	}
	return 0;
}
