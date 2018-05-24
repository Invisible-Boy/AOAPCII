#include <cstdio>
#include <cctype>
#include <set>
#include <vector>
#include <algorithm>
//在本地爆栈，在OJ上莫名AC
using namespace std;
const int Max = 202;
int H, W, w_cnt = 0, b_cnt = 0, result[Max][Max];
char data[Max][Max];
void read(int H, int W)
{
    for(int i = 1; i <= H; i++)
    {
        for(int j = 1; j <= W; j++)
        {
            char temp;
            int sum;
            scanf("%c", &temp);
            if(isdigit(temp)) sum = temp - '0';
            else sum = temp - 'a' + 10;
            for(int k = j * 4; k >= (j - 1) * 4 + 1; k--)
            {
                data[i][k] = (sum % 2) + '0';
                sum /= 2;
                result[i][k] = 0;
            }
        }
        scanf("\n");
    }
    for(int i = 0; i <= H + 1; i++)
    {
        data[i][0] = data[i][W*4+1] = '0';
        result[i][0] = result[i][W*4+1] = 0;
    }
    for(int i = 0; i <= W * 4 + 1; i++)
    {
        data[0][i] = data[H+1][i] = '0';
        result[0][i] = result[H+1][i] = 0;
    }
}
void DFS(int i, int j, int cnt, char target)
{
    for(int i_temp = i-1; i_temp < i+2; i_temp++)
    {
        if(i_temp < 0 || i_temp > H+1) continue;
        for(int j_temp = j-1; j_temp < j+2; j_temp++)
        {
            if(j_temp < 0 || j_temp > W+1) continue;
            if(data[i_temp][j_temp] == target && !result[i_temp][j_temp])
            {
                result[i_temp][j_temp] = cnt;
                DFS(i_temp, j_temp, cnt, target);
            }
        }
    }
}
int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int n = 1;
    while(scanf("%d%d\n", &H, &W) == 2 && H)
    {
        b_cnt = w_cnt = 0;
        read(H, W);
        W = W * 4;
        for(int i = 0; i < H+2; i++)
        {
            for(int j = 0; j < W+2; j++)
            {
                //printf("%c", data[i][j]);
                if(!result[i][j])
                {
                    int cnt;
                    if(data[i][j] == '1') cnt = ++b_cnt;
                    else cnt = --w_cnt;
                    DFS(i, j, cnt, data[i][j]);
                }
            }
            //printf("\n");
        }
        set<int> myset[b_cnt+1], whole;
        whole.insert(result[0][0]);
        for(int i = 1; i < H+1; i++)
            for(int j = 1; j < W+1; j++)
                if(result[i][j] < 0 && !whole.count(result[i][j]))
                {
                    bool flag = true;
                    for(int i_t = i+1; i_t < H+1 && flag; i_t++)
                        for(int j_t = j+1; j_t < W+1 && flag; j_t++)
                            if(result[i_t][j_t] > 0)
                            {
                                myset[result[i_t][j_t]].insert(result[i][j]);
                                whole.insert(result[i][j]);
                                flag = false;
                            }
                }
        vector<char> r;
        r.reserve(b_cnt);
        for(int i = 1; i <= b_cnt; i++)
        {
            if((int)myset[i].size() == 1) r.push_back('A');
            else if((int)myset[i].size() == 3) r.push_back('J');
            else if((int)myset[i].size() == 5) r.push_back('D');
            else if((int)myset[i].size() == 4) r.push_back('S');
            else if((int)myset[i].size() == 0) r.push_back('W');
            else if((int)myset[i].size() == 2) r.push_back('K');
        }
        sort(r.begin(), r.end());
        vector<char>::iterator p = r.begin();
        printf("Case %d: ", n++);
        while(p != r.end()) printf("%c", *p), p++;
        printf("\n");
    }
    return 0;
}
