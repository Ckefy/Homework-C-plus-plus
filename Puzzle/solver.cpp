#include "solver.h"
#include <iostream>
#include <queue>
#include <algorithm>

#define pb push_back
#define eb emplace_back
#define mp std::make_pair

solver::solver(const board &givenBoard){
    start = givenBoard;
    shifts.pb(mp(0, 1));
    shifts.pb(mp(1, 0));
    shifts.pb(mp(0, -1));
    shifts.pb(mp(-1, 0));
    goal = board(givenBoard.current_goal());
    solve();
} //explicit constructor with board to solve

solver::solver(const solver &givenSolver) = default; //default constructor

solver::~solver(){
    chain.clear();
    p.clear();
}

int solver::moves() const{ //how many moves to solve
    if (chain.size() == 0){
        return 0;
    }
    return chain.size() - 1;
}

////
solver::iterator::iterator (std::vector <board>::iterator begin, int sizeVect, bool finish) :
    itBegin (begin), itSizeVect (sizeVect){
        itIndex = (finish ? sizeVect : 0);
    }

solver::iterator::iterator (const solver::iterator &givenIterator) :
    itBegin (givenIterator.itBegin), itSizeVect (givenIterator.itSizeVect), itIndex (givenIterator.itIndex){}

solver::iterator solver::begin(){
    iterator it(chain.begin(), chain.size(), false);
    return it;
}

solver::iterator solver::end(){
    iterator it(chain.begin(), chain.size(), true);
    return it;
}

solver::iterator solver::iterator::operator++(int){
    iterator answer(*this);
    itIndex++;
    return answer;
}

solver::iterator solver::iterator::operator--(int){
    iterator answer(*this);
    itIndex--;
    return answer;
}

solver::iterator &solver::iterator::operator++(){
    itIndex++;
    return *this;
}

solver::iterator &solver::iterator::operator--(){
    iterator answer(*this);
    itIndex--;
    return *this;
}

solver::iterator& solver::iterator::operator=(const solver::iterator &givenIterator){
    itBegin = givenIterator.itBegin;
    itSizeVect = givenIterator.itSizeVect;
    itIndex = givenIterator.itIndex;
}

bool solver::iterator::operator==(const solver::iterator &givenIterator){
    return (itBegin + itIndex) == (givenIterator.itBegin + givenIterator.itIndex);
}

bool solver::iterator::operator!=(const solver::iterator &givenIterator){
    return (itBegin + itIndex) != (givenIterator.itBegin + givenIterator.itIndex);
}

board solver::iterator::operator*(){
    return *(itBegin + itIndex);
}
////

solver &solver::operator=(const solver &givenSolver) = default; //default check on equality

void solver::current_parents(){
    board temporary = goal;
    while(temporary != start){
        chain.eb(temporary);
        temporary = p[temporary];
    }
    chain.eb(temporary);
    reverse(chain.begin(), chain.end());
}

bool solver::onBoard(int newRow, int newCol) const{
    if (newRow < start.size() && newCol < start.size()){
        if (newRow >= 0 && newCol >= 0){
            return true;
        }
    }
    return false;
} //check if the point is on the board

bool solver::equalFunc::operator()(const board &first, const board &second) const{
    if (first == second){
        return true;
    } else {
        return false;
    }
}

int solver::hasherFunc::operator()(const board &givenBoard) const{
    int curHash = 0;
    for (int i = 0; i < givenBoard.size(); i++){
        for (int j = 0; j < givenBoard.size(); j++){
            curHash += givenBoard[i][j] * (j * givenBoard.size() + i);
        }
    }
    return curHash;
};

bool solver::comparator::operator()(const std::pair<int, board> &first, const std::pair<int, board> &second) const{ //distance and the board
    return (first.first > second.first);
}

void solver::solve(){
    if (!start.is_solvable()){
        std::cout<<"Can`t solve it"<<std::endl;
        std::cout<<start.to_string()<<std::endl;
        return;
    }
    //valuable = hamming + manhattan
    std::unordered_set<board, hasherFunc> was;
    std::unordered_map<board, int, hasherFunc, equalFunc> valuable; //3 and 4 parameters are hash and equal check, second - valuable for tabke (1 arg)
    std::priority_queue<std::pair<int, board>, std::vector<std::pair<int, board>>, comparator> que; //valuable and table
    valuable[start] = 0;
    que.push(mp(0, start));
    while (!que.empty()){
        std::pair<int, board> now = que.top();
        que.pop();
        if (now.second.is_goal()){
            current_parents();
            return;
        }
        was.insert(now.second);
        std::pair<int, int> emptiness = now.second.current_emptiness();
        for (int i = 0; i < 4; i++){
            int newRow = shifts[i].first + emptiness.first;
            int newCol = shifts[i].second + emptiness.second;
            board newBoard = now.second;
            if (onBoard(newRow, newCol)){
                std::vector<std::vector<int>> temporary = newBoard.current_board();
                std::swap(temporary[emptiness.first][emptiness.second], temporary[newRow][newCol]);
                newBoard = board(temporary);
                int nowValue = now.first + newBoard.hamming() + newBoard.manhattan(); //previous + valuable;
                if (!valuable.count(newBoard)){
                    valuable[newBoard] = INT_MAX;
                }
                if (!was.count(newBoard) || nowValue < valuable[newBoard]){
                    p[newBoard] = now.second;
                    valuable[newBoard] = nowValue;
                    que.push(mp(nowValue, newBoard));
                }
            }
        }
    }
}
