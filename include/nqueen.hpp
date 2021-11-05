#ifndef NQUEEN_HPP
#define NQUEEN_HPP
#include "queue.hpp"
#include <deque>
class NQueen{
  public:
    NQueen(int, int);
    ~NQueen();
    void solve();
    int getN(){return n;}
    Queue<std::deque<int>>* getSolutionsQueue(){return solutions;}
    int getType(){return type;}
  private:
    int n;
    int totalHW;
    Queue<std::deque<int>>* solutions;
    int type;
};
#endif