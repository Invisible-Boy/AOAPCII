/**
 * Title:   9-20UVa10934
 * Author:  InvisibleMan
 * Date:    2017-7-28
 * Time:    ms
 */

#include <iostream>

using namespace std;

int main() {
    int k;
    unsigned long long n, ans[105][105] = {0};
    for(int i = 1; i <= 100; i++)
        for(int j = 1; j < 64; j++)
            ans[i][j] = ans[i - 1][j - 1] + 1 + ans[i][j - 1];
    while((cin >> k >> n) && k) {
        if(ans[k][63] < n)
            cout << "More than 63 trials needed." << endl;
        else
            cout << lower_bound(ans[k], ans[k] + 64, n) - ans[k] << endl;
    }
    return 0;
}
