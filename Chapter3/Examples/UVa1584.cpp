#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

#define Nmax 101
int main()
{
    int T;
    char s[Nmax];
    scanf("%d", &T);
    while(T--)
    {
        scanf("%s", s);
        int len = strlen(s), num[4] = {0};
        for(int i = 0; i < len; i++)
        {
            switch(s[i])
            {
                case 'A':
                    num[0]++;
                    break;
                case 'C':
                    num[1]++;
                    break;
                case 'G':
                    num[2]++;
                    break;
                case 'T':
                    num[3]++;
                    break;
            }
        }
        char flag;
        int num_flag = 0;
        if(!num[0] && !num[1] &&!num[2])
        {
            printf("%s\n", s);
            continue;
        }
        else if(num[0])
        {
            flag = 'A';
            num_flag = num[0];
        }
        else if(num[1])
        {
            flag = 'C';
            num_flag = num[1];
        }
        else
        {
            flag = 'G';
            num_flag = num[2];
        }
        int start_num[Nmax];
        int j = 0;
        for(int i = 0; i < len; i++)
        {
            if(s[i] == flag)
                start_num[j++] = i;
        }
        if(num_flag == 1)
        {
            for(int i = 0; i < len; i++)
                putchar(s[(start_num[0] + i) % len]);
            printf("\n");
            continue;
        }
        int start = start_num[0];
        for(int i = 1; i < num_flag; i++)
        {
            for(int j = 1; j < len; j++)
            {
                if(s[(start + j) % len] != s[(start_num[i] + j) % len])
                {
                    start = (s[(start + j) % len] - s[(start_num[i] + j) % len] > 0)? start_num[i] : start;
                    break;
                }
            }
        }
        for(int i = 0; i < len; i++)
            putchar(s[(start + i) % len]);
        printf("\n");
    }
    //printf("%d\n%d",'A' - 'G','G' - 'A');
    return 0;
}
