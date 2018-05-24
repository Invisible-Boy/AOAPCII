#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

//注意读题，题干需要看清楚
int main()
{
    freopen("input.txt", "r", stdin);
    char s1[50], s2[50];
    int case_num;
    while(scanf("%d", &case_num))
    {
        if(case_num == -1)  break;
        scanf("%s%s",s1, s2);
        unsigned int num1[26] = {0}, ture_num = 0, false_num = 0;
        for(unsigned int i = 0; i < strlen(s1); i++)
            num1[s1[i] - 'a']++;
        for(unsigned int i = 0; i < strlen(s2); i++)
        {
            if(num1[s2[i] - 'a'])
            {
                ture_num += num1[s2[i] - 'a'];
                num1[s2[i] - 'a'] = 0;
            }
            else    false_num++;
            if(false_num == 7 || ture_num == strlen(s1))  break;
        }
        printf("Round %d\n", case_num);
        if(ture_num == strlen(s1))    printf("You win.\n");
        else if(false_num == 7) printf("You lose.\n");
        else    printf("You chickened out.\n");
    }
    return 0;
}
