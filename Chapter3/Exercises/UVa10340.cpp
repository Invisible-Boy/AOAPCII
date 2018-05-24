#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

#define Nmax 101000
char s1[Nmax], s2[Nmax];
int main()
{
    while(scanf("%s%s", s1, s2) == 2)
    {
        char* temp = s2;
        int len = strlen(s1), flag = 1;
        for(int i = 0; i < len; i++)
        {
            temp = strchr(temp, s1[i]);
            if(temp == NULL)
            {
                flag = 0;
                break;
            }
            else
                temp++;
        }
        printf("%s\n", flag ? "Yes" : "No");
    }
    return 0;
}
