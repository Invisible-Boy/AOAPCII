#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAX = 10;
struct node
{
    int r, c, dir;
    node(int r = 0, int c = 0, int dir = 0) : r(r), c(c), dir(dir) {}
};
node p[MAX][MAX][4];
int r0, c0, dir0, r1, c1, d[MAX][MAX][4], deta_r[] = {-1, 0, +1, 0}, deta_c[] = {0, -1, 0, 1};
bool has_edge[MAX][MAX][4][4];
map<char, int> mymap;
string name;
bool read()
{
    cin >> name;
    if(name == "END") return false;
    cout << name << endl;
    char temp;
    memset(has_edge, 0, sizeof(has_edge));
    memset(d, 0, sizeof(d));
    cin >> r0 >> c0 >> temp >> r1 >> c1;
    dir0 = mymap[temp];
    has_edge[r0][c0][dir0][dir0] = true;
    int temp_r, temp_c;
    while((cin >> temp_r) && temp_r)
    {
        cin >> temp_c; cin.get();
        while((temp = cin.get()) && temp != '*')
        {
            int dir = mymap[temp];
            while((temp = cin.get()) && temp != ' ')
                has_edge[temp_r][temp_c][dir][(mymap[temp] + dir) % 4] = 1;
        }
    }
    return true;
}
node walk(const node &A, int dir)
{
    return node(A.r + deta_r[dir], A.c + deta_c[dir], dir);
}
bool isin(const node &A)
{
    return A.r < 10 && A.r > 0 && A.c < 10 && A.c > 0;
}
void ans(node u)
{
    stack<node> result;
    result.push(u);
    while(d[u.r][u.c][u.dir] > 1)
    {
        u = p[u.r][u.c][u.dir];
        result.push(u);
    }
    result.push(node(r0, c0, dir0));
    int cnt = 0;
    while(!result.empty())
    {
        if(cnt % 10 == 0) cout << ' ';
        cout << " (" << result.top().r << ',' << result.top().c << ')'; result.pop();
        if(++cnt % 10 == 0) cout << endl;
    }
    if(cnt % 10) cout << endl;
}
void slove()
{
    queue<node> q;
    node u(r0 + deta_r[dir0], c0 + deta_c[dir0], dir0);
    d[u.r][u.c][u.dir] = 1;
    q.push(u);
    while(!q.empty())
    {
        u = q.front(); q.pop();
        if(u.r == r1 && u.c == c1){ans(u); return;}
        for(int i = 0; i < 4; i++)
        {
            node v = walk(u, i);
            if(has_edge[u.r][u.c][u.dir][i] && isin(v) && !d[v.r][v.c][v.dir])
            {
                d[v.r][v.c][v.dir] = d[u.r][u.c][u.dir] + 1;
                p[v.r][v.c][v.dir] = u;
                q.push(v);
            }
        }
    }
    cout << "  No Solution Possible\n";
}
int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    mymap['N'] = 0; mymap['W'] = 1; mymap['S'] = 2; mymap['E'] = 3;
    mymap['F'] = 0; mymap['L'] = 1; mymap['R'] = 3;
    name.reserve(21);
    while(read())
    {
        slove();
    }
    return 0;
}
