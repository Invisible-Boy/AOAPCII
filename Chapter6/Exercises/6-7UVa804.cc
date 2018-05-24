/*
 * Title:	6-7UVa804
 * Author:	Invisible_Man
 * Time:	2016-11-9
 * Tips:
 * 此题是一个简答的模拟题，主要是想明白开关的作用
 * 开关需要先判断是否可以打开，一旦可以打开就进行转移
 * 此题第二个坑就是，要理清题意，题目说的时，一旦可以发生转移就立刻转移，
 * 而同时转移的tokens不能认为是一次转移（即同时发生的也认为是多次）
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Tran {
	map<int, int> input, output;
};

int main() {
	int n, m, k, numCase = 1; // num of place, num of tran, num of firings
	while((cin >> n) && n) {
		bool flag = true; // the net is live
		vector<int> dataPlace(n + 1, 0);
		for(int i = 1; i <= n; i++)
			cin >> dataPlace[i];
		cin >> m;
		vector<Tran> dataTran(m);
		for(int i = 0; i < m; i++) {
			int temp;
			while((cin >> temp) && temp)
				if(temp > 0)
					if(dataTran[i].output.count(temp))
						dataTran[i].output[temp]++;
					else
						dataTran[i].output[temp] = 1;
				else {
					temp = -temp;
					if(dataTran[i].input.count(temp))
						dataTran[i].input[temp]++;
					else
						dataTran[i].input[temp] = 1;
				}
		}
		cin >> k;
		int cnt = 0; // now firing number
		map<int, int>::iterator p, q;
		while(cnt < k && flag) {
			flag = false;
			for(int i = 0; i < m; i++) {
				bool Enable = true;
				p = dataTran[i].input.begin();
				q = dataTran[i].input.end();
				for(; p != q && Enable; p++)
					if(dataPlace[p->first] < p->second)
						Enable = false;
				if(Enable) {
					flag = true;
					p = dataTran[i].input.begin();
					for(; p != q; p++)
						dataPlace[p->first] -= p->second;
					p = dataTran[i].output.begin();
					q = dataTran[i].output.end();
					for(; p != q; p++)
						dataPlace[p->first] += p->second;
					if(++cnt >= k) break;
				}
			}
		}
		cout << "Case " << numCase++ << ": ";
		if(flag)
			cout << "still live";
		else 
			cout << "dead";
		cout << " after " << cnt << " transitions\n";
		cout << "Places with tokens:";
		for(int i = 1; i <= n; i++)
			if(dataPlace[i] > 0)
				cout << ' ' << i << ' ' << '(' << dataPlace[i] << ')';
		cout << endl << endl;
	}
}
