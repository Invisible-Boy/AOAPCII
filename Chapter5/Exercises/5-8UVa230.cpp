#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <cstdio>
using namespace std;
struct book
{
    string name, author;
};
bool cmp(book& A, book& B)
{
    return A.author < B.author || (A.author == B.author && A.name < B.name);
}
int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    vector<book> word; word.reserve(100);
    vector<bool> l; l.reserve(100);
    map<string, int> mymap;
    priority_queue<int, vector<int>, greater<int> > q;
    int id = 0;
    char c;
    book temp; temp.author.reserve(80), temp.name.reserve(80);
    while(c = cin.get())
    {
        if(c == '"')
        {
            temp.name += '"';
            while(cin.get(c) && c != '"') temp.name += c;
            temp.name += '"';
            for(int i = 0; i < 4; i++) cin.get(c);
            while(cin.get(c) && c != '\n') temp.author += c;
            word.push_back(temp);
            l.push_back(true);
            temp.name.clear(); temp.author.clear();
        }
        else
        {
            for(int i = 0; i < 3; i++) cin.get();
            break;
        }
    }
    sort(word.begin(), word.end(), cmp);
    for(vector<book>::iterator p = word.begin(); p != word.end(); p++) mymap[p->name] = id++;
    string s; s.reserve(10);
    while(cin >> s && s != "END")
    {
        string title = "\""; title.reserve(80);
        if(s[0] == 'B' || s[0] == 'R')
        {
            while(cin.get(c) && c != '"');
            while(cin.get(c) && c != '"') title += c;
            title += '"';
        }
        if(s[0] == 'B') l[mymap[title]] = false;
        if(s[0] == 'R') q.push(mymap[title]);
        if(s[0] == 'S')
        {
            while(!q.empty())
            {
                string title = word[q.top()].name;
                int i = mymap[title] - 1;
                for(; i > -1 && !l[i]; i--);
                if(i < 0) cout << "Put " << title << " first\n";
                else cout << "Put " << title << " after " << word[i].name << '\n';
                l[mymap[title]] = true; q.pop();
            }
            cout << "END\n";
        }
    }
    return 0;
}
