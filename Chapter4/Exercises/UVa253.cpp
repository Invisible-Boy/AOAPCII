#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
//������õĲ�������ȫģ�⣬������ת�����壬��3���ᣬÿ���������ת4�Σ�һ��ģ��4*4*4 = 64��
//Ҳ���Բ��ù̶����������棬Ȼ��ֻ��ת4���棬����ֻ��Ҫ 6 * 4 = 24��
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
