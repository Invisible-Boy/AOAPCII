#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;

//设长方体的长大于等于宽大于等于高（ab,ac,bc）
//则长方体有三对面，长宽分别为(ab,ac,bc)

typedef struct pallet
{
    int l, w;
}pallet;

bool cmp(pallet a, pallet b)
{
    return (a.l > b.l || ((a.l == b.l) && a.w > b.w));
}

int main()
{
    pallet p[6];
    int j = 0;
    while(scanf("%d %d", &p[j].l, &p[j].w) == 2)
    {
        if(p[j].l < p[j].w)
        {
            int temp;
            temp = p[j].l;
            p[j].l = p[j].w;
            p[j].w = temp;
        }
        j++;
        if(j == 6)
        {
            j = 0;
            int flag = 1;
            sort(p, p+6, cmp);
            for(int i = 0; i < 6; i+=2)
            {
                if(p[i].l != p[i+1].l || p[i].w != p[i+1].w)
                {
                    flag = 0;
                    break;
                }
            }
            if(p[0].l != p[2].l || p[0].w != p[4].l || p[2].w != p[4].w)
                flag = 0;
            printf("%s\n", flag ? "POSSIBLE" : "IMPOSSIBLE");
        }
    }
    return 0;
}
