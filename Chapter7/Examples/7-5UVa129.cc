/*
 * Title:	7-6UVa129
 * Author:	InvisibleMan
 * Time:	2016-12-12
 */

#include <iostream>

using namespace std;

const int Nmax = 81;
int n, l, cur;
char result[Nmax];
bool flag;

bool isok(int len) {
	for(int i = 1; i <= (len >> 1); i++) {
		bool ok = true;
		for(int j = 0; j < i; j++)
			if(result[len - 1 - j] != result[len - 1 - i - j]) {
				ok = false;
				break;
			}
		if(ok) return false;
	}
	return true;
}

void search(int len) {
	if(flag) return;
	if(cur == n) {
		flag = true;
		cout << result[0];
		for(int i = 1; i < len; i++) {
			if(i % 64 == 0) cout << endl;
			else if(i % 4 == 0) cout << ' ';
			cout << result[i];
		}
		cout << endl << len << endl;
	}
	for(int i = 0; i < l && !flag; i++) {
		result[len] = 'A' + i;
		if(isok(len + 1)) {
			cur++;
			search(len + 1);
		}
	}
}

int main() {
	while((cin >> n >> l) && n && l) {
		flag = false;
		cur = 0;
		search(0);
	}
	return 0;
}
