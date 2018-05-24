#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int num, l, time = 0;
        vector<int> data;
        queue<int> q;
        scanf("%d%d", &num, &l);
        for(int i = 0; i < num; i++)
        {
            int temp;
            scanf("%d", &temp);
            data.push_back(temp); q.push(temp);
        }
        sort(data.begin(), data.end(), greater<int>());
        for(vector<int>::iterator p = data.begin(); p != data.end();)
        {
            if(l == 0)
            {
                if(q.front() == *p)
                {
                    time++; break;
                }
                else q.push(q.front()), q.pop(), l = (int)q.size() - 1;
            }
            else if(q.front() == *p) q.pop(), time++, l--, p++;
            else q.push(q.front()), q.pop(), l--;
        }
        printf("%d\n", time);
    }
    return 0;
}
