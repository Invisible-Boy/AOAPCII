#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main()
{
    char s[5][5], temp;
    int case_num = 0, j = 0, x = 0, y = 0;
    while((temp = getchar()) - 'Z')
    {
        if(temp == '\n')               //不能多输出回车
            continue;
        if(temp == ' ')
        {
            x = j % 5;
            y = j / 5;
        }
        s[j / 5][j % 5] = temp;
        j++;
        if(j == 25)
        {
            if(case_num++)
                printf("\n");
            printf("Puzzle #%d:\n", case_num);
            j = 0;
            int flag = 1;
            while((temp = getchar()) - '0')
            {
                if(!flag)
                    continue;
                if(temp == '\n' || temp == ' ')
                    continue;
                switch(temp)
                {
                    case 'A':
                        if(y == 0)
                            flag = 0;
                        else
                        {
                            s[y][x] = s[y - 1][x];
                            s[--y][x] = ' ';
                        }
                        break;
                    case 'B':
                        if(y == 4)
                            flag = 0;
                        else
                        {
                            s[y][x] = s[y + 1][x];
                            s[++y][x] = ' ';
                        }
                        break;
                    case 'L':
                        if(x == 0)
                            flag = 0;
                        else
                        {
                            s[y][x] = s[y][x - 1];
                            s[y][--x] = ' ';
                        }
                        break;
                    case 'R':
                        if(x == 4)
                            flag = 0;
                        else
                        {
                            s[y][x] = s[y][x + 1];
                            s[y][++x] = ' ';
                        }
                        break;
                    default:
                        flag = 0;
                }
            }
            if(!flag)
                printf("This puzzle has no final configuration.\n");
            else
            {
                for(int i = 0; i < 25; i++)
                {
                    if(i % 5 == 4)           //最后不能多输出空格
                        printf("%c", s[i / 5][i % 5]);
                    else
                        printf("%c ", s[i / 5][i % 5]);
                    if((i % 5) == 4)
                        printf("\n");
                }
            }
        }
    }
    return 0;
}
