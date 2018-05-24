#include <cstdio>
using namespace std;
const int Max = 100;
int r_max, m, n, result[Max][Max];
char data[Max][Max];
void DFS(int i, int j)
{
    result[i][j] = r_max;
    for(int i_temp = i - 1; i_temp <= i + 1; i_temp++)
    {
        if(i_temp < 0 || i_temp >= m) continue;
        for(int j_temp = j - 1; j_temp <= j + 1; j_temp++)
        {
            if(j_temp < 0 || j_temp >= n) continue;
            if(data[i_temp][j_temp] == '@' && result[i_temp][j_temp] == -1) DFS(i_temp, j_temp);
        }
    }
}
int main()
{
    freopen("input.txt", "r", stdin);
    while(scanf("%d%d\n", &m, &n) == 2 && m)
    {
        r_max = 0;
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                scanf("%c", &data[i][j]);
                result[i][j] = -1;
            }
            scanf("\n");
        }
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                if(data[i][j] == '@' && result[i][j] == -1)
                    DFS(i, j), r_max++;
        printf("%d\n", r_max);
    }
    return 0;
}
