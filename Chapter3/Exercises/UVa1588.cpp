#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
#define Nmax 201

int test(char* master, char* driven, int len_m, int len_d)
{
    int i;
    for(i = 0; i < len_m; i++)
    {
        int flag = 1;
        for(int j = 0; j < len_d && j + i < len_m; j++)
        {
            if(driven[j] + master[i + j] - '0' - '0' > 3)
            {
                flag = 0;
                break;
            }
        }
        if(flag)
            break;
    }
    return  (i + len_d) > len_m ? i + len_d : len_m;
}

int main()
{
    char master[Nmax], driven[Nmax];
    while(scanf("%s%s", master, driven) == 2)
    {
        int len_m = strlen(master), len_d = strlen(driven);
        int temp1 = test(master, driven, len_m, len_d);   //��������ǰ����ƥ��
        int temp2 = test(driven, master, len_d, len_m);   //�������Ӻ���ǰƥ��
        printf("%d\n", temp1 > temp2 ? temp2 : temp1);    //ȡ���������С�ĳ������
    }
    return 0;
}
