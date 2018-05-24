/**
 * Title:   6-20UVa1620
 * Author:  InvisibleMan
 * Date:    2017-5-19
 * Time:    0ms
 */

/**
 * 参考了网上的思路，此题主要是要想到连续翻转4位数，则产生序列的逆序对个数为偶数
 * 同时当数组的长度为偶数时，总有一种序列序列的逆序对为偶数
 * 当数组长度为奇数时，若逆序对长度为奇数，则不会有逆序对为偶数的序列
 * 此题网上有相关的证明(但都缺乏存在性证明，即只要是偶数个逆序对一定存在恢复序列的方法)
 * 此处就不再赘述
 */
#include <cstdio>

using namespace std;

int main() {
    int T, d[500];
    while(scanf("%d", &T) == 1) while(T--){
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
            scanf("%d", &d[i]);
        int cnt = 0;
        for(int i = 0; i < n; i++)
            for(int j = i + 1; j < n; j++)
                if(d[i] > d[j]) cnt++;
        if(cnt % 2 && n % 2) printf("impossible\n");
        else printf("possible\n");
    }
    return 0;
}
