/**
 * Title:   8-16UVa1608
 * Author:  InvisibleMan
 * Date:    2017-3-29
 * Time:    TLE
 */

#include <cstdio>
#include <map>

using namespace std;

const int Nmax = 2e5 + 1;
int data[Nmax], indx[Nmax][2];
map<int, int> myHash;


bool isBoring(int p, int q) {
    if(p > q - 2) return false;
    if(p == q - 2) return data[p] == data[p + 1];
    int cnt = -1;  // 记录每个元素出现的所有位置，遍历的做法很不好，会超时
                   // 只需要用数组存下每个位置对应元素上一次和下一次出现的位置
    for(int i = p; i < q && cnt < 0; ++i) {
        int count = 0;
        for(int j = myHash[data[i]]; j > -1 && count < 2; j = indx[j][0]) {
            if(indx[j][1] >=p && indx[j][1] < q) count++;
        }
        if(count == 1) cnt = i;
    }
    if(cnt < 0 || isBoring(p, cnt) || isBoring(cnt + 1, q)) return true;
    return false;
}

int main() {
    int T, n;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
            indx[i][0] = -1;
        myHash.clear();
        int cnt = 0;
        for(int i = 0; i < n; ++i) {
            scanf("%d", &data[i]);
            if(myHash.count(data[i]))
                indx[cnt][0] = myHash[data[i]], myHash[data[i]] = cnt;
            else myHash[data[i]] = cnt;
            indx[cnt++][1] = i;
        }
        if(isBoring(0, n)) printf("boring\n");
        else printf("non-boring\n");
    }
    return 0;
}
