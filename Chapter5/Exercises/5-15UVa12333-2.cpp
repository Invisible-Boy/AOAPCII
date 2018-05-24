#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cmath>
#include <cstdio>
//第一个版本被误删了，采用的方法是产生斐波那契数列，之后直接搜索，使用string.substr，直接TLE
//先产生斐波那契数列，之后生成一个字典树，进行查找
using namespace std;
struct node
{
    node *next[10];
    int id;
    node()
    {
        for(int i = 0; i < 10; i++) this->next[i] = NULL;
        this->id = -1;
    };
};
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    vector<int> f0, f1, f2, *p0, *p1, *p2; f0.reserve(100000); f1.reserve(100000); f2.reserve(100000);
    f0.push_back(1), f1.push_back(1);
    node root;
    root.next[1] = new node;
    root.next[1]->id = 0;
    p0 = &f0; p1 = &f1; p2 = &f2;
    for(int i = 2; i < 100000; i++)  //注意读题，T恤要求index smaller than 100000,即这里最大是99999，不能用超过的数据
    {
        stack<int> result;
        int d = 0;
        vector<int>::reverse_iterator pp0 = p0->rbegin(), pp1 = p1->rbegin();
        while(pp0 != p0->rend() && pp1 != p1->rend())
        {
            d = *pp0 + *pp1 + d;
            result.push(d % 10);
            d /= 10;
            pp0++, pp1++;
        }
        while(pp0 != p0->rend())
        {
            d = *pp0 + d;
            result.push(d % 10);
            d /= 10;
            pp0++;
        }
        while(pp1 != p1->rend())
        {
            d = *pp1 + d;
            result.push(d % 10);
            d /= 10;
            pp1++;
        }
        p2->clear();
        if(d != 0) p2->push_back(d);
        while(!result.empty()) p2->push_back(result.top()), result.pop();
        int num = min(40, (int)p2->size());
        node *p = &root;
        vector<int>::iterator pp = p2->begin();
        for(int j = 0; j < num; j++, pp++)
        {
            if(p->next[*pp] == NULL) p->next[*pp] = new node, p->next[*pp]->id = i;
            p = p->next[*pp];
        }
        vector<int> *temp = p0;
        p0 = p1; p1 = p2; p2 = temp;
    }
    int n; cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cout << "Case #" << i << ": ";
        string s; cin >> s;
        string::iterator pp = s.begin();
        node *p = &root;
        bool flag = true;
        for(; pp != s.end(); pp++)
        {
            int id = *pp - '0';
            if(p->next[id] != NULL) p = p->next[id];
            else
            {
                flag = false;
                break;
            }
        }
        if(flag) cout << p->id << endl;
        else cout << "-1\n";
    }
    return 0;
}
