#include<vector>
#include<string>
#include<map>
using namespace std;
string longestMirrorString(string strs)
{
	string str = "";//���ս��
	vector<string> maxstring;//����������Ӵ�
	int max = 0;//��¼������Ӵ�����
	map<char, char> mirror = { {'A','A'},{'E','3'},{'H','H'},{'I','I'},{'J','L'},
		{'L','J'},{'M','M'},{'O','O'},{'S','2'},{'T','T'},{'U','U'},
		{'V','V'},{'W','W'},{'X','X'},{'Y','Y'},{'Z','5'},{'0','0'},
		{'1','1'},{'2','S'},{'3','E'},{'5','Z'},{'8','8'} };//����ӳ��
	for (int j = 1; j <= 2 * strs.length() - 3; j++)//�����ķ��ҵ�������Ӵ�
	{
		int left = (j % 2 == 0) ? (j / 2 - 1) : (j / 2);
		int right = j / 2 + 1;
		if ((right - left == 2) && (mirror.count(strs[left + 1]) == 0 || strs[left + 1] != mirror[strs[left + 1]]))
			continue;//���Ĳ��Ǿ�����ĸ�����
		if (mirror.count(strs[right])==0||strs[left] != mirror[strs[right]])
			continue;//��ʼλ�ò��Գ����
		while (mirror.count(strs[right])!=0&&strs[left]==mirror[strs[right]] && left != 0 && right != (strs.length() - 1))
		{
			left--;
			right++;
		}
		if (mirror.count(strs[right]) == 0 || strs[left] != mirror[strs[right]])//����߽����
		{
			left++;
			right--;
		}
		int len = right - left + 1;//�����Ӵ�����
		if (len > max)//������󳤶�
		{
			max = len;
			maxstring.clear();
		}
		if (len == max)
			maxstring.push_back(strs.substr(left, len));
	}
	for (int i = 0; i < maxstring.size(); i++)//�ϲ�����������Ӵ�
	{
		if (i == 0)
			str = maxstring[i];
		else
		{
			str += "��";
			str += maxstring[i];
		}
	}
	return str;
}