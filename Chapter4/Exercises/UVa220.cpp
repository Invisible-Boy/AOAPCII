#include <iostream>
#include <stdio.h>
#include <ctype.h>

using namespace std;
char qiju[8][9];
const char gamer[] = {'W', 'B'};
int num[2];

int judge(int y, int x, int dy, int dx, int flag)
{
    if(num[0] + num[1] == 81)
        return 0;
    int i = 1;
    while(y + dy * i < 8 && y + dy * i > -1 && x + dx * i > -1 && x + dx * i < 8)
    {
        if(qiju[y + dy * i][x + dx * i] == '-' || qiju[y + dy][x + dx] == gamer[flag])
            return 0;
        if(qiju[y + dy * i][x + dx * i] == gamer[!flag])
            i++;
        else
            return i - 1;
    }
    return 0;
}

int List(int flag)
{
    int cont = 0;
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
        {
            int temp = 0;
            if(qiju[i][j] == '-')
            {
                for(int dy = -1; dy <= 1 && !temp; dy++)
                    for(int dx = -1; dx <= 1 && !temp; dx++)
                        temp += judge(i, j, dy, dx, flag);
            }
            if(temp && cont++)
                printf(" ");
            if(temp)
                printf("(%d,%d)", i + 1, j + 1);
        }
    if(!cont)
    {
        printf("No legal move.\n");
        return 0;
    }
    else
    {
        printf("\n");
        return 1;
    }
}

int mymove(int y, int x, int flag)
{
    int cont = 0;
    for(int dy = -1; dy <= 1; dy++)
        for(int dx = -1; dx <= 1; dx++)
        {
            int temp = judge(y, x, dy, dx, flag);
            for(int i = 1; i <= temp; i++)
                qiju[y + dy * i][x + dx * i] = gamer[flag];
            cont += temp;
        }
    if(cont)
    {
        num[flag] += cont + 1;
        num[!flag] -= cont;
        qiju[y][x] = gamer[flag];
        printf("Black - %2d White - %2d\n", num[1], num[0]);
        return 1;
    }
    else
        return 0;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        if(i)
            printf("\n");
        char temp;
        for(int j = 0; j < 8; j++)
            scanf("%s", qiju[j]);
        num[0] = 0;
        num[1] = 0;
        for(int k = 0; k < 8; k++)
            for(int j = 0; j < 8; j++)
            {
                if(qiju[k][j] == 'W')
                    num[0]++;
                else if(qiju[k][j] == 'B')
                    num[1]++;
            }
        int flag;
        while(!isalpha(temp = getchar()));
        if(temp == 'W')
            flag = 0;
        else
            flag = 1;
        while(temp != 'Q')
        {
            while(!isalpha(temp = getchar()));
            if(temp == 'L')
                List(flag);
            else if(temp == 'M')
            {
                int y, x;
                y = getchar() - '0';
                x = getchar() - '0';
                if(!mymove(y - 1, x - 1, flag))
                {
                    flag = !flag;
                    mymove(y - 1, x - 1, flag);
                }
                flag = !flag;
            }
        }
        for(int j = 0; j < 8; j++)
            printf("%s\n", qiju[j]);
        //printf("%s", qiju[7]);
    }
    return 0;
}
