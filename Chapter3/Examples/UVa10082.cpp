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
            printf(" ");    //注意输出空格。
        else if(c == '\n')
            printf("\n");   //注意输出回车。
        else
        {
            for(int i = 0; i < s_length; i++)  //除了回车和换行，其余的字符需要在数组中进行比对，输出对应字符前一个字符。
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
