#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
using namespace std;

#define Nmax 81

int main()
{
    int T;
    char s[Nmax];
    scanf("%d", &T);
    while(T--)
    {
        scanf("%s", s);
        int len = strlen(s), num[26] = {0};
        float weight = 0;
        for(int i = 0; i < len; i++)
        {
            int temp = 1, location, flag =1;
            if(!isdigit(s[i]))
                location = s[i] - 'A';
            while(isdigit(s[i+1]) && s[i+1]!='\0')
            {
                if(flag)
                {
                    temp = s[++i] - '0';
                    flag = 0;
                }
                else
                    temp = temp * 10 + s[++i] - '0';
            }
            num[location] += temp;
        }
        weight = num['C' - 'A'] * 12.01 + num['H' - 'A'] * 1.008 + num['O' - 'A'] * 16.00 + num['N' - 'A'] * 14.01;
        printf("%.3f\n", weight);
    }
    return 0;
}
