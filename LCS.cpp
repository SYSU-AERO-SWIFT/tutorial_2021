using namespace std;
#include <iostream>
string longestMirror(string s);
string s2;
string s;
int main()
{
    cin >> s;
   cout<< longestMirror(s)<<endl;
   if (longestMirror(s2) == longestMirror(s))
       cout << longestMirror(s2);
   
}
    int mirror(int input)
    {
        if (input == 65)
            return 65;
        else if (input == 69)
            return 51;
        else if (input == 72)
            return 72;
        else if (input == 73)
            return 73;
        else if (input == 74)
            return 76;
        else if (input == 76)
            return 74;
        else if (input == 77)
            return 77;
        else if (input == 79)
            return 79;
        else if (input == 83)
            return 50;
        else if (input == 84)
            return 84;
        else if (input == 85)
            return 85;
        else if (input == 86)
            return 86;
        else if (input == 87)
            return 87;
        else if (input == 88)
            return 88;
        else if (input == 89)
            return 89;
        else if (input == 90)
            return 53;
        else if (input == 48)
            return 48;
        else if (input == 49)
            return 49;
        else if (input == 50)
            return 83;
        else if (input == 51)
            return 69;
        else if (input == 53)
            return 90;
        else if (input == 56)
            return 56;
}
int EAC(string s, int left, int right) 
     {
        int L = left, R = right;
        while (L >= 0 && R < s.length() && s[L] == mirror(s[R])) 
        {
            L--;
            R++;
        }
        return R - L - 1;
    }
    string longestMirror(string s) 
    {
        if (s == "" || s.length() < 1) return "";
        int start = 0, end = 0;
        for (int i = 0; i < s.length(); i++) {
            int len1 = EAC(s, i, i);
            int len2 = EAC(s, i, i + 1);
            int len = max(len1, len2);
            if (len > end - start) {
                start = i - (len - 1) / 2;
                end = i + len / 2;
            }
        }
      string s2(s, end + 1);
       int LEN = end + 1 - start;
       if (size(s.substr(start, LEN)) < 3)
           return "";


       else
        return s.substr(start, LEN);
    }
