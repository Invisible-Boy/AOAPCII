#include <iostream>
#include <stack>
#include <cstdio>
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int n, temp, i = 1, j = 1, num = 0;
    while((cin >> n) && n)
    {
        stack<int> s;
        bool flag = true;
        while((cin >> temp) && temp)
        {
            while(i < n)
            {
                if(flag)
                    if(temp == j) j++;
                    else
                    {
                        while(j <= temp && j <= n) s.push(j++);
                        if(s.empty() || temp != s.top()) flag = false;
                        else s.pop();
                    }
                cin >> temp;
                i++;
            }
            cout << (flag ? "Yes\n" : "No\n");
            flag = true, i = 1, j = 1;
        }
        cout << endl;
    }
    return 0;
}
