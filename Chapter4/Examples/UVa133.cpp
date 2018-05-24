#include <iostream>
#include <stdio.h>
using namespace std;

int n, people[21] = {1};

int go(int p, int d, int s)
{
    while(s--)
    {
        do
        {
            p += d;
            if(p > n)
                p = 1;
            else if(p < 1)
                p = n;    //使用了全局变量
        }while(people[p] == 0);
    }
    return p;
}

int main()
{
    int k, m;
    while(scanf("%d%d%d", &n, &k, &m) && n)
    {
        for(int i = 1; i <= n; i++)
            people[i] = 1;
        int temp_A = n, temp_B = 1, leave = n;
        while(leave)
        {
            temp_A = go(temp_A, 1, k);
            temp_B = go(temp_B, -1, m);
            people[temp_A] = 0;
            people[temp_B] = 0;
            printf("%3d", temp_A);
            leave--;
            if(temp_B != temp_A)
            {
                printf("%3d", temp_B);
                leave--;
            }
            if(leave)
                printf(",");
        }
        printf("\n");
    }
    return 0;
}
