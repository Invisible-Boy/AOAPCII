#include <cstdio>
#include <vector>
using namespace std;
struct node
{
    int left, right;
};
vector<node> mylist;
void link(int x, int y)
{
    mylist[x].right = y;
    mylist[y].left = x;
}
int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int n, m, c_num = 0;
    while(scanf("%d%d", &n, &m) == 2)
    {
        bool flag = false;
        mylist.clear(), mylist.reserve(n+1);
        mylist[0].left = 0; mylist[0].right = 0;
        for(int i = 1; i <= n; i++)
        {
            mylist[i].right = mylist[i-1].right;
            mylist[i-1].right = i;
            mylist[i].left = i-1;
        }
        while(m--)
        {
            int cmd, x, y;
            scanf("%d", &cmd);
            if(cmd == 4) flag = !flag;
            else
            {
                scanf("%d%d", &x, &y);
                if(flag && cmd < 3) cmd = 3 - cmd;
                switch(cmd)
                {
                case 1:
                    if(mylist[y].left != x) link(mylist[x].left, mylist[x].right), link(mylist[y].left, x), link(x, y);
                    break;
                case 2:
                    if(mylist[y].right != x) link(mylist[x].left, mylist[x].right), link(x, mylist[y].right), link(y, x);
                    break;
                case 3:
                    int x_l = mylist[x].left, x_r = mylist[x].right, y_l = mylist[y].left, y_r = mylist[y].right;
                    if(x_l == y) link(y, x_r), link(y_l, x), link(x, y);
                    else if(x_r == y) link(x, y_r), link(x_l, y), link(y, x);
                    else link(x_l, y), link(y, x_r), link(y_l, x), link(x, y_r);
                }
            }
            //用来检查是否真正发生了变化
            /*printf("--------------------------\n");
            for(int i = mylist[0].right; i != 0; i = mylist[i].right)
                printf("%d", i);
            printf("\n");*/
        }
        long long num = 0;
        int j;
        if(flag && n % 2 == 0) j = 0;
        else j = 1;
        for(int i = mylist[0].right; i != 0; i = mylist[i].right, j++)
            if(j % 2 == 1) num += i;
        printf("Case %d: %I64d\n", ++c_num, num);   //OJ上运行的是linux系统，因此提交的时候需要把I64d换成lld，才能AC
    }
    return 0;
}
