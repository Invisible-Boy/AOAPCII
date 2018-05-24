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
    cin >> T; cin.get(); //�Ե����Ļس�
    string temp; temp.reserve(200);
    data.reserve(200); //Ϊvector�����ڴ�֮�󣬿���ֱ�ӷ��ʣ�����size()���ᷢ���ı䣬������Ҳ�������Խ����
    bug.insert(' '); bug.insert('#'); bug.insert('|'); bug.insert('-');
    while(T--)
    {
        data.clear();
        while(getline(cin, temp) && temp != "#")
            data.push_back(temp);
        cout << '(';
        int numrow = (int)data.size(), numcolum = 0;
        if(numrow) numcolum = (int)data[0].size(); //data.clear()֮�󣬲������ͷ�֮ǰռ�õ��ڴ�
                                                   //���������ж�data�Ĵ�С��ֱ�ӷ���data[0]�ܿ���������֮��ĵ�һ��Ԫ��
        for(int j = 0; j < numcolum; j++)
            if(!bug.count(data[0][j])) {Tree(0, j, numrow); break;}
        cout << ")\n";
    }
    return 0;
}
