#include <iostream>
#include <algorithm>
#include <map>
#include <queue>
#include <string>
#include <cstdio>
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    int T, k_num = 0;
    while(cin >> T && T)
    {
        cout << "Scenario #" << ++k_num << endl;
        map<int, int> member;
        for(int i = 0; i < T; i++)
        {
            int num;
            cin >> num;
            while(num--)
            {
                int people_code;
                cin >> people_code;
                member[people_code] = i;
            }
        }
        string cmd;
        queue<int> inter_q[1000], intra_q;
        while(cin >> cmd && cmd[0] != 'S')
        {
            if(cmd[0] == 'E')
            {
                int en_p;
                cin >> en_p;
                if(inter_q[member[en_p]].empty())
                    intra_q.push(member[en_p]);
                inter_q[member[en_p]].push(en_p);
            }
            else
            {
                cout << inter_q[intra_q.front()].front() << endl;
                inter_q[intra_q.front()].pop();
                if(inter_q[intra_q.front()].empty())
                    intra_q.pop();
            }
        }
        cout << endl;
    }
    return 0;
}
