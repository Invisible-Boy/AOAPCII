/*
 * Title:   EightHDU1043.cc
 * Author:  InvisibleMan
 * Time:    2016-12-15
 */

// 使用自己写的hash，速度提高到109ms

#include <iostream>
#include <queue>
#include <cctype>
#include <cstring>

using namespace std;

struct Node {
    long w, p;
    char op;
    Node *next;
    Node(long w, long p, char op, Node *n) : w(w), p(p), op(op), next(n) {}
};

const long goal = 123456780;
const char dict[4] = {'d', 'u', 'r', 'l'};
const int detx[4] = {-1, 1, 0, 0};
const int dety[4] = {0, 0, -1, 1};
const int MaxHash = 1000003;
Node *head[MaxHash];

int myhash(long num) {
    return num % MaxHash;
}

bool find(long num) {
    int h = myhash(num);
    Node *p = head[h];
    while(p) {
        if(p->w == num) return true;
        p = p->next;
    }
    return false;
}

Node* getNode(long num) {
    int h = myhash(num);
    Node *p = head[h];
    while(p) {
        if(p->w == num) return p;
        p = p->next;
    }
    return NULL;
}

void bfs(long num) {
    int A[3][3];
    queue<long> q;
    q.push(num);
    int x, y;
    while(!q.empty()) {
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
            if(find(num2)) continue;
            //fa[num2] = pair<long, char>(num, dict[i]);
            Node *pp = new Node(num2, num, dict[i], NULL);
            int h = myhash(num2);
            pp->next = head[h];
            head[h] = pp;
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
    memset(head, NULL, sizeof(head));
    Node *p = new Node(goal, 0, 'x', NULL);
    head[myhash(goal)] = p;
    bfs(goal);
    while(cin >> start) {
        long begin = 0;
        input(begin, start);
        for(int i = 0; i < 8; i++) {
            cin >> start;
            input(begin, start);
        }
        if(begin == goal) {
            cout << endl;
            continue;
        }
        if(getNode(begin)) {
            Node *pp = getNode(begin);
            for(long i = begin; pp->p; i = pp->p) {
                cout << pp->op;
                pp = getNode(pp->p);
            }
            cout << endl;
        }
        else
            cout << "unsolvable\n";
    }
    return 0;
}
