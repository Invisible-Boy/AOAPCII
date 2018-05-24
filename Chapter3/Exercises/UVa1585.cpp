#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define Nmax 81
int main()
{
    char s[Nmax];
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%s", s);
        int sum = 0, temp = 0, len = strlen(s);
        for(int i = 0; i < len; i++)
        {
            if(s[i] == 'O')
                sum = sum + (++temp);
            if(s[i] == 'X')
                temp = 0;
        }
        printf("%d\n", sum);
    }
    return 0;
}
