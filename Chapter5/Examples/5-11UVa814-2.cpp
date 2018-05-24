#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <cstdio>
using namespace std;
void read(string s, string& name, string& mta){
    bool flag = true;
    for(int i = 0; i < (int)s.length(); i++)
        if(s[i] == '@') flag = false;
        else if(flag) name += s[i];
        else mta += s[i];
}
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    string s;
    vector<set<string> > MTA_base;
    map<string, int> MTAID;
    while(cin >> s && s == "MTA"){
        string name, mta;
        int num;
        cin >> mta >> num;
        if(!MTAID.count(mta))
            MTAID[mta] = (int)MTA_base.size(), MTA_base.resize((int)MTA_base.size() + 1);
        while(num--)
            cin >> name, MTA_base[MTAID[mta]].insert(name);
    }
    while(cin >> s && s != "*"){
        queue<string> q1, q2[(int)MTA_base.size()];
        string s_name, s_mta, DATA;
        set<string> rev;
        read(s, s_name, s_mta);
        while(cin >> s && s != "*"){
            string r_name, r_mta;
            if(rev.count(s))
                continue;
            rev.insert(s);
            read(s, r_name, r_mta);
            if(q2[MTAID[r_mta]].empty())
                q1.push(r_mta);
            q2[MTAID[r_mta]].push(r_name);
        }
        char temp = cin.get();
        while(char a = cin.get()){
            if(temp == '\n' && a == '*') break;
            DATA += temp;
            temp = a;
        }
        DATA = DATA + '\n' + '.' + '\n';
        while(!q1.empty()){
            cout << "Connection between " << s_mta << " and " << q1.front() << endl;
            cout << "     HELO " << s_mta << endl << "     250" << endl;
            cout << "     MAIL FROM:<" << s_name << '@' << s_mta << '>' << endl << "     250" << endl;
            int id = MTAID[q1.front()];
            bool flag = false;
            while(!q2[id].empty()){
                cout << "     RCPT TO:<" << q2[id].front() << '@' << q1.front() << '>' << endl;
                if(MTA_base[id].count(q2[id].front()))
                    cout << "     250" << endl, flag = true;
                else
                    cout << "     550" << endl;
                q2[id].pop();
            }
            if(flag){
                cout << "     DATA" << endl << "     354";
                for(int i = 0; i < (int)DATA.length(); i++)
                    if(DATA[i] == '\n') cout << endl << "     ";
                    else cout << DATA[i];
                cout << "250" << endl;
            }
            cout << "     QUIT" << endl << "     221" << endl, q1.pop();
        }
    }
    return 0;
}
