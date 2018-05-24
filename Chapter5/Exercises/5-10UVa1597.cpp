#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;
//此版本TLE
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int N, M;
    cin >> N; cin.get();
    char c;
    vector<vector<string> > data; data.resize(N);
    for(int i = 0; i < N; i++)
    {
        data[i].reserve(1500);
        string temp; temp.reserve(80);
        while(cin.get(c))
        {
            temp += c;
            if(c == '\n')
            {
                if(temp == "**********\n") break;
                data[i].push_back(temp);
                temp.clear();
            }
        }
    }
    cin >> M; cin.get();
    while(M--)
    {
        int flag_q = 1;
        string query;
        vector<vector<string> >::iterator p1 = data.begin();
        char c;
        bool flag = true;
        while(cin.get(c))
        {
            if(c == '\n') break;
            if(isalpha(c)) query += tolower(c);
            else query += c;
        }
        if(query.find("and") != string::npos) flag_q = 2;
        else if(query.find("or") != string::npos) flag_q = 4;
        else if(query.find("not") != string::npos) flag_q = 8;
        while(p1 != data.end())
        {
            bool flag2 = true, flag_str1 = false, flag_str2 = false;
            vector<string>::iterator p2 = p1->begin();
            queue<vector<string>::iterator> result;
            while(p2 != p1->end())
            {
                string str1, str2;
                string temp; temp.reserve(80);
                string::iterator l = p2->begin();
                for(; l != p2->end(); l++)
                    if(isalpha(*l)) temp += tolower(*l);
                    else temp += *l;
                int p, flag3 = 0;
                switch(flag_q)
                {
                case 2:
                case 4:
                    p = query.find(' ');
                    str1 = query.substr(0, p);
                    str2 = query.substr(p+1);
                    p = str2.find(' ');
                    str2 = str2.substr(p+1);
                    if(temp.find(str1) != string::npos) flag_str1 = true, result.push(p2);
                    if(temp.find(str2) != string::npos) flag_str2 = true, result.push(p2);
                    break;
                case 8:
                    p = query.find(' ');
                    str1 = query.substr(p+1);
                    if(temp.find(str1) != string::npos) flag2 = false;
                    break;
                default:
                    if(temp.find(query) != string::npos) result.push(p2);
                }
                p2++;
            }
            if((flag_q == 1 && !result.empty()) || (flag_q == 2 && flag_str1 && flag_str2) || (flag_q == 4 && (flag_str1 || flag_str2)))
            {
                if(!flag) cout << "---------\n";
                while(!result.empty())
                {
                    flag = false;
                    cout << *result.front();
                    result.pop();
                }
            }
            else if(flag2 && flag_q == 8)
            {
                if(!flag) cout << "---------\n";
                flag = false;
                vector<string>::iterator l = p1->begin();
                for(; l != p1->end(); l++) cout << *l;
            }
            p1++;
        }
        if(flag) cout << "Sorry, I found nothing.\n";
        cout << "==========\n";
    }
    return 0;
}
