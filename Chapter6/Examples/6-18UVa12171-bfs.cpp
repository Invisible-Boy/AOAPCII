#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cstdio>
using namespace std;
const int Nmax = 105, Dmax = 1001;
int flag[Nmax][Nmax][Nmax], ndata, nx, ny, nz;
vector<int> X, Y, Z;
struct Scul
{
    int x0, x1, y0, y1, z0, z1;
};
vector<Scul> data;
void Init(vector<int> &A, int &n)
{
    A.push_back(Dmax);
    sort(A.begin(), A.end());
    n = unique(A.begin(), A.end()) - A.begin();
}
bool IsScul(int i, int j, int k)
{
    bool result = false;
    for(int n = 0; n < ndata && !result; n++)
        result = data[n].x0 <= X[i] && data[n].x1 >= X[i + 1] && data[n].y0 <= Y[j] && data[n].y1 >= Y[j + 1] && data[n].z0 <= Z[k] && data[n].z1 >= Z[k + 1];
    return result;
}
struct node
{
    int i, j, k;
    node(int x, int y, int z) : i(x), j(y), k(z) {}
};
void floodfill(int &S, int &V)
{
    queue<node> q;
    flag[0][0][0] = 2;
    node temp(0, 0, 0);
    q.push(temp);
    while(!q.empty())
    {
        temp = q.front(); q.pop();
        int i = temp.i, j = temp.j, k = temp.k;
        V += (X[i + 1] - X[i]) * (Y[j + 1] - Y[j]) * (Z[k + 1] - Z[k]);
        for(int deta = -1; deta < 2; deta++)
        {
            if(deta == 0) continue;
            if(i + deta > 0 && i + deta < nx - 1)
            {
                if(flag[i + deta][j][k] == 1)
                    S += (Y[j + 1] - Y[j]) * (Z[k + 1] - Z[k]);
                else if(!flag[i + deta][j][k])
                    q.push(node(i + deta, j, k)), flag[i + deta][j][k] = 2;;
            }
            if(j + deta > 0 && j + deta < ny - 1)
            {
                if(flag[i][j + deta][k] == 1)
                    S += (X[i + 1] - X[i]) * (Z[k + 1] - Z[k]);
                else if(!flag[i][j + deta][k])
                    q.push(node(i, j + deta, k)), flag[i][j + deta][k] = 2;
            }
            if(k + deta > 0 && k + deta < nz - 1)
            {
                if(flag[i][j][k + deta] == 1)
                    S += (Y[j + 1] - Y[j]) * (X[i + 1] - X[i]);
                else if(!flag[i][j][k + deta])
                    q.push(node(i, j, k + deta)), flag[i][j][k + deta] = 2;
            }
        }
    }
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int T; scanf("%d", &T);
    data.reserve(Nmax >> 1);
    X.reserve(Nmax), Y.reserve(Nmax), Z.reserve(Nmax);
    while(T--)
    {
        X.clear(), Y.clear(), Z.clear(), data.clear();
        X.push_back(0), Y.push_back(0), Z.push_back(0);
        memset(flag, 0, sizeof(flag));
        scanf("%d", &ndata);
        for(int i = 0; i < ndata; i++)
        {
            Scul temp;
            scanf("%d%d%d%d%d%d", &temp.x0, &temp.y0, &temp.z0, &temp.x1, &temp.y1, &temp.z1);
            temp.x1 += temp.x0, temp.y1 += temp.y0, temp.z1 += temp.z0;
            data.push_back(temp);
            X.push_back(temp.x0), X.push_back(temp.x1);
            Y.push_back(temp.y0), Y.push_back(temp.y1);
            Z.push_back(temp.z0), Z.push_back(temp.z1);
        }
        Init(X, nx); Init(Y, ny); Init(Z, nz);
        for(int i = 1; i < nx - 2; i++)
            for(int j = 1; j < ny - 2; j++)
                for(int k = 1; k < nz - 2; k++)
                	//此处直接搜索，查看是否是一个Scul，在LRJ的代码中使用的lower_bound函数，内部采用的是二分查找，执行效率要高很多
                    flag[i][j][k] = IsScul(i, j, k) ? 1 : 0;
        int S = 0, V = 0;
        floodfill(S, V);
        printf("%d %d\n", S, Dmax * Dmax * Dmax - V);
    }
    return 0;
}
