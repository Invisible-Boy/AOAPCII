#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <cctype>
#include <string>
#include <cstdio>
using namespace std;
map<char, int> a_in;
map<char, map<int, int> > b_in;
bool bug_hunt(string& s)
{
    bool flag = true;
    stack<char> mystack[2];
    string::iterator p;
    int i = 0, num[2] = {0};
    for(p = s.begin(); p != s.end(); p++)
        if(*p == '=') i++, flag = false;
        else if(isalpha(*p)) mystack[i].push(*p);
        else if(isdigit(*p)) num[i] = num[i] * 10 + *p - '0';
    char temp = mystack[0].top(); mystack[0].pop();
    while(!mystack[0].empty())
    {
        if(!a_in.count(temp) || num[0] >= a_in[temp] || !b_in[temp].count(num[0])) return false;
        num[0] = b_in[temp][num[0]];
        temp = mystack[0].top(); mystack[0].pop();
    }
    if(flag)
    {
        a_in[temp] = num[0];
        return true;
    }
    else
    {
        if(!a_in.count(temp) || num[0] >= a_in[temp]) return false;
        else if(mystack[1].empty())
        {
            b_in[temp][num[0]] = num[1];
            return true;
        }
        else
        {
            while(!mystack[1].empty())
            {
                char temp1 = mystack[1].top(); mystack[1].pop();
                if(!a_in.count(temp1) || num[1] >= a_in[temp1] || !b_in[temp1].count(num[1])) return false;
                num[1] = b_in[temp1][num[1]];
            }
            b_in[temp][num[0]] = num[1];
            return true;
        }
    }
}
int main()
{
    freopen("input.txt", "r", stdin);
    string s;
    while(cin >> s && s[0] != '.')
    {

        int i = 1;
        bool flag = true;
        flag = bug_hunt(s);
        if(!flag) cout << "1\n";
        while(cin >> s && s[0] != '.')
        {
            if(!flag) continue;
            flag = bug_hunt(s); i++;
            if(!flag) cout << i << '\n';
        }
        if(flag) cout << 0 << '\n';
        a_in.clear(); b_in.clear();
    }
    return 0;
}
