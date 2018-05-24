#include <vector>
#include <queue>
#include <cstdio>
using namespace std;
typedef pair<int, int> mypair;
const int INF = 1 << 30, Max = 100001;
vector<int> mynext[Max], color[Max], dis;
vector<bool> flag;
void BFS(int i)
{
    int nowdis = 0, id;
    queue<mypair> q;
    q.push(mypair(i, nowdis));
    while(!q.empty())
    {
        id = q.front().first, nowdis = q.front().second; q.pop();
        if(dis[id] >= 0) continue;
        dis[id] = nowdis++;
        vector<int>::iterator p = mynext[id].begin();
        for(; p != mynext[id].end(); p++)
            if(dis[*p] < 0) q.push(mypair(*p, nowdis));
    }
}
void init(int n)
{
    for(int i = 1; i < Max; i++)
    {
        mynext[i].clear();
        color[i].clear();
    }
    dis.clear();
    flag.clear();
    dis.resize(n + 1, -1); flag.resize(n + 1, true);
}
int main()
{
    freopen("input.txt", "r", stdin);
    int n, m, id1, id2, color_id;
    while(scanf("%d%d", &n, &m) == 2)
    {
        init(n);
        while(m--)
        {
            scanf("%d%d%d", &id1, &id2, &color_id);
            mynext[id1].push_back(id2);
            mynext[id2].push_back(id1);
            color[id1].push_back(color_id);
            color[id2].push_back(color_id);
        }
        BFS(n);
        int id = 1, nowdis = dis[1];
        vector<int> path; path.resize(nowdis, INF);
        printf("%d\n", dis[1]);
        queue<int> q; q.push(id);
        flag[id] = false;
        while(!q.empty())
        {
            id = q.front(); nowdis = dis[id] - 1; q.pop();
            if(nowdis == -1) continue;
            int len = (int)mynext[id].size(), t_color = INF, next_id;
            for(int i = 0; i < len; i++)
            {
                int t_id = mynext[id][i];
                if(dis[t_id] == nowdis && color[id][i] < t_color)
                    t_color = color[id][i], next_id = t_id;
            }
            if(t_color > path[dis[1] - 1 - nowdis]) continue;
            path[dis[1] - 1 - nowdis] = t_color;
            for(int i = 0; i < len; i++)
            {
                int t_id = mynext[id][i];
                if(flag[t_id] && dis[t_id] == nowdis && color[id][i] == t_color)
                    q.push(t_id), flag[t_id] = false;
            }
        }
        printf("%d", path[0]);
        for(int i = 1; i < dis[1]; i++)
            printf(" %d", path[i]);
        printf("\n");
    }
    return 0;
}
