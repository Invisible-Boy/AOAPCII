#include <iostream>
#include <stdio.h>
#include <ctype.h>
using namespace std;

int main()
{
    while(1)
    {
        //freopen("input.txt", "r", stdin);
        //freopen("output.txt", "w", stdout);
        char temp;
        int a = 0, b = 0;
        temp = getchar();
        if(temp == EOF)
            break;
        while(isdigit(temp))
        {
            a = a * 10 + temp - '0';
            temp = getchar();
        }
        temp = getchar();
        while(isdigit(temp))
        {
            b = b * 10 + temp - '0';
            temp = getchar();
        }
        int yushu[3001] = {0}, result[51] = {0};
        printf("%d/%d = %d.", a, b ,a / b);
        int i = 0, flag = 0, kuohao_begin, kuohao_end;
        while(!flag)
        {
            if(i < 51)
                result[i] = a / b;
            i++;
            int temp = a % b;
            if(yushu[temp])
            {
                flag = 1;
                kuohao_begin = yushu[temp];
                kuohao_end = i;
            }
            else
                yushu[temp] = i;
            a = (a % b) * 10;
        }
        if(kuohao_end < 51)
            for(int i = 1; i <= kuohao_end; i++)
            {
                if(i == kuohao_begin)
                    printf("(%d", result[i]);
                else if(i == kuohao_end)
                    printf(")");
                else
                    printf("%d", result[i]);
            }
        else if(kuohao_begin < 51)
        {
            for(int i = 1; i < 51; i++)
            {
                if(i == kuohao_begin)
                    printf("(%d", result[i]);
                else
                    printf("%d", result[i]);
            }
            printf("...)");
        }
        else
        {
            for(int i = 1; i < 51; i++)
                printf("%d", result[i]);
            printf("(...)");
        }
        printf("\n");
        printf("   %d = number of digits in repeating cycle\n\n", kuohao_end - kuohao_begin);
    }
    return 0;
}
