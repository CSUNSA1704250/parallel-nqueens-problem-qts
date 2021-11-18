#include "../include/utils.hpp"
#include <thread>
#include <iostream>
#include <mutex>
#include <fstream>
#include <sstream>
#include <string>

extern std::ofstream output;

namespace utils{
  int total = 0;
  std::mutex total_mutex;
  std::mutex ios_m;
  int getTotal(){return total;}
  int getTotalThreads(int n){
    int totalHW = std::thread::hardware_concurrency();
    if(n < totalHW) totalHW = n;
    return totalHW;
  }
  void sendSolutionToFile(std::deque<int> &queens){
    std::unique_lock<std::mutex> l(ios_m);
    for(auto& q: queens)
      output << q<<" ";
    output << "\n";
  }

  bool isEatable(int row, int column, std::deque<int> &queens) {
    for(int i = 0; i < queens.size(); i++) {
      if(row == i) return true;
      if(column == queens[i]) return true;
      if(i - queens[i] == row - column) return true;
      if(i + queens[i] == row + column) return true;
    }
    queens.push_back(column);
    return false;
  }
  
  int solve(int n, int row, std::deque<int> &queens, Queue<std::deque<int>>* solutions, int type) {
    if(queens.size() == n) {
      {
        std::unique_lock<std::mutex> l(total_mutex);
        total++;
      }
      std::deque<int> finalSolution = queens;
  
      while(!solutions -> push(finalSolution)){
        std::deque<int> solution;
        bool successSolution = solutions -> pop(&solution);
        if(successSolution)
          utils::sendSolutionToFile(solution);
      }
      return 1;
    }
    if(type == 1 && !solutions -> isEmptyOfData())
      return 1;
    for(int i = 0; i < n; i++) { 
        if(!isEatable(row,i,queens)) {
          if(solve(n, row + 1, queens, solutions, type)) {
              queens.pop_back();//return here to end in the first solution
              if(type == 1 && !solutions -> isEmptyOfData())
                return 1;
              continue;
          }
          else queens.pop_back();
        }
    }
    return 0;
  }

  void simple_tokenizer(std::string s, std::vector<std::string> &pos) {
    std::stringstream ss(s);
    std::string word;
    while (ss >> word)
        pos.push_back(word);
    pos.erase(pos.begin());
  }

  void generateDOTFile(std::string positions) {
    std::ofstream dotfile;
    dotfile.open("solution.dot", std::ios::out);
    std::string sol;
    std::vector<std::string> pos;
    for(size_t i = 0; i < positions.size(); ++i) {  
        if(positions[i] == '\n')
            break;
        else
            sol.push_back(positions[i]); 
    }

    simple_tokenizer(sol, pos);

    dotfile << "digraph D {\n"; 
    dotfile << "\tnode [shape=plaintext]\n";
    dotfile << "\tsome_node [\n";
    dotfile << "\tlabel=<\n";
    dotfile << "\t\t<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">\n";

    for(int i = 0; i < pos.size(); ++i) {
        dotfile << "\t\t\t<tr>";
        for(int j = 0; j < pos.size(); ++j) {
            if(std::to_string(j) == pos[i])
                dotfile << "<td>&#9813; </td>";
            else
                dotfile << "<td> </td>";
        }
        dotfile << "</tr>\n";
    }
    dotfile << "\t\t</table>>\n";
    dotfile << "\t];\n";
    dotfile << "}";
    dotfile.close();
  }
  std::string realPos(int n){
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

  std::string inverse(std::string values, int& n){
    std::string answer = "";
    std::string number = "";
    for(int i = 0; i < values.size(); i++){
      if(values[i] != ' ')
        number += values[i];
      else{
        answer += std::to_string(n-(atoi(number.c_str())-1))+' ';
        number ="";
      }
    }
    return answer;
  }
  void solveBitWay(int ld, int col, int rd, int ex1, int ex2, int* done, std::string answer){

    if(col == *done){
      //TODO change done to a member class
      total++;
      std::cout << answer <<"\n";
      //TODO change n for a real number
      int n =5;
      std::cout << inverse(answer, n) <<"\n";
      return;
    }
    int pos = ~(ld|rd|col|ex1) & *done;
    while(pos){
      int bit = pos & -pos;
      pos ^= bit;
      solveBitWay((ld|bit)>>1, col|bit, (rd|bit)<<1, ex2, 0, done, answer + realPos(bit)+' ');
      ex2 = 0;
    }

  }
}