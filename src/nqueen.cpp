#include "../include/nqueen.hpp"
#include "../include/producer.hpp"
#include "../include/queue.hpp"
#include "../include/utils.hpp"
#include <thread>

NQueen::NQueen(int n_, int type_):
n{n_},
type{type_}{
  totalHW = utils::getTotalThreads(n);
  solutions = new Queue<std::deque<int>> (totalHW);
}
NQueen::~NQueen(){
  delete solutions;
}
void NQueen::solve(){
  std::vector<std::thread> threadPool;
  threadPool.reserve(totalHW);
  std::vector<Producer *> producers;
  Queue<std::deque<int>>* dataToBeConsumed = new Queue<std::deque<int>> (totalHW);//TODO change int for the real type of data that will be consumed

  for(int i = 0; i < totalHW; i++){
    Producer* producer = new Producer(this, dataToBeConsumed);//send queue where producers will have their work and solutions queue to reduce data
    threadPool.emplace_back(&Producer::produceData, producer, i);
  }

  for(int i = 0; i < totalHW; i++){
    threadPool[i].join();
  }

  delete dataToBeConsumed;
  std::cout << utils::getTotal();
  
  return;
}