/*
 * Title:   7-7UVa1354.cc
 * Author:  InvisibleMan
 * Time:    2016-12-14
 */

#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>

using namespace std;

struct Node {
    double left, right;
    int weight;
    Node(double l = 0, double r = 0, int w = 0) : left(l), right(r), weight(w) {}
};
double stdWidth, maxWidth;
const double esp = 1e-9;

void dfs(vector<Node> &data) {
    int len = (int)data.size();
    if(len == 1) {
        double newWidth = data[0].right - data[0].left;
        if(newWidth < stdWidth - esp && newWidth > maxWidth)
            maxWidth = newWidth;
        return;
    }
    vector<Node> data2;
    data2.reserve(len - 1);
    for(int l = 0; l < len; l++)
        for(int r = 0; r < len; r++) {
            if(l == r) continue;
            data2.clear();
            for(int i = 0; i < len; i++)
                if(i != l && i != r)
                    data2.push_back(data[i]);
            Node newNode;
            newNode.weight = data[l].weight + data[r].weight;
            newNode.left = min(data[l].left - (double)data[r].weight / (double)newNode.weight, 
                               data[r].left + (double)data[l].weight / (double)newNode.weight);
            newNode.right = max(data[l].right - (double)data[r].weight / (double)newNode.weight,
                                data[r].right + (double)data[l].weight / (double)newNode.weight);
            if(newNode.right - newNode.left >= stdWidth - esp) continue;
            data2.push_back(newNode);
            dfs(data2);
        }
}

int main() {
    int n, num;
    vector<Node> data;
    cin >> n;
    while(n--) {
        cin >> stdWidth >> num;
        data.resize(num);
        maxWidth = -1;
        for(int i= 0; i < num; i++) {
            int t; cin >> t;
            data[i] = Node(0, 0, t);
        }
        if(num == 1) {
            cout << 0 << endl;
            continue;
        }
        if(stdWidth < 1) {
            cout << -1 << endl;
            continue;
        }
        dfs(data);
        cout << setprecision(16) << maxWidth << endl;
    }
    return 0;
}
