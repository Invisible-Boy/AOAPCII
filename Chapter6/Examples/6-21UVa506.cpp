#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef pair<int, int> mypair;
vector<string> name_base;
map<string, int> name2id;
vector<vector<int> > depend, depended;
vector<mypair> status;
vector<int> status_type;
int status_id = 1;
int add_name(string &name)
{
    int id;
    if(name2id.count(name)) return name2id[name];
    name2id[name] = id = (int)name_base.size();
    name_base.push_back(name);
    depend.push_back(vector<int>());
    depended.push_back(vector<int>());
    status.push_back(mypair(id, 0));
    status_type.push_back(0);
    return id;
}
void Install(int id)
{
    vector<int>::iterator p = depend[id].begin(), q = depend[id].end();
    for(; p != q; p++)
    {
        if(!status_type[*p])
        {
            status_type[*p] = 1;
            Install(*p);
        }
    }
    status[id].second = status_id++;
    cout << "   Installing " << name_base[id] << endl;
}
bool needed(int id)
{
    vector<int>::iterator p = depended[id].begin(), q = depended[id].end();
    for(; p != q; p++)
        if(status[*p].second) return true;
    return false;
}
void Remove(int id)
{
    if(status_type[id] == 1 && !needed(id))
    {
        cout << "   Removing " << name_base[id] << endl;
        status[id].second = 0;
        status_type[id] = 0;
        vector<int>::iterator p = depend[id].begin(), q = depend[id].end();
        for(; p != q; p++)
            Remove(*p);
    }
}
bool cmp(mypair &A, mypair &B)
{
    return A.second < B.second;
}
void List(vector<mypair> mylist)
{
    sort(mylist.begin(), mylist.end(), cmp);
    vector<mypair>::iterator p = mylist.begin(), q = mylist.end();
    for(; p != q; p++)
        if(p->second != 0)
            cout << "   " << name_base[p->first] << endl;
}
int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    string line;
    istringstream input;
    while(getline(cin, line) && line != "END")
    {
        cout << line << endl;
        input.clear(), input.str(line);
        string cmd, item;
        input >> cmd;
        if(cmd == "DEPEND")
        {
            input >> item;
            int id1 = add_name(item);
            while(input >> item)
            {
                int id2 = add_name(item);
                depend[id1].push_back(id2);
                depended[id2].push_back(id1);
            }
        }
        else if(cmd == "INSTALL")
        {
            input >> item;
            int id1 = add_name(item);
            if(!status_type[id1])
            {
                status_type[id1] = 2;
                Install(id1);
            }
            else
                cout << "   " << name_base[id1] << " is already installed.\n";
        }
        else if(cmd == "REMOVE")
        {
            input >> item;
            int id1 = add_name(item);
            if(!status_type[id1])
                cout << "   " << name_base[id1] << " is not installed.\n";
            else if(needed(id1))
                cout << "   " << name_base[id1] << " is still needed.\n";
            else
            {
                status_type[id1] = 1;
                Remove(id1);
            }
        }
        else
            List(status);
    }
    cout << "END\n";
    return 0;
}
