#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
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
    scanf("%d", &T);
    while(T--)
    {
        vector<point> data; data.reserve(1000);
        scanf("%d", &num); num1 = num;
        while(num--)
        {
            point temp;
            scanf("%d%d", &temp.x, &temp.y);
            data.push_back(temp);
        }
        int len = num1 >> 1;
        sort(data.begin(), data.end(), cmp);
        sort(data.begin() + len, data.end(), cmp1);
        if(data.begin()->x == data.back().x)
        {
            printf("YES\n");
            continue;
        }
        vector<point>::iterator p1 = data.begin();
        point* p2 = &data.back();
        bool flag = true;
        int ave = p1->x + p2->x;
        for(int i = 1; i < len + 1 && flag; i++, p1++, p2--)
        {
            if(p1->x == p2->x && p2->x == ave >> 1) continue;
            if(p1->y != p2->y || p1->x + p2->x != ave) flag = false;
        }
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
