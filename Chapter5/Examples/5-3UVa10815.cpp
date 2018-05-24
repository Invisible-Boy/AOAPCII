#include <iostream>
#include <string>
#include <set>
#include <cctype>
#include <sstream>
#include <cstdio>
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    set<string> dict;
    string s;
    while(cin >> s)
    {
        for(int i = 0; i < (int)s.length(); i++)
            if(isalpha(s[i]))
                s[i] = tolower(s[i]);
            else
                s[i] = ' ';
        stringstream ss(s);
        while(ss >> s)
            dict.insert(s);
    }

    for(set<string> :: iterator it = dict.begin(); it != dict.end(); it++)
        cout << *it << endl;
    return 0;
}
