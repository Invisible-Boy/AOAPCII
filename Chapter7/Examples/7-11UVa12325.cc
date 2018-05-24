/**
 * Title:   7-11UVa12325
 * Author:  InvisibleMan
 * Time:    2016-12-28
 */

// 第一个版本，速度为80ms

#include <iostream>

using namespace std;

typedef uint64_t LL;

int main() {
    int n, T, index, nMax;
    LL ans, s[2], v[2];
    cin >> T;
    for(int i = 1; i <=T; i++) {
        ans = 0;
        cout << "Case #" << i << ": ";
        cin >> n >> s[0] >> v[0] >> s[1] >> v[1];
        if(s[0] * s[1] < n) {
            LL newV[2] = {s[1] * v[0], s[0] * v[1]};
            index = newV[0] > newV[1] ? 1 : 0;
            nMax = s[1 - index];
        }
        else {
            index = s[0] > s[1] ? 0 : 1;
            nMax = n / s[index] + 1;
        }
        for(int j = 0; j < nMax; j++) {
            LL temp = v[index] * j + (n - s[index] * j) / s[1 - index] * v[1 - index];
            ans = temp > ans ? temp : ans;
        }
        cout << ans << endl;
    }
    return 0;
}
