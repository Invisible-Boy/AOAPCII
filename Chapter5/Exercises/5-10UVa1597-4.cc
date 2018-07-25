/**
 * Author:  InvisibleMan
 * Date;    2018/7/26
 * Time:    50ms
 */

#include <cstdio>
#include <string>
#include <unordered_map>
#include <set>
#include <cctype>
#include <cstring>

using namespace std;

char data[1505][85];
int tot = 0;

const char *End = "**********\n";
const char *Sep1 = "----------\n";
const char *Sep2 = "==========\n";

unordered_map<string, int> str2int;
unordered_map<int, set<int> > mp[105];
int start[105];

void addTag(string &str, int now, int index) {
    int id = 0;
    if(str2int.count(str)) id = str2int[str];
    else {
        id = str2int.size();
        str2int[str] = id;
    }
    str.clear();
    mp[now][id].insert(index);
}
int main() {
    int n;
    scanf("%d\n", &n);
    for(int i = 0; i < n; i++) {
        start[i] = tot;
        while(1) {
            fgets(data[tot], 85, stdin);
            if(strcmp(data[tot], End) == 0)
                break;
            string temp;
            char *str = data[tot];
            while(*str != '\0') {
                if(isalpha(*str)) temp += tolower(*str);
                else if(!temp.empty())
                    addTag(temp, i, tot);
                str++;
            }
            tot++;
        }
    }
    int m;
    scanf("%d\n", &m);
    string cmd[3];
    while(m--) {
        int cnt = 0;
        char t;
        while((t = getc(stdin)) != '\n') {
            if(t == ' ') cnt++;
            else cmd[cnt] += tolower(t);
        }
        bool flag = false;
        if(cnt == 0 && str2int.count(cmd[0])) {
            int id = str2int[cmd[0]];
            for(int i = 0; i < n; i++) {
                if(mp[i].count(id)) {
                    if(flag) printf("%s", Sep1);
                    flag = true;
                    set<int>::iterator p = mp[i][id].begin(), q = mp[i][id].end();
                    while(p != q)
                        printf("%s", data[*p++]);
                }
            }
        }
        else if(cnt == 1 && cmd[0] == "not") {
            int id = str2int[cmd[1]];
            for(int i = 0; i < n; i++) {
                if(mp[i].count(id) == 0) {
                    if(flag) printf("%s", Sep1);
                    flag = true;
                    int over = i + 1 < n ? start[i + 1] : tot;
                    for(int j = start[i]; j < over; j++)
                        printf("%s", data[j]);
                }
            }
        }
        else if(cnt == 2) {
            if(cmd[1] == "and" && str2int.count(cmd[0]) && str2int.count(cmd[2])) {
                int id[2] = {str2int[cmd[0]], str2int[cmd[2]]};
                for(int i = 0; i < n; i++) {
                    set<int> temp;
                    set<int>::iterator p, q;
                    if(mp[i].count(id[0]) && mp[i].count(id[1])) {
                        if(flag) printf("%s", Sep1);
                        flag = true;
                        for(int k = 0; k < 2; k++) {
                            p = mp[i][id[k]].begin(), q = mp[i][id[k]].end();
                            while(p != q) temp.insert(*p++);
                        }
                        p = temp.begin(), q = temp.end();
                        while(p != q)
                            printf("%s", data[*p++]);
                    }
                }
            }
            else if(cmd[1] == "or" && (str2int.count(cmd[0]) || str2int.count(cmd[2]))) {
                int id[2] = {str2int.count(cmd[0]) ? str2int[cmd[0]] : -1, str2int.count(cmd[2]) ? str2int[cmd[2]] : -1};
                for(int i = 0; i < n; i++) {
                    set<int> temp;
                    set<int>::iterator p, q;
                    if(mp[i].count(id[0]) || mp[i].count(id[1])) {
                        if(flag) printf("%s", Sep1);
                        flag = true;
                        for(int k = 0; k < 2; k++) {
                            if(mp[i].count(id[k]) < 1) continue;
                            p = mp[i][id[k]].begin(), q = mp[i][id[k]].end();
                            while(p != q) temp.insert(*p++);
                        }
                        p = temp.begin(), q = temp.end();
                        while(p != q)
                            printf("%s", data[*p++]);
                    }
                }
            }
        }
        if(!flag)
            printf("Sorry, I found nothing.\n");
        printf("%s", Sep2);
        for(int i = 0; i < 3; i++) cmd[i].clear();
    }
    return 0;
}
