#include <cstdio>
#include <cstring>
//头节点为next[0],本身不存任何有意义的数据
int main()
{
    freopen("input.txt", "r", stdin);
    const int Max = 100005;
    int next[Max], cur, last, n;
    char s[Max];
    while(scanf("%s", s+1) == 1)
    {
        n = strlen(s+1);
        cur = last = 0;
        next[0] = 0;
        for(int i = 1; i <= n; i++)
        {
            if(s[i] == '[') cur = 0;
            else if(s[i] == ']') cur = last;
            else
            {
                next[i] = next[cur];
                next[cur] = i;
                if(cur == last) last = i;
                cur = i;
            }
        }
        for(int i = next[0]; i != 0; i = next[i])
            printf("%c", s[i]);
        printf("\n");
    }
}
