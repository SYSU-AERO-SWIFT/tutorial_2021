/*#include<iostream>
#include<vector>
#include<string>

using namespace std;*/
string string1 = "AEHIJLMOSTUVWXYZ012358";//将镜像规则写入两个字符串
string string2 = "A3HILJMO2TUVWXY501SEZ8";

bool equal(char a, char b)//判断两个字符是否为镜像
{
	if (string1.find(a)==string2.find(b)&&string1.find(a)<25)
		return true;
	else
		return false;
}

int centermove(string strs, int i)//以下标为i的元素向两端展开，找到最长镜像子串
{
	int L = i;
	int R = i;
	for(; L >= 0 && R < strs.length() && equal(strs[R], strs[L]); L--,R++)
	{}
	return R - L - 1;//返回最长子串的长度

	
}

vector<string>longestMirrorString(string strs)
{ 
	int max = 0;//记录最长镜像子串的长度
vector<string>output;//返回的字符串向量


if(strs.length() <= 2)//长度小于等于2直接返回空串 
{
	output.push_back("");
	return output;
 }


for (int i = 0; i < strs.length(); i++)//从下标为0开始依次穷举所有子串的情况
{
	int sublength = centermove(strs, i);

	if (sublength ==max && sublength >= 2)//对应找到的子串跟现有子串一样长的情况
	{
		output.push_back(strs.substr(i - (sublength - 1)/2, sublength));
	}
	else if (sublength > max && sublength >= 2)//对应找到的子串比现有最长子串更长的情况
	{
		max = sublength;
		output.clear();//清空向量中的元素
		output.push_back(strs.substr(i - (sublength - 1)/2, sublength));//插入子串
	}

}
	for (int j = 0; j < output.size(); j++)//输出结果
		cout << output[j] << ',';
	return output;
}






/*
int main()
{
	longestMirrorString("LYOYLAOAL3OEL");
	
	
}
*/


