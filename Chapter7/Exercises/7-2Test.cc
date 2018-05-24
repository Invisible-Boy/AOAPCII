#include <cstdio>
#include <cstdlib>

using namespace std;

int main() {
    freopen("input", "w", stdout);
    int caseNum;
    scanf("%d", &caseNum);
    printf("%d\n", caseNum);
    for(int i= 0; i < caseNum; i++) {
        int n = rand() % 20 + 1;
        int m= rand() % 50 + 1;
        printf("%d\n%d\n", n, m);
        for(int j = 0; j < m; j++) {
            int tx = rand() % 51 - 25;
            int ty = rand() % 51 - 25;
            printf("%d %d\n", tx, ty);
        }
    }
    return 0;
}
