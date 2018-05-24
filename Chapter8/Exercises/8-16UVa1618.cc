/**
 * Title:   8-16UVa1618.cc
 * Author:  InvisibleMan
 * Date:    2017-5-9
 * Time:    30ms
 */

/**
 * 最近好久没做题，同时题目难度也增大，此题思考的思路不太对
 * 参考了网上的思路，采用分步暴力的解法
 * 直接暴力是O(n^4)，采用暴力存储中间结果,再暴力遍历a1和a3求解
 */

#include <cstdio>

using namespace std;

const int Nmax = 5005;
// mx[i][j]存储i，j之间最大元素的下标，mn[i][j]存储元素大于d[i]，且下标大于j的最小的元素值的下标
int mx[Nmax][Nmax], mn[Nmax][Nmax], n;

bool slove(int b[]) {
    for(int i = 0; i < n; i++) {
        mx[i][i] = i;
        for(int j = i + 1; j < n; j++)
            mx[i][j] = b[j] > b[mx[i][j - 1]] ? j : mx[i][j - 1];
    }
    for(int i = 0; i < n; i++) {
        mn[i][n - 1] = -1;
        for(int j = n - 2; j > i; j--) {
            if(b[j + 1] > b[i] && (mn[i][j + 1] == -1 || b[j + 1] < b[mn[i][j + 1]]))
               mn[i][j] = j + 1;
            else mn[i][j] = mn[i][j + 1];
        }
    }
    for(int i = 0; i < n - 3; i++) {
        for(int j = i + 2; j < n - 1; j++) {
            if(mn[i][j] > -1) {
                int a1 = b[i], a2 = b[mx[i][j]], a3 = b[j], a4 = b[mn[i][j]];
                if(a2 > a4 && a4 > a1 && a1 > a3) return true;
            }
        }
    }
    return false;
}

int main() {
    int T, d[Nmax], t[Nmax];
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
            scanf("%d", &d[i]);
        bool flag = slove(d);
        if(!flag) {
            for(int i = 0; i < n; i++)
                t[i] = d[n - 1 - i];
            flag = slove(t);
        }
        printf("%s\n", flag ? "YES" : "NO");
    }
    return 0;
}
