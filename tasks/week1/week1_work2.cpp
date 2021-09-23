#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
 *
 * Auther : PEACH
 * using the Brute algorithm
 * time complex: O(n^2)
 *  
 */

// -1 represent no mirror
// A - Z 0-25
int Mirror_rules[40] =
{
  0,-1,-1,-1,29,-1,-1,
  7,8,11,-1,9,12,-1,
  14,-1,-1,-1,28,19,20,
  21,22,23,24,31,26,27,
  18,4,-1,25,-1,-1,34,-1
};

//judge function
bool judge(int x,int y){
  if(Mirror_rules[x] == -1 || Mirror_rules[y] == -1) return 0;
  return x == Mirror_rules[y];
}

//change function----turn char to int tag
int s_i(char x){
  if(x<='9' && x>= '0') return 26 + x - '0';
  else return x - 'A';
}

//solution
string longestMirrorString(string strs){
  vector<string> tmp;
  int maxlen = 2;
  int len = strs.size();

  //odd b[a]b
  for(int i=0; i<len; ++i){ // the middle position
    int j;
    for(j=1; j<=i && j+i<len; ++j) {
      if( !judge(s_i(strs[i-j]),s_i(strs[i+j])) ){ //stop compare
        if(j+j-1 > maxlen){
          tmp.clear();
          maxlen = j + j - 1;
          tmp.push_back(strs.substr(i-j+1,maxlen));
        }

        else if(j+j-1 == maxlen){
          tmp.push_back(strs.substr(i-j+1,maxlen));
        }

        break;
      }
    }

    //finish all
    if(j>i || i+j>=len){
      if(j+j-1 > maxlen){
        tmp.clear();
        maxlen = j + j - 1;
        tmp.push_back(strs.substr(i-j+1,maxlen));
      }
      else if(j+j-1 == maxlen){
        tmp.push_back(strs.substr(i-j+1,maxlen));
      }
    }
  }

  //even b[aa]b
  for(int i=0; i<len-1; ++i){ // the first-middle position
    int j;
    for(j=0; j<=i && j+i+1<len; ++j){
      if( !judge(s_i(strs[i-j]),s_i(strs[i+j+1])) ){
        if(j+j > maxlen) { //find a better ans
          tmp.clear();
          maxlen = j + j ;
          tmp.push_back(strs.substr(i-j+1,maxlen));
        }
        else if(j+j == maxlen) {  //find another example
          tmp.push_back(strs.substr(i-j+1,maxlen));
        }

        break;

      }

      if(j>i || j+i >=len-1){
        if(j+j > maxlen) { //find a better ans
          tmp.clear();
          maxlen = j + j ;
          tmp.push_back(strs.substr(i-j+1,maxlen));
        }
        else if(j+j == maxlen) {  //find another example
          tmp.push_back(strs.substr(i-j+1,maxlen));
        }
      }
    }
  }

  string ans = "";
  // output control
  for(int i=0; i<tmp.size(); ++i){
    if(i == 0) ans += tmp[i];
    else ans += ","+ tmp[i];
  }
  return ans;
}


//main test function
int main(int argc,char **argv){
  string s;
//	for(int i=0;i<36;++i)
//		cout<<i<<"   "<<Mirror_rules[i]<<endl;
  cin>>s;
  cout<<longestMirrorString(s)<<endl;
  return 0;
}

