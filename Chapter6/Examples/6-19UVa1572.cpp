#include <cstring>
#include <cstdio>
//scanf和printf比cin和cout快5倍 50ms和250ms
//有向图环路的判定问题
using namespace std;
const int Max = 53;
bool exist[Max], flag;
int color[Max], has_edge[Max][Max];
void DFS(int i)
{
    if(flag) return;
    color[i] = 1;
    for(int j = 0; j < Max && !flag; j++)
        if(has_edge[i][j] && exist[j])
            if(!color[j])
            {
                DFS(j);
                color[j] = 2;
            }
            else if(color[j] == 1) flag = true;
}
int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    while(scanf("%d", &n) == 1)
    {
        flag = false;
        memset(exist, 0, sizeof(exist));
        memset(color, 0, sizeof(color));
        memset(has_edge, 0, sizeof(has_edge));
        char temp[10];
        for(int i = 0; i < n; i++)
        {
            scanf("%s", temp);
            int id[4] = {-1, -1, -1, -1};
            for(int j = 0; j < 4; j++)
            {
                if(temp[j << 1] == '0') continue;
                id[j] = temp[j << 1] - 'A';
                if(temp[(j << 1) + 1] == '+') id[j] += 27;
                else id[j] = 25 - id[j];
                exist[id[j]] = true;
            }
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 4; k++)
                    if(j != k && id[j] != -1 && id[k] != -1)
                        has_edge[id[j]][Max - 1 - id[k]] = true;
        }
        int color_id = 1;
        for(int i = 0; i < Max && !flag; i++)
            if(exist[i] && !color[i])
            {
                DFS(i);
                color[i] = 2;
            }
        if(flag) printf("unbounded\n");
        else printf("bounded\n");
    }
    return 0;
}
