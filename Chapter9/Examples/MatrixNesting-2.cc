/**
 * Title:   MatrixNesting (NYOJ-16)
 * Author:  InvisibleMan
 * Date:    2017-6-8
 * Time:    4ms
 */
#include <cstdio>
#include <algorithm>

using namespace std;

const int Nmax = 1e3;
pair<int, int> d[Nmax];
int l[Nmax];

int dp(int i, int n) {
    int &ans = l[i];
    if(ans > 1) return ans;
    for(int j = 0; j < n; j++)
        if(d[i].first < d[j].first && d[i].second < d[j].second)
            ans = max(ans, dp(j, n) + 1);
    return ans;
}

int main() {
    int N;
    scanf("%d", &N);
    while(N--) {
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            if(a > b) {
                int t = a;
                a = b;
                b = t;
            }
            d[i].first = a, d[i].second = b;
            l[i] = 1;
        }
        int answer = 0;
        for(int i = 0; i < n; i++)
            answer = max(answer, dp(i, n));
        printf("%d\n", answer);
    }
    return 0;
}
