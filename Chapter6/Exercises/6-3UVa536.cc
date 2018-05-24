/*
 * UVa536
 * Author: Invisible_Man
 * Time:  2016.11.4
 */

#include <iostream>
#include <string>

using namespace std;

string firstOder, midOder;

void DFS(int firstP, int firstQ, int midP, int midQ) {
    // for a empty tree
    if(firstP > firstQ) return;
    if(firstP == firstQ) {
        cout << firstOder[firstP];
        return;
    }
    int leftLen = midOder.find(firstOder[firstP]) - midP;
    DFS(firstP + 1, firstP + leftLen, midP, midP + leftLen - 1);
    DFS(firstP + leftLen + 1, firstQ, midP + leftLen + 1, midQ);
    cout << firstOder[firstP];
}

int main() {
    while(cin >> firstOder >> midOder) {
        int len = (int)firstOder.size();
        DFS(0, len - 1, 0, len - 1);
        cout << endl;
    }
}
