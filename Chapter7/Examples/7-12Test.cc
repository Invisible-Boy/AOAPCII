#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main() {
    freopen("input", "w", stdout);
    for(int n = 0; n < 20; n++) {
        int cnt[3] = {0};
        for(int i = 0; i < 24;) {
            int temp = rand() % 3;
            if(cnt[temp] < 8) {
                cout << temp + 1 << ' ';
                i++;
                cnt[temp]++;
            }
        }
        cout << endl;
    }
    return 0;
}
