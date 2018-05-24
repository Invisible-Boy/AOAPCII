#include <iostream>
#include <stdio.h>
#include <ctype.h>
using namespace std;

struct point
{
    int up;
    int down;
    int left;
    int right;
};

int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n, case_num = 0;
    point board[10][10];
    while(scanf("%d", &n) == 1)
    {
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
            {
                board[i][j].up = 0;
                board[i][j].down = 0;
                board[i][j].left = 0;
                board[i][j].right = 0;
            }
        int line_num;
        scanf("%d", &line_num);
        while(line_num--)
        {
            char temp;
            int i, j;
            while(!isalpha(temp = getchar()));
            scanf("%d %d", &i, &j);
            if(temp == 'H')
            {
                board[i][j].right = 1;
                board[i][j + 1].left = 1;
            }
            else if(temp == 'V')
            {
                board[j][i].down = 1;
                board[j + 1][i].up = 1;
            }
        }
        if(case_num++)
            printf("\n**********************************\n\n");
        printf("Problem #%d\n\n", case_num);
        int flag = 1;
        for(int mysize = 1; mysize <= n; mysize++)
        {
            int con = 0;
            for(int i = 1; i <= n - mysize; i++)
                for(int j = 1; j <= n - mysize; j++)
                {
                    int k;
                    for(k = 0; k < mysize; k++)
                    {
                        if(!(board[i][j + k].right && board[i + k][j].down && board[i + mysize - k][j + mysize].up && board[i + mysize][j + mysize -k].left))
                            break;
                    }
                    if(k == mysize)
                        con++;
                }
            if(con)
            {
                printf("%d square (s) of size %d\n", con, mysize);
                flag = 0;
            }
        }
        if(flag)
            printf("No completed squares can be found.\n");
    }
    return 0;
}
