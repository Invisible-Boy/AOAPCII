#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
//这个版本与第一个版本的区别在于使用了.back()而不是.end()，.back()返回的是最后一个元素对象，.end返回的是迭代器
struct point
{
    int x, y;
};
bool cmp(point& A, point& B)
{
    return A.x < B.x || (A.x == B.x && A.y < B.y);
}
bool cmp1(point& A, point& B)
{
    return A.x < B.x || (A.x == B.x && A.y > B.y);
}
int main()
{
    freopen("input.txt", "r", stdin);
    int T, num, num1;
    cin >> T;
    while(T--)
    {
        vector<point> data; data.reserve(1000);
        cin >> num; num1 = num;
        while(num--)
        {
            point temp;
            cin >> temp.x >> temp.y;
            data.push_back(temp);
        }
        int len = num1 >> 1;
        sort(data.begin(), data.end(), cmp);
        sort(data.begin() + len, data.end(), cmp1);
        if(data.begin()->x == data.back().x)
        {
            cout << "YES\n";
            continue;
        }
        vector<point>::iterator p1 = data.begin();
        point* p2 = &data.back();
        bool flag = true;
        for(int i = 0; i < len + 1 && flag; i++, p1++, p2--)
        {
            int ave;
            if(p1->x == p2->x && p2->x == ave >> 1) continue;
            if(p1->y == p2->y)
            {
                if(!i) ave = p1->x + p2->x;
                else if(p1->x + p2->x != ave) flag = false;
            }
            else flag = false;
        }
        if(flag) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
