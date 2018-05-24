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
        //if(cnt.find(s_std) == cnt.end()) //����ʹ��cnt.find(key)����cnt.count(key)�����ж�
        //    cnt[s_std] = 0;
        //cnt[s_std] += cnt.count(s_std); //���жϣ���ʹ�ã���������Ľ������������й�
                                          //��ʱ�Ƚ��к���ļ���ټ�,����һ�γ���s_std�����cnt[s_std]��ֵΪ0���Ҽ���count()�ķ���ֵ���˺�+1,���Ƽ���ôд,���׳���������,���mapĬ�ϸ�ֵ����0�ͻ����
        //cnt[s_std] = cnt.count(s_std); //��ʱ���ȴ���key�ٵ���count(),�ٸ�ֵ�����ȫ��1��
        cnt[s_std]++;  //���map��Key������ʱĬ�ϸ�ֵ����0��Ҳ�������GCC 5.3.0Ĭ����0�����ͨ����OJ����
        //��֮����ʹ��Mapʱ��Ҫ�ȼ�飬�ٸ�ֵ���߲����������������벻�������⡣
    }
    sort(word.begin(), word.end());
    for(int i = 0; i < (int)word.size(); i++)
        if(cnt[stand(word[i])] == 1)
            cout << word[i] << endl;
    return 0;
}
