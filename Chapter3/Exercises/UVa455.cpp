#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

#define Nmax 81
//����˼·�ǣ�����������֮�����ȼ���������г��ȣ�Ȼ���1��ʼ�����ж��ַ��������Ƿ����ⶨ����i��������
//������������Ļ����ͽ���ÿ��i���ַ������жϣ��������ȣ��������һ��i
//ע�������ʽ��Ҫ��
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
            printf("\n");    //���һ�в��ܶ�س���ע�������˵�ģ����ڽ��Ҫ�ÿ��и���
    }
    return 0;
}
