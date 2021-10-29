#include <iostream>
#include <deque>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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

void simple_tokenizer(std::string s, std::vector<std::string> &pos) {
    std::stringstream ss(s);
    std::string word;
    while (ss >> word)
        pos.push_back(word);
    pos.erase(pos.begin());
}

void generateDOTFile(std::string positions) {
    std::ofstream dotfile;
    dotfile.open("solution.dot", std::ios::out);
    std::string sol;
    std::vector<std::string> pos;
    for(size_t i = 0; i < positions.size(); ++i) {  
        if(positions[i] == '\n')
            break;
        else
            sol.push_back(positions[i]); 
    }

    simple_tokenizer(sol, pos);

    dotfile << "digraph D {\n"; 
    dotfile << "\tnode [shape=plaintext]\n";
    dotfile << "\tsome_node [\n";
    dotfile << "\tlabel=<\n";
    dotfile << "\t\t<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">\n";

    for(int i = 0; i < pos.size(); ++i) {
        dotfile << "\t\t\t<tr>";
        for(int j = 0; j < pos.size(); ++j) {
            if(std::to_string(j) == pos[i])
                dotfile << "<td>&#9813; </td>";
            else
                dotfile << "<td> </td>";
        }
        dotfile << "</tr>\n";
    }
    dotfile << "\t\t</table>>\n";
    dotfile << "\t];\n";
    dotfile << "}";
    dotfile.close();
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
    generateDOTFile(positions);
    return 0;
}