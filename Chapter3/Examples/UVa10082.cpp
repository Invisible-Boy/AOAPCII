#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main()
{
    char c;
    char s[] = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
    int s_length = strlen(s);
    while((c = getchar()) != EOF)
    {
        if(c == ' ')
            printf(" ");    //ע������ո�
        else if(c == '\n')
            printf("\n");   //ע������س���
        else
        {
            for(int i = 0; i < s_length; i++)  //���˻س��ͻ��У�������ַ���Ҫ�������н��бȶԣ������Ӧ�ַ�ǰһ���ַ���
            {
                if(c == s[i])
                {
                    printf("%c", s[i-1]);
                    break;
                }
            }
        }
    }
    return 0;
}
