/**
 * Title:   7-12UVa1343-2
 * Author:  InvisibleMan
 * Data:    2016-12-30
 * Time:    140ms
 */

// tips: IDA*

#include <cstdio>
#include <algorithm>

using namespace std;

const int Nmax = 7, Amax = 100;
const char ANS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
const int rev[] = {5, 4, 7, 6, 1, 0, 3, 2};
char ans[Amax];
int data[Nmax][Nmax];

void changeRow(int rNum, bool f) {
    int temp;
    if(f) {
        temp = data[rNum][6];
        for(int i = 6; i > 0; i--)
            data[rNum][i] = data[rNum][i - 1];
        data[rNum][0] = temp;
    }
    else {
        temp = data[rNum][0];
        for(int i = 0; i < 6; i++)
            data[rNum][i] = data[rNum][i + 1];
        data[rNum][6] = temp;
    }
}

void changeCol(int cNum, bool f) {
    int temp;
    if(f) {
        temp = data[6][cNum];
        for(int i = 6; i > 0; i--)
            data[i][cNum] = data[i - 1][cNum];
        data[0][cNum] = temp;
    }
    else {
        temp = data[0][cNum];
        for(int i = 0; i < 6; i++)
            data[i][cNum] = data[i + 1][cNum];
        data[6][cNum] = temp;
    }
}

void move(int index) {
    if(index == 0) changeCol(2, false);
    else if(index == 1) changeCol(4, false);
    else if(index == 2) changeRow(2, true);
    else if(index == 3) changeRow(4, true);
    else if(index == 4) changeCol(4, true);
    else if(index == 5) changeCol(2, true);
    else if(index == 6) changeRow(4, false);
    else changeRow(2, false);
}

bool dfs(int deep, int Dmax) {
    int cnt, tCnt[4] = {0};
    for(int i = 2; i < 5; i++)
        for(int j = 2; j < 5; j++)
            if(i != 3 || j != 3)
                tCnt[data[i][j]]++;
    cnt = 8 - max(max(tCnt[1], tCnt[2]), tCnt[3]);
    if(cnt > Dmax - deep) return false;
    if(cnt == 0) return true;
    for(int i = 0; i < 8; i++) {
        move(i);
        ans[deep] = ANS[i];
        if(dfs(deep + 1, Dmax)) return true;
        move(rev[i]);
    }
    return false;
}

int main() {
    int tempData[24];
    while(scanf("%d", &tempData[0]) == 1 && tempData[0]) {
        for(int i = 1; i < 24; i++) scanf("%d", &tempData[i]);
        for(int i = 0; i < 4; i++) {
            data[i / 2][(1 + (i % 2)) << 1] = tempData[i];
            data[5 + i / 2][(1 + (i % 2)) << 1] = tempData[i + 20];
        }
        data[3][2] = tempData[11];
        data[3][4] = tempData[12];
        for(int i = 4; i < 11; i++) {
            data[2][i - 4] = tempData[i];
            data[4][i - 4] = tempData[i + 9];
        }
        int i;
        for(i = 0; ; i++)
            if(dfs(0, i)) break;
        if(i == 0) printf("No moves needed");
        else
            for(int k = 0; k < i; k++)
                printf("%c", ans[k]);
        printf("\n%d\n", data[2][2]);
    }
    return 0;
}
