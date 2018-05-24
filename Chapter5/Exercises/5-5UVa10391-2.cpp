#include <iostream>
#include <set>
using namespace std;

int main()
{
    set<string> data;
    string temp;
    while(cin >> temp) data.insert(temp);
    for(set<string>::iterator p = data.begin(); p != data.end(); p++)
    {
        int len = (int)p->length() - 1;
        string str1, str2;
        str1.reserve(100); str2.reserve(100);
        for(int i = 1; i < len; i++)
        {
            str1 = p->substr(0, i), str2 = p->substr(i);
            if(data.count(str1) && data.count(str2))
            {
                cout << *p << endl;
                break;
            }
        }
    }
    return 0;
}
