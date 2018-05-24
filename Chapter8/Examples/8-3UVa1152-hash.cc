/**
 * Title:   8-3UVa1152
 * Authoe:  InvisibleMan
 * Date:    2017-3-13
 * Time:    ms
 */

// tips: 使用stl超时

#include <cstdio>
#include <cstring>

using namespace std;

const int INF = 16000000;

struct Node {
    int val;
    Node *next;
    Node(int _val = 0, Node *_next = NULL) : val(_val), next(_next) {}
};

void hash_insert(int t, Node *hash[]) {
    int index = t >= 0 ? t % INF : -t % INF;
    Node *temp = new Node(t);
    temp->next = hash[index];
    hash[index] = temp;
}

int hash_search(int t, Node *hash[]) {
    int index = t >= 0 ? t % INF : -t % INF;
    Node *p = hash[index];
    int ans = 0;
    while(p != NULL) {
        if(p->val == t) ans++;
        p = p->next;
    }
    return ans;
}

Node *hash[INF];

int main() {
    int T, n, num[4][4000];
    scanf("%d", &T);
    for(int t = 0; t < T; t++) {
        scanf("%d", &n);
        memset(hash, 0, sizeof(hash));
        for(int i = 0; i < n; i++)
            for(int j = 0; j < 4; j++)
                scanf("%d", &num[j][i]);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                hash_insert(num[0][i] + num[1][j], hash);
        int cnt = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                cnt += hash_search(-num[2][i] - num[3][j], hash);
        if(t) printf("\n");
        printf("%d\n", cnt);
    }
    return 0;
}
