#ifndef UTILS_HPP
#define UTILS_HPP

#include <deque>
#include "queue.hpp"
#include "nqueen.hpp"
#include <vector>
#include <string>

namespace utils{
  int getTotalThreads(int);
  bool isEatable(int,int,std::deque<int>&);
  int solve(int , int , std::deque<int> &, Queue<std::deque<int>>*, int type);
  void solveBitWay(int , int , int , int , int , int* , std::string , NQueen* );
  void sendSolutionToFile(std::deque<int> &);
  void sendSolutionToFile(std::string);
  int getTotal();
  void simple_tokenizer(std::string s, std::vector<std::string> &);
  void generateDOTFile(std::string);
  std::string realPos(int);
}
#endif