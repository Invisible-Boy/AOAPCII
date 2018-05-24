/**
 * Title:   9-10UVa1626
 * Author:  InvisibleMan
 * Date:    2017-6-30
 * Time:    ms
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int Nmax = 105;
int n, ans[Nmax][Nmax];
char d[Nmax];

void print(int p, int q) {
    if(p >= q) return;
    else if(p == q - 1) {
        if(d[p] == '(' || d[p] == ')') printf("()");
        else printf("[]");
    }
    else {
        if(d[q - 1] - d[p] > 0 && d[q - 1] - d[p] < 3 && ans[p][q] == ans[p + 1][q - 1]) {
            printf("%c", d[p]);
            print(p + 1, q - 1);
            printf("%c", d[q - 1]);
        }
        else {
            for(int i = p + 1; i < q; i++) {
                if(ans[p][q] == ans[p][i] + ans[i][q]) {
                    print(p, i);
                    print(i, q);
                    return;
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n); getchar();
    for(int k = 0; k < n; k++) {
        getchar();
        if(k) printf("\n");
        int len = 0;
        char t;
        while((t = getchar()) != '\n')
            d[len++] = t;
        for(int i = 0; i < len; i++) {
            ans[i][i + 1] = 1;
            ans[i][i] = 0;
        }
        for(int l = 2; l <= len; l++) {
            for(int i = 0; i <= len - l; i++) {
                ans[i][i + l] = ans[i][i + 1] + ans[i + 1][i + l];
                // 重要的一点，这是此题与其他题目的区别点，不是单纯的分为左右两个部分
                if(d[i + l - 1] - d[i] > 0 && d[i + l - 1] - d[i] < 3) ans[i][i + l] = min(ans[i][i + l], ans[i + 1][i + l - 1]);
                for(int j = i + 2; j <= i + l; j++)
                    ans[i][i + l] = min(ans[i][i + l], ans[i][j] + ans[j][i + l]);
            }
        }
        print(0, len);
        printf("\n");
    }
}
