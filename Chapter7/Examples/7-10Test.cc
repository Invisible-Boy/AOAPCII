#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    freopen("test.txt", "w", stdout);
    vector<int> data;
    for(int i = 9; i <= 9; i++) {
        data.resize(i);
        for(int j = 0; j < i; j++)
            data[j] = j + 1;
        do {
            printf("%d\n%d", i, data[0]);
            for(int j = 1; j < i; j++)
                printf(" %d", data[j]);
            printf("\n");
        } while(next_permutation(data.begin(), data.end()));
    }
    printf("0\n");
}
