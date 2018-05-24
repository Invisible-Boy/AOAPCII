#include <iostream>
#include <vector>
#include <stack>
#include <cstdio>
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
    freopen("input.txt", "w", stdout);
    cout << 10000 << endl;
    vector<int> f0, f1, f2, *p0, *p1, *p2; f0.reserve(100000); f1.reserve(100000); f2.reserve(100000);
    f0.push_back(1), f1.push_back(1);
    node root;
    root.next[1] = new node;
    root.next[1]->id = 0;
    p0 = &f0; p1 = &f1; p2 = &f2;
    cout << 1 << endl << 1 << endl;
    for(int i = 2; i < 100000; i++)
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
        vector<int>::iterator pp = p2->begin();
        if(i > 0 && i <= 10000)
            for(int j = 0; j < num; j++, pp++) cout << *pp;
        cout << endl;
        vector<int> *temp = p0;
        p0 = p1; p1 = p2; p2 = temp;
    }
    return 0;
}
