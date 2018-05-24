/*
 * Title:	6-9UVa127
 * Author:	Invisible_Man
 * Time:	2016-11-11
 */

#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	int pre[52], next[52];
	string temp;
	while((cin >> temp) && temp[0] != '#') {
		stack<string> data[52];
		int len = 52;
		data[0].push(temp);
		pre[0] = -1; next[0] = 1;
		for(int i = 1; i < 52; i++) {
			cin >> temp;
			data[i].push(temp);
			pre[i] = i - 1;
			next[i] = i + 1;
		}
		next[51] = -1;
		bool flag = true;
		while(flag) {
			flag = false;
			for(int it = next[0]; it != -1; it = next[it]) {
				string str1 = data[it].top();
				int p = pre[it];
				for(int i = 0; i < 2 && p != -1; i++)
					p = pre[p];
				if(p != -1)
				{
					string str2 = data[p].top();
					if(str1[0] == str2[0] || str1[1] == str2[1]) {
						flag = true;
						data[p].push(str1);
						data[it].pop();
						if(data[it].empty()) {
							len--;
							if(next[it] != -1)
								pre[next[it]] = pre[it];
							next[pre[it]] = next[it];
						}
						break;
					}
				}
				p = pre[it];
				if(p != -1) {
					string str2 = data[p].top();
					if(str1[0] == str2[0] || str1[1] == str2[1]) {
						flag = true;
						data[p].push(str1);
						data[it].pop();
						if(data[it].empty()) {
							len--;
							if(next[it] != -1)
								pre[next[it]] = pre[it];
							next[pre[it]] = next[it];
						}
						break;
					}
				}
			}
		}
		cout << len;
		if(len > 1) cout << " piles ";
		else cout << " pile ";
		cout << "remaining: " << data[0].size();
		for(int it = next[0]; it != -1; it = next[it])
			cout << ' ' << data[it].size();
		cout << endl;
	}
	return 0;
}
