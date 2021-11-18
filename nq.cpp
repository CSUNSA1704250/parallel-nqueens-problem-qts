#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;
long long count = 0;
int n;
string val;

string realPos(int n){
  switch(n){
    case 1:
      return "1";
    case 2:
      return "2";
    case 4:
      return "3";
    case 8:
      return "4";
    case 16:  
      return "5";
    case 32:
      return "6";
    case 64:
      return "7";
    case 128:
      return "8";
    case 256:
      return "9";
    case 512:
      return "10";
    case 1024:
      return "11";
    case 2048:
      return "12";
    case 4096:  
      return "13";
    case 8192:
      return "14";
    case 16384:
      return "15";
    case 32768:
      return "16";
    case 65536:
      return "17";
    case 131072:
      return "18";
    case 262144:
      return "19";
    case 524288:
      return "20";
    default:
      return "0";
  }
}
string inverse(string values){
  string answer = "";
  string number = "";
  for(int i = 0; i < values.size(); i++){
    if(values[i] != ' ')
      number += values[i];
    else{
      answer += to_string(n-(atoi(number.c_str())-1))+' ';
      number ="";
    }
  }
  return answer;
}
void solve(int ld, int col, int rd, int ex1, int ex2, int* done, string answer){

  if(col == *done){
    //TODO change done to a member class
    count++;
    cout << answer <<"\n";
    cout << inverse(answer) <<"\n";
    return;
  }
  int pos = ~(ld|rd|col|ex1) & *done;
  while(pos){
    int bit = pos & -pos;
    pos ^= bit;
    solve((ld|bit)>>1, col|bit, (rd|bit)<<1, ex2, 0, done, answer + realPos(bit)+' ');
    ex2 = 0;
  }

}
void nQueen(int n){
  if(n == 0 || n == 1) {
    cout << count <<endl;
    return;
  }
  
  int done = (1<<n) - 1;
  int exclusion = (1<<(n/2)) - 1;
  string answer= "3 ";
  solve(0,4,0,exclusion, n%2?exclusion: 0 ,&done, answer);
  cout << (count<<1) <<endl;
  count = 0;
}

int main(int argv, char** argc){
  n = atoi(argc[1]);
  nQueen(n);
  return 0;
}