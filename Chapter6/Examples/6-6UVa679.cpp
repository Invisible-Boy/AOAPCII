#include <cstdio>
using namespace std;

int main()
{
    int n, D, I;
    scanf("%d", &n);
    while(n--)
    {
        scanf("%d%d", &D, &I);
        int id = 1;
        for(int i = 1; i < D; i++)
            if(I % 2) id = id << 1, I = (I + 1) >> 1;
            else id = (id << 1) + 1, I = I >> 1;
        printf("%d\n", id);
    }
    return 0;
}
