#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;
string longestMirrorString(string strs);
int Compare(char a, char b);//用来判断是否镜像字符的函数
int main()
{
    string test1 = "ABC";
    string test2 = "ALOOJ";
    string test3 = "ALOOJYOOY";
    string test4 = "AYOOY3OOEY";
    string test5 = "LYOY3OELUJQWQ";
    cout <<"       【最长镜像字符串】" << endl;
    cout <<setw(14)<< test1 << " —>> "  << longestMirrorString(test1) << endl;
    cout <<setw(14)<< test2 << " —>> "  << longestMirrorString(test2) << endl;
    cout <<setw(14)<< test3 << " —>> "  << longestMirrorString(test3) << endl;
    cout <<setw(14)<< test4 << " —>> "  << longestMirrorString(test4) << endl;
    cout <<setw(14)<< test5 << " —>> "  << longestMirrorString(test5) << endl;
    return 0;
}

string longestMirrorString(string strs)
{   
    int i, j,m;
    int SIZE = strs.size() - 1;
    string out = "";
    vector<string>OUT;
    //（1）偶数长
    for(i=0;i<SIZE;i++)
    {
        out = "";
        j = i;
        if ( i + 1 <= SIZE && Compare(strs[i], strs[i + 1]) == 1 )
        {    
              out = out + strs[i] + strs[i + 1];
              for (int a = 1; (i - a) >= 0 && (i + a + 1) <= SIZE; a++)
              {
                  if (Compare(strs[i - a], strs[i + a + 1] )== 1)
                  {
                      out=strs[i - a] + out + strs[i + a + 1];
                  }
              }
              OUT.push_back(out);
        }
        i = j;
    }
    //（2）奇数长 
    for (i = 0; i <= SIZE; i++)
    {
        out = "";
        j = i;
        if (i + 2 <= SIZE && Compare(strs[i], strs[i + 2]) == 1)
        {
            if (strs[i + 1] == 'A' || strs[i + 1] == 'H' || strs[i + 1] == 'I' || strs[i + 1] == 'M' || strs[i + 1] == 'O' || strs[i + 1] == 'T' || strs[i + 1] == 'U' || strs[i + 1] == 'V' || strs[i + 1] == 'W' || strs[i + 1] == 'X' || strs[i + 1] == 'Y' || strs[i + 1] == '1' || strs[i + 1] == '8')
            {
                out = out + strs[i] + strs[i + 1] + strs[i + 2];
                for (int a = 1; i - a >= 0 && i + a + 2 <= SIZE; a++)
                {
                    if (Compare(strs[i - a], strs[i + a + 2]) == 1)
                    {
                        out = strs[i - a] + out + strs[i + a + 2];
                    }
                }
            }
            OUT.push_back(out);
        }
        i = j;
    }
    //(3)输出部分
    //【没有镜像字符串】
    if (OUT.size() == 0)
    {
        string blank = " ";
        OUT.push_back(blank);
        return OUT[0];
    }
    for(m=0;m<OUT.size()-1;m++)
    {
        if (OUT[m].size() > OUT[m + 1].size())
        {
            string temp = OUT[m + 1];
            OUT[m + 1] = OUT[m];
            OUT[m] = temp;
        }
    }
    //【只有一个】
    if (m == 0)
        return OUT[0];
    //【有>=2个】
    else if (OUT[m].size() == OUT[m - 1].size())
    {
        string store = OUT[m] + "、" + OUT[m - 1];
        for (int k = 1; m - 1 - k >= 0 && OUT[m - k].size() == OUT[m - k - 1].size(); k++)
        {
            store = store + "、" + OUT[m - k - 1];
        }
        return store;
    }
    else
        return OUT[m];
};
int Compare(char a, char b)//比较函数
{
    if (a == 'L' && b == 'J' || a == 'J' && b == 'L')
        return 1;
    else if (a == 'E' && b== '3' || a == '3' && b == 'E')
        return 1;
    else if (a == '5' && b == 'Z' || a == 'Z' && b== '5')
        return 1;
    else if (a == '2' && b == 'S' || a == 'S' && b== '2')
        return 1;
    else if (a== b)
        return 1;
    else
        return 0;
}
