#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdio>
//此版本只是为了精简代码，使得写的行数变少，效率没有太大的改变
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int N;
    cin >> N; cin.get();
    while(N--)
    {
        map<string, string> myset[2], whole;
        vector<string> ch[3]; ch[0].reserve(100), ch[1].reserve(100), ch[2].reserve(100);
        char c;
        string key, value; key.reserve(50), value.reserve(50);
        bool flag = true;
        for(int i = 0; i < 2; i++)
        {
            cin.get();
            while(cin.get(c) && c != '\n')
            {
                if(key.empty() && c == '}') continue;
                if(c == ':') flag = false;
                else if(c == ',' || c == '}')
                    myset[i][key] = value, whole[key] = value, flag = true, key.clear(), value.clear();
                else if(flag) key += c;
                else value += c;
            }
        }
        map<string, string>::iterator p = whole.begin();
        for(; p != whole.end(); p++)
        {
            if(!myset[0].count(p->first)) ch[0].push_back(p->first);
            else if(!myset[1].count(p->first)) ch[1].push_back(p->first);
            else if(myset[0][p->first] != p->second) ch[2].push_back(p->first);
        }
        vector<string>::iterator pp;
        char symbol[] = {'+', '-', '*'};
        for(int i = 0; i < 3; i++)
        {
            if(!ch[i].empty())
            {
                flag = false;
                cout << symbol[i];
                for(pp = ch[i].begin(); pp != ch[i].end() - 1; pp++) cout << *pp << ',';
                cout << *pp << '\n';
            }
        }
        if(flag) cout << "No changes\n";
        cout << '\n';
    }
    return 0;
}
