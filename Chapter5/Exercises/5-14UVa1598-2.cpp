#include <iostream>
#include <map>
#include <set>
#include <list>
#include <cstdio>
using namespace std;
struct cmd
{
    int id, csize;
};
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int n, case_n = 0;
    while(cin >> n)
    {
        if(case_n++) cout << endl;
        map<int, list<cmd> > sell_map;
        //此版本较上一个版本，区别就在于在这里使用了map的三参数定义法，这样可以定义key的排序方式
        //这样就不用像第一版，使用rbegin和rend
        map<int, list<cmd>, greater<int> >  buy_map;
        for(int i = 1; i <= n; i++)
        {
            string mycmd; mycmd.reserve(10);
            cin >> mycmd;
            map<int, list<cmd> >::iterator p;
            set<int> c_set;
            list<cmd>::iterator pp;
            if(mycmd[0] == 'C')
            {
                int id; cin >> id;
                if(!c_set.count(id))
                {
                    c_set.insert(id);
                    bool flag = true;
                    p = buy_map.begin();
                    while(flag && p != buy_map.end())
                    {
                        pp = p->second.begin();
                        while(flag && pp != p->second.end())
                            if(pp->id == id)
                            {
                                flag = false;
                                p->second.erase(pp);
                                if(p->second.empty()) buy_map.erase(p);
                            }
                            else pp++;
                        p++;
                    }
                    p = sell_map.begin();
                    while(flag && p != sell_map.end())
                    {
                        pp = p->second.begin();
                        while(flag && pp != p->second.end())
                            if(pp->id == id)
                            {
                                flag = false;
                                p->second.erase(pp);
                                if(p->second.empty()) sell_map.erase(p);
                            }
                            else pp++;
                        p++;
                    }
                }
            }
            else
            {
                int csize, cprice, trade_size, trade_price;
                cin >> csize >> cprice;
                if(mycmd[0] == 'B')
                {
                    p = sell_map.begin();
                    while(csize && p != sell_map.end() && cprice >= p->first)
                    {
                        pp = p->second.begin();
                        while(pp != p->second.end() && csize)
                        {
                            trade_size = 0; trade_price = p->first;
                            if(csize >= pp->csize)
                            {
                                csize -= pp->csize;
                                trade_size += pp->csize;
                                p->second.erase(pp++);
                            }
                            else
                            {
                                trade_size += csize;
                                pp->csize -= csize;
                                csize = 0;
                            }
                            cout << "TRADE " << trade_size << ' ' << trade_price << endl;
                        }
                        if(p->second.empty()) sell_map.erase(p++);
                        else break;
                    }
                    if(csize)
                    {
                        cmd temp;
                        temp.id = i;
                        temp.csize = csize;
                        buy_map[cprice].push_back(temp);
                    }
                }
                else
                {
                    p = buy_map.begin();
                    while(csize && p != buy_map.end() && cprice <= p->first)
                    {
                        pp = p->second.begin();
                        while(pp != p->second.end() && csize)
                        {
                            trade_size = 0; trade_price = p->first;
                            if(csize >= pp->csize)
                            {
                                csize -= pp->csize;
                                trade_size += pp->csize;
                                p->second.erase(pp++);
                            }
                            else
                            {
                                pp->csize -= csize;
                                trade_size += csize;
                                csize = 0;
                            }
                            cout << "TRADE " << trade_size << ' ' << trade_price << endl;
                        }
                        if(p->second.empty()) buy_map.erase(p++);
                        else break;
                    }
                    if(csize)
                    {
                        cmd temp;
                        temp.id = i;
                        temp.csize = csize;
                        sell_map[cprice].push_back(temp);
                    }
                }
            }
            int bid_price = 0, bid_size = 0, ask_price = 99999, ask_size = 0;
            if(!buy_map.empty())
            {
                p = buy_map.begin();
                bid_price = p->first;
                pp = p->second.begin();
                for(; pp != p->second.end(); pp++) bid_size += pp->csize;
            }
            if(!sell_map.empty())
            {
                p = sell_map.begin();
                ask_price = p->first;
                pp = p->second.begin();
                for(; pp != p->second.end(); pp++) ask_size += pp->csize;
            }
            cout << "QUOTE " << bid_size << ' ' << bid_price << " - " << ask_size << ' ' << ask_price << endl;
        }
    }
    return 0;
}
