#include <iostream>
#include <queue>
#include <string>
#include <map>
#include <cstdio>
using namespace std;
struct cmd
{
    int c, t2;
    char t1;
};
struct program
{
    int id;
    queue<cmd> q_cmd;
};
int main()
{
    freopen("input.txt", "r", stdin);
    int n; cin >> n;
    for(int i = 0; i < n; i++)
    {
        if(i) cout << endl;
        int p_num, t[5], t_slice, j = 1;
        cin >> p_num >> t[0] >> t[1] >> t[2] >> t[3] >> t[4] >> t_slice;
        map<char, int> mymap;
        deque<program> q_ready;
        queue<program> q_lock;
        while(p_num--)
        {
            q_ready.push_back(program());
            program &p_temp = q_ready.back();
            p_temp.id = j++;
            string temp; temp.reserve(10);
            while((cin >> temp) && temp != "end")
            {
                p_temp.q_cmd.push(cmd());
                cmd &c_temp = p_temp.q_cmd.back();
                if(temp == "print")
                {
                    c_temp.c = 1;
                    cin >> c_temp.t1;
                }
                else if(temp == "lock") c_temp.c = 2;
                else if(temp == "unlock") c_temp.c = 3;
                else
                {
                    c_temp.c = 0;
                    c_temp.t1 = temp[0];
                    cin >> temp; cin >> c_temp.t2;
                }
            }
        }
        bool flag = false;
        while(!q_ready.empty() || !q_lock.empty())
        {
            bool flag2 = true;
            int time = t_slice;
            program p_temp = q_ready.front(); q_ready.pop_front();
            while(time > 0 && !p_temp.q_cmd.empty())  //没有存入end,反而导致要多一步操作，架构上的问题
            {
                cmd c_temp = p_temp.q_cmd.front();
                if(c_temp.c == 0) mymap[c_temp.t1] = c_temp.t2;
                else if(c_temp.c == 1) cout << p_temp.id << ": " << mymap[c_temp.t1] << endl;
                else if(c_temp.c == 2)
                {
                    if(flag)
                    {
                        q_lock.push(p_temp);
                        flag2 = false;  //没有写成子函数，导致要加一个标志位
                        break;
                    }
                    else flag = true;
                }
                else
                {
                    flag = false;
                    if(!q_lock.empty())
                    {
                        q_ready.push_front(q_lock.front());
                        q_lock.pop();
                    }
                }
                time -= t[c_temp.c];
                p_temp.q_cmd.pop();
            }
            if(!p_temp.q_cmd.empty() && flag2) q_ready.push_back(p_temp);
        }
    }
    return 0;
}
