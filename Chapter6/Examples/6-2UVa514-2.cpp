#include <stack>
#include <cstdio>
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int n, temp, i = 1, j = 1;
    while((scanf("%d", &n)) && n)
    {
        stack<int> s;
        bool flag = true;
        while((scanf("%d", &temp)) && temp)
        {
            while(i < n)
            {
                if(flag)
                    if(temp == j) j++;
                    else
                    {
                        while(j <= temp && j <= n) s.push(j++);
                        if(s.empty() || temp != s.top()) flag = false;
                        else s.pop();
                    }
                scanf("%d", &temp);
                i++;
            }
            printf("%s\n", flag ? "Yes" : "No");
            flag = true, i = 1, j = 1;
        }
        printf("\n");
    }
    return 0;
}
