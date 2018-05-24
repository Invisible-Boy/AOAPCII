/**
 * Title:   8-7UVa11925
 * Author:  InvisibleMan
 * Date:    2017-4-9
 * Time:    10ms
 */

// tips: 构造法,题目是从有序序列转换成给定序列

#include <cstdio>

using namespace std;

int main() {
    int n, d[301];
    while(scanf("%d", &n) == 1 && n) {
        int t;
        // 相当于将乱序序列转换为有序序列
        // 类似于带权重的排序，为每个元素赋一个权重值
        for(int i = 1; i <= n; i++) {
            scanf("%d", &t);
            d[t - 1] = i;
        }
        int head = 0;
        // 第i轮循环结束，序列尾部为1 2 3 ... i
        for(int i = 1; i <= n; i++) {
            while(d[head] != i) {
                head = (head + 1) % n;
                printf("2");
            }
            int next = (head + 1) % n;
            while(i > 1 && d[next] != 1) {
                int t = d[head];
                d[head] = d[next];
                d[next] = t;
                head = next;
                next = (head + 1) % n;
                printf("12");
            }
            for(int j = 1; j < i; j++) {
                next = (head + 1) % n;
                int t = d[head];
                d[head] = d[next];
                d[next] = t;
                head = next;
                printf("12");
            }
            head = (head + 1) % n;
            printf("2");
        }
        printf("\n");
    }
    return 0;
}
