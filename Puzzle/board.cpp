#include "board.h"

#include <time.h>
#include <algorithm>
#include <iostream>
#include <random>
#define mp std::make_pair
#define pb push_back

board::board(){
    boardSize = 0;
}  //non-parameters constructor

board::~board(){
    b.clear();
    goal.clear();
} //destructor

board::board(const std::vector <std::vector <int>> &givenArray){
    boardSize = givenArray.size();
    b = givenArray; //current board;
    initialize();
    find_emptiness();
} //explicit constructor which take board

board::board(int givenSize){
    boardSize = givenSize;
    int boardSizeSqr = boardSize * boardSize;
    b.resize(boardSize, std::vector <int> (boardSize));
    std::vector <int> temporary (boardSizeSqr);
    initialize();
    for (int i = 0; i < boardSizeSqr; i++){
        temporary[i] = i;
    }
    std::shuffle (temporary.begin(), temporary.end(), std::mt19937(std::random_device()()));
    for (int i = 0; i < boardSizeSqr; i++){
        int row = i / boardSize;
        int col = i % boardSize;
        b[row][col] = temporary[i];
        if (b[row][col] == 0){
            emptiness = mp(row, col);
        }
    }
}  //explicit constructor which take size and init random board this size

board::board(const board &givenBoard) = default; //default constructor

int board::size() const{
    return boardSize;
} //method returns the size of the board, can`t change object`s poles

int board::hamming() const{
    int currentDist = 0;
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            if (b[i][j] == goal[i][j]){
                continue;
            }
            currentDist++;
        }
    }
    return currentDist;
} //method returns the count of unordered blocks

int board::manhattan() const{
    int currentDist = 0;
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            int row; //where it must be
            int col; //where it must be
            if (b[i][j] != 0){
                row = (b[i][j] - 1) / boardSize;
                col = (b[i][j] - 1) % boardSize;;
            } else {
                row = boardSize - 1;
                col = boardSize - 1;
            }
            int dx = abs(row - i);
            int dy = abs(col - j);
            currentDist += (dx + dy);
        }
    }
    return currentDist;
} //method returns summary of Manhattan distance between blocks and goal
//Manhattan distance == summary of subtraction point`s current coordinations and needed

bool board::is_goal() const{
    return (b == goal);
} //check if current board is the goal

bool board::is_solvable() const{
    int counter = 0; //number of inverses
    std::vector <int> temporary;
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            temporary.pb(b[i][j]);
        }
    }
    for (int i = 0; i < temporary.size(); i++){
        if (temporary[i] != 0){
            for (int j = 0; j < temporary.size(); j++){
                if (temporary[i] < temporary[j] && i > j){
                    counter++;
                }
            }
        } else {
            counter += (1 + i / boardSize); //number of row with emptiness
        }
    }
    bool isEven = (counter & 1 ? false : true); //if counter is an even number than it`s got a solution
    return isEven;
} //check if current board have any solution

//Let`s make operators as friends to have the access to private poles
//So we can initialize them not in the class

bool operator==(const board &first, const board &second){
    return first.b == second.b;
}

bool operator!=(const board &first, const board &second){
    return first.b != second.b;
}

bool operator<(const board &first, const board &second){
    return first.b < second.b;
}

bool operator>(const board &first, const board &second){
    return first.b > second.b;
}

std::ostream &operator<<(std::ostream &output, const board &current){
    output << current.to_string();
    return output;
} //output operator to represent board as a text

std::string board::to_string() const{
    std::string toString;
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            toString += std::to_string(b[i][j]);
            toString += ' ';
        }
        toString[toString.size() - 1] = '\n';
    }
   return toString;
}

//Some helpful methods/operators

void board::find_emptiness(){
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            if (b[i][j] == 0){
                emptiness = {i, j};
                return;
            }
        }
    }
}

void board::initialize(){
    goal.resize(boardSize, std::vector <int>(boardSize));
    for (int i = 0; i < boardSize * boardSize; i++){
        int row = i / boardSize;
        int col = i % boardSize;
        goal[row][col] = i + 1;
    }
    goal[boardSize - 1][boardSize - 1] = 0;
}

const std::vector<int> &board::operator[](int ind) const{
    return b[ind];
} //operator which helps us to get access in board like in vector

board &board::operator=(const board &givenBoard) = default;

std::pair<int, int> board::current_emptiness() const{
    return emptiness;
}

std::vector<std::vector<int>> board::current_goal() const{
    return goal;
}

std::vector<std::vector<int>> board::current_board() const{
    return b;
}
