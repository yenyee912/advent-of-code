#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int two_digit(string test_str){

  char ch;
  vector<int> ch_arr;
  int num;

  for (int i=0; i< test_str.length(); i++ ){
    ch= test_str[i];
    //cout<< ch << endl;

    if (ch>= 48 && ch<=57 ){
      num= ch-48;
      ch_arr.push_back(num);
    }
  }

  int num1= ch_arr[0];
  int num2= ch_arr[ch_arr.size()-1];
  int sum= (num1*10)+num2;
  cout<< sum << endl;
  return sum;

}

/**int main(){
    string str1[4]= {"1abc2", "pqr3stu8vwx", "a1b2c3d4e5f", "treb7uchet"};
    two_digit(str1[0]);
    two_digit(str1[1]);
    two_digit(str1[2]);
    two_digit(str1[3]);

    return 0;


}**/

int main(){
  fstream myFile;
  myFile.open("day1.txt", ios::in);

  vector<string> str_arr;
  string cur_str="";

  int sum=0;
  while (!myFile.eof()){
    getline(myFile, cur_str);
    if (cur_str.length()>0){
      str_arr.push_back(cur_str);
      int num= two_digit(cur_str);
      sum+=num;
    }
  }



  cout<< str_arr.size() << " "<< sum;
  //for (string x : str_arr){
    //cout << x << endl;
  //}
}
