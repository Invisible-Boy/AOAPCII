#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cctype>
#include <cstdio>
//直接每个command都遍历会TLE，需要按照题目所给出的方法来简化复杂度
using namespace std;
int main()
{
    freopen("input1.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int N, M;
    char c;
    cin >> N; cin.get(); //吃掉N后面的回车
    vector<vector<string> > data; data.resize(N);
    vector<vector<string> >::iterator p = data.begin();
    while(N--)
    {
        string temp; temp.reserve(80);
        p->reserve(100);
        while(cin.get(c))
        {
            temp += c;
            if(c == '\n')
            {
                if(temp == "**********\n") break;
                p->push_back(temp), temp.clear();
            }
        }
        p++;
    }
    cin >> M; cin.get(); //吃掉M后面的回车
    while(M--)
    {
        bool flag = false; //flag表示此次command是否有过输出
        int cmd = 1, l; //表示query是什么操作
        string query, str1, str2; query.reserve(80); str1.reserve(40); str2.reserve(40);
        while(cin.get(c))
        {
            if(c == '\n') break;
            if(isalpha(c)) query += tolower(c);
            else query += c;
        }
        l = query.find(' ');
        if(query.find("and") != string::npos)
        {
            cmd = 2;
            str1 = query.substr(0, l); str2 = query.substr(l+5);
        }
        else if(query.find("or") != string::npos)
        {
            cmd = 4;
            str1 = query.substr(0, l); str2 = query.substr(l+4);
        }
        else if(query.find("not") != string::npos)
        {
            cmd = 8;
            str1 = query.substr(l+1);
        }
        else str1 = query;
        for(p = data.begin(); p != data.end(); p++)
        {
            bool flag1 = false, flag_str1 = false, flag_str2 = false, flag_not = true; //flag1表示文本内是否有过输出
            vector<string>::iterator pp;
            queue<vector<string>::iterator > q;
            for(pp = p->begin(); pp != p->end(); pp++)
            {
                string temp; temp.reserve(80);
                string::iterator ppp;
                for(ppp = pp->begin(); ppp != pp->end(); ppp++)
                    if(isalpha(*ppp)) temp += tolower(*ppp);
                    else temp += *ppp;
                if(cmd != 8)
                {
                    if(temp.find(str1) != string::npos) flag_str1 = true, q.push(pp);
                    if(temp.find(str2) != string::npos && cmd > 1) flag_str2 = true, q.push(pp);
                }
                else
                    if(temp.find(str1) != string::npos) flag_not = false;
            }
            if(cmd != 8)
            {
                if((cmd == 1 && !q.empty()) || (cmd == 2 && flag_str1 && flag_str2) || (cmd == 4 && (flag_str1 || flag_str2)))
                {
                    while(!q.empty())
                    {
                        if(flag && !flag1) cout << "---------\n";
                        flag = true, flag1 = true, cout << *q.front(); q.pop();
                    }
                }
            }
            else if(flag_not)
            {
                if(flag && !flag1) cout << "---------\n";
                for(pp = p->begin(); pp != p->end(); pp++)
                    flag = true, flag1 = true, cout << *pp;
            }
        }
        if(!flag) cout << "Sorry, I found nothing.\n";
        cout << "==========\n";
    }
    return 0;
}
