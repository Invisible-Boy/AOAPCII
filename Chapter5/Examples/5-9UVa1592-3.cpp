#include <iostream>
#include <string>
#include <map>
#include <cstdio>
using namespace std;
struct node
{
    int x, y;
    node(int a = 0, int b = 0): x(a), y(b) {}
};

bool operator < (const node& A, const node& B)
{
    return A.x < B.x || (A.x == B.x && A.y < B.y);
}

int main()
{
    //freopen("input.txt", "r", stdin);
    const int Nmax = 10000, Mmax = 10;
    int n, m, d_base[Nmax][Mmax];
    while(cin >> n >> m)
    {
        cin.get();
        string s;
        map<string, int> Map;
        char b;
        int i = 0, j = 0, ID = 0;
        while(i < n && (b = cin.get()))
        {
            if(b == ',' || b == '\n')
            {
                if(!Map.count(s))
                    Map[s] = ID++;
                d_base[i][j] = Map[s];
                j++;
                s.clear();
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
        for(int i = 0; i < m - 1 && flag; i++)
        {
            for(int j = i + 1; j < m && flag; j++)
            {
                map<node, int> result;
                for(int r = 0; r < n && flag; r++)
                {
                    node p(d_base[r][i], d_base[r][j]);
                    if(!result.count(p))
                        result[p] = r;
                    else
                    {
                        flag = 0;
                        cout << "NO" << endl << result[p] + 1 << ' ' << r + 1 << endl << i + 1 << ' ' << j + 1 << endl;
                    }
                }
            }
        }
        if(flag)
            cout << "YES" << endl;
    }
    return 0;
}
