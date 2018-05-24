#include <iostream>
#include <queue>
using namespace std;
int main()
{
    int n;
    while((cin >> n) && n)
    {
        queue<int> q;
        for(int i = 1; i <= n; i++) q.push(i);
        cout << "Discarded cards:";
        for(int i = 2; i < n; i++)
        {
            cout << ' ' << q.front() << ',', q.pop();
            q.push(q.front()), q.pop();
        }
        if(n > 1) cout << ' ' << q.front(), q.pop();
        cout << "\nRemaining card: " << q.front() << endl;
    }
    return 0;
}
