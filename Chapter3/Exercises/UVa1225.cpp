#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int temp, num[10] = {0};
        scanf("%d", &temp);
        for(int i = 1; i <= temp; i++)
        {
            int temp_fenjie = i;
            while(temp_fenjie)
            {
                num[temp_fenjie % 10]++;
                temp_fenjie /= 10;
            }
        }
        for(int i = 0; i < 9; i++)
            printf("%d ", num[i]);
        printf("%d", num[9]);   //行末不能有空格，否则会PE
        printf("\n");
    }
    return 0;
}
