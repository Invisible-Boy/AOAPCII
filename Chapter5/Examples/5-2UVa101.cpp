#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

const int Nmax = 26;
int location[Nmax][Nmax] = {0}, block[Nmax][2]; //location矩阵存放每个位置放置的积木编号，block存放每个积木所在的位置
void guiwei(int a)
{
    int start = block[a][1] + 1, length = location[block[a][0]][25];
    for(int i = start; i < length; i++)
    {
        block[location[block[a][0]][i]][0] = location[block[a][0]][i];
        location[location[block[a][0]][i]][location[location[block[a][0]][i]][25]] = location[block[a][0]][i];
        block[location[block[a][0]][i]][1] = location[location[block[a][0]][i]][25]++;
    }
    location[block[a][0]][25] = start;
}
void move_ab(int a, int b)
{
    int temp = block[a][0], start = block[a][1], length = location[temp][25];
    for(int i = start; i < length; i++)
    {
        block[location[temp][i]][0] = block[b][0];
        location[block[b][0]][location[block[b][0]][25]] = location[temp][i];
        block[location[temp][i]][1] = location[block[b][0]][25]++;
    }
    location[temp][25] = start;
}
void cmd(int a, int b, int flag)
{
    if(a == b || block[a][0] == block[b][0])
        return;
    switch(flag)
    {
        case 0:
            guiwei(a);guiwei(b);
            break;
        case 1:
            guiwei(a);
            break;
        case 2:
            guiwei(b);
    }
    move_ab(a, b);
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    string command;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        block[i][0] = i;
        block[i][1] = 0;
        location[i][0] = i;
        location[i][25] = 1;
    }
    while(cin >> command && command != "quit")
    {
        int a, b;
        if(command == "move")
        {
            cin >> a >> command >> b;
            if(command == "onto")
                cmd(a, b, 0);
            else
                cmd(a, b, 1);
        }
        else
        {
            cin >> a >> command >> b;
            if(command == "onto")
                cmd(a, b, 2);
            else
                cmd(a, b, 3);
        }
    }
    for(int i = 0; i < n; i++)
    {
        cout << i << ":";
        for(int j = 0; j < location[i][25]; j++)
            cout << " " << location[i][j];
        cout << endl;
    }
    return 0;
}
