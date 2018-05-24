/*
 * Title:   EightHDU1043.cc
 * Author:  InvisibleMan
 * Time:    2016-12-15
 */

// ������������ʱ

#include <iostream>
#include <map>
#include <queue>
#include <cctype>
#include <stack>

using namespace std;

const long goal = 123456780;
const char dict[4] = {'u', 'd', 'l', 'r'};
const int detx[4] = {-1, 1, 0, 0};
const int dety[4] = {0, 0, -1, 1};
map<long, pair<long, char> > fa;
bool flag;
int A[3][3];

void bfs(long num) {
    queue<long> q;
    q.push(num);
    int x, y;
    while(!q.empty() && !flag) {
        num = q.front(); q.pop();
        long num1 = num;
        for(int i = 2; i > -1; i--)
            for(int j = 2; j > -1; j--) {
                A[i][j] = num1 % 10;
                num1 /= 10;
                if(!A[i][j]) x = i, y = j;
            }
        for(int i = 0; i < 4; i++) {
            int newx = x + detx[i];
            int newy = y + dety[i];
            if(newx < 0 || newx > 2 || newy < 0 || newy > 2) continue;
            A[x][y] = A[newx][newy];
            A[newx][newy] = 0;
            long num2 = 0;
            for(int ii = 0; ii < 3; ii++)
                for(int jj = 0; jj < 3; jj++)
                    num2 = num2 * 10 + A[ii][jj];
            A[newx][newy] = A[x][y];
            A[x][y] = 0;
            if(fa.count(num2)) continue;
            fa[num2] = pair<long, char>(num, dict[i]);
            if(num2 == goal) {
                flag = true;
                break;
            }
            q.push(num2);
        }
    }
}

void input(long &n, char c) {
    if(!isdigit(c)) c = '0';
    n = n * 10 + c - '0';
}

int main() {
    char start;
    stack<char> result;
    while(cin >> start) {
        flag = false;
        fa.clear();
        long begin = 0;
        input(begin, start);
        for(int i = 0; i < 8; i++) {
            cin >> start;
            input(begin, start);
        }
        bfs(begin);
        fa[begin] = pair<long, char>(0, 'x');
        if(begin == goal) {
            cout << endl;
            continue;
        }
        if(flag) {
            for(long i = goal; fa[i].first; i = fa[i].first)
                result.push(fa[i].second);
            while(!result.empty()) {
                cout << result.top();
                result.pop();
            }
            cout << endl;
        }
        else
            cout << "unsolvable\n";
    }
    return 0;
}
