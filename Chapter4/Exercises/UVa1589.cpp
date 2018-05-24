#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
using namespace std;

char qiju[11][11];
int judge_target(int target_y, int target_x)
{
    int temp, con = 0;
    for(temp = target_x - 1; temp > 0; temp--)
    {
        if((qiju[target_y][temp] == 'R' || qiju[target_y][temp] == 'G') && !con)
            return 0;
        else if(qiju[target_y][temp] == 'C' && con == 1)
            return 0;
        else if(qiju[target_y][temp] != 'X')
            con++;
    }
    con = 0;
    for(temp = target_x + 1; temp < 11; temp++)
    {
        if((qiju[target_y][temp] == 'R' || qiju[target_y][temp] == 'G') && !con)
            return 0;
        else if(qiju[target_y][temp] == 'C' && con == 1)
            return 0;
        else if(qiju[target_y][temp] != 'X')
            con++;
    }
    con = 0;
    for(temp = target_y - 1; temp > 0; temp--)
    {
        if((qiju[temp][target_x] == 'R' || qiju[temp][target_x] == 'G') && !con)
            return 0;
        else if(qiju[temp][target_x] == 'C' && con == 1)
            return 0;
        else if(qiju[temp][target_x] != 'X')
            con++;
    }
    con = 0;
    for(temp = target_y + 1; temp < 11; temp++)
    {
        if((qiju[temp][target_x] == 'R' || qiju[temp][target_x] == 'G') && !con)
            return 0;
        else if(qiju[temp][target_x] == 'C' && con == 1)
            return 0;
        else if(qiju[temp][target_x] != 'X')
            con++;
    }
    if(target_x + 2 < 11 && target_y + 1 < 11 && qiju[target_y + 1][target_x + 2] == 'H' && qiju[target_y + 1][target_x + 1] == 'X')
        return 0;
    if(target_x + 2 < 11 && target_y - 1 > 0 && qiju[target_y - 1][target_x + 2] == 'H' && qiju[target_y - 1][target_x + 1] == 'X')
        return 0;
    if(target_x - 2 > 0 && target_y + 1 < 11 && qiju[target_y + 1][target_x - 2] == 'H' && qiju[target_y + 1][target_x - 1] == 'X')
        return 0;
    if(target_x - 2 > 0 && target_y - 1 > 0 && qiju[target_y - 1][target_x - 2] == 'H' && qiju[target_y - 1][target_x - 1] == 'X')
        return 0;
    if(target_y + 2 < 11 && target_x + 1 < 11 && qiju[target_y + 2][target_x + 1] == 'H' && qiju[target_y + 1][target_x + 1] == 'X')
        return 0;
    if(target_y + 2 < 11 && target_x - 1 > 0 && qiju[target_y + 2][target_x - 1] == 'H' && qiju[target_y + 1][target_x - 1] == 'X')
        return 0;
    if(target_y - 2 > 0 && target_x + 1 < 11 && qiju[target_y - 2][target_x + 1] == 'H' && qiju[target_y - 1][target_x + 1] == 'X')
        return 0;
    if(target_y - 2 > 0 && target_x - 1 > 0 && qiju[target_y - 2][target_x - 1] == 'H' && qiju[target_y - 1][target_x - 1] == 'X')
        return 0;
    return 1;
}
int main()
{
    freopen("input.txt", "r", stdin);
    int R_num;
    while(scanf("%d", &R_num) && R_num)
    {
        memset(qiju, 'X', sizeof(qiju));
        int BG_y, BG_x;
        scanf("%d%d", &BG_y, &BG_x);
        for(int i = 0; i < R_num; i++)
        {
            int temp_y, temp_x;
            char temp_name;
            while(!isalpha(temp_name = getchar()));
            scanf("%d%d", &temp_y, &temp_x);
            qiju[temp_y][temp_x] = temp_name;
        }
        int flag = 0;    //表示是否还有活路
        if(BG_y > 1 && !flag)
            flag = judge_target(BG_y - 1, BG_x);
        if(BG_y < 3 && !flag)
            flag = judge_target(BG_y + 1, BG_x);
        if(BG_x > 4 && !flag)
            flag = judge_target(BG_y, BG_x - 1);
        if(BG_x < 6 && !flag)
            flag = judge_target(BG_y, BG_x + 1);
        printf("%s\n", flag ? "NO" : "YES");
    }
    return 0;
}
