#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <string>
#include <map>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef set<int> Set;
vector<Set> Setcash;
map<Set, int> IDcash;

int ID(Set x)
{
    if(IDcash.find(x) != IDcash.end())
        return IDcash[x];
    Setcash.push_back(x);
    return IDcash[x] = Setcash.size() - 1;
}

int main()
{
    freopen("input.txt", "r", stdin);
    int T, n;
    cin >> T;
    stack<int> s;
    while(T--)
    {
        cin >> n;
        while(n--)
        {
            string command;
            cin >> command;
            if(command[0] == 'P')
                s.push(ID(Set ()));
            else if(command[0] == 'D')
                s.push(s.top());
            else
            {
                Set x1 = Setcash[s.top()]; s.pop();
                Set x2 = Setcash[s.top()]; s.pop();
                Set x;
                if(command[0] == 'U')
                    set_union(x1.begin(), x1.end(), x2.begin(), x2.end(), inserter(x, x.begin()));
                else if(command[0] == 'I')
                    set_intersection(x1.begin(), x1.end(), x2.begin(), x2.end(), inserter(x, x.begin()));
                else
                {
                    x = x2;
                    x.insert(ID(x1));
                }
                s.push(ID(x));
            }
            cout << Setcash[s.top()].size() << endl;
        }
        cout << "***" << endl;
    }
    return 0;
}
