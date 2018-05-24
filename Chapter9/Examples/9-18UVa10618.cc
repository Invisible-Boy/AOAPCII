/**
 * Title:   9-18UVa10618
 * Author:  InvisibleMan
 * Date:    2017-7-22
 * Time:    280ms
 */

#include <cstdio>
#include <cstring>

using namespace std;

const int Nmax = 75;
const int Smax = 260;
const int INF = 1e6;
const char sta[] = {'U', 'L', 'D', 'R'};
const int cost[] = {1, 3, 5, 7};

char data[Nmax];
int d[Nmax][Smax], next[Nmax][Smax], len;

inline int abs(int a) {
    return (a > 0 ? a : -a) & 1;
}

int dp(int now, int state) {
    int &ans = d[now][state];
    if(now == len) return 0;
    if(ans > -1) return ans;
    ans = INF;
    int nowl = state >> 6, nowr = (state >> 2) & 3, stal = (state >> 4) & 3, star = state & 3;
    if(data[now] == '.') {
        int tans = dp(now + 1, state & 0xCC);
        if(tans < ans) {
            ans = tans;
            next[now][state] = state & 0xCC;
        }
        if(nowl == 3) {
            int newState = state & 12;
            newState |= (7 << 4);
            int newAns = (stal == 0 ? 1 : 7) + dp(now + 1, newState);
            if(newAns < ans) {
                ans = newAns;
                next[now][state] = newState;
            }
            newState &= 12;
            newState |= ((2 - nowr) << 6) | 0x20;
            newAns = (stal == 0 ? 1 : 5) + dp(now + 1, newState);
            if(newAns < ans) {
                ans = newAns;
                next[now][state] = newState;
            }
        }
        else if(nowr == 1) {
            int newState = state & 0xC0;
            newState |= 15;
            int newAns = (star == 0 ? 1 : 7) + dp(now + 1, newState);
            if(newAns < ans) {
                ans = newAns;
                next[now][state] = newState;
            }
            newState &= 0xC0;
            newState |= ((2 - nowl) << 2) | 2;
            newAns = (star == 0 ? 1 : 5) + dp(now + 1, newState);
            if(newAns < ans) {
                ans = newAns;
                next[now][state] = newState;
            }
        }
        else {
            for(int i = 0; i < 4; i++) {
                if(i != nowl && i != nowr) {
                    int newState = state & 12;
                    newState |= (i << 6) | 0x20;
                    newState |= abs(i - nowl) == 1 ? 0 : 0x10;
                    int newAns = (stal == 0 ? 1 : cost[(newState >> 4) & 3]) + dp(now + 1, newState);
                    if(newAns < ans) {
                        ans = newAns;
                        next[now][state] = newState;
                    }
                }
            }
            for(int i = 0; i < 4; i++) {
                if(i != nowl && i != nowr) {
                    int newState = state & 0xC0;
                    newState |= (i << 2) | 2;
                    newState |= abs(i - nowr) == 1 ? 0 : 1;
                    int newAns = (star == 0 ? 1 : cost[newState & 3]) + dp(now + 1, newState);
                    if(newAns < ans) {
                        ans = newAns;
                        next[now][state] = newState;
                    }
                }
            }
        }
    }
    else if(sta[nowl] == data[now]) {
        int newState = (state & 0xCC) | 0x10;
        int newAns = (stal == 0 ? 1 : 3) + dp(now + 1, newState);
        if(newAns < ans) {
            ans = newAns;
            next[now][state] = newState;
        }
    }
    else if(sta[nowr] == data[now]) {
        int newState = (state & 0xCC) | 1;
        int newAns = (star == 0 ? 1 : 3) + dp(now + 1, newState);
        if(newAns < ans) {
            ans = newAns;
            next[now][state] = newState;
        }
    }
    else {
        int idex;
        for(idex = 0; idex < 4 && sta[idex] != data[now]; idex++);
        if(nowr != 1) {
            int newState = (state & 12) | 0x20;
            newState |= (idex << 6) | (abs(idex - nowl) == 1 ? 0 : 0x10); 
            int newAns = (stal == 0 ? 1 : cost[(newState >> 4) & 3]) + dp(now + 1, newState);
            if(newAns < ans) {
                ans = newAns;
                next[now][state] = newState;
            }
        }
        if(nowl != 3) {
            int newState = (state & 0xC0) | 2;
            newState |= (idex << 2) | (abs(idex - nowr) == 1 ? 0 : 1);
            int newAns = (star == 0 ? 1 : cost[newState & 3]) + dp(now + 1, newState);
            if(newAns < ans) {
                ans = newAns;
                next[now][state] = newState;
            }
        }
    }
    return ans;
}

int main() {
    while(scanf("%s", data) == 1 && data[0] != '#') {
        memset(d, -1, sizeof(d));
        len = strlen(data);
        int now = 0x4C;
        dp(0, now);
        for(int i = 0; i < len; i++) {
            now = next[i][now];
            if(now & 3) printf("R");
            else if(now & 0x30) printf("L");
            else printf(".");
        }
        printf("\n");
    }
    return 0;
}
