#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int T; cin >> T;
    while(T--)
    {
        int num, temp;
        cin >> num;
        int data[num];
        for(int i = 0; i < num; i++)
            cin >> data[i];
        bool flag = false;
        for(int j = 0; j < 1000 && !flag; j++)
        {
            flag = true;
            temp = data[0];
            for(int i = 0; i < num - 1; i++)
            {
                data[i] = abs(data[i] - data[i + 1]);
                if(data[i]) flag = false;
            }
            data[num - 1] = abs(data[num - 1] - temp);
            if(data[num - 1]) flag = false;
            if(flag) cout << "ZERO\n";
        }
        if(!flag) cout << "LOOP\n";
    }
    return 0;
}
