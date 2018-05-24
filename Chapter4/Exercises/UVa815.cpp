#include <iostream>
#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <cstdlib>
using namespace std;

void test()
{
    for(int i = 0; i < 10000; i++)
    {
        int m, n;
        m = (rand() % 30) + 1;
        n = (rand() % 30) + 1;
        cout << m << ' ' << n << endl;
        for(int j = 0; j < m; j++)
        {
            for(int k = 0; k < n; k++)
            {
                if(k) cout << ' ';
                cout << rand() % 100001 - 50000;
            }
            cout << endl;
        }
        cout << rand() % 5000000 + 1 << endl;
    }
    cout << "0 0" << endl;
}

int main()
{
    //freopen("input.txt", "w", stdout);
    //test();
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int square[901], m, n, case_num = 0;
    while(scanf("%d%d", &m, &n) && m)
    {
        for(int i = 0; i < m * n; i++)
            scanf("%d", &square[i]);
        double V_flood;
        cin >> V_flood;
        V_flood /= 100;
        sort(square, square + m * n);
        int num_flood = V_flood > 0 ? 1 : 0;
        double height_flood = (double)square[0];
        for(int i = 1; i < m * n && V_flood; i++)
        {
            V_flood -= (square[i] - square[i - 1]) * num_flood;
            if(V_flood > 0)
                num_flood++;
            else if(V_flood == 0)
                height_flood = (double)square[i];
            else
            {
                V_flood += (square[i] - square[i - 1]) * num_flood;
                height_flood = square[i - 1] + (double)V_flood / (num_flood);
                V_flood = 0;
            }
        }
        //使用cout和printf输出精度会有些许差别，但是在oj上都AC了
        //注意在最后要多输出一行空格，否则算错WA，WA了20次 - -||
        if(V_flood)
            height_flood = square[n * m - 1] + (double)V_flood / (num_flood);
        cout << "Region " << ++case_num <<endl;
        //printf("Water level is %.2lf meters.\n", height_flood);
        cout << "Water level is " << fixed << setprecision(2) << height_flood << " meters." << endl;
        cout << num_flood * 100.0 / (n * m) << " percent of the region is under water." << endl << endl;
        //printf("%.2lf percent of the region is under water.\n\n", num_flood * 100.0 / (n * m));   //最后要多输出一行空行
    }
    return 0;
}

