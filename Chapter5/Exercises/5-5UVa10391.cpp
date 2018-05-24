#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cstdio>
using namespace std;
//第一版的思路采用合成词，但是复杂度为n^2，超时
bool cmp(string& A, string& B)
{
    return (int)A.length() < (int)B.length() || ((int)A.length() == (int)B.length() && A < B);
}
int main()
{
    freopen("input.txt", "r", stdin);
    vector<string> data; data.reserve(120000);
    set<string> data_b, result;
    string temp;
    while(cin >> temp)
    {
        data.push_back(temp);
        data_b.insert(temp);
    }
    sort(data.begin(), data.end(), cmp);
    data.resize(unique(data.begin(), data.end()) - data.begin());
    vector<string>::iterator p, p1;
    for(p = data.begin(); p != data.end() - 1; p++)
        for(p1 = p + 1; p1 != data.end(); p1++)
        {
            temp = *p + *p1;
            if((int)temp.length() > (int)data.back().length()) break;
            if(data_b.count(temp)) result.insert(temp);
            temp = *p1 + *p;
            if(data_b.count(temp)) result.insert(temp);
        }
    for(set<string>::iterator p = result.begin(); p != result.end(); p++) cout << *p << endl;
    return 0;
}
