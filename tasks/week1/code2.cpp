#include <iostream>
#include <string.h>
using namespace std;

char mirror(char c)	//建立字符和镜像间的映射函数
{
	//把字符和镜像相等的字符构成数组same
	char same[15] = { 'A', 'H', 'I', 'M', 'O', 'T', 'U', 'V', 'X', 'Y', '0', '1', '8'};
	//判定c是否在same内
	for (int i = 0; i < strlen(same); i++)
	{
		if (c == same[i])
			return same[i];
	}
	//把字符和镜像相互对称的字符构成数组group
	char group[4][3] = { "3E", "JL", "2S", "5Z" };
	//判定c是否在group内
	for (int j = 0; j < 4; j++)
		for (int k = 0; k < 2; k++)
		{
			if (c == group[j][k])
				return group[j][!k];	//!k即为第j个字符中对称的字符
		}
	return '\0';
}

string longestMirrorString(string strs)
{
	int len = strs.length();	//序列长度len
	string ans, odd;
	int left, right;
	for (int mid = 1; mid < len; mid++)
	{
		left = mid - 1;		//初始化left right
		right = mid + 1;
		while (left >= 0 && right <= strs.length()-1 && strs[right] != '\0' && strs[right] == mirror(strs[left]))
		{
			//在不越界的前提下判定strs[right] != '\0' && strs[right] == mirror(strs[left])是否成立
			//cout << "mirror equal: " << strs[left] << ", " << strs[right] << endl;
			left--;
			right++;
		}
		odd = strs.substr(left+1, right-left-1);	//通过求得的left和right得到strs对应位置的字串odd
		if (odd.length() > 2)	//当odd的长度大于2时（最小满足题意的序列长度为3）
		{
			//cout << "ans append : " << odd << endl;
			ans.append(odd);	//将odd赋值到ans末尾
			ans = ans + ' ';	//通过' '分割找到的所有满足条件的字串
		}
	}
	return ans;
}

int main()
{
	//  测试mirror
	//	char c;
	//	cin >> c;
	//	cout << mirror(c);

	//  测试函数longestMirrorString
	string a;
	cout << "input a string: ";
	cin >> a;
	cout << "longestMirrorString is " << longestMirrorString(a) << endl;
	return 0;
}
