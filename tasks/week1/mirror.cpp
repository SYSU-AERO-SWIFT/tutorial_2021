
#include<iostream></iostream>
#include<string></string>
#include<vector></vector>
using namespace std;
string longestMirrorString(string strs);

char getmirror( char c);//每个元素对应的镜像字符
int single_begin(string s,int p);//对称轴只有一个长度
int double_begin(string s, int p);//对称轴有两个长度
string mirror_str(string& s, vector<int></int> p, int l);//输出该子字符串
int main()
{	
	string s;
	cout &lt;&lt; "please input the string" &lt;&lt; endl;//提示输入字符串
	cin &gt;&gt; s;
	
	cout &lt;&lt; longestMirrorString(s);
}
string longestMirrorString(string strs)
{
	if(strs.length()&lt;2)
	{
		cout &lt;&lt; " ";
		system("pause");
	}
	char this_c= strs[0];//当前的对称轴
	char next_c;//下一个的对称轴
	vector<int></int> position;//储存字符串的某个有最大长度的子字符串的对称轴
	int length_max=0;//某个子字符串的有最大长度
	
	for (int i = 1; i &lt; strs.length() - 1; i++)//循环找到最长的位置
	{
		next_c = strs[i];
		if (next_c == getmirror(next_c))//对称轴只有一个长度
		{				
			if (length_max &lt; 2 * single_begin(strs, i) + 1)
			{
				length_max = 2 * single_begin(strs, i) + 1;
				position.clear();
				position.push_back(i);
			}
			else if(length_max== 2 * single_begin(strs, i) + 1)
			{
				position.push_back(i);
			}
		}
		if (next_c == getmirror(this_c))//对称轴有两个长度
		{			
			if (length_max &lt; 2 * double_begin(strs, i) + 2)
			{
				length_max = 2 * double_begin(strs, i) + 2;
				position.clear();
				position.push_back(i);
			}
			else if (length_max == 2 * double_begin(strs, i) + 2)
			{
				position.push_back(i);
			}

		}
		this_c = next_c;
	}
	return mirror_str(strs,position , length_max);//输出最长的对称子字符串

}
char getmirror(char c)//每个元素对应的镜像字符
{
	char result='+';
	switch (c)
	{
	case 'A':
	case'H':
	case'I':
	case'M':
	case'O':
	case'T':
	case'U':
	case'V':
	case'W':
	case'X':
	case'Y':
	case'0':
	case'1':
	case'8':
		result = c;
		break;
	case'E':
		result = '3';
		break; 
	case'J':
			result = 'L';
			break;
	case'L':
		result = 'J';
		break;
	case'S':
		result = '2';
		break;
	case'Z':
		result = '5';
		break;
	
	case'2':
		result = 'S';
		break;

	case'3':
		result = 'E';
		break;
	case'5':
		result = 'Z';
		break;
	default:'+';//用于没有对称的情况
		break;
	}
	return result;
}
int single_begin(string s,int p)
{
	int l = s.length();
	int d_max = (p &gt; l / 2.0 ) ? (l-1)-p :p ;
	int d = 0;

	for (int i = 1; i &lt;= d_max; i++)
	{
		if (s[p + i] == getmirror(s[p - i]))
		{
			d++;
		}
		else
		{
			break;
		}
	}
	return d;
}//对称轴只有一个长度
int double_begin(string s, int p) {
	int l = s.length();
	int d_max = (p &gt; l / 2.0) ? (l - 1) - p : (p-1);
	int d = 0;

	for (int i = 1; i &lt;= d_max; i++)
	{
		if (s[p + i] == getmirror(s[p - i-1]))
		{
			d++;
		}
		else
		{
			break;
		}
	}
	return d;
}//对称轴有两个长度
string mirror_str(string& s,vector<int></int> p, int l)//输出该子字符串
{	string s1;
	if (l &lt; 2)
	{
		s1 = " ";
	}
	else
	{
		for (int i = 0; i &lt; p.size(); i++)
		{
			int min_index = (l % 2 == 0) ? (p[i] - l / 2) : p[i]-(l-1)/2;
	
			
			s1 += s.substr(min_index, l);
			
			if (i &lt; p.size() - 1)
			{
				s1+= '、';
			}
		}		
	}
	return s1;
}


