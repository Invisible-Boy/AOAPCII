#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <string.h>
#include <queue>
#define msc(X) memset(X,-1,sizeof(X))
#define ms(X) memset(X,0,sizeof(X))
typedef long long LL;
using namespace std;
const int INF=0x7fffffff;
int gcd(int a,int b)
{return b?gcd(b,a%b):a;}
int arr[8],k,res[19000],tmp[19000];
bool IDDFS(int cur,int mcr,int a,int b,int lt)
{
    if(cur>=mcr-1){
        if(a!=1||b<lt) return false;
        for(int j=0;j<k;j++) if(arr[j]==b) return false;
        tmp[cur]=b;
        bool flg=false;
        if(res[0]){
            for(int i=cur;i>-1;i--)
                if(res[i]!=tmp[i]){flg=(res[i]>tmp[i]);break;}
        }
        if(res[0]==0||flg)
        memcpy(res,tmp,sizeof(tmp));
        return true;
    }
    if(!a) return false;
    lt=max(lt,(a+b-1)/a);
    bool flg=false;
    for(int i=lt;i<=INF/b&&i<=(mcr-cur)*b/a;i++)//i<=INF/b关键的一步，否则wa
    {
        bool Is_s=true;
        for(int j=0;j<k;j++) if(i==arr[j]) {
            Is_s=false;
            break;
        }
        if(!Is_s) continue;
        int na=a*i-b,nb=b*i;
        if(na<0) continue;
        tmp[cur]=i;
        int g=gcd(na,nb);
        na/=g,nb/=g;
        flg=IDDFS(cur+1,mcr,na,nb,i+1)||flg;
    }
    return flg;
}
int main(int argc, char const *argv[])
{
    int t,ti=0;
    scanf("%d",&t);
    while(++ti<=t){
        int a,b;
        scanf("%d %d %d",&a,&b,&k);
        for(int i=0;i<k;i++) scanf("%d",arr+i);
        int mcr=1;
        ms(res);
        while(1)
            if(IDDFS(0,mcr,a,b,2))  break;
            else mcr++;
        printf("Case %d: %d/%d=1/%d",ti,a,b,res[0] );
        for(int i=1;i<mcr;i++)
            printf("+1/%d", res[i]);
        putchar('\n');
    }
    return 0;
}
