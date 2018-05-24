#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <cstdio>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
    string data; data.reserve(128);
    int n;
    cin >> n; cin.get();
    while(n--)
    {
        getline(cin, data);
        string::iterator p = data.begin();
        stack<char> mystack;
        bool ok = true;
        for(; p != data.end(); p++)
            if(*p == '(' || *p == '[')
            	mystack.push(*p);
            else if(*p == ')' || *p == ']')
            {
                if(mystack.empty() || abs(*p - mystack.top()) > 2)
                {
                	
                    ok = false;
                    break;
                }
                mystack.pop();
            }
        if(!mystack.empty()) ok = false;
        if(ok) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
