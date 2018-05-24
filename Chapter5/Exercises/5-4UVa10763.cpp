#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
struct stu
{
    int l, t;
};
bool cmp1(stu& A, stu& B)
{
    return A.l < B.l || (A.l == B.l && A.t < B.t);
}
bool cmp2(stu& A, stu& B)
{
    return A.t < B.t || (A.t == B.t && A.l < B.l);
}
int main()
{
    freopen("input.txt", "r", stdin);
    int num;
    while((cin >> num) && num)
    {
        bool flag = true;
        if(num % 2 == 1) flag = false;
        stu data1[num], data2[num];
        for(int i = 0; i < num; i++)
            cin >> data1[i].l >> data1[i].t;
        memcpy(data2, data1, sizeof(data1));
        sort(data1, data1 + num, cmp1);
        sort(data2, data2 + num, cmp2);
        for(int i = 0; i < num / 2 && flag; i++)
        {
            if(data1[i].l != data2[i].t || data1[i].t != data2[i].l)
                flag = false;
        }
        if(flag) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
