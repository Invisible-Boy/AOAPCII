#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define Nmax 1000
//整体思路，通过哈希算法，先统计正确编码中的每个数字出现的次数
//将每次猜测的数组先存下来，首先判断是否在对应位置相等，如果对应位置相等，A++，且将猜测数组中的数字置0，且对应数字的统计值减一
//再对比在对应位置数字不同的猜测数，每判断成功一次（B++一次），对应数的统计值需要-1
int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int code[Nmax], N, case_num = 0;
    while((scanf("%d", &N) == 1) && N)
    {
        case_num++;
        printf("Game %d:\n", case_num);
        int code_num[11] = {0};    //用来统计正确编码中每个码的个数
        for(int i = 0; i < N; i++)
        {
            scanf("%d", &code[i]);
            code_num[code[i]]++;
        }
        int guss[Nmax];
        while(1)
        {
            int A = 0, B = 0, sum = 0;
            int code_num2[11];   //为了防止修改正确数字出现的次数，在修改前新建一个数组，将正确数字出现测次数拷贝到新的数组中，修改这个数组
            memcpy(code_num2, code_num, sizeof(code_num));
            for(int i = 0; i < N; i++)
            {
                scanf("%d", &guss[i]);
                sum += guss[i];
                if(guss[i] == code[i])
                {
                    A++;
                    code_num2[guss[i]]--;
                    guss[i] = 0;
                }
            }
            if(sum == 0)
                break;
            for(int i = 0; i < N; i++)
                if(guss[i] && code_num2[guss[i]])
                {
                    B++;
                    code_num2[guss[i]]--;      //题目样例2的第二个guss提示，只要猜测的数字与正确的数字有一次对应，正确数字就应该被删除
                }
            printf("    (%d,%d)\n", A, B);
        }
    }
    return 0;
}
