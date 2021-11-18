#ifndef CONSUMER_HPP
#define CONSUMER_HPP
#include "queue.hpp"
#include "nqueen.hpp"
#include <deque>

class Consumer{
  public:
    Consumer(Queue<int>*, NQueen*);
    void consumeData(bool);
  private:
    Queue<int>* dataConsumed;
    NQueen* queenProblem;
};

#endif