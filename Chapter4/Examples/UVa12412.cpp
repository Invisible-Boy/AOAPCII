#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define Nmax 101
#define EPS 1e-5
using namespace std;

struct student
{
    char SID[11], name[11];
    int CID, score[4], myrank, score_sum;
};
student stu[Nmax];
int stu_num = 0;

void Add()
{
    while(1)
    {
        printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
        scanf("%s", stu[stu_num].SID);
        if(strlen(stu[stu_num].SID) == 1)
            return;
        else
        {
            int flag = 1;
            for(int i = 0; i < stu_num; i++)
                if(!strcmp(stu[stu_num].SID, stu[i].SID))
                {
                    printf("Duplicated SID.\n");
                    flag = 0;
                    break;
                }
            scanf("%d %s%d%d%d%d", &stu[stu_num].CID, stu[stu_num].name, &stu[stu_num].score[0], &stu[stu_num].score[1], &stu[stu_num].score[2], &stu[stu_num].score[3]);
            if(flag)
            {
                stu[stu_num].score_sum = stu[stu_num].score[0] + stu[stu_num].score[1] + stu[stu_num].score[2] + stu[stu_num].score[3];
                if(!stu_num)
                {
                    stu[0].myrank = 1;
                    stu_num++;
                    continue;
                }
                int min_rank = 10000;
                for(int i = 0; i < stu_num; i++)
                {
                    if(stu[stu_num].score_sum >= stu[i].score_sum)
                    {
                        if(min_rank > stu[i].myrank)
                            min_rank = stu[i].myrank;
                        if(stu[stu_num].score_sum > stu[i].score_sum)
                            stu[i].myrank++;
                    }
                }
                stu[stu_num].myrank = (min_rank == 10000) ? stu_num + 1 : min_rank;
                stu_num++;
            }
        }
    }
}

void Remove()
{
    while(1)
    {
        printf("Please enter SID or name. Enter 0 to finish.\n");
        char temp[11];
        scanf("%s", temp);
        if(strlen(temp) == 1 && temp[0] == '0')
            return;
        if(isdigit(temp[0]))
        {
            int i;
            for(i = 0; i < stu_num; i++)
                if(!strcmp(temp, stu[i].SID))
                    break;
            if(i != stu_num)
            {
                int tagert_rank = stu[i].myrank;
                for(int j = 0; j < stu_num - 1; j++)
                {
                    if(j >= i)
                        stu[j] = stu[j + 1];
                    if(stu[j].myrank > tagert_rank)
                        stu[j].myrank--;
                }
                stu_num--;
                printf("1 student(s) removed.\n");
            }
            else
                printf("0 student(s) removed.\n");
        }
        else
        {
            int num = 0;
            for(int i = 0; i < stu_num; i++)
            {
                if(!strcmp(temp, stu[i].name))
                {
                    num++;
                    int tagert_rank = stu[i].myrank;
                    for(int j = 0; j < stu_num - 1; j++)
                    {
                        if(j >= i) stu[j] = stu[j + 1];
                        if(stu[j].myrank > tagert_rank) stu[j].myrank--;
                    }
                    stu_num--, i--;  //采用覆盖删除，因此在覆盖之后i的值不能++，否则删除的不完全
                }
            }
            printf("%d student(s) removed.\n", num);
        }
    }
}

void Query()
{
    while(1)
    {
        printf("Please enter SID or name. Enter 0 to finish.\n");
        char temp[11];
        scanf("%s",temp);
        if(strlen(temp) == 1 && temp[0] == '0')
            return;
        if(isdigit(temp[0]))
        {
            for(int i = 0; i < stu_num; i++)
                if(!strcmp(temp, stu[i].SID))
                {
                    printf("%d %s %d %s %d %d %d %d %d %.2lf\n", stu[i].myrank, stu[i].SID, stu[i].CID, stu[i].name, stu[i].score[0], stu[i].score[1], stu[i].score[2], stu[i].score[3], stu[i].score_sum, (double)stu[i].score_sum / 4.0 + EPS);
                    break;
                }
        }
        else
            for(int i = 0; i < stu_num; i++)
                if(!strcmp(temp, stu[i].name))
                    printf("%d %s %d %s %d %d %d %d %d %.2lf\n", stu[i].myrank, stu[i].SID, stu[i].CID, stu[i].name, stu[i].score[0], stu[i].score[1], stu[i].score[2], stu[i].score[3], stu[i].score_sum, (double)stu[i].score_sum / 4.0 + EPS);
    }
}
void Show_rank()
{
    printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");
}

void Show_sta()
{
    printf("Please enter class ID, 0 for the whole statistics.\n");
    int CID, pass[5] = {0}, pass_s[4] = {0}, sum_s[4] = {0}, num_sum = 0;
    scanf("%d", &CID);
    for(int i = 0; i < stu_num; i++)
    {
        if(stu[i].CID == CID || !CID)
        {
            int temp = 0;
            for(int j = 0; j < 4; j++)
            {
                if(stu[i].score[j] >= 60)
                {
                    pass_s[j]++;
                    temp++;
                }
                sum_s[j] += stu[i].score[j];
            }
            pass[temp]++;
            num_sum++;
        }
    }
    for(int i = 0; i < 4; i++)
    {
        if(i == 0)
            printf("Chinese\n");
        else if(i == 1)
            printf("Mathematics\n");
        else if(i == 2)
            printf("English\n");
        else if(i == 3)
            printf("Programming\n");
        printf("Average Score: %.2lf\nNumber of passed students: %d\nNumber of failed students: %d\n\n",num_sum == 0 ? 0.0 : (double)sum_s[i] / (double)num_sum + EPS, pass_s[i], num_sum - pass_s[i]);
    }
    printf("Overall:\n");
    printf("Number of students who passed all subjects: %d\n", pass[4]);
    printf("Number of students who passed 3 or more subjects: %d\n", pass[3] + pass[4]);
    printf("Number of students who passed 2 or more subjects: %d\n", pass[2] + pass[3] + pass[4]);
    printf("Number of students who passed 1 or more subjects: %d\n", pass[1] + pass[2] + pass[3] + pass[4]);
    printf("Number of students who failed all subjects: %d\n\n", pass[0]);
}

int main()
{
    //freopen("input.txt", "r", stdin);
    while(1)
    {
        int flag;
        printf("Welcome to Student Performance Management System (SPMS).\n\n1 - Add\n2 - Remove\n3 - Query\n4 - Show ranking\n5 - Show Statistics\n0 - Exit\n\n");
        scanf("%d", &flag);
        switch(flag)
        {
            case 1:
                Add();
                break;
            case 2:
                Remove();
                break;
            case 3:
                Query();
                break;
            case 4:
                Show_rank();
                break;
            case 5:
                Show_sta();
                break;
        }
        if(!flag)
            break;
    }
    return 0;
}
