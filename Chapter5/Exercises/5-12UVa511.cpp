#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;
double x_1, y_1;
struct mymap
{
    string name;
    double x[2], y[2], r, s;
};
bool cmp(mymap& A, mymap& B)
{
    return A.x[0] < B.x[0];
}
double dis(double x, double y)
{
    return pow((x_1 - x), 2) + pow((y_1 - y), 2);
}
bool cmp1(vector<mymap>::iterator A, vector<mymap>::iterator B)
{
    if(A->s != B->s) return A->s > B->s;
    double A_midx = (A->x[0] + A->x[1]) / 2, A_midy = (A->y[0] + A->y[1]) / 2, B_midx = (B->x[0] + B->x[1]) / 2, B_midy = (B->y[0] + B->y[1]) / 2;
    if(dis(A_midx, A_midy) != dis(B_midx, B_midy)) return dis(A_midx, A_midy) > dis(B_midx, B_midy);
    if(A->r != B->r) return A->r > B->r;
    double A_ry = min(A->y[0], A->y[1]), B_ry = min(B->y[0], B->y[1]);
    if(dis(A->x[1], A_ry) != dis(B->x[1], B_ry)) return dis(A->x[1], A_ry) < dis(B->x[1], B_ry);
    return A->x[0] > B->x[0];
}
int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    string s;
    vector<mymap> data; data.reserve(100);
    map<string, vector<vector<mymap>::iterator> > data_map;
    while((cin >> s) && s != "LOCATIONS")
    {
        if(s == "MAPS") continue;
        mymap temp;
        temp.name = s;
        for(int i = 0; i < 2; i++)
            cin >> temp.x[i] >> temp.y[i];
        if(temp.x[0] > temp.x[1])
        {
            double a = temp.x[0];
            temp.x[0] = temp.x[1], temp.x[1] = a;
        }
        double height = temp.y[0] - temp.y[1], width = temp.x[0] - temp.x[1];
        temp.r = abs(abs(height / width) - 0.75);
        temp.s = abs(height * width);
        data.push_back(temp);
    }
    sort(data.begin(), data.end(), cmp);
    while((cin >> s) && s != "REQUESTS")
    {
        cin >> x_1 >> y_1;
        vector<mymap>::iterator p = data.begin();
        if(!data_map.count(s)) data_map[s].reserve(50);
        for(; p != data.end(); p++)
            if(x_1 < p->x[0]) break;
            else if((x_1 - p->x[0]) * (x_1 - p->x[1]) <= 0 && (y_1 - p->y[0]) * (y_1 - p->y[1]) <= 0) data_map[s].push_back(p);
        sort(data_map[s].begin(), data_map[s].end(), cmp1);
        for(int i = 0; i < (int)data_map[s].size() - 1; i++)
            if(data_map[s][i]->s == data_map[s][i+1]->s) data_map[s][i] = data_map[s][i+1];
        data_map[s].resize(unique(data_map[s].begin(), data_map[s].end()) - data_map[s].begin());   //面积决定等级，同等级只保留一张地图
    }
    while((cin >> s) && s != "END")
    {
        int level; cin >> level;
        cout << s << " at detail level " << level << ' ';
        if(!data_map.count(s)) cout << "unknown location\n";
        else if(data_map[s].empty()) cout << "no map contains that location\n";
        else if(level > (int)data_map[s].size()) cout << "no map at that detail level; using " << data_map[s].back()->name << '\n';
        else cout << "using " << data_map[s][level-1]->name << '\n';
    }
    return 0;
}
