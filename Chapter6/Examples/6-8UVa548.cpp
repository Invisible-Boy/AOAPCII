#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstdio>
using namespace std;
const int Max = 10000, INF = 100000001; //INF表示当左或右子树为空时，将和设为一个很大的数
vector<int> mid, after;
typedef pair<int, int> node;
node result(int mid_b, int mid_e, int aft_b, int aft_e)
{
    int v_root = after[aft_e--], i, num;
    if(aft_e < aft_b) return node(v_root, v_root);
    for(i = mid_b; i <= mid_e && mid[i] != v_root; i++);
    num = i - mid_b - 1;
    node temp_l, temp_r;
    if(num >= 0)
    {
        temp_l = result(mid_b, mid_b + num, aft_b, aft_b + num);
        temp_l.first += v_root;
    }
    else temp_l.first = INF;
    num = mid_e - i - 1;
    if(num >= 0)
    {
        temp_r = result(mid_e - num, mid_e, aft_e - num, aft_e);
        temp_r.first += v_root;
    }
    else temp_r.first = INF;
    if(temp_l.first != temp_r.first) return temp_l.first < temp_r.first ? temp_l : temp_r;
    return temp_l.second < temp_r.second ? temp_l : temp_r;
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    mid.reserve(Max), after.reserve(Max);
    istringstream ss;
    string s; s.reserve(50000);
    while(getline(cin, s))
    {
        ss.clear(), ss.str(s);
        int temp;
        while(ss >> temp) mid.push_back(temp);
        getline(cin, s);
        ss.clear(), ss.str(s);
        while(ss >> temp) after.push_back(temp);
        cout << result(0, (int)mid.size()-1, 0, (int)after.size()-1).second << endl;
        mid.clear(); after.clear();
    }
    return 0;
}
