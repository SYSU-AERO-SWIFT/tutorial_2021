#include <iostream>
#include<string>
#include<vector>
using namespace std;
string longestMirrorString(string str);                  
bool is_mirror(char character1,char character2);                  //判断两个字符是否为镜像
string getsubstring(string strs, int leftindex, int rightindex);  //以某个字符为中心，返回以该字符为中心的最长的镜像子串
int main()
{

}

string longestMirrorString(string strs)
{
	vector<string> vec_longest_string;         //用于存放最长镜像子串
	int max=0;                                 //用于记录最长的子串的长度
	for (int i = 0; i < strs.length(); i++)
	{
		string temp_strs1;
		string temp_strs2;
		temp_strs1 = getsubstring(strs, i, i);             //镜像子串的长度为奇数
		temp_strs2 = getsubstring(strs, i, i + 1);         //镜像子串的长度为偶数
		//用if语句判断各种可能的情况，并且把符合的子串添加到vector中
		if (temp_strs1.length() == temp_strs2.length() && temp_strs1.length() == max)
		{
			vec_longest_string.push_back(temp_strs1);
			vec_longest_string.push_back(temp_strs2);
		}
		else if (temp_strs1.length() > temp_strs2.length() && temp_strs1.length() == max)
		{
			vec_longest_string.push_back(temp_strs1);

		}
		else if (temp_strs1.length() < temp_strs2.length() && temp_strs1.length() == max)
		{
			vec_longest_string.push_back(temp_strs2);
		}
		else if (temp_strs1.length() > temp_strs2.length() && temp_strs1.length() > max)
		{
			vec_longest_string.clear();
			vec_longest_string.push_back(temp_strs1);
			max = temp_strs1.length();
		}
		else if (temp_strs2.length() > temp_strs1.length() && temp_strs2.length() > max)
		{
			vec_longest_string.clear();
			vec_longest_string.push_back(temp_strs2);
			max = temp_strs2.length();
		}
	}
	// 如果镜像子串的最长长度为0，返回一个空string
	if (max == 0)
	{
		return "";
	}
	// 如果镜像子串的最长长度不为0，将vector里面保存的string按格式拼接为一个string，并返回
	else
	{
		string temp;
		while (vec_longest_string.begin() != vec_longest_string.end())
		{
			temp = temp + vec_longest_string.back() + "、";
			vec_longest_string.pop_back();
		}
		temp = temp.substr(0, temp.length() - 2);
		return temp;
	}
}
//判断是否为镜像字符，用switch语句列举
bool is_mirror(char character1,char character2)
{
	switch (character1)
	{

	    case 'A':
	    case 'H':
    	case 'I':
	    case 'M':
     	case 'O':
    	case 'T':
	    case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case '0':
		case '1':
		case '8': if (character1 == character2) return true;  else return false; break;
		case 'E': if (character2 == '3') return true; else return false; break;
		case 'J': if (character2 == 'L') return true;  else return false; break;
		case 'L': if (character2 == 'J') return true;  else return false; break;
		case 'S': if (character2 == '2') return true;  else return false; break;
		case 'Z': if (character2 == '5') return true;  else return false; break;
		case '2': if (character2 == 'S') return true;  else return false; break;
		case '3': if (character2 == 'E') return true;  else return false; break;
		case '5': if (character2 == 'Z') return true;  else return false; break;
        default:return false;
	}
}

string getsubstring(string strs, int leftindex, int rightindex)
{
	//如果左右字符镜像对称且下标没越界，左下标减一，右下标加一，继续判断
	while( leftindex >= 0 && rightindex < strs.length() && is_mirror(strs[leftindex], strs[rightindex]) )
	{
		leftindex--;
		rightindex++;
	}
	
	if (rightindex - leftindex >= 3)
		return strs.substr(leftindex + 1, rightindex - leftindex - 1);
	else
		return "";
}
