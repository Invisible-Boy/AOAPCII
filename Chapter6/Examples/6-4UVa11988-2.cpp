#include <cstdio>
#include <cstring>
int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    const int Max = 100005;
    char s[Max];
    int next[Max], start, last, cur, n;
    while(scanf("%s", s) == 1)
    {
        n = strlen(s);
        start = last = cur = -1;
        bool flag_b = true;
        for(int i = 0; i < n; i++)
        {
            if(s[i] == '[') flag_b = true;
            else if(s[i] == ']') flag_b = false, cur = last;
            else
            {
                if(flag_b || start == -1)
                {
                    flag_b = false;
                    next[i] = start;
                    start = i;
                }
                else
                {
                    next[i] = next[cur];
                    next[cur] = i;
                }
                if(cur == last || last == -1) last = i;
                cur = i;
            }
        }
        for(int i = start; i != -1; i = next[i])
            printf("%c", s[i]);
        printf("\n");
    }
    return 0;
}
