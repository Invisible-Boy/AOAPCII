/**
 * Title:   7-14UVa307
 * Author:  InvisibleMan
 * Date:    2017-4-6
 * Time:    90ms
 */

#include <cstdio>
#include <cstring>

using namespace std;

int n, exist[51], max, min, sum;

bool init() {
    scanf("%d", &n);
    if(!n) return false;
    max = 0;
    min = 51;
    sum = 0;
    int t;
    memset(exist, 0, sizeof(exist));
    for(int i = 0; i < n; i++) {
        scanf("%d", &t);
        exist[t]++;
        max = t > max ? t : max;
        min = t < min ? t : min;
        sum += t;
    }
    return true;
}

int target, deep;

bool dfs(int now, int nn, int start) {
    for(int i = start; i >= min; i--) {
        if(exist[i]) {
            exist[i]--;
            int next = now + i;
            if(next < target) {
                if(dfs(next, nn, i)) return true;
            }
            else if(next == target) {
                if(nn + 1 == deep - 1) return true;
                if(dfs(0, nn + 1, max)) return true;
                exist[i]++;
                return false;
            }
            exist[i]++;
            // 如果当前的总和为0，且选取当前值后无法找到合适的组合，则永远找不到合适的组合
            if(now == 0) return false;
        }
    }
    return false;
}

int main() {
    while(init()) {
        deep = sum / max;
        // IDA*
        while(deep > 1) {
            if(sum % deep == 0) {
                target = sum / deep;
                // 从大的开始搜索比较容易跳出
                if(dfs(0, 0, max)) break;
            }
            deep--;
        }
        printf("%d\n", sum / deep);
    }
}
