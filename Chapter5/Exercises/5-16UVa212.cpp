#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <iomanip>
#include <list> //priority_queueʹ��list��Ϊ���������bug
#include <cstdio>
using namespace std;
struct mytime
{
    int hour, minute;
};
struct patient
{
    //id��ʾ���˱�š�room��ʾ���˵������ҡ�bed��ʾ���˵Ļָ���λ
    //need_oper��ʾ������Ҫ��ʱ�䡢need_reco��ʾ�ָ���Ҫ��ʱ��
    int id, room, bed, need_oper, need_reco;
    //oper_b��ʾ������ʼ��ʱ�䡢oper_e��ʾ����������ʱ��
    //reco_b��ʾ�ָ���ʼ��ʱ�䡢reco_e��ʾ�ָ�������ʱ��
    mytime oper_b, oper_e, reco_b, reco_e;
    string name;
};
struct room
{
    //id��ʾ�����һ��ߴ�λ�š�begin_time��ʾ��һ�������һ��ߴ�λ����ʹ�õ�ʱ��
    int id, use_t;
    mytime begin_time;
};
bool cmp_room1(room &A, room &B)
{
    return A.id < B.id;
}
struct cmp_room
{
    bool operator () (room &A, room &B)
    {
        if(A.begin_time.hour != B.begin_time.hour) return A.begin_time.hour > B.begin_time.hour;
        if(A.begin_time.minute != B.begin_time.minute) return A.begin_time.minute > B.begin_time.minute;
        return A.id > B.id;
    }
};
bool cmp_patient(patient &A, patient &B)
{
    return A.id < B.id;
}
bool cmp_patient1(patient &A, patient &B)
{
    if(A.oper_e.hour != B.oper_e.hour) return A.oper_e.hour < B.oper_e.hour;
    if(A.oper_e.minute != B.oper_e.minute) return A.oper_e.minute < B.oper_e.minute;
    return A.room < B.room;
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    //��ʾ�ܵ�ʱ��
    mytime begin_time;
    //room_num��ʾ�����ҷ�������bed_num��ʾ�ָ�����Ŀ��oper_begin��ʾ��һ�����˿�ʼ������ʱ��
    //otr_time��ʾ�Ӵ������ҵ��ָ��ҵ�ʱ�䡢oper_pretime��ʾ������׼��ʱ�䡢reco_pretime��ʾ�ָ��ҵ�׼��ʱ��
    //patient_num��ʾ��������
    int room_num, bed_num, oper_begin, otr_time, oper_pretime, reco_pretime, patient_num, all_time = 0;
    while(cin >> room_num >> bed_num >> oper_begin >> otr_time >> oper_pretime >> reco_pretime >> patient_num)
    {
        begin_time.hour = oper_begin; begin_time.minute = 0;
        vector<room> a_bed;
        priority_queue<room, vector<room>, cmp_room> q_room;
        vector<patient> a_patient; a_patient.reserve(patient_num), a_bed.reserve(bed_num);
        for(int i = 1; i <= room_num; i++)
        {
            room temp;
            temp.id = i, temp.begin_time = begin_time, temp.use_t = 0;
            q_room.push(temp);
        }
        for(int i = 1; i <= bed_num; i++)
        {
            room temp;
            temp.id = i, temp.begin_time = begin_time, temp.use_t = 0;
            a_bed.push_back(temp);
        }
        for(int i = 1; i <= patient_num; i++)
        {
            patient temp;
            temp.id = i;
            cin >> temp.name >> temp.need_oper >> temp.need_reco;
            a_patient.push_back(temp);
        }
        vector<patient>::iterator p = a_patient.begin(), p_end = a_patient.begin();
        for(; p != a_patient.end(); p++)
        {
            room temp = q_room.top(); q_room.pop();
            p->oper_b = temp.begin_time;
            p->oper_e = p->oper_b;
            p->oper_e.minute += p->need_oper;
            p->oper_e.hour += p->oper_e.minute / 60;
            p->oper_e.minute %= 60;
            p->room = temp.id;
            p->reco_b = p->oper_e;
            p->reco_b.minute += otr_time;
            p->reco_b.hour += p->reco_b.minute / 60;
            p->reco_b.minute %= 60;
            temp.begin_time = p->oper_e;
            temp.begin_time.minute += oper_pretime;
            temp.begin_time.hour += temp.begin_time.minute / 60;
            temp.begin_time.minute %= 60;
            temp.use_t += p->need_oper;
            q_room.push(temp);
        }
        sort(a_patient.begin(), a_patient.end(), cmp_patient1);
        p = a_patient.begin();
        for(; p != a_patient.end(); p++)
        {
            bool flag = true;
            vector<room>::iterator pp = a_bed.begin(), temp = a_bed.begin();
            for(; pp != a_bed.end(); pp++)
                if(pp->begin_time.hour < p->oper_e.hour || (pp->begin_time.hour == p->oper_e.hour && pp->begin_time.minute <= p->oper_e.minute))
                {
                    p->reco_e = p->reco_b;
                    p->reco_e.minute += p->need_reco;
                    p->reco_e.hour += p->reco_e.minute / 60;
                    p->reco_e.minute %= 60;
                    pp->begin_time = p->reco_e;
                    pp->begin_time.minute += reco_pretime;
                    pp->begin_time.hour += pp->begin_time.minute / 60;
                    pp->begin_time.minute %= 60;
                    pp->use_t += p->need_reco;
                    p->bed = pp->id;
                    flag = false;
                    break;
                }
                else if(pp->begin_time.hour < temp->begin_time.hour || (pp->begin_time.hour == temp->begin_time.hour && pp->begin_time.minute < temp->begin_time.minute))
                    temp = pp;
            if(flag)
            {
                if(temp->begin_time.hour > p->reco_b.hour || (temp->begin_time.hour == p->reco_b.hour && temp->begin_time.minute > p->reco_b.minute))
                    p->reco_b = temp->begin_time;
                p->reco_e = p->reco_b;
                p->reco_e.minute += p->need_reco;
                p->reco_e.hour += p->reco_e.minute / 60;
                p->reco_e.minute %= 60;
                p->bed = temp->id;
                temp->begin_time = p->reco_e;
                temp->begin_time.minute += reco_pretime;
                temp->begin_time.hour += pp->begin_time.minute / 60;
                temp->begin_time.minute %= 60;
                temp->use_t += p->need_reco;
            }
            if(p->reco_e.hour > p_end->reco_e.hour || (p->reco_e.hour == p_end->reco_e.hour && p->reco_e.minute > p_end->reco_e.minute))
                p_end = p;
        }
        all_time = 1;
        if(patient_num) all_time = (p_end->reco_e.hour - begin_time.hour) * 60 + p_end->reco_e.minute;
        sort(a_patient.begin(), a_patient.end(), cmp_patient);
        cout << " Patient          Operating Room          Recovery Room\n #  Name     Room#  Begin   End      Bed#  Begin    End\n ------------------------------------------------------\n";
        string temp_t = "01";
        p = a_patient.begin();
        for(; p != a_patient.end(); p++)
        {
            cout << setw(2) << p->id << "  " << setw(10) << left << p->name << right << setw(2) << p->room << "   " << setw(2) << p->oper_b.hour << ':';
            if(p->oper_b.minute < 10) cout << 0;
            cout << p->oper_b.minute << "   " << setw(2) << p->oper_e.hour << ':';
            if(p->oper_e.minute < 10) cout << 0;
            cout << p->oper_e.minute << "     " << setw(2) << p->bed << "   " << setw(2) << p->reco_b.hour << ':';
            if(p->reco_b.minute < 10) cout << 0;
            cout << p->reco_b.minute << "   " << setw(2) << p->reco_e.hour << ':';
            if(p->reco_e.minute < 10) cout << 0;
            cout << p->reco_e.minute << endl;
        }
        cout << "\nFacility Utilization\nType  # Minutes  % Used\n-------------------------\n";
        vector<room> a_room; a_room.reserve(room_num);
        while(!q_room.empty()) a_room.push_back(q_room.top()), q_room.pop();
        sort(a_room.begin(), a_room.end(), cmp_room1);
        for(int i = 0; i < room_num; i++)
        {
            cout << "Room " << setw(2) << a_room[i].id << setw(8) << a_room[i].use_t << "   ";
            if(a_room[i].use_t * 100 / all_time < 10) cout << ' ';
            cout << fixed << setprecision(2) << (double)a_room[i].use_t / all_time * 100 << endl;
        }
        for(int i = 0; i < bed_num; i++)
        {
            cout << "Bed  " << setw(2) << a_bed[i].id << setw(8) << a_bed[i].use_t << "   ";
            if(a_bed[i].use_t * 100 / all_time < 10) cout << ' ';
            cout << fixed << setprecision(2) << (double)a_bed[i].use_t / all_time * 100 << endl;
        }
        cout << endl;
    }
    return 0;
}
