#ifndef PRODUCER_HPP
#define PRODUCER_HPP
#include "queue.hpp"
#include "nqueen.hpp"
#include <vector>
#include <deque>

class Producer{
  public:
    Producer(NQueen*, Queue<int>*);
    void produceData(int);
    bool isProducing(){return producing;}
    static std::vector<Producer*> producers;
    static std::mutex producers_mutex;
    bool checkProducersState();
  private:
    NQueen* queenProblem;
    Queue<int>* dataProduced;
    int totalHW;
    bool producing;
};

#endif