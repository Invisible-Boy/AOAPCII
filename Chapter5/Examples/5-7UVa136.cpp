#include <iostream>
#include <set>
using namespace std;

int main()
{
    set<long long> Set;
    Set.insert(1);
    set<long long>::iterator j = Set.begin();
    for(int i = 1; ;i++)
    {
        if(i == 1500)
        {
            cout << "The 1500'th ugly number is "<< *j << '.' << endl;
            break;
        }
        Set.insert((*j) * 2);
        Set.insert((*j) * 3);
        Set.insert((*j) * 5);
        j++;
    }
    return 0;
}
