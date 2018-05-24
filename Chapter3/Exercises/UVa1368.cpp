#include <iostream>
#include <stdio.h>
using namespace std;

int my_max(int *num, int len)
{
    int max_index = 0;
    for(int i = 1; i < len; i++)
        if(num[i] > num[max_index])
            max_index = i;
    return max_index;
}

int main()
{
    freopen("input.txt", "r", stdin);
    const char check[]={'A', 'C', 'G', 'T'};
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int a, b, num[1000][4] = {0}, sum = 0;
        scanf("%d%d", &a, &b);
        for(int i = 0; i < a; i++)
            for(int j = 0; j < b; j++)
            {
                char temp = getchar();
                switch(temp)
                {
                    case 'A':
                        num[j][0]++;
                        break;
                    case 'C':
                        num[j][1]++;
                        break;
                    case 'G':
                        num[j][2]++;
                        break;
                    case 'T':
                        num[j][3]++;
                        break;
                    default:
                        j--;
                }
            }
        for(int i = 0; i < b; i++)
        {
            int temp;
            temp = my_max(num[i], 4);
            printf("%c", check[temp]);
            sum += a - num[i][temp];
        }
        printf("\n%d\n",sum);
    }
    return 0;
}
