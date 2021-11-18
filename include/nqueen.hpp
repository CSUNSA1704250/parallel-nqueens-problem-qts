#ifndef NQUEEN_HPP
#define NQUEEN_HPP
#include "queue.hpp"
#include <deque>
#include <string>
class NQueen{
  public:
    NQueen(int, int);
    ~NQueen();
    void solve();
    int getN(){return n;}
    Queue<std::string>* getSolutionsQueue(){return solutions;}
    int getType(){return type;}
  private:
    int n;
    int totalHW;
    Queue<std::string>* solutions;
    int type;
};
#endif