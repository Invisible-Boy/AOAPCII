#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <set>
using namespace std;
vector<string> data;
set<char> bug;
void Tree(int i, int j, int numrow)
{
    if(bug.count(data[i][j])) return;
    cout << data[i][j] << '(';
    if(i + 1 < numrow && data[i + 1][j] == '|')
    {
        int p, q, len; p = q = j;
        while(p > 0 && data[i + 2][p - 1] == '-') p--;
        len = (int)data[i + 2].size();
        while(q + 1 < len && data[i + 2][q + 1] == '-') q++;
        for(; p <= q && p < (int)data[i+3].size(); p++)
            Tree(i + 3, p, numrow);
    }
    cout << ')';
}
int main()
{
    freopen("input.txt", "r", stdin);
    int T;
    cin >> T; cin.get(); //吃掉最后的回车
    string temp; temp.reserve(200);
    data.reserve(200); //为vector分配内存之后，可以直接访问，但是size()不会发生改变，编译器也不会进行越界检查
    bug.insert(' '); bug.insert('#'); bug.insert('|'); bug.insert('-');
    while(T--)
    {
        data.clear();
        while(getline(cin, temp) && temp != "#")
            data.push_back(temp);
        cout << '(';
        int numrow = (int)data.size(), numcolum = 0;
        if(numrow) numcolum = (int)data[0].size(); //data.clear()之后，并不会释放之前占用的内存
                                                   //因此如果不判断data的大小，直接访问data[0]很可能是上轮之后的第一行元素
        for(int j = 0; j < numcolum; j++)
            if(!bug.count(data[0][j])) {Tree(0, j, numrow); break;}
        cout << ")\n";
    }
    return 0;
}
