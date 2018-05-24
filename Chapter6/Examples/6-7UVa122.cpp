#include <iostream>
#include <map>
#include <string>
#include <cstdio>
//ʹ��map��������
using namespace std;
struct node
{
    string name;
    int len;
    bool operator < (node B) const
    {
        if(this->len != B.len) return this->len < B.len;
        return this->name < B.name;
    }
};
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    string s; s.reserve(30);
    map<node, string> mymap;
    while(cin >> s)
    {
        int pos = s.find(','), pos1 = s.find(')');
        string myfirst = s.substr(1, pos - 1), mysecond = s.substr(pos + 1, pos1 - pos - 1);
        if(mysecond.empty() && !myfirst.empty()) mysecond = "A";
        node temp; temp.name = mysecond; temp.len = (int)mysecond.length();
        mymap[temp] = myfirst;
        bool flag = true; //�ж����Ƿ���������
        while((cin >> s) && s != "()")
        {
            pos = s.find(','), pos1 = s.find(')');
            myfirst = s.substr(1, pos - 1), mysecond = s.substr(pos+1, pos1 - pos - 1);
            if(mysecond.empty()) mysecond = "A";
            temp.name = mysecond; temp.len = (int)mysecond.length();
            if(!mymap.count(temp)) mymap[temp] = myfirst;
            else flag = false; //����ظ���ֵ�������������������
        }
        map<node, string>::iterator p = mymap.begin();
        if(p->first.name != "A" && flag) flag = false; //���û�и��ڵ㣬������������
        else if(flag)
            for(;p != mymap.end(); p++)
            {
                if(p->first.len == 1) continue; //����һ�����Ѿ��ж��и��ڵ㣬���еڶ�����Բ����ж�
                node t; //���û�и��ڵ㣬˵��������������
                t.name = p->first.name.substr(0, p->first.len - 1);
                t.len = (int)t.name.length();
                if(!mymap.count(t))
                {
                    flag = false;
                    break;
                }
            }
        if(flag)
        {
            p = mymap.begin();
            cout << p->second; p++;
            while(p != mymap.end())
            {
                cout << ' ' << p->second;
                p++;
            }
        }
        else cout << "not complete";
        cout << endl;
        mymap.clear();
    }
    return 0;
}
