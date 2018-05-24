#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int n, m, T = 1;
    while((cin >> n) && n)
    {
        cout << "S-Tree #" << T++ << ":\n";
        vector<int> oder(n);
        string temp, result, X;
        for(int i = 0; i < n; i++)
        {
            cin >> temp;
            oder[i] = temp[1] - '1';
            //cout << oder[i] << "****\n";
        }
        cin >> result;
        // cout << result << endl;
        cin >> m;
        for(int i = 0; i < m; i++)
        {
            cin >> X;
            // cout << "X = " << X << endl;
            int id = 1;
            for(int j = 0; j < n; j++)
                id = (id << 1) + X[oder[j]] - '0';
            id -= 1 << n;
            cout << result[id];
        }
        cout << "\n\n";
    }
}
