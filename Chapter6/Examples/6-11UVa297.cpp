#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
typedef string::iterator iter;
iter p1, p2;
int Quda(int flag)
{
    if(*p1 == 'e' && *p2 == 'e') return 0;
    if(*p1 == 'f' || *p2 == 'f')
    {
        int i, j = 3;
        if(*p1 == 'p')
        {
            p1++;
            for(i = 0; i < j; i++, p1++)
                if(*p1 == 'p') j += 4;
        }
        else if(*p2 == 'p')
        {
            p2++;
            for(i = 0; i < j; i++, p2++)
                if(*p2 == 'p') j += 4;
        }
        return flag;
    }
    int result = 0;
    if(*p1 == 'p' || *p2 == 'p')
    {
        int f = 0;
        if(*p1 == 'p') f |= 1;
        if(*p2 == 'p') f |= 2;
        for(int i = 0; i < 4; i++)
        {
            if(f & 1) p1++;
            if(f & 2) p2++;
            result += Quda(flag >> 2);
        }
    }
    return result;
}
int main()
{
    freopen("input.txt", "r", stdin);
    int n, result;
    string s1, s2; s1.reserve(100), s2.reserve(100);
    scanf("%d\n", &n);
    while(n--)
    {
        getline(cin, s1); getline(cin, s2);
        int flag = 1024;
        p1 = s1.begin(); p2 = s2.begin();
        result = Quda(flag);
        printf("There are %d black pixels.\n", result);
    }
    return 0;
}
