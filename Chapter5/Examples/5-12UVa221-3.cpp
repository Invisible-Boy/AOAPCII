#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

struct building
{
    double px_b, py, px_e, height;
    int id;
    bool flag;
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
    //freopen("output.txt", "w", stdout);
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
            temp.px_e += temp.px_b, temp.id = ID++, temp.flag = false; data.push_back(temp);
            p.push_back(temp.px_b); p.push_back(temp.px_e);
        }
        sort(data.begin(), data.end(), cmp);
        sort(p.begin(), p.end());
        p.resize(unique(p.begin(), p.end()) - p.begin());
        vector<int> result[(int)p.size() - 1];
        for(int i = 0; i < (int)data.size(); i++)
            for(int j = 0; j < (int)p.size() - 1; j++)
                if(isin(data[i], p[j], p[j + 1])) result[j].push_back(i);
        cout << "For map #" << case_num << ", the visible buildings are numbered as follows:\n";
        vector<building> fresult;
        for(int i = 0; i < (int)p.size() - 1; i++)
            for(int j = 0; j < (int)result[i].size(); j++)
            {
                int id = result[i][j];
                if(data[id].flag) continue;
                bool flag = true;
                for(int k = 0; k < (int)result[i].size(); k++)
                {
                    int id2 = result[i][k];
                    if(data[id2].height >= data[id].height && data[id2].py < data[id].py)
                    {
                        flag = false;
                        break;
                    }
                }
                if(flag)
                {
                    fresult.push_back(data[id]);
                    data[id].flag = true;
                }
            }
        sort(fresult.begin(), fresult.end(), cmp);
        for(int i = 0; i < (int)fresult.size(); i++)  //最后排序，修正了第1个版本的问题
        {
            if(i) cout << ' ';
            cout << fresult[i].id;
        }
        cout << '\n';
    }
    return 0;
}
