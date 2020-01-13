#pragma once

#include "board.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>

struct solver{
    explicit solver(const board &givenBoard); //explicit constructor with board to solve

    solver(const solver &givenSolver); //default constructor

    ~solver();

    int moves() const; //how many moves to solve

    struct iterator {

        iterator (std::vector <board>::iterator begin, int sizeVect, bool finish);

        iterator (const iterator &givenIterator);

        iterator() = default;

        ~iterator() = default;

        iterator operator++(int);

        iterator operator--(int);

        iterator &operator++();

        iterator &operator--();

        iterator &operator=(const iterator &givenIterator);

        bool operator==(const iterator &givenIterator);

        bool operator!=(const iterator &givenIterator);

        board operator*();

    private:
        int itSizeVect = 0;

        int itIndex = 0;

        std::vector <board>::iterator itBegin;
    };

    iterator begin();

    iterator end();

    solver &operator=(const solver &givenSolver);

  private:

    board start, goal;

    std::vector<board> chain; //chain of boards from start to goal

     struct hasherFunc{
        int operator()(const board &givenBoard) const;
    };

    struct equalFunc{
        bool operator()(const board &first, const board &second) const;
    };

    std::unordered_map<board, board, hasherFunc, equalFunc> p; //hassherFunc - hash keys, equalFunc - check if keys are equal

    void current_parents();

    void solve();

    bool onBoard(int newRow, int newCol) const;  //check if the point is on the board

    std::vector<std::pair<int, int>> shifts; //shifts to neighbors

    struct comparator{ //distance and the board
        bool operator()(const std::pair<int, board> &first, const std::pair<int, board> &second) const;
    };
};
