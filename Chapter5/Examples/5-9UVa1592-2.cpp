#include <string>
#include <map>
#include <vector>
#include <cstdio>
using namespace std;
const int Nmax = 10000, Mmax = 10;
int main()
{
    freopen("input.txt", "r", stdin);
    int n, m, d_base[Nmax][Mmax];
    while(scanf("%d%d", &n, &m) == 2)
    {
        getchar();
        string s;
        map<string, int> Map;
        char b;
        int i = 0, j = 0, ID = 0;
        while(i < n && (b = getchar()))
        {
            if(b == ',' || b == '\n')
            {
                if(!Map.count(s))
                {
                    Map[s] = ID;
                    ID++;
                }
                d_base[i][j] = Map[s];
                s.clear();
                j++;
            }
            else
                s += b;
            if(b == '\n')
            {
                i++;
                j = 0;
            }
        }
        int flag = 1;
        for(int j = 0; j < m - 1 && flag; j++)
            for(int i = 0; i < n - 1 && flag; i++)
                for(int k = i + 1; k < n && flag; k++)
                    if(d_base[i][j] == d_base[k][j])
                        for(int l = j + 1; l < m; l++)
                            if(d_base[i][l] == d_base[k][l])
                            {
                                flag = 0;
                                printf("NO\n%d %d\n%d %d\n", i+1, k+1, j+1, l+1);
                                break;
                            }
        if(flag)
            printf("YES\n");
    }
    return 0;
}
