/**
 * Title:   7-12UVa1343
 * Author:  InvisibleMan
 * Data:    2016-12-30
 * Time:    600ms
 */

#include <cstdio>

using namespace std;

const int Nmax = 7, Amax = 3000;
const char ANS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
bool data[3][Nmax][Nmax], flag, flag2;
char ans[3][Amax];
int ansIndex;

void changeRow(int index, int rNum, bool f) {
    bool temp;
    if(f) {
        temp = data[index][rNum][6];
        for(int i = 6; i > 0; i--)
            data[index][rNum][i] = data[index][rNum][i - 1];
        data[index][rNum][0] = temp;
    }
    else {
        temp = data[index][rNum][0];
        for(int i = 0; i < 6; i++)
            data[index][rNum][i] = data[index][rNum][i + 1];
        data[index][rNum][6] = temp;
    }
}

void changeCol(int index, int cNum, bool f) {
    bool temp;
    if(f) {
        temp = data[index][6][cNum];
        for(int i = 6; i > 0; i--)
            data[index][i][cNum] = data[index][i - 1][cNum];
        data[index][0][cNum] = temp;
    }
    else {
        temp = data[index][0][cNum];
        for(int i = 0; i < 6; i++)
            data[index][i][cNum] = data[index][i + 1][cNum];
        data[index][6][cNum] = temp;
    }
}

void dfs(int index, int deep, int Dmax) {
    int cnt = 0;
    for(int i = 2; i < 5; i++)
        for(int j = 2; j < 5; j++)
            if((i != 3 || j != 3) && !data[index][i][j])
                cnt++;
    if(cnt > Dmax - deep) return;
    if(cnt == 0) {
        flag = true;
        return;
    }
    bool oldData[Nmax][Nmax];
    for(int i = 0; i < Nmax; i++)
        for(int j = 0; j < Nmax; j++)
            oldData[i][j] = data[index][i][j];
    for(int i = 0; i < 8 && !flag; i++) {
        if(i == 0) changeCol(index, 2, false);
        else if(i == 1) changeCol(index, 4, false);
        else if(i == 2) changeRow(index, 2, true);
        else if(i == 3) changeRow(index, 4, true);
        else if(i == 4) changeCol(index, 4, true);
        else if(i == 5) changeCol(index, 2, true);
        else if(i == 6) changeRow(index, 4, false);
        else if(i == 7) changeRow(index, 2, false);
        ans[index][deep] = ANS[i];
        dfs(index, deep + 1, Dmax);
        for(int ii = 0; ii < Nmax; ii++)
            for(int jj = 0; jj < Nmax; jj++)
                data[index][ii][jj] = oldData[ii][jj];
    }
}

int main() {
    int tempData[24];
    while(scanf("%d", &tempData[0]) == 1 && tempData[0]) {
        for(int i = 1; i < 24; i++) scanf("%d", &tempData[i]);
        for(int j = 0; j < 3; j++) {
            for(int i = 0; i < 4; i++) {
                data[j][i / 2][(1 + (i % 2)) << 1] = (tempData[i] == j + 1);
                data[j][5 + i / 2][(1 + (i % 2)) << 1] = (tempData[i + 20] == j + 1);
            }
            data[j][3][2] = (tempData[11] == j + 1);
            data[j][3][4] = (tempData[12] == j + 1);
            for(int i = 4; i < 11; i++) {
                data[j][2][i - 4] = (tempData[i] == j + 1);
                data[j][4][i - 4] = (tempData[i + 9] == j + 1);
            }
        }
        flag2 = false;
        int i, j;
        for(i = 0; !flag2; i++)
            for(j = 0; j < 3; j++) {
                flag = false;
                dfs(j, 0, i);
                if(flag) {
                    if(!flag2) ansIndex = j, flag2 = true;
                    else 
                        for(int k = 0; k < i; k++)
                            if(ans[j][k] != ans[ansIndex][k]) {
                                if(ans[j][k] < ans[ansIndex][k])
                                    ansIndex = j;
                                break;
                            }
                }
            }
        if(--i == 0) printf("No moves needed");
        else
            for(int k = 0; k < i; k++)
                printf("%c", ans[ansIndex][k]);
        printf("\n%d\n", ++ansIndex);
    }
    return 0;
}
