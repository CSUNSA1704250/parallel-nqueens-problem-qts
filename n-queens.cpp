#include <iostream>
#include <deque>

int total = 0;
bool isEatable(int row, int column, std::deque<int> &queens){
    for(int i = 0; i < queens.size(); i++){
        if(row == i) return true;
        if(column == queens[i]) return true;
        if(i - queens[i] == row - column) return true;
        if(i + queens[i] == row + column) return true;
    }
    queens.push_back(column);
    return false;
}

int solve(int n, int row, std::deque<int> &queens){
    if(queens.size() == n) {
        /*for(auto i: queens)
            std::cout << i <<" ";
        std::cout << std::endl;*/
        total ++;
        return 1;
    }
    for(int i = 0; i < n; i++){
        if(!isEatable(row,i,queens)){
            if(solve(n, row + 1, queens)) {
                queens.pop_back();//return here to end in the first solution
                continue;
            }
            else queens.pop_back();
        }
    }    
    return 0;
}

int main(int argc, char **argv) {
    
    std::string n;
    if (argc > 1)
        n = argv[1];
    int ROW = 0;
    int nQueens = atoi(n.c_str());
    std::deque<int> queens;
    solve(nQueens, ROW, queens);
    std::cout << total;
    return 0;
}