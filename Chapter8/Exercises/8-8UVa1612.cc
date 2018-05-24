/**
 * Title:   8-8UVa1612
 * Author:  InvisibleMan
 * Date:    2017-4-9
 * Time:    40ms
 */

#include <cstdio>

using namespace std;

const int Nmax = 16384;

int main() {
     int n, link[Nmax], d[Nmax][3], cnt = 1;
     double t1, t2, t3;
     while(scanf("%d", &n) == 1 && n) {
        printf("Case %d: ", cnt++);
        for(int i = 0; i < n; i++) {
            scanf("%lf%lf%lf", &t1, &t2, &t3);
            // 转化为整数，控制精度
            d[i][0] = (int)(t1 * 100 + 0.005); // 强制转换是舍位转换
            d[i][1] = (int)(t2 * 100 + 0.005);
            d[i][2] = (int)(t3 * 100 + 0.005);
        }
        for(int i = 0; i < n; i++)
            scanf("%d", &link[i]);
        int pre = -1, score = 400000;
        for(int i = 0; i < n; i++) {
            int now = link[i] - 1;
            int t[7] = {d[now][0], d[now][1], d[now][2], d[now][0] + d[now][1], d[now][0] + d[now][2], d[now][1] + d[now][2], d[now][0] + d[now][1] + d[now][2]};
            int nowScore = -100;
            for(int i = 0; i < 7; i++)
                if((t[i] < score || (t[i] == score && now > pre)) && t[i] > nowScore)
                    nowScore = t[i];
            score = nowScore;
            if(score < 0) break;
            pre = now;
        }
        if(score < 0) printf("No solution\n");
        else printf("%d.%d%d\n", score / 100, (score % 100) / 10, score % 10);
    }
    return 0;
}
