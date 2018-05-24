#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define Nmax 1000
int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    while(scanf("%d", &n) == 1)
    {
        int IP_address[Nmax][4] = {0},temp[4] = {0}, mask_len = 4;
        scanf("%d.%d.%d.%d", &IP_address[0][0], &IP_address[0][1], &IP_address[0][2], &IP_address[0][3]);
        for(int i = 1; i < n; i++)
        {
            scanf("%d.%d.%d.%d", &IP_address[i][0], &IP_address[i][1], &IP_address[i][2], &IP_address[i][3]);
            int j;
            for(j = 0; j < mask_len; j++)
            {
                if(IP_address[i][j] != IP_address[0][j])
                    break;
            }
            mask_len = j;
        }
        if(mask_len == 4)
        {
            printf("%d.%d.%d.%d\n", IP_address[0][0], IP_address[0][1], IP_address[0][2], IP_address[0][3]);
            printf("255.255.255.255\n");
            continue;
        }
        int temp1 = 0;
        for(int i = 7; i >= 0; i--)
        {
            int flag = IP_address[0][mask_len] & (1 << i), j;
            for(j = 1; j < n; j++)
                if((IP_address[j][mask_len] & (1 << i)) != flag)
                    break;
            if(j == n)
                temp1++;
            else
                break;
        }
        for(int i = 0; i < mask_len; i++)
            temp[i] = 255;
        int j = 7;
        for(int i = 0; i < temp1; i++)
        {
            temp[mask_len] += (1 << j);
            j--;
        }
        printf("%d.%d.%d.%d\n", IP_address[0][0] & temp[0], IP_address[0][1] & temp[1], IP_address[0][2] & temp[2], IP_address[0][3] & temp[3]);
        printf("%d.%d.%d.%d\n", temp[0], temp[1], temp[2], temp[3]);
    }
    return 0;
}
