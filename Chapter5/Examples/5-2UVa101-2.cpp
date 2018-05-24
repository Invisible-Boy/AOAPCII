#include <iostream>
#include <vector>
#include <string>
using namespace std;
const int Nmax = 30;
int n;
vector<int> pile[Nmax];
void find_block(int& a, int& pa, int& ha)
{
    for(pa = 0; pa < n; pa++)
        for(ha = 0; ha < pile[pa].size(); ha++)
            if(pile[pa][ha] == a) return;
}
void guiwei(int pa, int ha)
{
    for(int i = ha + 1; i < pile[pa].size(); i++)
        pile[pile[pa][i]].push_back(pile[pa][i]);
    pile[pa].resize(ha + 1);
}
void move_ab(int pa, int ha, int pb)
{
    for(int i = ha; i < pile[pa].size(); i++)
        pile[pb].push_back(pile[pa][i]);
    pile[pa].resize(ha);
}
int main()
{
    cin >> n;
    for(int i = 0; i < n; i++)
        pile[i].push_back(i);
    string c1, c2;
    while(cin >> c1 && c1 != "quit")
    {
        int a, b, pa, pb, ha, hb;
        cin >> a >> c2 >> b;
        find_block(a, pa, ha);
        find_block(b, pb, hb);
        if(pa == pb)
            continue;
        if(c1 == "move")    guiwei(pa, ha);   //不能提前归位，必须先判断是否是有效操作
        if(c2 == "onto")    guiwei(pb, hb);
        move_ab(pa, ha, pb);
    }
    for(int i = 0; i < n; i++)
    {
        cout << i << ":";
        for(int j = 0; j < pile[i].size(); j++)
            cout << " " << pile[i][j];
        cout << endl;
    }
    return 0;
}
