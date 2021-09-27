#include "LmsFun.h"
int counts = 0, most = 2;//初始化全局变量；
string s = "";
string ret[100] = { "" };
bool flag(char a, char b)//判断两个字符是否满足镜像对称；
{
	string test1 = "E3JLS2Z5", test2 = "BCDFGKNPQR4679";
	for (int i = 0;i < test1.length();i++)
	{
		if (a == test1[i] && b == test1[i])
			return false;
	}
	for (int i = 0;i < test2.length();i++)
	{
		if (a == test2[i] || b == test2[i])
			return false;

	}
	if (a == 'E' && b == '3') return true;
	if (a == '3' && b == 'E') return true;
	if (a == 'J' && b == 'L') return true;
	if (a == 'L' && b == 'J') return true;
	if (a == 'S' && b == '2') return true;
	if (a == '2' && b == 'S') return true;
	if (a == 'Z' && b == '5') return true;
	if (a == '5' && b == 'Z') return true;
	if (a == b) return true;
	return false;
}
void spread(string s, int left, int right)//寻找镜像对称字符串；
{
	int L = left, R = right;
	while (L >= 0 && R < s.size() && flag(s[L], s[R]))
	{
		if (R - L + 1 >= most)
		{
			most = R - L + 1;
			ret[counts] = s.substr(L, R - L + 1);
			counts++;

		}
		L--; R++;
	}
}
string longestMirrorString(string strs) 
{
	if (strs.size() <= 1) return "";
	for (int i = 0;i < strs.size();i++) {
		spread(strs, i, i);//从单个字符开始扩散，字符串含奇数个字符；
		spread(strs, i, i + 1);//从相邻的两个字符开始扩散，字符串含偶数个字符；
	}
	int Len = counts;
	if (Len == 0) return "";
	if (Len == 1) return ret[0];
	else
	{
		int kk = 1;//kk表示最长镜像字符串的个数；
		bool flag1 = 0;
		int i = Len - 1;
		do
		{
			flag1 = 0;
			if (ret[i].size() == ret[i - 1].size())//ret数组中的字符串是逐渐增长的，因此若前者比后者短就没必要继续判断；
			{
				++kk;
				flag1 = 1;
			}
			i--;
		} while (flag1 == 1 && i >= 0);
		int k = kk;
		string sss;
		for (int j = kk;j > 0;j--)
		{
			sss.append(ret[Len - j]);
			k--;
			if (k != 0)
				sss.append("、");
		}
		return sss;
	}
}
