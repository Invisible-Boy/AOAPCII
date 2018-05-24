#include <cstdio>
#include <cstring>
using namespace std;
const int Max = 80;
int sum[Max] = {0};
bool leaf(int pos)
{
    int temp;
    scanf("%d", &temp);
    if(temp == -1) return false;
    sum[pos] += temp;
    leaf(pos-1);  //此处不能用++或者--。必须要保证本层的pos不会在本层发生变化
    leaf(pos+1);
    return true;
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int i, pos = Max / 2, case_n = 1;
    while(leaf(pos))
    {
        for(i = 0; i < Max && sum[i] == 0; i++);
        printf("Case %d:\n%d", case_n++, sum[i++]);
        for(; i< Max && sum[i] != 0; i++) printf(" %d", sum[i]); printf("\n\n");
        pos = Max / 2; memset(sum, 0, sizeof(sum));
    }
    return 0;
}
