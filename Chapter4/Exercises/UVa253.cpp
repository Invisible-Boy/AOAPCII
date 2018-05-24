#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
//本题采用的策略是完全模拟，进行旋转正方体，有3个轴，每个轴可以旋转4次，一共模拟4*4*4 = 64次
//也可以采用固定上下两个面，然后只旋转4个面，这样只需要 6 * 4 = 24次
void myswap(char* s1, int times, int flag)
{
    if(flag == 0)
    {
       while(times --)
       {
            char temp = s1[0];
            s1[0] = s1[4];
            s1[4] = s1[5];
            s1[5] = s1[1];
            s1[1] = temp;
       }
    }
    else if(flag == 1)
    {
        while(times--)
        {
            char temp = s1[2];
            s1[2] = s1[4];
            s1[4] = s1[3];
            s1[3] = s1[1];
            s1[1] = temp;
        }
    }
    else
    {
        while(times--)
        {
            char temp = s1[0];
            s1[0] = s1[2];
            s1[2] = s1[5];
            s1[5] = s1[3];
            s1[3] = temp;
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    char s[13], s1[7], s2[7];
    while(scanf("%s", s) == 1)
    {
        sprintf(s2, "%s", s + 6);
        s[6] = '\0';
        sprintf(s1, "%s", s);
        int flag = 0;
        for(int i = 0; i < 4; i++)
        {
            if(flag)
                break;
            char temp[7];
            sprintf(temp, "%s", s1);
            myswap(temp, i, 0);
            for(int j = 0; j < 4; j++)
            {
                if(flag)
                    break;
                myswap(temp, j, 1);
                for(int k = 0; k < 4; k++)
                {
                    if(flag)
                        break;
                    myswap(temp, k, 2);
                    if(!strcmp(temp, s2))
                        flag = 1;
                }
            }
        }
        printf("%s\n", flag ? "TRUE" : "FALSE");
    }
    return 0;
}
