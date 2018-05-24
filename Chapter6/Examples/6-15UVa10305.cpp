#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int MAX = 101;
int cnt;
bool flag[MAX]; //表示是否已经执行;
                //如果要检测是否有环路，则状态必须改为3态：未执行、执行中、执行过，在执行过程中判断标志位发现有执行中的即为有环路存在。
queue<int> myq[MAX];
void DFS(int i)
{
    if(flag[i])
    {
        while(!myq[i].empty()) myq[i].pop();
        return;
    }
    while(!myq[i].empty())
    {
        DFS(myq[i].front()); myq[i].pop();
    }
    if(cnt++) cout << ' ';
    cout << i;
    flag[i] = true;
}
int main()
{
    int n, m, id1, id2;
    while((cin >> n >> m) && n)
    {
        memset(flag, 0, sizeof(flag));
        cnt = 0;
        for(int i = 1; i <= m; i++)
        {
            cin >> id1 >> id2;
            myq[id2].push(id1);
        }
        for(int i = 1; i <= n; i++)
            DFS(i);
        cout << endl;
    }
    return 0;
}
