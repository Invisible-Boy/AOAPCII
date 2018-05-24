#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdio>
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    vector<string> words[1000];
    vector<int> p;
    char c;
    int i = 0;
    string temp;
    while((c = cin.get()) && c != EOF)
    {
        if(c == ' ' || c == '\n')
        {
            if(!temp.empty())
            {
                words[i].push_back(temp);
                int word_len = (int)words[i].size(), temp_len = (int)temp.length();
                if(word_len > (int)p.size()) p.push_back(temp_len);
                else if(p[word_len - 1] < temp_len) p[word_len - 1] = temp_len;
                temp.clear();
            }
        }
        else temp += c;
        if(c == '\n') i++;
    }
    cout << left;
    for(i = 0; i < 1000; i++)
    {
        if(words[i].empty()) break;
        for(int j = 0; j < (int)words[i].size(); j++)
        {
            if(j) cout << ' ';
            if(j != (int)words[i].size() - 1) cout << setw(p[j]);
            cout << words[i][j];
        }
        cout << '\n';
    }
    return 0;
}
