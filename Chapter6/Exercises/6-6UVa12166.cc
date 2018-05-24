/*
 * Title:   6-6UVa12166
 * Author:  Invisible_Man
 * Time:    2016-11-6
 */

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

typedef long long LL;

int main() {
    int T;
    string temp;
    vector<LL> result;
    cin >> T; cin.get();
    while(T--) {
        result.clear();
        int flag = -1; 
        getline(cin, temp);
        string::iterator p = temp.begin();
        string::iterator q = temp.end();
        while(p != q) {
            if(*p == '[') flag++;
            else if(*p == ']') flag--;
            else if(isdigit(*p)) {
                LL temp = 0;
                while( p != q && isdigit(*p) ) {
                    temp = temp * 10 + *p - '0';
                    p++;
                }
                p--;
                if(flag > 0) temp = temp << flag;
                result.push_back(temp);
            }
            p++;
        }
        int len = (int)result.size();
        if(len == 1) cout << 0 << endl;
        else {
            sort(result.begin(), result.end());
            LL temp = result[0], ans = 1, anst = 1;
            for(int i = 1; i < len; i++)
                if(result[i] == temp) {
                    if(++anst > ans)
                        ans = anst;
                }
                else {
                    temp = result[i];
                    anst = 1;
                }
            cout << len - ans << endl;
        }
    }
    return 0;
}
