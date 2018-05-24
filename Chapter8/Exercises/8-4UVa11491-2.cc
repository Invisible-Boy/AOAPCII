/**
 * Title;   8-4UVa11491-2
 * Author:  InvisibleMan
 * Date:    2017-4-6
 * Time:    0ms
 */

// tips: 参考了网上的代码，只是简单的模拟就可以完成整个操作
#include <cstdio>

const int Nmax = 1e5 + 1;
char ans[Nmax];

int main() {
    int n, d;
    while(scanf("%d%d\n", &n, &d) == 2 && n) {
        d = n - d;
        int k = 0;
        for(int i = 0; i <= d; i++) ans[i] = '\0';
        // 每个字符最多被加入和删除两次，因此复杂度还是O(n)
        // 相比之下可以不适用单调队列来维护性质，更加方便
        for(int i = 0; i < n; i++) {
            char t = getchar();
            while(k > -1 && n - i + k >= d && t > ans[k]) --k;
            if(k + 1 < d)
                ans[++k] = t;
        }
        getchar();
        printf("%s\n", ans);
    }
    return 0;
}
