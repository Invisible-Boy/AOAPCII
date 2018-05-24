/**
 * Title:   8-2UVa1610
 * Author:  InvisibleMan
 * Date:    2017-4-4
 * Time:    0ms
 */

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string str[1001];

int main() {
    int n;
    while((cin >> n) && n) {
        for(int i = 0; i < n; i++)
            cin >> str[i];
        sort(str, str + n);
        string s1 = str[n / 2], s2 = str[n / 2 - 1];
        string ans;
        for(int i = 0; i < s2.length(); i++) {
            ans += s2[i];
            if(ans == s2)
                break;
            if(ans[i] != 'Z') {
                ++ans[i];
                if(ans >= s2 && ans < s1)
                    break;
                --ans[i];
            }
        }
        cout << ans << endl;
    }
    return 0;
}
