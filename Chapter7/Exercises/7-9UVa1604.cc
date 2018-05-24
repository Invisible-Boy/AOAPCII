/**
 * Title:   7-9UVa1604
 * Author:  InvisibleMan
 * Date:    2017-2-15
 * Time:    970ms
 */

/**
 * tips:状态压缩+双向bfs，经过测试，正向搜索19层，反向搜索11层时速度最快，970ms
 * 由于此题的最后结果不是唯一的，侧面和正面有256种情况，
 * 因此在反向bfs之前，需要先将所有的结果都遍历出来
 */


#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int staMax = 1 << 27, stepMax = 19;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
int x, y, aim, aimx, aimy, ans, start[3];
bool vis[staMax], revis[staMax];

struct node {
    int sta[3], x, y, now;
    node(int _sta[3], int _x = 0, int _y = 0, int _now = 0) : x(_x), y(_y), now(_now) {
        sta[0] = _sta[0];
        sta[1] = _sta[1];
        sta[2] = _sta[2];
    }
};

queue<node> requeue;

int code(char temp) {
    switch(temp) {
        case 'E': return 0;
        case 'R': return 1;
        case 'B': return 2;
        default:  return 3;
    }
}

int code1(int s1, int s2) {
    s1 &= 3, s2 &= 3;
    if(s1 == 1 && s2 == 2) return 1;
    if(s1 == 1 && s2 == 3) return 2;
    if(s1 == 2 && s2 == 1) return 3;
    if(s1 == 2 && s2 == 3) return 4;
    if(s1 == 3 && s2 == 1) return 5;
    if(s1 == 3 && s2 == 2) return 6;
    return 7;
}

int move(int x, int y) {
    return (12 - x * 3 - y) << 1;
}

int tran(int s[]) {
    int sta = 0;
    for(int i = 0; i < 9; i++)
        sta = (sta << 3) + code1(s[0] >> (i << 1), s[1] >> (i << 1));
    return sta;
}

void findResult(int now, int s[]) {
    if(now == 9) {
        requeue.push(node(s, aimx, aimy, stepMax));
        revis[tran(s)] = true;
        return;
    }
    int used = (s[0] >> (now << 1)) & 3;
    if(used == 0) {
        s[1] &= ~(3 << (now << 1));
        s[2] &= ~(3 << (now << 1));
        findResult(now + 1, s);
        return;
    }
    for(int i = 1; i < 4; i++) {
        if(i == used) continue;
        s[1] &= ~(3 << (now << 1));
        s[2] &= ~(3 << (now << 1));
        s[1] |= i << (now << 1);
        s[2] |= (6 - used - i) << (now << 1);
        findResult(now + 1, s);
    }
}

bool init() {
    scanf("%d%d\n", &y, &x);
    if(!x || !y) return false;
    memset(vis, false, sizeof(vis));
    memset(revis, false, sizeof(revis));
    requeue = queue<node>();
    aim = 0;
    ans = -1;
    start[0] = 0x0003ffff;
    start[1] = 0x00015555;
    start[2] = 0x0002aaaa;
    int mv = move(x, y);
    start[0] &= ~(3 << mv);
    start[1] &= ~(3 << mv);
    start[2] &= ~(3 << mv);
    vis[tran(start)] = true;
    char t;
    for(int i = 0; i < 9; i++) {
        t = getchar(); getchar();
        aim = (aim << 2) + code(t);
        if(t == 'E') aimx = i / 3 + 1, aimy = i % 3 + 1;
    }
    int r[3] = {aim};
    findResult(0, r);
    return true;
}

bool judge(queue<node> &myqueue, int m, bool v1[], bool v2[]) {
    while(!myqueue.empty()) {
        node now = myqueue.front(); myqueue.pop();
        int newx, newy;
        for(int i = 0; i < 4; i++) {
            newx = now.x + dx[i];
            newy = now.y + dy[i];
            if(newx < 1 || newx > 3 || newy < 1 || newy > 3) continue;
            int index = dx[i] ? 1 : 2;
            int newmv = move(newx, newy);
            int oldmv = move(now.x, now.y);
            int oldSta[3] = {(now.sta[0] >> newmv) & 3,
                             (now.sta[1] >> newmv) & 3,
                             (now.sta[2] >> newmv) & 3};
            int newSta[3];
            newSta[0] = now.sta[0] | (oldSta[index] << oldmv);
            newSta[index] = now.sta[index] | (oldSta[0] << oldmv);
            newSta[3 - index] = now.sta[3 - index] | (oldSta[3 - index] << oldmv);
            newSta[0] &= ~(3 << newmv);
            newSta[1] &= ~(3 << newmv);
            newSta[2] &= ~(3 << newmv);
            int sta = tran(newSta);
            if(v1[sta]) continue;
            v1[sta] = true;
            if(v2[sta]) {
                ans = now.now + 1;
                return true;
            }
            if(now.now < m)
                myqueue.push(node(newSta, newx, newy, now.now + 1));
        }
    }
    return false;
}
 

bool bfs() {
    if(start[0] == aim) {
        ans = 0;
        return true;
    }
    queue<node> myqueue;
    myqueue.push(node(start, x, y, 0));
    return judge(myqueue, stepMax - 1, vis, revis);
}

int main() {
    while(init()) {
        if(!bfs()) judge(requeue, 29, revis, vis);
        printf("%d\n", ans);
    }
    return 0;
}
