#include <cstdio>
using namespace std;
bool flag;
//ʹ��stdioʹ���ٶȴ�0.08��Ϊ0.03
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
