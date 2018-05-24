/*
 * Title:   7-8UVa10603.cc
 * Author:  InvisibleMan
 * Time:    2016-12-16
 */

// 使用STL的第一个版本，优化空间很大。

#include <iostream>
#include <map>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

struct State {
    int nowa, nowb, nowc;
    State(int a = 0, int b = 0, int c = 0) : nowa(a), nowb(b), nowc(c) {}
    bool operator < (const State &other) const {
        if(nowa != other.nowa) return nowa < other.nowa;
        if(nowb != other.nowb) return nowb < other.nowb;
        if(nowc != other.nowc) return nowc < other.nowc;
        return false;
    }
    bool operator == (const State &other) const {
        return nowa == other.nowa && nowb == other.nowb && nowc == other.nowc;
    }
};
const int Nmax = 201;
int d1, d, stda, stdb, stdc, result[Nmax];
map<State, int> mymap;
void changeresult(State &now, int total) {
    if(now.nowa <= d && now.nowa >= d1) {
        result[now.nowa] = min(result[now.nowa], total);
        d1 = now.nowa;
    }
    if(now.nowb <= d && now.nowb >= d1) {
        result[now.nowb] = min(result[now.nowb], total);
        d1 = now.nowb;
    }
    if(now.nowc <= d && now.nowc >=d1) {
        result[now.nowc] = min(result[now.nowc], total);
        d1 = now.nowc;
    }
    mymap[now] = total;
}

void bfs(State &now) {
    queue<State> q;
    q.push(now);
    State next;
    int total, nowtotal;
    while(!q.empty()) {
        now = q.front(); q.pop();
        nowtotal = mymap[now];
        if(now.nowa != stda) {
            if(now.nowb > 0) {
               next.nowc = now.nowc;
               int change = min(stda - now.nowa, now.nowb);
               next.nowa = now.nowa + change;
               next.nowb = now.nowb - change;
               total = nowtotal + change;
               if(!mymap.count(next) || mymap[next] > total) {
                   changeresult(next, total);
                   q.push(next);
               }
            }
            if(now.nowc > 0) {
                next.nowb = now.nowb;
                int change = min(stda - now.nowa, now.nowc);
                next.nowa = now.nowa + change;
                next.nowc = now.nowc - change;
                total = nowtotal + change;
                if(!mymap.count(next) || mymap[next] > total) {
                    changeresult(next, total);
                    q.push(next);
                }
            }
        }
        if(now.nowb != stdb) {
            if(now.nowa > 0) {
                next.nowc = now.nowc;
                int change = min(stdb - now.nowb, now.nowa);
                next.nowb = now.nowb + change;
                next.nowa = now.nowa - change;
                total = nowtotal + change;
                if(!mymap.count(next) || mymap[next] > total) {
                    changeresult(next, total);
                    q.push(next);
                }
            }
            if(now.nowc > 0) {
                next.nowa = now.nowa;
                int change = min(stdb - now.nowb, now.nowc);
                next.nowb = now.nowb + change;
                next.nowc = now.nowc - change;
                total = nowtotal + change;
                if(!mymap.count(next) || mymap[next] > nowtotal) {
                    changeresult(next, total);
                    q.push(next);
                }
            }
        }
        if(now.nowc != stdc) {
            if(now.nowa > 0) {
                next.nowb = now.nowb;
                int change = min(stdc - now.nowc, now.nowa);
                next.nowc = now.nowc + change;
                next.nowa = now.nowa - change;
                total = nowtotal + change;
                if(!mymap.count(next) || mymap[next] > total) {
                    changeresult(next, total);
                    q.push(next);
                }
            }
            if(now.nowb > 0) {
                next.nowa = now.nowa;
                int change = min(stdc - now.nowc, now.nowb);
                next.nowc = now.nowc + change;
                next.nowb = now.nowb - change;
                total = nowtotal + change;
                if(!mymap.count(next) || mymap[next] > total) {
                    changeresult(next, total);
                    q.push(next);
                }
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    while(n--) {
        mymap.clear();
        d1 = 0;
        memset(result, 0x7f, sizeof(result));
        cin >> stda >> stdb >> stdc >> d;
        if(d >= stdc) {
            cout << 0 <<  ' ' << stdc << endl;
            continue;
        }
        result[stdc] = 0;
        result[0] = 0;
        State now = State(0, 0, stdc);
        mymap[now] = 0;
        bfs(now);
        cout << result[d1] <<  ' ' << d1 << endl;
    }
    return 0;
}
