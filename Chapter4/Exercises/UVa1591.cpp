#include <iostream>
#include <stdio.h>
using namespace std;
int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    unsigned long long  Sp, Sq;
    int N;
    while(cin >> N >> Sp >> Sq)
    {
        unsigned long long k = (unsigned long long)1 << 60;
        int ans_A = 0, ans_B = 0;
        for(int A = 0; A < 32; A++)
            for(int B = 0; B < 32; B++)
                if((((N - 1) * Sp + (((N - 1) * Sp) << A)) >> B) + Sq >= N * Sq && (((N - 1) * Sp + (((N - 1) * Sp) << A)) >> B) + Sq < k)  //ÿ�����ӵ���λ������ͬ�ģ����ֻ��Ҫ�ж�����ܵĿռ��Ƿ����N*Sq����
                {
                    k = (((N - 1) * Sp + (((N - 1) * Sp) << A)) >> B) + Sq;
                    ans_A = A;
                    ans_B = B;
                }
        cout << k << ' ' << ans_A  << ' ' << ans_B << endl;
    }
    return 0;
}
