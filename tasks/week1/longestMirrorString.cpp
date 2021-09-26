#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

//初始化哈希表，便于查询
unordered_map<char, char> hashTable
	{{'A','A'},{'E','3'},{'3','E'},{'H','H'},{'I','I'},{'J','L'},{'L','J'},{'M','M'},{'O','O'},{'S','2'},{'T','T'},
	{'U','U'},{'V','V'},{'W','W'},{'X','X'},{'Y','Y'},{'Z','5'},{'0','0'},{'1','1'},{'2','S'},{'5','Z'},{'8','8'}};

//给定向左和向右对称查找的初始位置，求最长的镜像字符串
string find_longest(int left_firstpos, int right_firstpos, string& target){
	int n = target.size();
	if(left_firstpos < 0 || right_firstpos >= n)
		return "";
	while (left_firstpos >= 0 && right_firstpos < n){
		if (hashTable[target[left_firstpos]] == target[right_firstpos]){
			left_firstpos--;
			right_firstpos++;
		}
		else
			break;
	}
	return target.substr(left_firstpos + 1, right_firstpos - left_firstpos - 1);
}


string longestMirrorString(string strs) {

	int n = strs.size();
	vector<string> possible_ansSet;
	string possible_ans;

	//遍历每个可能是对称中心的位置
	for (int i = 0; i < n; i++)
	{
		//镜像串长度为奇数的可能答案
		possible_ans = find_longest(i-1, i+1, strs);
		if(possible_ans.size() != 1)
			possible_ansSet.push_back(possible_ans);
		//镜像串长度为偶数的可能答案
		possible_ansSet.push_back(find_longest(i, i+1, strs));
	}

	//寻找可能答案中长度的最大值
	if (possible_ansSet.empty())
		return "";
	int max = possible_ansSet[0].size();
	for (auto ele : possible_ansSet)
	{
		if (ele.size() > max)
			max = ele.size();
	}
	if(!max)
		return "";

	//将可能答案中长度为最大值的答案添加进字符串
	string ans;
	for (auto ele : possible_ansSet) {
		if (ele.size() == max){
			ans += ele;
			ans += ",";
		}
	}
	ans.pop_back();

	return ans;
}
