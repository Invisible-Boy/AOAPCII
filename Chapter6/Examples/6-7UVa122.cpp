#include <iostream>
#include <map>
#include <string>
#include <cstdio>
//使用map代替链表
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
        bool flag = true; //判断树是否是完整的
        while((cin >> s) && s != "()")
        {
            pos = s.find(','), pos1 = s.find(')');
            myfirst = s.substr(1, pos - 1), mysecond = s.substr(pos+1, pos1 - pos - 1);
            if(mysecond.empty()) mysecond = "A";
            temp.name = mysecond; temp.len = (int)mysecond.length();
            if(!mymap.count(temp)) mymap[temp] = myfirst;
            else flag = false; //如果重复赋值，则表明树不是完整的
        }
        map<node, string>::iterator p = mymap.begin();
        if(p->first.name != "A" && flag) flag = false; //如果没有根节点，树不是完整的
        else if(flag)
            for(;p != mymap.end(); p++)
            {
                if(p->first.len == 1) continue; //在上一级中已经判断有根节点，所有第二层可以不用判断
                node t; //如果没有父节点，说明树不是完整的
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
