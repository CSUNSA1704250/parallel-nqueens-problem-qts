#include "../include/consumer.hpp"
#include "../include/utils.hpp"

Consumer::Consumer(Queue<std::deque<int>>* dataConsumed_, NQueen* queenProblem_):
dataConsumed{dataConsumed_},
queenProblem{queenProblem_}{}

void Consumer::consumeData(bool stillProducing){
  std::deque<int> data;
  Queue<std::deque<int>> * solutions = queenProblem -> getSolutionsQueue();
  while(true){
    //for find 
    //check flag of queenProblem if its set to true
      //check if a solution has been found and set flag true
    //if both flags are true stop consuming
    bool success = dataConsumed -> pop(&data);
    bool productionStillRunning = dataConsumed -> isProductionRunning();
    if(!success && !solutions -> isEmptyOfData()){
      std::deque<int> solution;
      bool successSolution = solutions -> pop(&solution);
      if(successSolution)
        utils::sendSolutionToFile(solution);
      continue;
    }
    if(!success && !productionStillRunning){
      return;
    }
    if(success){
      //if data is available exec
      int nProblem = queenProblem -> getN();
      int nextRow = data.size();
      utils::solve(nProblem, nextRow, data, queenProblem -> getSolutionsQueue(), queenProblem -> getType());
      //data is still solvable from here
      if(stillProducing)
        return;
    }
  }
}