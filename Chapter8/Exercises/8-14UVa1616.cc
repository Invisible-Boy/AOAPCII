/**
 * Title:   8-14UVa1616
 * Author:  InvisibleMan
 * Date:    2017-5-13
 * Time:    70ms
 */

/**
 * 参考了网上的思路，一直思考这个问题，没有想到有效的解决方案
 * 使用二分法，找到合适小数的答案
 * 关键在于如何将小数转化为分数，这个参考了网上的代码
 * 此题控制精度也是一个关键
 */

#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int Nmax = 1e5;
const double eps = 1e-9;

struct Node {
    int l, r;
    bool operator < (const Node &rhs) const {
        return l < rhs.l || (l == rhs.l && r < rhs.r);
    }
};

long long gcd(long long t1, long long t2) {
    if(t1 == 0) return t2;
    return gcd(t2 % t1, t1);
}

Node node[Nmax];

bool slove(double step, int n) {
    double now = 0;
    for(int i = 0; i < n; i++) {
        if(now < node[i].l - eps)
            now = node[i].l;
        now += step;
        if(now > node[i].r + eps)
            return false;
    }
    return true;
}

int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; i++)
            scanf("%d%d", &node[i].l, &node[i].r);
        sort(node, node + n);
        double l = 0, r = (double)node[0].r + eps;
        while(r > l + eps) {
            double mid = (l + r) / 2.0;
            if(slove(mid, n)) l = mid;
            else r = mid;
        }
        int rp = 0, rq = 1;
        for(int p, q = 1; q <= n; q++) {
            p = (int)(l * q + 0.5);
            if(fabs(double(p) / q - l) < fabs(double(rp) / rq - l))
                rp = p, rq = q;
        }
        printf("%d/%d\n", rp, rq);
    }
    return 0;
}
