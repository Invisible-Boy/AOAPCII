#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
//ʹ��scanf��printf��û��ʹЧ�ʱ�ߣ���������0.01��
struct staff
{
    int id, r_t, b_t, k;
    vector<int> tid;
};
struct topic
{
    int num, b_t, r_t, dt, flag;
};
bool cmp(staff& A, staff& B)
{
    return A.r_t < B.r_t || (A.r_t == B.r_t && A.b_t < B.b_t) || (A.r_t == B.r_t && A.b_t == B.b_t && A.id < B.id);
}
int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int N, M, case_n = 1;
    while((scanf("%d", &N)) && N)
    {
        map<int, topic> topic_map;
        vector<staff> man;
        for(int i = 0; i < N; i++)
        {
            int tid;
            topic temp;
            scanf("%d%d%d%d%d", &tid, &temp.num, &temp.b_t, &temp.r_t, &temp.dt);
            temp.flag = 0;
            topic_map[tid] = temp;
        }
        scanf("%d", &M); man.reserve(M);
        for(int i = 0; i < M; i++)
        {
            staff temp;
            scanf("%d%d", &temp.id, &temp.k);
            temp.id = i, temp.b_t = 0, temp.r_t = 0;
            for(int j = 0; j < temp.k; j++)
            {
                int tid;
                scanf("%d", &tid); temp.tid.push_back(tid);
            }
            man.push_back(temp);
        }
        int result = 0;
        bool flag = true;
        while(flag)
        {
            flag = false;
            map<int, topic>::iterator p = topic_map.begin();
            for(; p != topic_map.end(); p++)
            {
                if(p->second.num && result == p->second.b_t) p->second.b_t += p->second.dt, p->second.flag++, p->second.num--; //�ж��Ƿ���������
                if(p->second.num || p->second.flag) flag = true;
            }
            sort(man.begin(), man.end(), cmp);
            for(int i = 0; i < M; i++)
                if(man[i].r_t) man[i].r_t--;
                else
                    for(int j = 0; j < man[i].k; j++)
                    {
                        int tid = man[i].tid[j];
                        if(topic_map[tid].flag)
                        {
                            topic_map[tid].flag--, man[i].r_t = topic_map[tid].r_t - 1, man[i].b_t = result;
                            break;
                        }
                    }
            result++;
        }
        //��ͼͨ�����һ��ֱ����ʱ��+ʣ��ʱ��,��������һ��flag=1,��r_t = 1,��ô�����һ���ӱ������...������WA,û���ж�
        int temp = 0;
        for(int i = 0; i < M; i++) if(man[i].r_t > temp) temp = man[i].r_t;
        result += temp;
        printf("Scenario %d: All requests are serviced within %d minutes.\n", case_n++, result);
    }
    return 0;
}
