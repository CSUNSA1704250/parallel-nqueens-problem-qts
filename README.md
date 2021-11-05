#Name
Jefferson Flores Herrera
Brian Pinto Medina

#Compile
g++ include/queue.hpp src/consumer.cpp src/nqueen.cpp src/producer.cpp src/utils.cpp main.cpp -lpthread -o main

#Run
./main -problemType [all, find] -N <sizeOfProblem>