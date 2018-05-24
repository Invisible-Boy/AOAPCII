#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
    freopen("input.txt", "w", stdout);
    srand((unsigned)time(NULL));
    int n = 100;
    cout << n << endl;
    while(n--)
    {
        int m = 50;
        cout << m << endl;
        while(m--)
        {
            int b[3], e[3];
            for(int i = 0; i < 3; i++)
            {
                b[i] = rand() % 400 + 1;
                e[i] = rand() % (500 - 400) + 1;
                cout << b[i] << ' ';
            }
            cout << e[0] << ' ' << e[1] << ' ' << e[2] << endl;
        }
    }
    return 0;
}
