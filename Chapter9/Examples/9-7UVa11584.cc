/**
 * Title:   9-7UVa11584
 * Author:  InvisibleMan
 * Date:    2017-6-16
 * Time:    30ms
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int Nmax = 1005;

int main() {
    int n, ans[Nmax];
    char temp[Nmax];
    bool isP[Nmax][Nmax];
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%s", temp);
        int len = strlen(temp);
        for(int i = 0; i < len; i++) {
            for(int j = 0; j < i; j++) {
                isP[i][j] = false;
                if(temp[j] == temp[i] && (i - 1 <= j + 1 || isP[i - 1][j + 1]))
                    isP[i][j] = true;
            }
            isP[i][i] = true;
        }
        ans[0] = 0;
        for(int i = 1; i <= len; i++) {
            ans[i] = ans[i - 1] + 1;
            for(int j = 1; j <= i; j++) {
                if(isP[i - 1][j - 1])
                    ans[i] = min(ans[i], ans[j - 1] + 1);
            }
        }
        printf("%d\n", ans[len]);
    }
    return 0;
}
