#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdio>

using namespace std;

struct Node
{
    double x, y, range;
    Node(double x = 0, double y = 0, double range = 0) : x(x), y(y), range(range) {}
};

const int NMAX = 1000;
vector<Node> data(NMAX);
vector<bool> flag(NMAX);
double ans_l, ans_r;
int n;

bool IsConnect(int i, int j)
{
    int detax = data[i].x - data[j].x;
    int detay = data[i].y - data[j].y;
    int detar = data[i].range + data[j].range;
    return sqrt(pow(detax, 2) + pow(detay, 2)) <= detar;
}

bool Dfs(int i)
{
    flag[i] = true;
    if(data[i].y - data[i].range <= 0)
        return false;
    if(data[i].x - data[i].range <= 0)
        ans_l = min(ans_l, data[i].y - sqrt(pow(data[i].range, 2) - pow(data[i].x, 2)));
    if(data[i].x + data[i].range >= 1000)
        ans_r = min(ans_r, data[i].y - sqrt(pow(data[i].range, 2) - pow(1000 - data[i].x, 2)));
    for(int j = 0; j < n; j++)
        if(!flag[j] && IsConnect(i, j) && !Dfs(j))
            return false;
    return true;
}

int main()
{
    freopen("input.txt", "r", stdin);
    while(cin >> n)
    {
        data.clear();
        flag.clear();
        for(int i = 0; i < n; i++)
        {
            int x, y, range;
            cin >> x >> y >> range;
            data.push_back(Node(x, y, range));
            flag.push_back(false);
        }
        ans_l = ans_r = 1000;
        bool ok = true;
        for(int i = 0; i < n; i++)
            if(!flag[i] && data[i].y + data[i].range >= 1000 && !Dfs(i))
            {
                ok = false;
                break;
            }
        if(ok) cout << "0.00 " << setprecision(2) << fixed << ans_l << " 1000.00 " << ans_r << endl;
        else cout << "IMPOSSIBLE\n";
    }
    return 0;
}
