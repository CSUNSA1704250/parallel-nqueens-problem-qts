[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=6136219&assignment_repo_type=AssignmentRepo)

#Compile using
g++ include/queue.hpp src/consumer.cpp src/nqueen.cpp src/producer.cpp src/utils.cpp main.cpp -lpthread -o main

#Run
./main -problemType [all, find] -N <sizeOfProblem>