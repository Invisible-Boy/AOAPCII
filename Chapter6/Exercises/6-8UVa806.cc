/*
 * Title:	6-8UVa806
 * Author:	Invisible_Man
 * Time:	2016-11-10
 */

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

const int MAXN = 64;
int data[MAXN][MAXN];
vector<int> qTreeId;

void image2Tree(int index[], int size, int weight, int value, int dirt) {
	int num[2] = {0};
	value += dirt * weight;
	for(int i = index[0]; i < index[0] + size; i++)
		for(int j = index[1]; j < index[1] + size; j++)
			num[data[i][j]]++;
	if(num[1] == size * size) qTreeId.push_back(value);
	else if(num[1] > 0) {
	weight = weight == 0 ? 1 : weight * 5;
	size = size >> 1;
		int index2[4][2] = { {index[0], index[1]}, 
							 {index[0], index[1] + size},
							 {index[0] + size, index[1]},
							 {index[0] + size, index[1] + size}
						   };
		for(int i = 0; i < 4; i++)
			image2Tree(index2[i], size, weight, value, i + 1);
	}
}

void Tree2Image(int size, int value) {
	int index[2] = {0};
	while(value) {
		size = size >> 1;
		int index2[4][2] = {{index[0], index[1]},
						{index[0], index[1] + size},
						{index[0] + size, index[1]},
						{index[0] + size, index[1] + size}
						};
		int id = value % 5;
		index[0] = index2[id - 1][0];
		index[1] = index2[id - 1][1];
		value /= 5;
	}
	for(int i = index[0]; i < index[0] + size; i++)
		for(int j = index[1]; j < index[1] + size; j++)
			data[i][j] = 1;
	return;
}

int main() {
	int n, numCase = 0;
	while((cin >> n) && n) {
		memset(data, 0, sizeof(data));
		qTreeId.clear();
		if(numCase++) cout << endl;
		cout << "Image " << numCase;
		if(n > 0) {
			cin.get();
			for(int i = 0; i < n; i++) {
				string s;
				getline(cin, s);
				for(int j = 0; j < n; j++)
					data[i][j] = s[j] - '0';
			}
			int index[2] = {0};
			image2Tree(index, n, 0, 0, 0);
			sort(qTreeId.begin(), qTreeId.end());
			int len = (int)qTreeId.size();
			for(int i = 0; i < len; i++)
				if(i % 12 == 0) cout << endl << qTreeId[i];
				else cout << ' ' << qTreeId[i];
			cout << "\nTotal number of black nodes = " << len << endl; 
		}
		else {
			int temp;
			n = -n;
			while((cin >> temp) && temp != -1)
				qTreeId.push_back(temp);
			for(int i = 0; i < (int)qTreeId.size(); i++)
				Tree2Image(n, qTreeId[i]);
			cout << endl;
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++)
					if(data[i][j]) cout << '*';
					else cout << '.';
				cout << endl;
			}
		}
	}
	return 0;
}
