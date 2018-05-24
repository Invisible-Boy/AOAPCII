#include <iostream>
#include <string>
#include <cstdio>
#include <queue>
#include <sstream>
//此版本使用指针的方式，效率与map似乎没有明显差距
using namespace std;
struct node
{
    node *l, *r;
    int value, flag;
};
node* newnode()
{
    node *p = new(node);
    p->l = NULL; p->r = NULL; p->flag = 0;
    return p;
}
void delnode(node *root)
{
    queue<node*> q;
    q.push(root);
    while(!q.empty())
    {
        node *u = q.front(); q.pop();
        if(u->l != NULL) q.push(u->l);
        if(u->r != NULL) q.push(u->r);
        delete(u);
    }
}
void link(node *root, string &s, bool &flag)
{
    int value;
    istringstream ss(s);
    char temp;
    ss >> temp >> value >> temp >> s;
    string::iterator p = s.begin();
    node *u = root;
    for(; p != s.end(); p++)
    {
        if(*p == 'L')
        {
            if(u->l == NULL) u->l = newnode();
            u = u->l;
        }
        else if(*p == 'R')
        {
            if(u->r == NULL) u->r = newnode();
            u = u->r;
        }
    }
    if(u->flag) flag = false;
    else u->flag++, u->value = value;
}
int main()
{
    string s;
    while((cin >> s) && s != "()")
    {
        bool flag = true;
        node *root = newnode();
        if(flag) link(root, s, flag);
        while((cin >> s) && s != "()") if(flag) link(root, s, flag);
        queue<int> result;
        queue<node*> q;
        q.push(root);
        while(!q.empty())
        {
            node *t = q.front(); q.pop();
            if(!t->flag) flag = false;
            if(t->l != NULL) q.push(t->l);
            if(t->r != NULL) q.push(t->r);
            result.push(t->value);
            delete(t);
        }
        if(!flag) cout << "not complete";
        else
        {
            cout << result.front(); result.pop();
            while(!result.empty()) {cout << ' ' << result.front(); result.pop();}
        }
        cout << endl;
    }
    return 0;
}
