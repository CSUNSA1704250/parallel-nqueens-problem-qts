#include "../include/producer.hpp"
#include "../include/consumer.hpp"
#include "../include/utils.hpp"

Producer::Producer(NQueen* queenProblem_, Queue<std::deque<int>>* dataProduced_):
queenProblem{queenProblem_},
dataProduced{dataProduced_},
producing{true}{
  totalHW = utils::getTotalThreads(queenProblem -> getN());
  {
    std::unique_lock<std::mutex> lock(producers_mutex);
    producers.push_back(this);
  }
}

bool Producer::checkProducersState(){
  std::unique_lock<std::mutex> lock(producers_mutex);
  for(auto& producer: producers){
    if(producer -> producing)
      return true;
  }
  return false;
}

void Producer::produceData(int id){
  while(producers.size() < totalHW);
  Consumer consumer(dataProduced, queenProblem);
  for(int i = id; i < queenProblem -> getN(); i += totalHW){
    std::deque<int> currentQueens; currentQueens.push_back(i);
    //push data to dataProduced 
    while(!dataProduced -> push(currentQueens)){
      //if dataProduced is full, start consuming data
      consumer.consumeData(true);
    }
  }
  producing = false;
  //if all producers finished production set production to false
  if(!checkProducersState()) dataProduced -> setProductionState(false);
  //after production start consuming data
  consumer.consumeData(false);
  return;
}