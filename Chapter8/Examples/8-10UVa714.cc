/**
 * Title:   8-10UVa714
 * Author:  InvisibleMan
 * Date:    2017-3-22
 * Time:    0ms
 */

// tips: 贪心+二分查找

#include <cstdio>

using namespace std;

typedef unsigned int uint;

uint num[501], div[501];
int T, n, k;

uint find(uint p, uint q) {
    if(p == q) return p;
    uint mid = (p + q) >> 1;
    int i = 0, j = 0;
    while(j++ < k && i < n) {
        uint nowSum = 0;
        while(i < n && nowSum + num[i] <= mid)
            nowSum += num[i++];
    }
    return i==n ? find(p, mid) : find(mid + 1, q);
}

int main() {
    uint sum;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &k);
        for(int i = 0; i < n; i++) {
            scanf("%u", &num[i]);
            sum += num[i];
        }
        uint ans = find(0, sum);
        int index = k - 2, i = n - 1;
        while(index > -1) {
            uint nowSum = 0;
            while(i > index && nowSum + num[i] <= ans)
                nowSum += num[i], i--;
            div[index--] = i;
        }
        for(int i = 0, j = 0; i < n - 1; i++) {
            printf("%u ", num[i]);
            if(i == div[j]) {
                printf("/ ");
                j++;
            }
        }
        printf("%d\n", num[n - 1]);
    }
    return 0;
}
