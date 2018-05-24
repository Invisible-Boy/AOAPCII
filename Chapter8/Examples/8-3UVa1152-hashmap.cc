/**
 * Title:   8-3UVa1152
 * Authoe:  InvisibleMan
 * Date:    2017-3-13
 * Time:    670ms
 */

// tips: 参考网上的题解，设计一个hashmap

#include <cstdio>

const int INF = 0x7fffff; // 这个数取大了会导致时间增加，取小了会导致无法hash到数组中，从而死循环

struct Hash {
    int p[INF + 1], q[INF + 1];
    void clear() {
        for(int i = 0; i <= INF; i++) // 由于hash采用的是按位取，所以这里药取等号(i <= INF, 而不是 i < INF)
            p[i] = 0;
    }
    int& operator [] (int t) {
        int i;
        for(i = t & INF; p[i] && q[i] != t; i = (i + 1) & INF); // 按位与金星hash
        q[i] = t;
        return p[i];
    }
}hash;

int main() {
    int T, n, num[4][4000];
    scanf("%d", &T);
    for(int t = 0; t < T; t++) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < 4; j++)
                scanf("%d", &num[j][i]);
        hash.clear();
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                hash[num[0][i] + num[1][j]]++;
        int cnt = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                cnt += hash[-num[2][i] - num[3][j]];
        if(t) printf("\n");
        printf("%d\n", cnt);
    }
    return 0;
}
