#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cctype>

using namespace std;

string stand(string s)
{
    string ans = s;
    for(int i = 0; i < (int)s.length(); i++)
        //ans.push_back(tolower(s[i]));
        ans[i] = tolower(s[i]);
    sort(ans.begin(), ans.end());
    return ans;
}

int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    string s;
    map<string, int> cnt;
    vector<string> word;
    while(cin >> s && s[0] != '#')
    {
        string s_std = stand(s);
        word.push_back(s);
        //if(cnt.find(s_std) == cnt.end()) //可以使用cnt.find(key)或者cnt.count(key)进行判断
        //    cnt[s_std] = 0;
        //cnt[s_std] += cnt.count(s_std); //先判断，再使用，否则产生的结果将与编译器有关
                                          //此时先进行后面的检查再加,即第一次出现s_std，会给cnt[s_std]赋值为0并且加上count()的返回值，此后+1,不推荐这么写,容易出错，有歧义,如果map默认赋值不是0就会出错
        //cnt[s_std] = cnt.count(s_std); //此时，先创建key再调用count(),再赋值，因此全是1；
        cnt[s_std]++;  //如果map在Key不存在时默认赋值不是0，也会出错，但GCC 5.3.0默认是0，因此通过了OJ测试
        //总之，在使用Map时，要先检查，再赋值或者操作，否则会出现意想不到的问题。
    }
    sort(word.begin(), word.end());
    for(int i = 0; i < (int)word.size(); i++)
        if(cnt[stand(word[i])] == 1)
            cout << word[i] << endl;
    return 0;
}
