#include <cstdio>
#include <stack>
#include <cctype>
//本题没有什么难点，主要是注意，在getchar之前要注意吃掉前一行的换行符
using namespace std;
struct node
{
    int r, c;
};
int main()
{
    freopen("input.txt", "r", stdin);
    node data[26];
    int n, num = 0;
    scanf("%d\n", &n);
    char c;
    while(n--)
    {
        scanf("%c", &c);
        int id = c - 'A';
        scanf("%d%d\n", &data[id].r, &data[id].c);
    }
    stack<node> s;
    bool flag = true;
    while((c = getchar()) && c != EOF)
    {
        if(flag)
        {
            if((c == ')' || c == '\n') && (int)s.size() > 1)
            {
                node &B = s.top(); s.pop();
                node &A = s.top(); s.pop();
                if(A.c != B.r) flag = false;
                else
                {
                    num += A.r * A.c * B.c;
                    node temp = {A.r, B.c};
                    s.push(temp);
                }
            }
            else if(isalpha(c)) s.push(data[c - 'A']);
        }
        if(c == '\n')
        {
            if(flag) printf("%d\n", num);
            else printf("error\n");
            flag = true, num = 0;
            while(!s.empty()) s.pop();
        }
    }
    return 0;
}
