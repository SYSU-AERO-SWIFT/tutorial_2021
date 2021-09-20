#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
//mirror函数用于返回一个字符的镜像字符
char mirror(char c){
    if(c == 'A'){
        return 'A';
    }
    if(c == 'E'){
        return '3';
    }
    if(c == 'H'){
    	return 'H';
    }
    if (c == 'I')
    {
    	return 'I';
    }
    if (c == 'J')
    {
    	return 'L';
    }
    if (c == 'L')
    {
    	return 'J';
    }
    if (c == 'M')
    {
    	return 'M';
    }
    if (c == 'O')
    {
    	return 'O';
    }
    if (c == 'S')
    {
    	return '2';
    }
    if (c == 'T')
    {
    	return 'T';
    }
    if (c == 'U')
    {
    	return 'U';
    }
    if (c == 'V')
    {
    	return 'V';
    }
    if (c == 'W')
    {
    	return 'W';
    }
    if (c == 'X')
    {
    	return 'X';
    }
    if (c == 'Y')
    {
    	return 'Y';
    }
    if (c == 'Z')
    {
    	return '5';
    }
    if (c == '0')
    {
    	return '0';
    }
    if (c == '1')
    {
    	return '1';
    }
    if (c == '2')
    {
    	return 'S';
    }
    if (c == '3')
    {
    	return 'E';
    }
    if (c == '5')
    {
    	return 'Z';
    }
    if (c == '8')
    {
    	return '8';
    }
    return 0;
}

//区间dp，时间、空间复杂度为O（n ^ 2）
string longestMirrorString(string strs){
	int maxlen = 0;//记录最长镜像子串长度
	int len = strs.size();
	bool dp[len][len + 1];//区间dp数组，第一个下标存子串起始位置，第二个下标存字串长度，0代表不是对称，非0代表对称。
	//初始化
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < len + 1; ++j)
		{
			dp[i][j] = 0;
		}
	}
	//归纳基之一，标记长度为1的对称子串
	for (int i = 0; i < len; ++i)
	{
		if (strs[i] == mirror(strs[i]))
		{
			dp[i][1] = 1;
			maxlen = 1;
		}
	}
	//归纳基之二，标记长度为2的对称子串
	for (int i = 0; i < len - 1; ++i)
	{
		if (strs[i] == mirror(strs[i + 1]))
		{
			dp[i][2] = 1;
			maxlen = 2;
		}
	}
	//归纳步，若s[i..j]为对称子串且s[i - 1] == mirror([j + 1])，则s[i - 1..j + 1]也为对称子串
	for (int l= 3; l< len + 1; ++l)
	{
		for (int i = 0; i < len - l + 1; ++i)
		{
			if (dp[i + 1][l - 2] && (strs[i] == mirror(strs[i + l - 1])))
			{
				dp[i][l] = 1;
				maxlen = l;
			}
		}
	}

	//输出
	if (maxlen == 1)
	{
		return "";
	}
	string ans = "";
	for (int i = 0; i < len - maxlen + 1; ++i)
	{
		if (dp[i][maxlen])
		{
			ans = ans + strs.substr(i,maxlen);
			ans = ans + "、";
		}
	}
	string ss = "、";
	return ans.substr(0,ans.size() - ss.size());//去尾

}

