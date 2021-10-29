#include <iostream>
#include <deque>
#include <fstream>
#include <string>

int total = 0;
bool isEatable(int row, int column, std::deque<int> &queens) {
    for(int i = 0; i < queens.size(); i++) {
        if(row == i) return true;
        if(column == queens[i]) return true;
        if(i - queens[i] == row - column) return true;
        if(i + queens[i] == row + column) return true;
    }
    queens.push_back(column);
    return false;
}

int solve(int n, int row, std::deque<int> &queens, std::string &positions) {

    if(queens.size() == n) {
        positions = positions + std::to_string(total + 1) + " ";
        for(auto i: queens)
            positions = positions + std::to_string(i) + " ";
        positions = positions + "\n";
        total++;
        return 1;
    }

    #pragma omp paralel if(queens)
    #pragma omp task shared(queens, positions)
    for(int i = 0; i < n; i++) { 
        if(!isEatable(row,i,queens)) {
            if(solve(n, row + 1, queens, positions)) {
                queens.pop_back();//return here to end in the first solution
                continue;
            }
            else queens.pop_back();
        }
    }
    #pragma omp taskwait
    return 0;
}

void printSolutions(std::string positions, int nQueens) {
    std::ofstream output;
    output.open("solutions.txt", std::ios::out);
    output << "___________________________________________\n";
    output << "BEGIN FILE solutions.txt\n";
    output << "___________________________________________\n";
    output << "#Solutions for " << nQueens << " queens\n";
    output << total;
    output << "\n" + positions;
    output << "___________________________________________\n";
    output << "END FILE solutions.txt\n";
    output << "___________________________________________\n";
    output.close();
}

int main(int argc, char **argv) {   
    std::string n;
    if (argc > 1)
        n = argv[1];
    int ROW = 0;
    int nQueens = atoi(n.c_str());
    std::deque<int> queens;
    std::string positions;
    #pragma omp parallel
    #pragma omp single
    solve(nQueens, ROW, queens, positions);
    printSolutions(positions, nQueens);
    return 0;
}