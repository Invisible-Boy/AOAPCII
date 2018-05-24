#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdio>
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int N;
    cin >> N; cin.get();
    while(N--)
    {
        map<string, string> set1, set2, whole;
        vector<string> add, sub, change; add.reserve(100), sub.reserve(100), change.reserve(100);
        char c;
        string key, value; key.reserve(50), value.reserve(50);
        cin.get();
        bool flag = true;
        while(cin.get(c) && c != '\n')
        {
            if(key.empty() && c == '}') continue;
            if(c == ':') flag = false;
            else if(c == ',' || c == '}')
                set1[key] = value, whole[key] = value, flag = true, key.clear(), value.clear();
            else if(flag) key += c;
            else value += c;
        }
        cin.get();
        while(cin.get(c) && c != '\n')
        {
            if(key.empty() && c == '}') continue;
            if(c == ':') flag = false;
            else if(c == ',' || c == '}')
                set2[key] = value, whole[key] = value, flag = true, key.clear(), value.clear();
            else if(flag) key += c;
            else value += c;
        }
        map<string, string>::iterator p = whole.begin();
        for(; p != whole.end(); p++)
        {
            if(!set1.count(p->first)) add.push_back(p->first);
            else if(!set2.count(p->first)) sub.push_back(p->first);
            else if(set1[p->first] != p->second) change.push_back(p->first);
        }
        vector<string>::iterator pp;
        if(!add.empty())
        {
            cout << '+';
            for(pp = add.begin(); pp != add.end() - 1; pp++) cout << *pp << ',';
            cout << *pp << '\n';
        }
        if(!sub.empty())
        {
            cout << '-';
            for(pp = sub.begin(); pp != sub.end() - 1; pp++) cout << *pp << ',';
            cout << *pp << '\n';
        }
        if(!change.empty())
        {
            cout << '*';
            for(pp = change.begin(); pp != change.end() - 1; pp++) cout << *pp << ',';
            cout << *pp << '\n';
        }
        if(add.empty() && sub.empty() && change.empty()) cout << "No changes\n";
        cout << '\n';
    }
    return 0;
}
