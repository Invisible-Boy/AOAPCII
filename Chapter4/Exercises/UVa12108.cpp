#include <iostream>
#include <stdio.h>
using namespace std;

struct student
{
    int awake_time;
    int sleep_time;
    int initial_time;
};
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);   //使用随机数产生测试样本，进行测试
    int n, case_num = 0, temp_time[10];
    student stu[10];
    while(scanf("%d", &n) && n)
    {
        printf("Case %d: ", ++case_num);
        int now_time = 1;
        for(int i = 0; i < n; i++)
        {
            scanf("%d%d%d", &stu[i].awake_time, &stu[i].sleep_time, &stu[i].initial_time);
            temp_time[i] = stu[i].initial_time;
        }
        while(1)
        {
            int num_sleep = 0, num_initial = 0;
            for(int i = 0; i < n; i++)
            {
                if(now_time - 1 && temp_time[i] == stu[i].initial_time)
                    num_initial++;
                if(temp_time[i] > stu[i].awake_time)
                    num_sleep++;
            }
            if(!num_sleep)
            {
                printf("%d\n", now_time);
                break;
            }
            else if(num_initial == n)
            {
                printf("-1\n");
                break;
            }
            else if(num_sleep * 2 <= n)
                for(int i = 0; i < n; i++)
                    if(temp_time[i] == stu[i].awake_time)
                        temp_time[i] = 0;
            for(int i = 0; i < n; i++)
                temp_time[i] = temp_time[i] % (stu[i].awake_time + stu[i].sleep_time) + 1;
            now_time++;
        }
    }
    return 0;
}
