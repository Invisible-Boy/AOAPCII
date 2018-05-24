/*
 * Title:	6-11UVa10410
 * Author:	Invisible_Man
 * Time:	2016-11-14
 */

#include <iostream>
#include <stack>
#include <vector>

// tip:参考了题解，需要继续思考

using namespace std;

int main() {
	int n, temp;
	while(cin >> n) {
		vector<int> pos(n + 1);
		for(int i = 0; i < n; i++) {
			cin >> temp;
			pos[temp] = i;
		}
		int root;
		cin >> root;
		stack<int> s;
		s.push(root);
		vector<vector<int> > result(n + 1);
		for(int i = 1; i < n; i++) {
			cin >> temp;
			while(!s.empty()) { // 每一个后读入的节点，一定存在父节点
				int now = s.top();
				if(now == root || pos[temp] - pos[now] > 1){
					result[now].push_back(temp);
					s.push(temp); //找到父节点之后，将其入栈，寻找自己的子节点
					break;
				}
				else
					s.pop(); //不再存在子节点，出栈
			}
		}
		for(int i = 1; i <= n; i++) {
			cout << i << ':';
			vector<int>::iterator p = result[i].begin();
			vector<int>::iterator q = result[i].end();
			for(; p != q; p++)
				cout << ' ' << *p;
			cout << endl;
		}
	}
	return 0;
}
