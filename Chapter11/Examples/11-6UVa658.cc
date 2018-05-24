/**
 * Title:   11-6UVa658
 * Author:  InvisibleMan
 * Date:    2018/5/16
 * Time:    120ms
 */

#include <cstdio>

const int Nmax = 105;

struct Patch {
    int rmask, amask, bugRemove, bugAdd, cost;
} patch[Nmax];

struct Node {
    int cost, sta;
} heap[1 << 20];

int tot, pos[1 << 20], vis[1 << 20], n, m, kase;

inline void init() {
    tot = 1;
    for(int i = 0; i < m; i++) {
        scanf("%d ", &patch[i].cost);
        int j = 0;
        int rmask = 0, amask = 0;
        char c;
        while((c = getchar()) != ' ') {
            if(c == '-') rmask |= 1 << j;
            else if(c == '+') amask |= 1 << j;
            j++;
        }
        j = 0;
        int bugRemove = 0, bugAdd = 0;
        while((c = getchar()) != '\n') {  
            if(c == '-') bugRemove |= 1 << j;
            else if(c == '+') bugAdd |= 1 << j;
            j++;
        }
        patch[i].rmask = rmask; patch[i].amask = amask;
        patch[i].bugRemove = bugRemove; patch[i].bugAdd = bugAdd;
    }
}

void decrease(int nodeId, int cost) {
    Node tmp = heap[nodeId];
    while(nodeId >> 1) {
        int parent = nodeId >> 1;
        if(cost < heap[parent].cost) {
            heap[nodeId] = heap[parent];
            pos[heap[nodeId].sta] = nodeId;
            nodeId >>= 1;
        }
        else break;
    }
    tmp.cost = cost;
    heap[nodeId] = tmp;
    pos[tmp.sta] = nodeId;
}

inline void insert(int now, int cost) {
    heap[tot].sta = now;
    vis[now] = kase;
    decrease(tot++, cost);
}

inline void heapify() {
    Node tmp = heap[1];
    int now = 1;
    while((now << 1) < tot) {
        int swp = now << 1;
        if(swp + 1 < tot && heap[swp + 1].cost < heap[swp].cost)
            swp++;
        if(heap[swp].cost < tmp.cost) {
            heap[now] = heap[swp];
            pos[heap[now].sta] = now;
            now = swp;
        }
        else break;
    }
    heap[now] = tmp;
    pos[tmp.sta] = now;
}

void dijkstra(int &nowCost) {
    insert((1 << n) - 1, 0);
    while(tot > 1) {
        int nowSta = heap[1].sta;
        nowCost = heap[1].cost;
        if(nowSta == 0) return;
        pos[nowSta] = -1;
        heap[1] = heap[--tot];
        if(tot > 2) heapify();
        for(int i = 0; i < m; i++) {
            if(((nowSta & patch[i].rmask) == 0) && ((nowSta & patch[i].amask) == patch[i].amask)) {
                int newSta = (nowSta | patch[i].bugAdd) & (~patch[i].bugRemove);
                int newCost = nowCost + patch[i].cost;
                if(vis[newSta] != kase) insert(newSta, newCost);
                else if(newCost < heap[pos[newSta]].cost) decrease(pos[newSta], newCost);
            }
        }
    }
    nowCost = -1;
}

int main() {
    kase = 1;
    while((scanf("%d%d", &n, &m) == 2) && n && m) {
        init();
        int ans;
        dijkstra(ans);
        printf("Product %d\n", kase++);
        if(ans == -1)
            printf("Bugs cannot be fixed.\n\n");
        else
            printf("Fastest sequence takes %d seconds.\n\n", ans);
    }
    return 0;
}
