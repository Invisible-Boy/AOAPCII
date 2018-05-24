/**
 * Title:   7-8UVa12107
 * Author:  InvisibleMan
 * Date:    2017-2-13
 * Time:    120ms
 */

#include <iostream>
#include <string>

using namespace std;

const char s[] = {'*', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
int num[3];
string str, str1;

bool init() {
    string temp;
    cin >> temp;
    if(temp[0] == '0') return false;
    str = temp;
    num[0] = temp.size();
    for(int i = 1; i < 3; i++) {
        cin >> temp;
        num[i] = temp.size();
        str += temp;
    }
    return true;
}

int judge(int now) {
    if(now == num[0] + num[1]) {
        int n[3] = {0}, nn = 0;
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < num[i]; j++)
                n[i] = n[i] * 10 + str[nn++] - '0';
        n[2] = n[0] * n[1];
        char temp[4];
        for(int i = num[2] - 1; i > -1; i--) {
            temp[i] = n[2] % 10 + '0';
            n[2] /= 10;
        }
        if(n[2] || temp[0] == '0') return 0;
        int begin = num[0] + num[1];
        for(int i = 0; i < num[2]; i++)
            if(str[begin + i] != temp[i] && str[begin + i] != '*') return 0;
        if(n[0] == n[1] || num[0] != num[1]) return 1;
        for(int i = 0; i < num[0]; i++)
            if(!(str1[i] == str1[num[0] + i] || (str1[i] == '*' && str1[num[0] + i] == '*') 
                || (str1[i] == '*' && str1[num[0] + i] == str[i])
                || (str1[num[0] + i] == '*' && str1[i] == str[num[0] + i])))
                return 1;
        return 2;
    }
    int ans = 0;
    if(str[now] == '*') {
        for(int i = 0; i < 10; i++) {
            if((now == 0 || now == num[0] || now == num[0] + num[1]) && i == 0) continue;
            str[now] = '0' + i;
            ans += judge(now + 1);
            if(ans > 1) break;
        }
        str[now] = '*';
    }
    else ans += judge(now + 1);
    return ans;
}

bool dfs(int now, int max, int start) {
    if(str.length() - start < max - now) return false;
    if(now == max) {
        str1 = str;
        if(judge(0) == 1) return true;
        return false;
    }
    bool flag = true;
    for(int i = 0; i < 11; i++) {
        if((s[i] >= str[start]) && flag) {
            if(dfs(now, max, start + 1))
                return true;
            else flag = false;
        }
        if(s[i] == str[start] || ((start == 0 || start == num[0] || start == num[1] + num[0]) && i == 1)) continue;
        char t = str[start];
        str[start] = s[i];
        if(dfs(now + 1, max, start + 1)) return true;
        str[start] = t;
    }
    return false;
}

int main() {
    int cnt = 0;
    while(init()) {
        for(int i = 0; i <= (int)str.length(); i++)
            if(dfs(0, i, 0)) break;
        cout << "Case " << ++cnt << ':';
        int sta = 0;
        for(int i = 0; i < 3; i++) {
            cout << ' ';
            for(int j = 0; j < num[i]; j++)
                cout << str[sta++];
        }
        cout << endl;
    }
    return 0;
}
