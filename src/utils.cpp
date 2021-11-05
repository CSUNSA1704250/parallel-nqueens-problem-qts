#include "../include/utils.hpp"
#include <thread>
#include <iostream>
#include <mutex>
#include <fstream>
#include <sstream>

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
}