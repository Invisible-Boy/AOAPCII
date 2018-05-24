/**
 * Title:   7-14UVa1602
 * Author:  InvisibleMan
 * Data:    2017-1-4
 * Time:    510ms;
 */

// tips: 单纯的打表可以达到410ms，参见reference中lrj的代码
// 如果把1000个答案打出来，写成一个矩阵，则可以达到0ms

#include <iostream>
#include <set>
#include <vector>
#include <cstring>

using namespace std;

const int Nmax = 10;
const int Nmax2 = Nmax << 1;

int n, w, h, ans;

struct Node {
    bool s[Nmax][Nmax];
    bool operator < (const Node &rth) const {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(s[i][j] != rth.s[i][j])
                    return !s[i][j];
        return false;
    }
    Node() {
        for(int i = 0; i < Nmax; i++)
            for(int j = 0; j < Nmax; j++)
                s[i][j] = false;
    }
};

set<Node> sta;
bool temp[Nmax2][Nmax2];

void T(Node &A, Node &B) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            B.s[i][j] = A.s[j][i];
}

void R(Node &A, Node &B) {
    int cnt = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            B.s[i][j] = false;
    for(int i = n - 1; i > -1; i--) {
        bool flag = false;
        for(int j = 0; j < n; j++) {
            B.s[cnt][j] = A.s[j][i];
            if(A.s[j][i]) flag = true;
        }
        if(flag) cnt++;
    }
}

void print(Node &t);

bool isok() {
    int xMin, yMin, xMax, yMax;
    xMin = yMin = 1000;
    xMax = yMax = -1000;
    for(int i = 0; i < Nmax2; i++)
        for(int j = 0; j < Nmax2; j++)
            if(temp[i][j]) {
                if(i < yMin) yMin = i;
                if(j < xMin) xMin = j;
                if(i > yMax) yMax = i;
                if(j > xMax) xMax = j;
            }
    int ww = yMax - yMin + 1;
    int hh = xMax - xMin + 1;
    if(ww > hh) {
        int tt = ww;
        ww = hh;
        hh = tt;
    }
    Node tNode[2];
    if(ww > w || hh > h) return false;
    for(int i = yMin; i <= yMax; i++)
        for(int j = xMin; j <= xMax; j++)
            tNode[0].s[i - yMin][j - xMin] = temp[i][j];
    if(sta.count(tNode[0])) return false;
    Node tNode1[2];
    T(tNode[0], tNode[1]);
    if(sta.count(tNode[1])) return false;
    for(int ii = 0; ii < 2; ii++) {
        R(tNode[ii], tNode1[0]);
        if(sta.count(tNode1[0])) return false;
        R(tNode1[0], tNode1[1]);
        if(sta.count(tNode1[1])) return false;
        R(tNode1[1], tNode1[0]);
        if(sta.count(tNode1[0])) return false;
    }
    sta.insert(tNode[0]);
    return true;
}

void dfs(int now) {
    if(now == n) {
        ans++;
        return;
    }
    for(int i = 0; i < Nmax2; i++)
        for(int j = 0; j < Nmax2; j++)
            if(temp[i][j]) {
                for(int det = -1; det < 2; det++) {
                    if(det == 0) continue;
                    if(i + det > -1 && i + det < Nmax2 && !temp[i + det][j]) {
                        temp[i + det][j] = true;
                        if(isok())
                            dfs(now + 1);
                        temp[i + det][j] = false;
                    }
                    if(j + det > -1 && j + det < Nmax2 && !temp[i][j + det]) {
                        temp[i][j + det] = true;
                        if(isok())
                            dfs(now + 1);
                        temp[i][j + det] = false;
                    }
                }
            }
}

int main() {
    while(cin >> n >> w >> h) {
        if(w > h) {
            int tt = w;
            w = h;
            h = tt;
        }
        if(n > w * h) {
            cout << 0 << endl;
            continue;
        }
        else if(n < 3 || n == w * h || w == 1) {
            cout << 1 << endl;
            continue;
        }
        sta.clear();
        memset(temp, false, sizeof(temp));
        temp[Nmax][Nmax - 1] = true;
        temp[Nmax][Nmax] = true;
        ans = 0;
        Node tt;
        tt.s[0][0] = tt.s[0][1] = true;
        sta.insert(tt);
        dfs(2);
        cout << ans << endl;
    }
    return 0;
}
