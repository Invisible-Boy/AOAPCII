// UVa1354 Mobile Computing
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

struct Tree {
  double L, R; // distance from the root to the leftmost/rightmost point
  Tree():L(0),R(0) {}
};

const int maxn = 6;

int n, vis[1<<maxn];
double r, w[maxn], sum[1<<maxn];
vector<Tree> tree[1<<maxn];

void dfs(int subset) {
  if(vis[subset]) return;
  vis[subset] = true;

  bool have_children = false;
  // 使用按位与操作，可以实现在子集中的选取
  for(int left = (subset-1)&subset; left; left = (left-1)&subset) // 此处-1，表示下一个子集，因为有与操作，因此相当于将一堆10000110001001010变为111111，直接可以忽略中间的0；
  // 在这个做法中，使用一个整数代替一个子集，传入整数相当于传入了子集，在我子集的代码中，需要开辟一个vector存储每个子集，笨拙了很多。
  {
    have_children = true;

    int right = subset^left;
    double d1 = sum[right] / sum[subset];
    double d2 = sum[left] / sum[subset];

    dfs(left); dfs(right);

    for(int i = 0; i < tree[left].size(); i++)
      for(int j = 0; j < tree[right].size(); j++) {
        Tree t;
        t.L = max(tree[left][i].L + d1, tree[right][j].L - d2);  //将左子树与右子树的组合放进root中
        t.R = max(tree[right][j].R + d2, tree[left][i].R - d1);
        if(t.L + t.R < r) tree[subset].push_back(t);  //剪枝
      }
  }

  if(!have_children) tree[subset].push_back(Tree());
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%lf%d", &r, &n);
    for(int i = 0; i < n; i++) scanf("%lf", &w[i]);
    for(int i = 0; i < (1<<n); i++) { //将所有子集的权重都算出来，存储，不用每次调用的时候计算
      sum[i] = 0;
      tree[i].clear();
      for(int j = 0; j < n; j++)
        if(i & (1<<j)) sum[i] += w[j];
    }

    int root = (1<<n)-1;
    memset(vis, 0, sizeof(vis));
    dfs(root);

    double ans = -1;
    for(int i = 0; i < tree[root].size(); i++)
      ans = max(ans, tree[root][i].L + tree[root][i].R);
    printf("%.10lf\n", ans);
  }
  return 0;
}
