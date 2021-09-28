#include<vector>
#include<string>
#include<map>
using namespace std;
string longestMirrorString(string strs)
{
	string str = "";//最终结果
	vector<string> maxstring;//储存最长镜像子串
	int max = 0;//记录最大镜像子串长度
	map<char, char> mirror = { {'A','A'},{'E','3'},{'H','H'},{'I','I'},{'J','L'},
		{'L','J'},{'M','M'},{'O','O'},{'S','2'},{'T','T'},{'U','U'},
		{'V','V'},{'W','W'},{'X','X'},{'Y','Y'},{'Z','5'},{'0','0'},
		{'1','1'},{'2','S'},{'3','E'},{'5','Z'},{'8','8'} };//镜像映射
	for (int j = 1; j <= 2 * strs.length() - 3; j++)//用中心法找到最长镜像子串
	{
		int left = (j % 2 == 0) ? (j / 2 - 1) : (j / 2);
		int right = j / 2 + 1;
		if ((right - left == 2) && (mirror.count(strs[left + 1]) == 0 || strs[left + 1] != mirror[strs[left + 1]]))
			continue;//中心不是镜像字母的情况
		if (mirror.count(strs[right])==0||strs[left] != mirror[strs[right]])
			continue;//起始位置不对称情况
		while (mirror.count(strs[right])!=0&&strs[left]==mirror[strs[right]] && left != 0 && right != (strs.length() - 1))
		{
			left--;
			right++;
		}
		if (mirror.count(strs[right]) == 0 || strs[left] != mirror[strs[right]])//检验边界情况
		{
			left++;
			right--;
		}
		int len = right - left + 1;//镜像子串长度
		if (len > max)//更新最大长度
		{
			max = len;
			maxstring.clear();
		}
		if (len == max)
			maxstring.push_back(strs.substr(left, len));
	}
	for (int i = 0; i < maxstring.size(); i++)//合并所有最大镜像子串
	{
		if (i == 0)
			str = maxstring[i];
		else
		{
			str += "、";
			str += maxstring[i];
		}
	}
	return str;
}