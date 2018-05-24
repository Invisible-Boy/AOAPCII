#include <iostream>
#include <stdio.h>
#include <string.h>
#define Nmax 11
using namespace std;

int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int x, y, case_num = 0;
    char s[Nmax][Nmax];
    while(1)
    {
        scanf("%d", &y);
        if(!y)
        {
            printf("\n");    //最后要以回车结尾，否则一直会WA
            break;
        }
        scanf("%d", &x);
        if(case_num++)
            printf("\n\n");
        printf("puzzle #%d:\n", case_num);
        for(int i = 0; i < y; i++)
            scanf("%s", s[i]);            //scanf（“%c"）会读入回车
        printf("Across");
        int start_num[Nmax][Nmax] = {0}, start = 0;
        for(int i = 0; i < y; i++)
            for(int j = 0; j < x; j++)
            {
                if(s[i][j] != '*')
                {
                    if((j == 0 || s[i][j - 1] == '*') || (i == 0 || s[i - 1][j] == '*'))
                        start_num[i][j] = ++start;
                }
            }
        for(int i = 0; i < y; i++)
            for(int j = 0; j < x; j++)
            {
                if(s[i][j] != '*')
                {
                    if(j == 0 || s[i][j - 1] == '*')
                        printf("\n%3d.", start_num[i][j]);
                    printf("%c", s[i][j]);
                }
            }
        printf("\nDown");
        for(int i = 0; i < y; i++)
            for(int j = 0; j < x; j++)
            {
                if((s[i][j] != '*') && (i == 0 || s[i - 1][j] == '*'))
                {
                    printf("\n%3d.", start_num[i][j]);
                    for(int k = i; k < y; k++)
                    {
                        if(s[k][j] != '*')
                            printf("%c", s[k][j]);
                        if(s[k][j] == '*')
                        {
                            break;
                        }
                    }
                }
            }
    }
    return 0;
}
