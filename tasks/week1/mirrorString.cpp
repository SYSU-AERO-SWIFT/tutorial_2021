#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>
using namespace std;

//num中包含所有将用到的字符的ascii码
//sum中则包含对应镜像字符的ascii码的和，如76（L） +74（ J） = 150 
//主要采用对可能的镜像字符串倒叙相加的方法判断它是否属于镜像字符串
int num[22]={0,1,2,3,5,8,65,69,72,73,74,76,77,79,83,84,85,86,87,88,89,90};
int sum[18]={0,2,16,72,85,95,130,144,146,150,154,158,168,170,172,174,176,178};

vector<int> vnum;
vector<int> vsum;
//将num和sum压入vector
void init()
{   
	    for(int i = 0; i<22; i++)
		    {
			    vnum.push_back(num[i]);
		    }
    
	    for(int i = 0; i<18; i++)
		    {
			    vsum.push_back(sum[i]);
		    }
}

// --函数的定义-- 
string longestMirrorString(string strs)
{
    //将字符串转换成数组
    int len = strs.length();
    const char* p1 = strs.c_str();
    int value[len];  // value保存strs对应的数组
    for(int i = 0; i<len; i++){
        value[i] = int(*(p1+i));
    }

   
    vector<int>  mir[len]; 

    //获取可能的镜像字符串，分别保存在mir[i]
     int count = 0;
     bool fc = 0;
    for(int i = 0; i<len; i++)
    {
         if(find(vnum.begin(), vnum.end(),value[i]) != vnum.end())
         {
             if(fc) {count++; fc = 0;}
             mir[count].push_back(value[i]);
          }
         else
         {
             fc = 1;
         }
    }



    //确定出在mir[i]中的镜像字符串，将它们的长度、序号保存在pair数组(命名为sizeSerial)中
    //in a vector of pairs
    vector<pair<int,int>> sizeSerial;

    for(int i = 0; i<=count; i++)
    {
        vector<int>::reverse_iterator bward = mir[i].rbegin();
        for(vector<int>::iterator fward = mir[i].begin(); fward!=mir[i].end(); ++fward)
        {
            if(find(vsum.begin(), vsum.end(),*fward+*bward) == vsum.end())
                { break; }
            ++bward;
            if(bward == mir[i].rend())
            {
                sizeSerial.push_back(pair<int,int>(mir[i].size(),i));
            }
        } 
    }
   

    //冒泡排序得到最大镜像字符串对应与sizeSerial中的位置
    for(int i = 0; i < sizeSerial.size()-1; i++)
        for(int j = 0; j < sizeSerial.size()-1-i; j++)
                if(sizeSerial[j].first > sizeSerial[j+1].first)
                {
                    pair<int,int> temp = sizeSerial[j+1];
                    sizeSerial[j+1] = sizeSerial[j];
                    sizeSerial[j] = temp;
                }
    
    // 初始化保存最终结果的字符串
     string str = ""; 
    int lastLen;

    for(vector<pair<int,int>>::reverse_iterator it = sizeSerial.rbegin(); it != sizeSerial.rend();)
    {
        if((*it).first == 1) return " ";

        int mirlen = mir[(*it).second].size();

        char mirchar[mirlen+1];
        //将ascii码数组转换到字符串并加到str中
        if(it == sizeSerial.rbegin() || lastLen == mirlen)
        {
             for(int i = 0; i<mirlen; i++)
                mirchar[i] = (mir[(*it).second])[i];

            str += mirchar;
            str += "  ";
        }

        lastLen = mirlen;
       ++it;
    }
    return str; //返回结果
}


int main()
{
    init();
    string strs;
    cout<<"输入字符串：";
    cin>>strs;
    cout<<"结果为：";
    cout<<longestMirrorString(strs)<<endl;
    return 0;
}