/**
 * Title:   8-8UVa1471
 * Author:  InvisibleMan
 * Date:    2017-3-18
 * Time:    490ms
 */

/**
 * tips: lower_bound是返回第一个>=输入的元素，upper_bound是返回第一个大于的元素，如果没有则返回.end()
 * 此题要求是严格的上升序列，如果输入 1 1 1，输出应该是1 而不是 3
 */
#include <cstdio>
#include <set>

using namespace std;

#define max(x, y) ((x) > (y) ? (x) : (y))
const int Nmax = 2e5 + 1;
typedef pair<int, int> Pair;

set<Pair> myset;
int l[Nmax], r[Nmax], num[Nmax];

int main() {
    int T, n;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        int *p = num;
        for(int i = 0; i < n; p++, i++)
            scanf("%d", p);
        r[n - 1] = 1, l[0] = 1;
        for(int i = n - 2; i > -1; i--)
            if(num[i] < num[i + 1]) r[i] = r[i + 1] + 1;
            else r[i] = 1;
        for(int i = 1; i < n; i++)
            if(num[i] > num[i - 1]) l[i] = l[i - 1] + 1;
            else l[i] = 1;
        int ans = 1;
        myset.clear();
        myset.insert(Pair(num[0], l[0]));
        for(int i = 1; i < n; i++) {
            Pair now(num[i], l[i]);
            set<Pair>::iterator p = myset.lower_bound(now);
            if(p == myset.begin())
                ans = max(ans, r[i]);
            else {
                --p;
                ans = max(ans, r[i] + p->second);
            }
            if(p->first <= num[i] && p->second >= l[i]) continue;
            while(p != myset.end())
                if(p->first >= num[i]) {
                    if(p->second <= l[i]) p = myset.erase(p);
                    else break;
                }
                else p++;
            myset.insert(now);
        }
        printf("%d\n", ans);
    }
    return 0;
}
