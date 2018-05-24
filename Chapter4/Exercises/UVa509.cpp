#include <iostream>
#include <stdio.h>
#include <ctype.h>
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int d, case_num = 0;
    char block[101][7][65];
    while(scanf("%d", &d) && d)
    {
        int s, b, flag = 1;
        scanf("%d%d", &s, &b);
        char check;
        while(!isalpha(check = getchar()));
        int check_num = check == 'O' ? 1 : 0;
        for(int j = 0; j < d; j++)
            for(int i = 0; i < b; i++)
                for(int k = 0; k < s; k++)
                    while(!isalnum(block[i][j][k] = getchar()));
        for(int i = 0; i < b && flag; i++)
            for(int k = 0; k < s && flag; k++)
            {
                int x_num = 0, temp = 0;
                for(int j = 0; j < d && flag; j++)
                {
                    if(block[i][j][k] == 'x')
                        x_num++;
                    else
                        temp ^= block[i][j][k] - '0';
                    if(x_num > 1)                //判断要在x_num++之后立刻进行，否则对于x正好在j=d-1的情况会出错
                        flag = 0;
                }
                if(!x_num && temp != check_num)
                    flag = 0;
                else if(x_num == 1)
                    for(int j = 0; j < d && flag; j++)
                        if(block[i][j][k] == 'x')
                        {
                            block[i][j][k] = temp ^ check_num + '0';
                            break;
                        }
            }
        if(flag)
        {
            printf("Disk set %d is valid, contents are: ", ++case_num);
            int number = 0, cnt = 0;
            for(int i = 0; i < b; i++)
                for(int j = 0; j < d; j++)
                {
                    if(j == i % d)
                        continue;
                    for(int k = 0; k < s; k++)
                    {
                        if(block[i][j][k] != 'x')
                        {
                            number = number * 2 + block[i][j][k] - '0';
                            cnt++;
                        }
                        if(cnt == 4)
                        {
                            printf("%c", (number < 10) ? number + '0' : number - 10 + 'A');
                            number = 0;
                            cnt = 0;
                        }
                    }
                }
            if(cnt)
            {
                number = number << (4 - cnt);
                printf("%c", number < 10 ? number + '0' : number - 10 + 'A');
            }
            printf("\n");
        }
        else
            printf("Disk set %d is invalid.\n", ++case_num);
    }
    return 0;
}
