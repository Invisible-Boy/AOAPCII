#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>
#include <cstdio>
#include <iomanip>
using namespace std;
//-2版本测试，分开处理奖金和集中计算奖金的精度是否会影响OJ评判，结果是不会
//此题有两个坑，第一个，对于DQ的玩家，其首先要按照完成的轮数排序，再按总分（有几轮算几轮）排序，最后按名字排序
struct person
{
    string name;
    int score[4], total2, total4, dq;
};

bool cmp1(person A, person B)
{
    if(A.dq > 1 && B.dq > 1) return A.total2 < B.total2;
    return A.dq > B.dq;
}

bool cmp2(person A, person B)
{
    if(A.dq != B.dq) return A.dq > B.dq;
    if(A.total4 != B.total4) return A.total4 < B.total4;
    return A.name < B.name;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int k;
    cin >> k;
    while(k--)
    {
        double purse, per_purse[70];
        cin >> purse;
        for(int i = 0; i < 70; i++)
        {
            cin >> per_purse[i];
            per_purse[i] = per_purse[i] / 100.0 * purse;
        }
        int person_num;
        cin >> person_num;
        cin.get();
        vector<person> p_base;
        while(person_num--)
        {
            person temp;
            temp.name.clear();
            string temp1;
            for(int i = 0; i < 20; i++)
            {
                char a = cin.get();
                if(a == ' ')
                    temp1 += a;
                else
                {
                    temp.name += temp1 + a;
                    temp1.clear();
                }
            }
            if(temp.name.empty())
                temp.name += temp1;
            int flag = 1;
            temp.dq = 4;
            for(int i = 0; i < 4 && flag; i++)
            {
                temp.score[i] = 0;
                for(int j = 0; j < 3 && flag; j++)
                {
                    char a = cin.get();
                    if(isdigit(a))
                        temp.score[i] = temp.score[i] * 10 + a - '0';
                    else if(a == 'D')
                    {
                        cin.get();
                        temp.dq = i;
                        flag = 0;
                    }
                }
            }
            cin.get(); temp.total4 = 0;
            temp.total2 = temp.dq > 1 ? temp.score[0] + temp.score[1] : temp.score[0];
            for(int j = 0; j < temp.dq; j++) temp.total4 += temp.score[j];
            p_base.push_back(temp);
        }
        sort(p_base.begin(), p_base.end(), cmp1);
        for(int i = 0; i < (int)p_base.size(); i++)
        {
            if(i < 70 && p_base[i].dq < 2)
                p_base.resize(i);
            if(i >= 70 && p_base[i].total2 > p_base[69].total2)
                p_base.resize(i);
        }
        sort(p_base.begin(), p_base.end(), cmp2);
        cout << "Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won" << endl;
        cout << "-----------------------------------------------------------------------" << endl;
        int money_rank = 0;
        for(int i = 0; i < (int)p_base.size();)
        {
            int temp = 0, temp_A = 0;
            while(i + temp < (int)p_base.size() && p_base[i + temp].total4 == p_base[i].total4)
            {
                if(p_base[i + temp].name[p_base[i + temp].name.length() - 1] == '*')
                    temp_A++;
                temp++;
            }
            double money = 0.0;
            bool flag_m = false;
            for(int j =0; j < temp - temp_A; j++)
                if(money_rank < 70)
                    money += per_purse[money_rank++], flag_m = true;
            if(temp - temp_A > 0)
                money = money / (temp - temp_A);
            for(int j = 0; j < temp; j++)
            {
                int pro;
                cout << left << setw(21) << p_base[i + j].name;
                if(p_base[i + j].name[p_base[i + j].name.length() - 1] == '*' || !flag_m)  //如果奖金发完了，则该玩家即使是职业玩家也不得奖金
                                                                                           //因此其排名不能有T，同时奖金不输出（与奖金是0.0）不同
                                                                                           //因此其表现与业余选手相同
                    pro = 0;
                else
                    pro = 1;
                if(p_base[i + j].dq != 4)
                    cout << "          ";
                else if(!pro || temp - temp_A < 2)
                    cout << setw(10) << i + 1;
                else
                    cout << i + 1 << setw(i + 1 > 9 ? 8 : 9) << 'T';
                for(int k = 0; k < p_base[i + j].dq; k++) cout << setw(5) << p_base[i + j].score[k];
                for(int k = p_base[i + j].dq; k < 4; k++) cout << "     ";
                if(p_base[i + j].dq == 4)
                {
                    if(!pro)
                    {
                        cout << p_base[i + j].total4 << endl;
                        continue;
                    }
                    cout << setw(10) << p_base[i + j].total4 << '$' << right << setw(9) << setiosflags(ios::fixed) <<setprecision(2) << money + 1e-8 << endl;
                }
                else
                    cout << "DQ" << endl;
            }
            i += temp;
        }
        if(k)
            cout << endl;
    }
    return 0;
}
