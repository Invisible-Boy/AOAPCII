#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
using namespace std;
typedef map<char, pair<int, int> > MAP; //map中的char表示以该字母为开头的单词的入度（first）和出度（second）
bool flag[26], has_edge[26][26];  //flag表示节点是否存在
int DFS(int p)
{
    if(!flag[p]) return 0;
    int result = 1;
    flag[p] = false;
    for(int i = 0; i < 26; i++)
        if(flag[i] && (has_edge[p][i] || has_edge[i][p])) result += DFS(i);
    return result;
}
int main()
{
    int n, m;
    string str; str.reserve(1001);
    MAP mymap;
    cin >> n;
    while(n--)
    {
        bool flag_r = false;
        char b, e;
        mymap.clear();
        memset(flag, 0, sizeof(flag)); memset(has_edge, 0, sizeof(has_edge));
        cin >> m;
        while(m--)
        {
            cin >> str;
            b = *str.begin(); e = *(str.rbegin());
            mymap[b].second++; mymap[e].first++;
            flag[b - 'a'] = true; flag[e - 'a'] = true;
            has_edge[b - 'a'][e - 'a'] = true;
        }
        if(DFS(b - 'a') == (int)mymap.size())
        {
            int i = 0, temp_b = 0, temp_e = 0;
            MAP::iterator p = mymap.begin();
            for(; p != mymap.end() && i < 3; p++)
                if(p->second.first != p->second.second)
                    if(abs(p->second.first - p->second.second) != 1) i = 3;
                    else
                    {
                        i++;
                        temp_e += p->second.second;
                        temp_b += p->second.first;
                    }
            if(i < 3 && temp_b == temp_e) flag_r = true;
        }
        if(flag_r) cout << "Ordering is possible.\n";
        else cout << "The door cannot be opened.\n";
    }
    return 0;
}
