#include <iostream>
#include <stdio.h>
using namespace std;

//�����˼·�ǣ�����ÿ����������֮ǰ���������֣������б�����⡣
//����������յĽ���ǳ�ʱ�����ǿ���ѡ����ķ�������һ��100000�����飬Ȼ����в��ҵķ�ʽ�����Ӷȴ�O��n����ΪO��1����
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
//���ķ�ʽ�����ʾ��ǽ������㷨�ļ�����̼�¼������ʹ�ü���ֻ��Ҫһ��
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
