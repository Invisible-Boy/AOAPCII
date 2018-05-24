/*
 * Ttile:   6-13UVa215-2
 * Author:  Invisible_Man
 * Time:    2016-11-15
 */

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <iomanip>

using namespace std;

const int MAXR = 20, MAXC = 10;
const int INF = 99999;
int m, n, sheet[MAXR][MAXC];
string data[MAXR][MAXC];
int status[MAXR][MAXC];

typedef string::iterator strit;
int find(int i, int j);

int str2int(strit p, strit q) {
    bool flag = false;
    int t = 0;
    if(*p == '+') p++;
    else if(*p == '-') flag = true, p++;
    if(isdigit(*p)) {
        while(p != q) {
            t = t * 10 + *p - '0';
            p++;
        }
    }
    else if(isalpha(*p)) {
        int ii = *p - 'A';
        int jj = *(p + 1) - '0';
        t = sheet[ii][jj] = find(ii, jj);
    }
    if(t >= INF) return INF;
    return flag ? -t : t;
}

int find(int i, int j) {
    if(status[i][j] == -1) return INF;
    if(status[i][j] == 1) return sheet[i][j];
    status[i][j] = -1;
    strit p = data[i][j].begin();
    strit q = data[i][j].end();
    strit pp, qq;
    int t = 0;
    while(p != q) {
        if(*p == '+' || *p == '-') {
            pp = p++;
            while(p != q && *p != '+' && *p != '-')
                 p++;
            qq = p;
            t += str2int(pp, qq);
        }
        else if(isdigit(*p)) {
            pp = p++;
            while(p != q && *p != '+' && *p != '-')
                p++;
            qq = p;
            t += str2int(pp, qq);
        }
        else {
            int ii = *p - 'A';
            int jj = *(++p) - '0';
            sheet[ii][jj] = find(ii, jj);
            t += sheet[ii][jj];
            p++;
        }
    }
    if(t > 10000) return INF; //题目说的是结果的绝对值小于10000，INF选择的是99999，即使之前是负数，此处也成立。
    status[i][j] = 1;
    return t;
}

int main() {
    while((cin >> m >> n) && m && n) {
        cin.get();
        memset(status, 0, sizeof(status));
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                cin >> data[i][j];
        bool flag = true;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++) {
                if(status[i][j] != 0) continue;
                sheet[i][j] = find(i, j);
                if(sheet[i][j] >= INF) flag = false;
            }
        if(flag) {
            cout << ' ';
            for(int i = 0; i < n; i++)
                cout << setw(6) << i;
            cout << endl;
            for(int i = 0; i < m; i++) {
                cout << (char)('A' + i);
                for(int j = 0; j < n; j++)
                    cout << setw(6) << sheet[i][j];
                cout << endl;
            }
            cout << endl;
        }
        else {
            for(int i = 0; i < m; i++)
                for(int j = 0; j < n; j++)
                    if(status[i][j] == -1)
                        cout << (char)('A' + i) << j << ": " << data[i][j] << endl;
            cout << endl;
        }
    }        
}

