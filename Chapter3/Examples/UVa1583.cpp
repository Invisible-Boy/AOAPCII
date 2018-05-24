#include <iostream>
#include <stdio.h>
using namespace std;

//本题的思路是，遍历每个案例数字之前的所有数字，来进行暴力求解。
//这个做法最终的结果是超时，我们可以选择打表的方法，开一个100000的数组，然后进行查找的方式，复杂度从O（n）变为O（1）。
/*int main()
{
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        int temp, j, flag = 0;
        scanf("%d", &temp);
        for(j = 1; j < temp; j++)
        {
            int temp_fenjie = j, sum = j;
            do
            {
                sum += temp_fenjie % 10;
                temp_fenjie /= 10;
            }while(temp_fenjie);
            if(sum == temp)
            {
                flag = 1;
                break;
            }
            if(flag)
                break;
        }
        printf("%d\n", flag ? j : 0);
    }
    return 0;
}*/
//打表的方式，本质就是将暴力算法的计算过程记录下来，使得计算只需要一遍
#define Nmax 100000
int num[Nmax + 1] = {0};
int main()
{
    int N;
    for(int i = 1; i < Nmax; i++)
    {
        int temp_fenjie = i, sum = i;
        do
        {
            sum += temp_fenjie % 10;
            temp_fenjie /= 10;
        }while(temp_fenjie);
        if((sum <= Nmax) && !num[sum])
            num[sum] = i;
    }
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        int temp;
        scanf("%d", &temp);
        printf("%d\n", num[temp]);
    }
    return 0;
}
