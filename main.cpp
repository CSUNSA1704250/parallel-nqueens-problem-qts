#include "include/nqueen.hpp"
#include "include/producer.hpp"
#include <iostream>
#include <fstream>

std::mutex Producer::producers_mutex;
std::vector<Producer*> Producer::producers;
std::ofstream output;

int main(int argc, char **argv){

  std::string problemFlag = argv[1];
  std::string typeProblem = argv[2];
  std::string NFlag = argv[3];
  std::string n = argv[4];
  output.open("solutions.txt", std::ios::out);

  if(argc < 5)
      std::cout << "Wrong type of run see the exampl\n ./main -problemType[all,find] -N <sizeOfProblem>";
  else {
      if(NFlag.compare(std::string("-N")) != 0){
          std::cout << "Error con flag de tamanho\n";
          return -1;
      }

      if(problemFlag.compare(std::string("-problemType")) == 0){
          if(typeProblem.compare(std::string("all")) == 0){
              int nProblem = atoi(n.c_str());
              NQueen problem(nProblem,0);
              problem.solve();
          }

          else if(typeProblem.compare(std::string("find")) == 0){
              int nProblem = atoi(n.c_str());
              NQueen problem(nProblem,1);
              problem.solve();
          }
      }
	}
  
  output.close();
}