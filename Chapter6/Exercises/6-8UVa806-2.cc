/*
 * Title:	6-8UVa806-2
 * Author:	Invisible_Man
 * Time:	2016-11-10
 */

#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 64;
int data[MAXN][MAXN];
vector<int> qTreeId;

void image2Tree(int index[], int size, int weight, int value, int dirt) {
	bool flag = true;
	value += dirt * weight;
	int ch = data[index[0]][index[1]];
	for(int i = index[0]; flag && i < index[0] + size; i++)
		for(int j = index[1]; flag && j < index[1] + size; j++)
			if(data[i][j] != ch) flag = false;
	if(flag && ch) qTreeId.push_back(value);
	else if(!flag) {
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
	while(scanf("%d", &n) == 1 && n) {
		memset(data, 0, sizeof(data));
		qTreeId.clear();
		if(numCase++) putchar('\n');
		printf("Image %d", numCase);
		if(n > 0) {
			getchar();
			for(int i = 0; i < n; i++) {
				char s[MAXN];
				scanf("%s", s);
				for(int j = 0; j < n; j++)
					data[i][j] = s[j] - '0';
			}
			int index[2] = {0};
			image2Tree(index, n, 0, 0, 0);
			sort(qTreeId.begin(), qTreeId.end());
			int len = (int)qTreeId.size();
			for(int i = 0; i < len; i++)
				if(i % 12 == 0) printf("\n%d", qTreeId[i]); 
				else printf(" %d", qTreeId[i]);
			printf("\nTotal number of black nodes = %d\n", len);
		}
		else {
			int temp;
			n = -n;
			while(scanf("%d", &temp) && temp != -1)
				qTreeId.push_back(temp);
			for(int i = 0; i < (int)qTreeId.size(); i++)
				Tree2Image(n, qTreeId[i]);
			printf("\n");
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++)
					if(data[i][j]) putchar('*');
					else putchar('.');
				putchar('\n');
			}
		}
	}
	return 0;
}
