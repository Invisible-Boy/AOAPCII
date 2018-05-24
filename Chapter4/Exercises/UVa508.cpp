#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;
struct sn
{
    string s;
    int num;
};
int main()
{
    freopen("input.txt", "r", stdin);
    map<char, string> char_map;
    map<string, sn> string_map;
    set<string> data;
    char c;
    string temp, morse; temp.reserve(80), morse.reserve(80);
    while(cin.get(c) && c != '*')
    {
        cin >> temp;
        char_map[c] = temp;
        cin.get();
    }
    while((cin >> temp) && temp != "*")
    {
        data.insert(temp);
        string::iterator p = temp.begin();
        for(; p != temp.end(); p++)
            morse += char_map[*p];
        if(!string_map.count(morse)) string_map[morse].s = temp, string_map[morse].num = 1;
        else
        {
            string_map[morse].num++;
            if(temp < string_map[morse].s) string_map[morse].s = temp;
        }
        morse.clear();
    }
    while((cin >> morse) && morse != "*")
    {
        bool flag = false;
        if(string_map.count(morse))
        {
            cout << string_map[morse].s;
            if(string_map[morse].num != 1) cout << '!';
            cout << endl;
            flag = true;
        }
        else
        {
            map<string, sn>::iterator p = string_map.begin();
            string result; result.reserve(20);
            int len = (int)morse.length(), chan_num = 1000000000;
            for(; p != string_map.end(); p++)
            {
                int len1 = (int)p->first.length(), chan = abs(len - len1);
                if(len == len1) continue;
                if(chan <= chan_num)
                {
                    string temp1 = len > len1 ? morse : p->first;
                    temp1.resize(min(len, len1));
                    if(temp1 == morse || temp1 == p->first)
                    {
                        flag = true;
                        if(chan < chan_num) chan_num = abs(len - len1), result = p->second.s;
                        else if(p->second.s < result) result = p->second.s;
                    }
                }
            }
            //if(!flag) result = *data.begin();
            cout << result << "?\n";
        }
    }
    return 0;
}
