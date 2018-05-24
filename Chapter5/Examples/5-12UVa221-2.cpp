#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

struct building
{
    double px_b, py, px_e, height;
    int id;
};

bool cmp(building& A, building& B)
{
    return A.px_b < B.px_b || (A.px_b == B.px_b && A.py < B.py);
}
//判断建筑是否在某个区间内
bool isin(building& A, double x1, double x2)
{
    return A.px_b < x2 && A.px_e > x1;
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int case_num = 0, num;
    while(cin >> num && num)
    {
        if(case_num++) cout << '\n';
        vector<building> data;
        vector<double> p;
        int ID = 1;
        while(num--)
        {
            int l;
            building temp;
            cin >> temp.px_b >> temp.py >> temp.px_e >> l >> temp.height;
            temp.px_e += temp.px_b, temp.id = ID++; data.push_back(temp);
            p.push_back(temp.px_b); p.push_back(temp.px_e);
        }
        sort(data.begin(), data.end(), cmp);
        sort(p.begin(), p.end());
        p.resize(unique(p.begin(), p.end()) - p.begin());
        cout << "For map #" << case_num << ", the visible buildings are numbered as follows:\n";
        int cnt = 0;
        for(int i = 0; i < (int)data.size(); i++)
            for(int j = 0; j < (int)p.size() - 1; j++)
            {
                bool flag = false;
                if(isin(data[i], p[j], p[j + 1]))
                {
                    flag = true;
                    for(int k = 0; k < (int)data.size(); k++)
                        if(isin(data[k], p[j], p[j + 1]) && data[k].height >= data[i].height && data[k].py < data[i].py)
                        {
                            flag = false;
                            break;
                        }
                }
                if(flag)
                {
                    if(cnt++) cout << ' ';
                    cout << data[i].id;
                    break;
                }
            }
        cout << '\n';
    }
    return 0;
}
