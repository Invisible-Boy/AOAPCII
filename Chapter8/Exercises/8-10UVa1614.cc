/**
 * Title:   8-10UVa1614
 * Author:  InvisibleMan
 * Date:    2017-4-13
 * Time:    830ms
 */

#include <cstdio>

typedef long long LL;
int d[100000];
bool ans[100000];

bool dfs(LL aim, int index) {
    if(aim == 0) return true;
    if(aim < 1 || aim > ((LL)index * (index + 1)) >> 1)
        return false;
    int i = index - 1;
    while(i > 0) {
        if(dfs(aim - d[i], i)) {
            ans[i] = true;
            return true;
        }
        ans[i] = false;
        while(i > 0 && d[i - 1] == d[i]) --i;
        --i;
    }
    return false;
}

int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        LL sum = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &d[i]);
            sum += d[i];
            ans[i] = false;
        }
        if((sum & 1) == 0) {
            if(dfs(sum >> 1, n)) {
                printf("Yes\n%d", ans[0] ? 1 : -1);
                for(int i = 1; i < n; i++)
                    printf(" %d", ans[i] ? 1 : -1);
                printf("\n");
            }
        }
        else
            printf("No\n");
    }
    return 0;
}
