#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstdio>
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n;
    while(cin >> n)
    {
        cout << "------------------------------------------------------------" << endl;
        vector<string> s;
        unsigned int length = 0;
        for(int i = 0; i < n; i++)
        {
            string temp;
            cin >> temp;
            s.push_back(temp);
            unsigned int temp_len = temp.length();//此处如果直接写lenth = max(temp.length(), length),在本地运行没问题，但是到OJ上会报错
                                                  //原因是.length()返回的是size_type类型，与unsigned int类型不符，需要强制转换一下
                                                  //size_type本质上是整数，但是是一个抽象的尺度类型，与平台有关，其长度会发生改变，因此为了正常比较，需要强制转换一下，否则可能会出错
            length = max(temp_len, length);
        }
        sort(s.begin(), s.end());
        int C_num = (60 - length) / (length + 2) + 1;
        int R_num = (n - 1) / C_num + 1;
        /*int cnt = 0;
        cout << left;
        for(int i = 0; i < R_num; i++)
        {
            for(int j = 0; j < C_num - 1; j++)
            {
                if(cnt == n - 1)
                    cout << setw(length) << s[j * R_num + i];
                else if(j * R_num + i < n)
                    cout << setw(length + 2) << s[j * R_num + i];
                else break;
                cnt++;
            }
            if((C_num - 1) * R_num + i < n)
            {
                cout << setw(length) <<s[(C_num - 1) * R_num + i];
                cnt++;
            }
            cout << endl;
        }*/
        cout << left;
        for(int i = 0; i < R_num; i++)
        {
            for(int j = 0; j < C_num; j++)
                if(j * R_num + i < n)
                    cout << setw(j == C_num - 1 ? length : length + 2) << s[j * R_num + i];
            cout << endl;
        }
    }//此题对于最后一行空格的要求不是很严格，可以认为最后一行如果最后一列没有数据额，则可以输出length也可以按length+2输出
    return 0;
}
