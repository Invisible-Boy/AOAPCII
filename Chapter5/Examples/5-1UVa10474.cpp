/*#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    int N, Q, marble[10000], case_num = 0;
    while((cin >> N >> Q) && N)
    {
        for(int i = 0; i < N; i++)
            cin >> marble[i];
        sort(marble, marble + N);
        cout << "CASE# " << ++case_num << ":" << endl;
        for(int i = 0; i < Q; i++)
        {
            int temp;
            cin >> temp;
            for(int j = 0; j < N; j++)
            {
                if(marble[j] == temp)
                {
                    cout << temp << " found at " << j+1 << endl;
                    break;
                }
                if(marble[j] > temp || j == N - 1)
                {
                    cout << temp << " not found" << endl;
                    break;
                }
            }
        }
    }
    return 0;
}
*/
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

const int maxn = 10000;
//单纯的cin和cout430ms 关掉同步为250ms 单纯的scanf和printf只需50ms
int main()
{
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    int n, q, x, a[maxn], kcase = 0;
    while(cin >> n >> q && n)
    {
        //printf("CASE# %d:\n", ++kcase);
        cout << "CASE# " << ++kcase << ":" << endl;
        for(int i = 0; i < n; i++)
            cin >> a[i];
        sort(a, a + n);
        while(q--)
        {
            //scanf("%d", &x);
            cin >> x;
            int p = lower_bound(a, a+n, x) - a;
            if(a[p] == x) cout << x << " found at " << p+1 << endl;
            else cout << x << " not found" << endl;
        }
    }
    return 0;
}
