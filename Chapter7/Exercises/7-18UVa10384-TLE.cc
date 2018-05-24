/**
 * Title:   7-18UVa10384
 * Author:  InvisibleMan
 * Date:    2017-3-1
 * Time:    tle
 */

// 本来的思路是bfs，但是使用new创建新对象，set、queue等stl创建node对象需要大量的时间，需要改变思路

#include <cstdio>
#include <set>
#include <queue>

using namespace std;

struct Node {
    int sta1, sta2, x, y;
    char dict;
    Node *fa;
    Node(int _sta1, int _sta2, int _x, int _y, char _dict, Node *_fa) 
        : sta1(_sta1), sta2(_sta2), x(_x), y(_y), dict(_dict), fa(_fa) {}
    bool operator < (const Node &rhs) const {
        if(sta1 != rhs.sta1) return sta1 < rhs.sta1;
        if(sta2 != rhs.sta2) return sta2 < rhs.sta2;
        if(x != rhs.x) return x < rhs.x;
        if(y != rhs.y) return y < rhs.y;
        return true;
    }
};

Node* bfs(int x, int y, int sta1, int sta2) {
    queue<Node*> q;
    set<Node> vis;
    Node *now = new Node(sta1, sta2, x, y, 0, NULL);
    q.push(now); vis.insert(*now);
    Node *ans = now, *next;
    while(!q.empty()) {
        now = q.front(); q.pop();
        if(now->x == 0 && !(now->sta1 & (1 << now->y))) {
            ans = new Node(sta1, sta2, x, y, 'N', now);
            break;
        }
        if(now->x == 3 && !(now->sta1 & (1 << (24 + now->y)))) {
            ans = new Node(sta1, sta2, x, y, 'S', now);
            break;
        }
        if(now->y == 0 && !(now->sta2 & (1 << now->x))) {
            ans = new Node(sta1, sta2, x, y, 'W', now);
            break;
        }
        if(now->y == 5 && !(now->sta2 & (1 << (24 + now->x)))) {
            ans = new Node(sta1, sta2, x, y, 'E', now);
            break;
        }
        if(now->x > 0) {
            if(!(now->sta1 & (1 << (now->x * 6 + now->y)))) {
                next = new Node(now->sta1, now->sta2, now->x - 1, now->y, 'N', now);
                if(!vis.count(*next)) {
                    q.push(next);
                    vis.insert(*next);
                }
            }
            else if(!(now->sta1 & (1 << ((now->x - 1) * 6 + now->y)))) {
                int newSta1 = now->sta1 | (1 << ((now->x - 1) * 6 + now->y));
                newSta1 &= ~(1 << (now->x * 6 + now->y));
                next = new Node(newSta1, now->sta2, now->x - 1, now->y, 'N', now);
                if(!vis.count(*next)) {
                    q.push(next);
                    vis.insert(*next);
                }
            }
        }
        if(now->x < 3) {
            if(!(now->sta1 & (1 << ((now->x + 1) * 6 + now->y)))) {
                next = new Node(now->sta1, now->sta2, now->x + 1, now->y, 'S', now);
                if(!vis.count(*next)) {
                    q.push(next);
                    vis.insert(*next);
                }
            }
            else if(!(now->sta1 & (1 << ((now->x + 2) * 6 + now->y)))) {
                int newSta1 = now->sta1 | (1 << ((now->x + 2) * 6 + now->y));
                newSta1 &= ~(1 << ((now->x + 1) * 6 + now->y));
                next = new Node(newSta1, now->sta2, now->x + 1, now->y, 'S', now);
                if(!vis.count(*next)){
                    q.push(next);
                    vis.insert(*next);
                }
            }
        }
        if(now->y > 0) {
            if(!(now->sta2 & (1 << (now->y * 4 + now->x)))) {
                next = new Node(now->sta1, now->sta2, now->x, now->y - 1, 'W', now);
                if(!vis.count(*next)) {
                    q.push(next);
                    vis.insert(*next);
                }
            }
            else if(!(now->sta2 & (1 << ((now->y - 1) * 4 + now->x)))) {
                int newSta2 = now->sta2 | (1 << ((now->y - 1) * 4 + now->x));
                newSta2 &= ~(1 << (now->y * 4 + now->x));
                next = new Node(now->sta1, newSta2, now->x, now->y - 1, 'N', now);
                if(!vis.count(*next)) {
                    q.push(next);
                    vis.insert(*next);
                }
            }
        }
        if(now->y < 5) {
            if(!(now->sta2 & (1 << (((now->y + 1) * 4 + now->x))))) {
                next = new Node(now->sta1, now->sta2, now->x, now->y + 1, 'E', now);
                if(!vis.count(*next)) {
                    q.push(next);
                    vis.insert(*next);
                }
            }
            else if(!(now->sta2 & (1 << (((now->y + 2) * 4 + now->x))))) {
                int newSta2 = now->sta2 | (1 << (((now->y + 2) * 4 + now->x)));
                newSta2 &= ~(1 << (((now->y + 1) * 4 + now->x)));
                next = new Node(now->sta1, newSta2, now->x, now->y + 1, 'E', now);
                if(!vis.count(*next)){
                    q.push(next);
                    vis.insert(*next);
                }
            }
        }
    }
    return ans;
}

void print(Node *now) {
    if(now->fa != NULL) {
        print(now->fa);
        printf("%c", now->dict);
    }
}

int main() {
    int x, y;
    while(scanf("%d%d", &y, &x) == 2 && x && y) {
        int t, sta1 = 0, sta2 = 0;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 6; j++) {
                scanf("%d", &t);
                if(t & 1) sta2 |= 1 << (j * 4 + i);
                if(t & 2) sta1 |= 1 << (i * 6 + j);
                if(t & 4) sta2 |= 1 << ((j + 1) * 4 + i);
                if(t & 8) sta1 |= 1 << ((i + 1) * 6 + j);
            }
        }
        print(bfs(--x, --y, sta1, sta2));
        printf("\n");
    }
    return 0;
}
