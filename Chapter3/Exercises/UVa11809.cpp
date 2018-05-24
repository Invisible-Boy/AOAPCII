#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
using namespace std;
#define deta 0.00001

int main()
{
    freopen("input.txt", "r", stdin);
    double A[10][31];
    int B[10][31];
    for(int i = 0; i <= 9; i++)
    {
        for(int j = 1; j<= 30; j++)
        {
            A[i][j] = log10(1 - pow(2, -i - 1)) + log10(2) * (pow(2, j) - 1);
            B[i][j] = floor(A[i][j]);
            A[i][j] = pow(10, A[i][j] - B[i][j]);
        }
    }
    while(1)
    {
        double aim_A;
        int aim_B;
        //scanf("%lf%d", &aim_A, &aim_B);     //在C中1e3 = 1000 e代表指数的含义
        char temp[25];
        scanf("%s", temp);
        *strchr(temp, 'e') = ' ';
        sscanf(temp,"%lf%d", &aim_A, &aim_B);
        if(aim_A == 0 && aim_B == 0)
            break;
        while(aim_A < 0.1 && aim_B > 0)
        {
            aim_A *= 10;
            aim_B--;
        }
        int flag = 0;
        for(int i = 0; i <= 9; i++)
        {
            for(int j = 1; j <= 30; j++)
            {
                if(aim_B == B[i][j] && fabs(aim_A - A[i][j]) < deta)
                {
                    printf("%d %d\n", i, j);
                    flag = 1;
                    break;
                }
            }
            if(flag)
                break;
        }
    }
    return 0;
}
