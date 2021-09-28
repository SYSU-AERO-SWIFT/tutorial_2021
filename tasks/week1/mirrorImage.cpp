//程序说明：该程序能根据特定的镜像规则，找出一段字符串中的最长镜像字符串
#include<iostream>
#include<string>
#include<vector>
using namespace std;
string longestMirrorString(string strs);//寻找最长镜像字符串
string Single(string s, string strs, int& num);//寻找最长奇数镜像字符串
string Double(string s, string strs, int& num);//寻找最长偶数镜像字符串
char judge(char ch);//判断字符类型，并将其镜像化，如把L变J，J仍为J
int main()
{
    string strs1;//初始字符串
    string strs2;//镜像字符串

    //输入初始字符串，找最长镜像字符串，输出镜像字符串
    //**********************************
    cout << "pleasre input a string:" << endl;
    cin >> strs1;
    
    strs2 = longestMirrorString(strs1);
    cout << "the  longest mirror string is:" << endl;
    cout << strs2 << endl;
    //***************************************
    return 0;
}

string longestMirrorString(string strs)
{
    string s = strs;
    string s1;//连续有效字符(已镜像）（镜像为空格的是无效字符)
    string s2;//s1对应的原字符串
    string s3;//从s2中找出的奇数镜像字符串（有多个，如YOY YYY AAA;)
    string s4;//从s2中找出的偶数镜像字符串(同上）
    string s5;//最长镜像字符串（同上）

    int si1;//s3中单个连续字符串长度
    int si2;//s4中单个连续字符串长度
    int si3 = 0;//s5中单个连续字符串长度
    char ch1='.';//s中单个字符
    int num1 = 1;//s3中字符串个数（如YOY YYY AAA，有3个）
    int num2 = 1;//s4中字符串个数(同上）

    int si = s.size();//输入字符串的长度
    int j1 = 0;
    int j2 = 0;
    int ps1 = 0;//s2在s中的起始位置
    int ps2=0;//s2在s中的末端位置
    for (int i = 0; i < si+1; i++)
    {
        //判断字符是否有效
        if(i!=si)
            ch1 = judge(s[i]);
        if ((i != si) & (ch1 != ' '))
        {
            j2++;
            s1 += ch1;
        }
        //对一段连续有效字符串进行查找
        else    
        {
            num1 = 1;
            num2 = 1;
            ps2 = ps1+j2;
            //复制s1在s的对应部分到s2
            for (int k = ps1; k < ps2;k++)
                s2 += strs[k];

            s3 = Single(s1, s2, num1);//从s2中查找最长奇数镜像字符串
            s4 = Double(s1, s2, num2);//从s2中查找最长偶数镜像字符串
            
            //比较s3、s4中单个字符串长度，取最长的，并将其与s5做比较，再取最长的
            si1 = (s3.size() - num1 + 1) / num1;
            si2 = (s4.size() - num2 + 1) / num2;
            if (si1 > si2)
            {
                if (si1 > si3)
                {
                    si3 = si1;
                    s5 = s3;
                }
                else if (si1 == si3)
                {
                    s5 += ' ';
                    s5 += s3;
                }
            }
            else if ((si1 < si2) & (si2 > si3))
            {
                if (si2 > si3)
                {
                    si3 = si1;
                    s5 = s4;
                }
                else if (si2 == si3)
                {
                    s5 += ' ';
                    s5 += s4;
                }
            }
            ps1 = i+1;
            s1.clear();
            s2.clear();
            j2 = 0;
        }
    }
    return s5;
}
// 判断字符类型，并将其镜像化，如把L变J，J仍为J
char judge(char ch)
{
    switch (ch)
    {
    case 'B':
    case 'C':
    case 'D':
    case 'F':
    case 'G':
    case 'K':
    case 'N':
    case 'P':
    case 'Q':
    case 'R':
    case '4':
    case '6':
    case '7':
    case '9':
        return ' ';
        break;
    case 'E':
        return '3';
        break;
    case 'J':
        return 'L';
        break;
    case 'S':
        return '2';
        break;
    case 'Z':
        return '5';
        break;
    default:
        return ch;
    }
}
//查找方法：从当前字符向两边比较，找出两端相同的字符，逐个比较找出最长的那一段
string Single(string s,string strs,int& num)
{
    int si = s.size();
    int ps=0;
    int si1=1;
    int si2 = 0;
    string s1;
    for (int i = 0; i < si; i++)
    {
        int n1 = i;
        int n2 = si - i-1;
        int j = 1;
        ps = i;
        si2 = 0;
        //比较左右两边是否相同
        while ((j <= n1) & (j <= n2))
        {
            if (s[i - j] == s[i + j])
            {               
                j++;
                si2 = (j - 1) * 2 + 1;
            }
            else
            {
                j = si + 1;
            }
        }
        //对每一段进行比较，找出最长的或等长的
        if (si1 < si2)
        {
            s1.clear();
            si1 = si2;
            for (int i = ps - (si1 - 1) / 2; i <= ps + (si1 - 1) / 2; i++)
                s1 += strs[i];
        }
        else if ((si1>1)&(si1 == si2))
        {
            s1 += ' ';
            for (int i = ps - (si1 - 1) / 2; i < ps + (si1 - 1) / 2+1; i++)
                s1 += strs[i];
            num++;
        }
    }
    return s1;
}
string Double(string s, string strs,int& num)
{
    int si = s.size();
    int ps = 0;
    int si1 = 0;
    int si2 = 0;
    string s1;
    for (int i = 0; i < si; i++)
    {
        int n1 = i+1;
        int n2 = si - i - 1;
        int j = 0;
        ps = i;
        si2 = 0;
        //比较左右两边是否相同
        while ((j < n1) & (j < n2))
        {
            if (s[i - j] == s[i + j+1])
            {
                j++;
                si2 = j * 2;
            }
            else
            {
                j = si + 1;
            }
        }
        //对每一段进行比较，找出最长的或等长的
        if (si1 < si2)
        {
            s1.clear();
            si1 = si2;
            for (int i = ps - si1 / 2 + 1; i < ps + si1 / 2+1; i++)
                s1 += strs[i];
        }
        else if ((si1!=0)&(si1 == si2))
        {
            s1 += ' ';
            for (int i = ps - si1 / 2 + 1; i < ps + si1 / 2+1; i++)
                s1 += strs[i];
            num++;
        }
    }
    return s1;
}
