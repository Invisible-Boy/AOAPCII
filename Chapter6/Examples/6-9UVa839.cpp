#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
using namespace std;
stringstream ss;
string s;
bool flag;
int mobile()
{
    getline(cin, s);
    ss.clear(); ss.str(s);
    int Wl, Dl, Wr, Dr;
    ss >> Wl >> Dl >> Wr >> Dr;
    if(!Wl) Wl = mobile();
    if(!Wr) Wr = mobile();
    if(Wl * Dl != Wr * Dr) flag = false;
    return Wl + Wr;
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int n;
    cin >> n; cin.get(); cin.get();
    s.reserve(10);
    while(n--)
    {
        flag = true;
        mobile();
        cout << (flag ? "YES\n" : "NO\n");
        if(n) cout << endl;
        cin.get();
    }
    return 0;
}
