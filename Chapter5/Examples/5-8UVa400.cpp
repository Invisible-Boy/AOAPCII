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
            unsigned int temp_len = temp.length();//�˴����ֱ��дlenth = max(temp.length(), length),�ڱ�������û���⣬���ǵ�OJ�ϻᱨ��
                                                  //ԭ����.length()���ص���size_type���ͣ���unsigned int���Ͳ�������Ҫǿ��ת��һ��
                                                  //size_type��������������������һ������ĳ߶����ͣ���ƽ̨�йأ��䳤�Ȼᷢ���ı䣬���Ϊ�������Ƚϣ���Ҫǿ��ת��һ�£�������ܻ����
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
    }//����������һ�пո��Ҫ���Ǻ��ϸ񣬿�����Ϊ���һ��������һ��û�����ݶ��������lengthҲ���԰�length+2���
    return 0;
}
