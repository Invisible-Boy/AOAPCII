/*
 * Title：	7-7UVa140
 * Author:	InvisibleMan
 * Time:	2016-12-13
 */

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <cctype>
#include <algorithm>

// 注意输入可能临界点包含自己，同时题目只是说包含邻居节点，并没有说包含全部的邻居节点。

using namespace std;
set<char> g[26];
map<char, int> index;
int minband, cnt;
char result[8], temp[8];

int find(char temp) {
	int it = temp - 'A';
	int n = 0, m = 0;
	set<char>::iterator p = g[it].begin();
	for(; p != g[it].end(); p++)
		if(index[*p] >= 0)
			n = max(n, index[temp] - index[*p]);
		else m++;
	return n > m ? n : m;
}

void search(int len, int nowband) {
	if(len == cnt && nowband < minband) {
		for(int i = 0; i < len; i++)
			result[i] = temp[i];
		minband = nowband;
		return;
	}
	map<char, int>::iterator p;
	for(p = index.begin(); p != index.end(); p++) {
		if(p->second < 0) {
			p->second = len;
			int newband = max(find(p->first), nowband);
			if(newband < minband) {
				temp[len] = p->first;
				search(len + 1, newband);
			}
			p->second = -1;
		}
	}
}

void init() {
	map<char, int>::iterator p;
	for(p = index.begin(); p != index.end(); p++)
		g[p->first - 'A'].clear();
	index.clear();
}

int main() {
	string str; str.reserve(100);
	while((cin >> str) && str[0] != '#') {
		str += ';';
		cnt = 0;
		minband = 1000;
		for(int i = 0; i < (int)str.length(); i++) {
			index[str[i]] = -1;
			int it = str[i] - 'A';
			i += 2;
			while(isalpha(str[i])) {
				index[str[i]] = -1;
				g[str[i] - 'A'].insert('A' + it);
				g[it].insert(str[i++]);
			}
		}
		cnt = (int)index.size();
		search(0, 0);
		for(int i = 0; i < cnt; i++)
			cout << result[i] << ' ';
		cout << "-> " << minband << endl;
		init();
	}
	return 0;
}
