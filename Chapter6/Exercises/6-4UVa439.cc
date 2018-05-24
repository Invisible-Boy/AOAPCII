/*
 * 6-4UVa439
 * Author: Invisible_Man
 * Time: 2016-11-4
 */

#include <iostream>
#include <queue>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

const int MAXN = 8;
bool data[MAXN][MAXN];

void print(string &src, string &dst, int result) {
    cout << "To get from " << src << " to " << dst << " takes " << result << " knight moves.\n";
}

struct Node {
    int src0, src1, result;
    Node(int src0, int src1, int result) : src0(src0), src1(src1), result(result) {}
};

bool ok(int src, int dst) {
    return src > -1 && src < MAXN && dst > -1 && dst < MAXN && !data[src][dst];
}

int BFS(int src[2], int dst[2]) {
    int result = 0;
    queue<Node> q;
    q.push(Node(src[0], src[1], result));
    while(!q.empty()) {
        Node temp = q.front(); q.pop();
        //cout << "temp = " << temp.src0 << '-' << temp.src1 << '-' << temp.result << endl;
        data[temp.src0][temp.src1] = true;
        for(int i = -2; i < 3; i++)
            for(int j = -2; j < 3; j++)
                if(abs(i) + abs(j) == 3) 
                    if(temp.src0 + i == dst[0] &&
                       temp.src1 + j == dst[1]) 
                        return temp.result + 1;
                    else if(ok(temp.src0 + i, temp.src1 + j))
                        q.push(Node(temp.src0 + i, temp.src1 + j, temp.result + 1));
    }
}

int main() {
    string src, dst;
    while(cin >> src >> dst) {
        int result = 0;
        if(src == dst) {
            print(src, dst, result);
            continue;
        }
        memset(data, 0, sizeof(data));
        int srcId[2] = {src[0] - 'a', src[1] - '1'};
        int dstId[2] = {dst[0] - 'a', dst[1] - '1'};
        data[srcId[0]][srcId[1]] = true;
        result = BFS(srcId, dstId);
        print(src, dst, result);
    }
}
