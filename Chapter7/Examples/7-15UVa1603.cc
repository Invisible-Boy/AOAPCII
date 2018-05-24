/**
 * Title:   7-15UVa1603
 * Author:  InvisibleMan
 * Data:    2017-1-13
 * Time:    0ms 
 */

/** 
 * tips: 采用顶点连通矩阵代表边的关系，在oj上的运行时间为0ms，但是自己测试的n = 5，不去除火柴的情况下，运行时间为5s(lrj的代码运行时间很长且时间未知)
 * 应该是测试样例中有比较多的删除的火柴
 */

#include <cstdio>
#include <cstring>
// #include <ctime>

using namespace std;

const int Nmax = 7;
int n, ansM;
bool edge[Nmax][Nmax][2];  //只存储向右和向下的方向的边

bool judge(int xx, int yy, int edgeMax) {
    for(int i = 0; i < edgeMax; i++)
        if(!(edge[xx][yy + i][0] && edge[xx + i][yy][1] && edge[xx + edgeMax][yy + i][0] && edge[xx + i][yy + edgeMax][1]))
            return false;
    return true;
}

bool next(int now, int edgeMax, int xx, int yy);

bool dfs(int now, int edgeMax, int xx, int yy) {
    if(now > ansM) return false;
    if(edgeMax == n) {
        bool flag = judge(0, 0, n);
        if(!flag || (flag && now + 1 <= ansM)) return true;
        return false;
    };
    if(judge(xx, yy, edgeMax)) {
        for(int i = 0; i < edgeMax; i++) {
            edge[xx][yy + i][0] = false;
            if(next(now + 1, edgeMax, xx, yy)) return true;
            edge[xx][yy + i][0] = true;

            edge[xx + i][yy][1] = false;
            if(next(now + 1, edgeMax, xx, yy)) return true;;
            edge[xx + i][yy][1] = true;

            edge[xx + edgeMax][yy + i][0] = false;
            if(next(now + 1, edgeMax, xx, yy)) return true;
            edge[xx + edgeMax][yy + i][0] = true;

            edge[xx + i][yy + edgeMax][1] = false;
            if(next(now + 1, edgeMax, xx, yy)) return true;
            edge[xx + i][yy + edgeMax][1] = true;
        }
    }
    else if(next(now, edgeMax, xx, yy)) return true;
    return false;
}

bool next(int now, int edgeMax, int xx, int yy) {
    if(yy + 1 + edgeMax > n) {
        if(xx + 1 + edgeMax > n)
            return dfs(now, edgeMax + 1, 0, 0);
        else
            return dfs(now, edgeMax, xx + 1, 0);
    }
    else return dfs(now, edgeMax, xx, yy + 1);
}

int main() {
    // clock_t start = clock();
    int T;
    scanf("%d", &T);
    while(T--) {
        int m;
        scanf("%d%d", &n, &m);
        for(int i = 0; i <= n; i++)
            for(int j = 0; j <= n; j++)
                for(int k = 0; k < 2; k++)
                    edge[i][j][k] = true;
        while(m--) {
            int temp;
            scanf("%d", &temp);
            int t1 = temp / ((n << 1) + 1);
            int t2 = temp % ((n << 1) + 1);
            if(t2 == 0)
                edge[--t1][n][1] = false;
            else if(t2 <= n)
                edge[t1][t2 - 1][0] = false;
            else
                edge[t1][t2 - n - 1][1] = false;
        }
        bool t = false;
        for(ansM = 0; ansM < 14; ansM++)
            if(dfs(0, 1, 0, 0)) {
                t = true;
                printf("%d\n", ansM);
                break;
            }
        if(!t)
            printf("14\n");

    }
    /*
    clock_t end = clock();
    printf("%lu\n", end - start);
    printf("%f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    */
    return 0;
}
