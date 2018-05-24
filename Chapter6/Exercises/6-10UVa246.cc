/*
 * Title:	6-10UVa246
 * Author:	Invisible_Man
 * Time:	2016-11-13
 */

// tip:使用set保存之前经历的状态,对于vector之类的容器，默认比较大小的方式为类似字典序，即从前往后，依次比较各个元素的大小

#include <iostream>
#include <deque>
#include <vector>
#include <set>

using namespace std;

typedef deque<int> deq;

int main() {
	int temp;
	while((cin >> temp) && temp) {
		vector<deq> data(8);
		set<vector<deq> > vis;
		data[0].push_back(temp);
		for(int i = 0; i < 51; i++) {
			cin >> temp;
			data[0].push_back(temp);
		}
		int result = 0;
		for(int i = 0; i < 2; i++)
			for(int j = 1; j < 8; j++) {
				data[j].push_back(data[0].front());
				data[0].pop_front();
				result++;
			}
		vis.insert(data);
		int flag = 0; // flag = 1 win; flag = 2 loss; flag = 3 draw;
		while(!flag) {
			flag = 1;
			for(int i = 1; i < 8; i++) {
				if(data[i].empty())	continue;
				flag = 0;
				if(data[0].empty()) {
					flag = 2;
					break;
				}
				else {
					result++;
					data[i].push_back(data[0].front());
					data[0].pop_front();
					bool flag_c = true; // continue pick up or not
					while(flag_c && (int)data[i].size() >= 3) {
						flag_c = false;
						deq::reverse_iterator p = data[i].rbegin();
						if((data[i][0] + data[i][1] + *p) % 10 == 0) {
							flag_c = true;
							data[0].push_back(data[i][0]);
							data[0].push_back(data[i][1]);
							data[0].push_back(data[i].back());
							data[i].pop_front();
							data[i].pop_front();
							data[i].pop_back();
						}
						else if((data[i][0] + *p + *(p + 1)) % 10 == 0) {
							flag_c = true;
							data[0].push_back(data[i][0]);
							data[0].push_back(*(p + 1));
							data[0].push_back(*p);
							data[i].pop_front();
							data[i].pop_back();
							data[i].pop_back();
						}						
						else if((*p + *(p + 1) + *(p + 2)) % 10 == 0) {
							flag_c = true;
							data[0].push_back(*(p + 2));
							data[0].push_back(*(p + 1));
							data[0].push_back(*p);
							data[i].pop_back();
							data[i].pop_back();
							data[i].pop_back();
						}
					}
					if(vis.count(data)) {
						flag = 3;
						break;
					}
					vis.insert(data);
				}
			}
		}
		if(flag == 1) cout << "Win : ";
		else if(flag == 2) cout << "Loss: ";
		else cout << "Draw: ";
		cout << result << endl;
	}
	return 0;
}
