#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define Nmax 1000
//����˼·��ͨ����ϣ�㷨����ͳ����ȷ�����е�ÿ�����ֳ��ֵĴ���
//��ÿ�β²�������ȴ������������ж��Ƿ��ڶ�Ӧλ����ȣ������Ӧλ����ȣ�A++���ҽ��²������е�������0���Ҷ�Ӧ���ֵ�ͳ��ֵ��һ
//�ٶԱ��ڶ�Ӧλ�����ֲ�ͬ�Ĳ²�����ÿ�жϳɹ�һ�Σ�B++һ�Σ�����Ӧ����ͳ��ֵ��Ҫ-1
int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int code[Nmax], N, case_num = 0;
    while((scanf("%d", &N) == 1) && N)
    {
        case_num++;
        printf("Game %d:\n", case_num);
        int code_num[11] = {0};    //����ͳ����ȷ������ÿ����ĸ���
        for(int i = 0; i < N; i++)
        {
            scanf("%d", &code[i]);
            code_num[code[i]]++;
        }
        int guss[Nmax];
        while(1)
        {
            int A = 0, B = 0, sum = 0;
            int code_num2[11];   //Ϊ�˷�ֹ�޸���ȷ���ֳ��ֵĴ��������޸�ǰ�½�һ�����飬����ȷ���ֳ��ֲ�����������µ������У��޸��������
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
                    code_num2[guss[i]]--;      //��Ŀ����2�ĵڶ���guss��ʾ��ֻҪ�²����������ȷ��������һ�ζ�Ӧ����ȷ���־�Ӧ�ñ�ɾ��
                }
            printf("    (%d,%d)\n", A, B);
        }
    }
    return 0;
}
