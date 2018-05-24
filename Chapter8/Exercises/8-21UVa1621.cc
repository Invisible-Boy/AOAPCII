/**
 * Title:   8-21UVa1621
 * Author:  InvisibleMan
 * Date:    2017-5-15
 * Time:    55ms
 */

// 参考了网上的代码，代码并没有通过UVa的测试，感觉是评测机制出了问题，使用在VJ上通过的代码进行测试，也不能通过
/**
 * 具体思路为，对于3，2，1三种门票，如果比较大的使用完，且停在在最后一个位置p，
 * 在p的左侧的所有位置都已经访问过，则在p右侧的所有位置都可以用较小的门票全部访问
 * 通过构造出一种对较大门票的访问，做出所有的访问
 * 在UVaLive中通过
 */

#include <cstdio>

using namespace std;

inline void move(int &now, int num, int step) {
    for(int i = 0; i < num; i++) {
        now += step;
        printf(" %d", now);
    }
}

int main() {
    int T;
    while(scanf("%d", &T) == 1) while(T--) {
        int a, b, c, now = 0;
        scanf("%d%d%d", &a, &b, &c);
        int aim = a + b + c;
        printf("0");
        int k = c / 3;
        if(c % 3 == 0) {
            move(now, k, 3);
            move(now, 1, 1);
            move(now, k, -3);
            move(now, 1, 1);
            move(now, k, 3);
            a -= 2;
        }
        else if(c % 3 == 1) {
            move(now, k + 1, 3);
            move(now, 1, -2);
            move(now, k, -3);
            move(now, 1, 1);
            move(now, k, 3);
            move(now, 1, 2);
            b -= 2;
            a -= 1;
        }
        else {
            move(now, k + 1, 3);
            move(now, 1, -1);
            move(now, k, -3);
            move(now, 1, -1);
            move(now, k + 1, 3);
            a -= 2;
        }
        for(int i = 0; i < a - 1; i++)
            printf(" %d", ++now);
        if(b % 2 == 0) {
            move(now, b >> 1, 2);
            move(now, 1, 1);
            move(now, b >> 1, -2);
        }
        else {
            move(now, (b >> 1) + 1, 2);
            move(now, 1, -1);
            move(now, b >> 1, -2);
        }
        printf("\n");
    }
    return 0;
}
