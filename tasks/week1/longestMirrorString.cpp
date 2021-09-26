/*************************************************************************
	> File Name: longestMirrorString.cpp
	> Author: ZX Xie
	> Mail: 1514806752@qq.com
	> Created Time: 2021年09月24日 星期五 05时03分49秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <map>

using namespace std;
//测试代码
// string longestMirrorString(string strs);

// int main() {
//     for (;;) {
//         string str;
//         cin >> str;
//         if (str == "BACK" ) {
//             break;
//         }
//         else {
//             cout << longestMirrorString(str) << endl;
//         }
//     }
//     return 0;
// }

string longestMirrorString(string strs) {
    map<char, int> hash_set ;
    hash_set['A'] = 0; hash_set['E'] = 1; hash_set['3'] = -1; hash_set['H'] = 0;
    hash_set['I'] = 0; hash_set['J'] = 2; hash_set['L'] = -2; hash_set['M'] = 0;
    hash_set['O'] = 0; hash_set['S'] = 3; hash_set['2'] = -3; hash_set['T'] = 0;
    hash_set['U'] = 0; hash_set['V'] = 0; hash_set['W'] = 0; hash_set['X'] = 0;
    hash_set['Y'] = 0; hash_set['Z'] = 4; hash_set['5'] = -4; hash_set['0'] = 0;
    hash_set['1'] = 0; hash_set['8'] = 8;
    //动态规划,时间复杂度为 O(n)
    int dp[strs.size()][strs.size()];
    int maxlength = 1;
    //初始化dp
    for (int i = 0; i < strs.size(); i++)
    for (int j = i+1; j < strs.size(); ++j) dp[i][j] = 0;
    
    for(int i = 0; i < strs.size(); ++i) {
        dp[i][i] = 1;
        if(i != strs.size()-1){
            if (!hash_set.count(strs[i]) || !hash_set.count(strs[i+1])) continue;
            if (hash_set[strs[i]] == 0) dp[i][i+1] = (strs[i] == strs[i+1]);
            else  dp[i][i+1] = (hash_set[strs[i]] + hash_set[strs[i+1]] == 0);
        }
    }
    //状态转移
    for (int i = strs.size()-2; i >= 0; --i)
    for (int j = strs.size()-1; j >=i+1; --j) {
        if (!hash_set.count(strs[i]) || !hash_set.count(strs[j])) continue;
        if (!hash_set[strs[i]]) dp[i][j] = dp[i+1][j-1] & (strs[i] == strs[j]);
        else  dp[i][j] = dp[i+1][j-1] & (hash_set[strs[i]] + hash_set[strs[j]] == 0);
        if (dp[i][j]) maxlength = maxlength>(j-i+1)?maxlength:(j-i+1);
    }
    //处理结果输出
    int flag = 0;
    string ans_str;
    if (maxlength == 1) return "";
    else {
        for (int i = 0; i + maxlength - 1 < strs.size(); ++i) {
            if (dp[i][i+maxlength-1]) 
            if(flag)
                ans_str += "、" + strs.substr(i,maxlength);
            else {
                flag = 1;
                ans_str += strs.substr(i,maxlength);
            }
        }
        return ans_str;
    }
}
