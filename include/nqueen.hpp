#ifndef NQUEEN_HPP
#define NQUEEN_HPP
#include "queue.hpp"
#include <deque>
class NQueen{
  public:
    NQueen(int);
    ~NQueen();
    void solve();
    int getN(){return n;}
    Queue<std::deque<int>>* getSolutionsQueue(){return solutions;}
  private:
    int n;
    int totalHW;
    Queue<std::deque<int>>* solutions;
};
#endif