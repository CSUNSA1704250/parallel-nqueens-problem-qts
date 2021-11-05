#include "../include/utils.hpp"
#include <thread>
#include <iostream>
#include <mutex>
#include <fstream>

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
  
  int solve(int n, int row, std::deque<int> &queens, Queue<std::deque<int>>* solutions) {
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
    for(int i = 0; i < n; i++) { 
        if(!isEatable(row,i,queens)) {
          if(solve(n, row + 1, queens, solutions)) {
              queens.pop_back();//return here to end in the first solution
              continue;
          }
          else queens.pop_back();
        }
    }
    return 0;
  }
}