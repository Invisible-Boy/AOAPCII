#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
using namespace std;
#define Nmax 51

int num_r, num_c;
struct point
{
    int location_r, location_c;
};
point table[Nmax][Nmax];
void DR(int target[], int num)
{
    for(int i = 1; i <= num_r; i++)
        for(int j = 1; j <= num_c; j++)
        {
                int temp = 0;
                for(int k = 0; k < num; k++)
                {
                    if(table[i][j].location_r == target[k])
                    {
                        table[i][j].location_r = 0;
                        break;
                    }
                    if(table[i][j].location_r > target[k])
                        temp++;
                }
            table[i][j].location_r -= temp;
        }
}

void DC(int target[], int num)
{
    for(int i = 1; i <= num_r; i++)
        for(int j = 1; j <= num_c; j++)
        {
                int temp = 0;
                for(int k = 0; k < num; k++)
                {
                    if(table[i][j].location_c == target[k])
                    {
                        table[i][j].location_c = 0;
                        break;
                    }
                    if(table[i][j].location_c > target[k])
                        temp++;
                }
            table[i][j].location_c -= temp;
        }
}

void IR(int target[], int num)
{
    for(int i = 1; i <= num_r; i++)
        for(int j = 1; j <= num_c; j++)
        {
            int temp = 0;
            for(int k = 0; k < num; k++)
                if(table[i][j].location_r >= target[k])
                    temp++;
            table[i][j].location_r += temp;
        }
}

void IC(int target[], int num)
{
    for(int i = 1; i <= num_r; i++)
        for(int j = 1; j <= num_c; j++)
        {
            int temp = 0;
            for(int k = 0; k < num; k++)
                if(table[i][j].location_c >= target[k])
                    temp++;
            table[i][j].location_c += temp;
        }
}

void EX(int r1, int c1, int r2, int c2)
{
    for(int i = 1; i <= num_r; i++)
        for(int j = 1; j <= num_c; j++)
        {
            if(table[i][j].location_r == r1 && table[i][j].location_c == c1)
            {
                table[i][j].location_r = r2;
                table[i][j].location_c = c2;
            }
            else if(table[i][j].location_r == r2 && table[i][j].location_c == c2)
            {
                table[i][j].location_r = r1;
                table[i][j].location_c = c1;
            }
        }
}

int main()
{
    freopen("input.txt", "r", stdin);
    int case_num = 0;
    while(scanf("%d%d", &num_r, &num_c))
    {
        if(num_r * num_c == 0)
            break;
        if(case_num++)
            printf("\n");
        printf("Spreadsheet #%d\n", case_num);
        for(int i = 1; i <= num_r; i++)
            for(int j = 1; j <= num_c; j++)
            {
                table[i][j].location_r = i;
                table[i][j].location_c = j;
            }
        int operation_num;
        scanf("%d", &operation_num);
        while(operation_num--)
        {
            char temp[3] = {'\0'};
            int i = 0;
            while(i != 2)
                if(isalpha(temp[i] = getchar()))
                    i++;
            if(!strcmp(temp, "EX"))
            {
                int r1, c1, r2, c2;
                scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
                EX(r1, c1, r2, c2);
            }
            else
            {
                int tagert_num, tagert[10];
                scanf("%d", &tagert_num);
                for(int i = 0; i < tagert_num; i++)
                    scanf("%d", &tagert[i]);
                if(!strcmp(temp, "DR"))
                    DR(tagert, tagert_num);
                else if(!strcmp(temp, "DC"))
                    DC(tagert, tagert_num);
                else if(!strcmp(temp, "IR"))
                    IR(tagert, tagert_num);
                else if(!strcmp(temp, "IC"))
                    IC(tagert, tagert_num);
            }
        }
        int chaxun_num;
        scanf("%d", &chaxun_num);
        while(chaxun_num--)
        {
            int i, j;
            scanf("%d%d", &i, &j);
            if(table[i][j].location_c > 0 && table[i][j].location_r > 0)
                printf("Cell data in (%d,%d) moved to (%d,%d)\n", i, j, table[i][j].location_r, table[i][j].location_c);
            else
                printf("Cell data in (%d,%d) GONE\n", i, j);
        }
    }
    return 0;
}
