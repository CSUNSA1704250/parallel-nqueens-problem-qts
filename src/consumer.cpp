#include "../include/consumer.hpp"
#include "../include/utils.hpp"

Consumer::Consumer(Queue<int>* dataConsumed_, NQueen* queenProblem_):
dataConsumed{dataConsumed_},
queenProblem{queenProblem_}{}

void Consumer::consumeData(bool stillProducing){
  int data;
  //Queue<std::string> * solutions = queenProblem -> getSolutionsQueue();
  while(true){
    //for find 
    //check flag of queenProblem if its set to true
      //check if a solution has been found and set flag true
    //if both flags are true stop consuming
    bool success = dataConsumed -> pop(&data);
    bool productionStillRunning = dataConsumed -> isProductionRunning();
    /*if(!success && !solutions -> isEmptyOfData()){
      std::string solution;
      bool successSolution = solutions -> pop(&solution);
      if(successSolution)
        utils::sendSolutionToFile(solution);
      continue;
    }*/
    if(!success && !productionStillRunning){
      return;
    }
    if(success){
      //if data is available exec
      int nProblem = queenProblem -> getN();
      int done = (1<<nProblem) - 1;
      int exclusion = (1<<(nProblem/2)) - 1;
      int exclusion2;
      //utils::solve(nProblem, nextRow, data, queenProblem -> getSolutionsQueue(), queenProblem -> getType());
      int col = 0, ld = 0, rd = 0;
      int bit = 1<<data;
      std::string solutionstr = utils::realPos(bit) + " ";
      if(data == nProblem/2)
        exclusion2 = nProblem%2? exclusion : 0;
      else
        exclusion2 = 0;
      utils::solveBitWay((ld|bit)>>1, col|bit, (rd|bit)<<1, exclusion2, 0, &done, solutionstr, queenProblem);
      //data is still solvable from here
      if(stillProducing)
        return;
    }
  }
}