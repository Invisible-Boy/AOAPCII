/**
 * Title:   乘船问题NYOJ-71
 * Author:  InvisibleMan
 * Date:    2017-3-11
 * Time:    0ms
 */

#include <cstdio>
#include <algorithm>
// #include <functional> //本地测试没有问题，但是在oj上编译出错，less算子是在这个库中的

using namespace std;

int main() {
    int T, w, n, weight[310];
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &w, &n);
        for(int i = 0; i < n; i++) 
            scanf("%d", &weight[i]);
        sort(weight, weight + n);
        // sort(weight, weight + n, less<int>()); // sort默认是从小到大
        int p = 0, q = n, ans = 0;
        while(q > p) {
            q--;
            if(weight[p] + weight[q] <= w || (p == q && weight[p] <= w)) p++;
            ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
