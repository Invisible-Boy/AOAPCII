#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <cstdio>
using namespace std;
struct index
{
    map<int, set<vector<string>::iterator> > myiter; //存储一个映射表
};
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int N, M;
    cin >> N; cin.get();
    char c;
    vector<vector<string> > data; data.resize(N);
    vector<vector<string> >::iterator p = data.begin();
    map<string, index> mymap;
    for(int i = 0; i < N; i++, p++)
    {
        string temp; temp.reserve(85);
        p->reserve(1500);     //vector不能预置的太小，否则重新分配内存的时候，会使之前的引用失效（可以把1500改为1来验证）
                              //如果p->reserve(50)，则只奥有一个doc超过50行，则vector会重新分配内存，使得p++不能正确指向下个doc的地址
        while(cin.get(c))
        {
            temp += c;
            if(c == '\n')
            {
                if(temp == "**********\n") break;
                else
                {
                    p->push_back(temp);
                    string temp1; temp1.reserve(85);
                    for(string::iterator pp = temp.begin(); pp != temp.end(); pp++)
                    {
                        if(isalpha(*pp)) temp1 += tolower(*pp);
                        else if(!temp1.empty())
                            mymap[temp1].myiter[i].insert(p->end()-1), temp1.clear();
                    }
                }
                temp.clear();
            }
        }
    }
    cin >> M; cin.get();
    while(M--)
    {
        string str[3];
        bool flag = false;
        int l = 0, flag_q = 1;
        while(cin.get(c))      //可能有单词中含有and、or、not，所以不能直接find，会报错
        {
            if(c == '\n') break;
            else if (c == ' ') l++;
            else if(isalpha(c)) str[l] += tolower(c);
        }
        if(str[0] == "not") flag_q = 8;
        else if(str[1] == "and") flag_q = 2;
        else if(str[1] == "or") flag_q = 4;
        for(int i = 0; i < N ; i++)
        {
            set<vector<string>::iterator > result;
            if(flag_q == 1 && mymap.count(str[0]) && mymap[str[0]].myiter.count(i))
            {
                if(flag) cout << "----------\n";
                for(set<vector<string>::iterator>::iterator j = mymap[str[0]].myiter[i].begin(); j != mymap[str[0]].myiter[i].end(); j++)
                    cout << **j;
                flag = true;
            }
            else if(flag_q == 2 && mymap.count(str[0]) && mymap.count(str[2]) && mymap[str[0]].myiter.count(i) && mymap[str[2]].myiter.count(i))
            {
                for(set<vector<string>::iterator>::iterator j = mymap[str[0]].myiter[i].begin(); j != mymap[str[0]].myiter[i].end(); j++)
                    result.insert(*j);
                for(set<vector<string>::iterator>::iterator j = mymap[str[2]].myiter[i].begin(); j != mymap[str[2]].myiter[i].end(); j++)
                    result.insert(*j);
                if(flag) cout << "----------\n";
                for(set<vector<string>::iterator>::iterator j = result.begin(); j != result.end(); j++)
                    cout << **j;
                flag = true;
            }
            else if(flag_q == 4)
            {
                if(mymap.count(str[0]) && mymap[str[0]].myiter.count(i))
                    for(set<vector<string>::iterator>::iterator j = mymap[str[0]].myiter[i].begin(); j != mymap[str[0]].myiter[i].end(); j++)
                        result.insert(*j);
                if(mymap.count(str[2]) && mymap[str[2]].myiter.count(i))
                    for(set<vector<string>::iterator>::iterator j = mymap[str[2]].myiter[i].begin(); j != mymap[str[2]].myiter[i].end(); j++)
                        result.insert(*j);
                if(!result.empty())
                {
                    if(flag) cout << "----------\n";
                    for(set<vector<string>::iterator>::iterator j = result.begin(); j != result.end(); j++)
                        cout << **j;
                    flag = true;
                }
            }
            else if(flag_q == 8 && !(mymap.count(str[1]) && mymap[str[1]].myiter.count(i)))
            {
                if(flag) cout << "----------\n";
                for(int j = 0; j < (int)data[i].size(); j++)
                    cout << data[i][j];
                flag = true;
            }
        }
        if(!flag) cout << "Sorry, I found nothing.\n";
        cout << "==========\n";
     }
    return 0;
}
