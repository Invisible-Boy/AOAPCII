#include <cstdio>
#include <cstring>
using namespace std;
//�˰汾TLE������ֱ��ģ�⣬����ÿ�����������Ҫģ��2^19 * 20�����㣬���������ܴܺ󣬵��³�ʱ
int main()
{
    const int Max = 1 << 20;
    bool data[Max];
    int n;
    scanf("%d", &n);
    while(n--)
    {
        int D, I, id;
        scanf("%d%d", &D, &I);
        D = 1 << D;
        memset(data, true, sizeof(bool)* D);
        while(I--)
        {
            id = 1;
            while(id < D)
                if(data[id] && 2 * id < D) data[id] = !data[id], id = 2 * id;
                else if(!data[id] && 2 * id + 1 < D) data[id] = !data[id], id = 2 * id + 1;
                else break;
        }
        printf("%d\n", id);
    }
    scanf("%d", &n);
    return 0;
}
