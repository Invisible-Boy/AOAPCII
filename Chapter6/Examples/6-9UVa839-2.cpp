#include <cstdio>
using namespace std;
bool flag;
//使用stdio使得速度从0.08变为0.03
int mobile()
{
    int Wl, Dl, Wr, Dr;
    scanf("%d%d%d%d", &Wl, &Dl, &Wr, &Dr);
    if(!Wl) Wl = mobile();
    if(!Wr) Wr = mobile();
    if(Wl * Dl != Wr * Dr) flag = false;
    return Wl + Wr;
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int n; scanf("%d", &n);
    while(n--)
    {
        flag = true;
        mobile();
        printf("%s\n", flag ? "YES" : "NO");
        if(n) printf("\n");
    }
    return 0;
}
