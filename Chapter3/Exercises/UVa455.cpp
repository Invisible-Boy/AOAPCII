#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

#define Nmax 81
//主题思路是，先输入序列之后首先计算出其序列长度，然后从1开始，先判断字符串长度是否是拟定周期i的整数倍
//如果是整数倍的话，就进行每隔i个字符进行判断，如果都相等，则输出第一个i
//注意输出格式的要求
int main()
{
    int N;
    scanf("%d", &N);
    while(N--)
    {
        char s[Nmax];
        scanf("%s", s);
        int len = strlen(s), flag = 0;
        for(int i = 1; i < len; i++)
        {
            if(len % i)
                continue;
            flag = 1;
            for(int j = 0; j < len - i; j++)
            {
                if(s[j] != s[j+i])
                {
                    flag = 0;
                    break;
                }
            }
            if(flag)
            {
                printf("%d\n", i);
                break;
            }
        }
        if(!flag)
            printf("%d\n", len);
        if(N)
            printf("\n");    //最后一行不能多回车，注意题干中说的，相邻结果要用空行隔开
    }
    return 0;
}
