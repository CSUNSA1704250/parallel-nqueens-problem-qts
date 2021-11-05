#ifndef UTILS_HPP
#define UTILS_HPP

#include <deque>
#include "queue.hpp"
#include <vector>
#include <string>

namespace utils{
  int getTotalThreads(int);
  bool isEatable(int,int,std::deque<int>&);
  int solve(int , int , std::deque<int> &, Queue<std::deque<int>>*, int type);
  void sendSolutionToFile(std::deque<int> &);
  int getTotal();
}
#endif