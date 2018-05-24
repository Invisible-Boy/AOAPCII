#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int main()
{
    //freopen("input.txt", "r", stdin);
    char s1[101], s2[101];
    while(scanf("%s%s", s1, s2) == 2)
    {
        int len = strlen(s1), num1[26] = {0}, num2[26] = {0};
        for(int i = 0; i < len; i++)
        {
            num1[s1[i] - 'A']++;
            num2[s2[i] - 'A']++;
        }
        qsort(num1, 26, sizeof(int), cmp);
        qsort(num2, 26, sizeof(int), cmp);
        int flag = 1;
        for(int i = 0; i < 26; i++)
            if(num1[i] - num2[i])
            {
                flag = 0;
                break;
            }
        printf("%s\n", flag ? "YES" : "NO");
    }
    return 0;
}
