#include <iostream>
#include <stdio.h>
#include <string.h>
#define maxn 50
using namespace std;

char Character_Reverse[] = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";

char r(char c)
{
    if(c - 'A' >= 0)
        return Character_Reverse[c - 'A'];
    else
        return Character_Reverse[c - '0' + 25];
}

int main()
{
    char s[maxn];
    while(scanf("%s", s) == 1)  //当scanf读到eof的时候，返回-1
    {

        int p = 1, m = 1;
        int len = strlen(s);
        for(int i = 0; i < len; i++)
        {
            if(p && (s[i] != s[len - 1 - i]))
                p = 0;
            if(m && (s[i] != r(s[len - 1 -i])))
                m = 0;
            if(!p && !m)
                break;
        }
        if(p && m)
            printf("%s -- is a mirrored palindrome.", s);
        else if(p)
            printf("%s -- is a regular palindrome.", s);
        else if(m)
            printf("%s -- is a mirrored string.", s);
        else
            printf("%s -- is not a palindrome.", s);
        printf("\n\n");
    }
    return 0;
}
