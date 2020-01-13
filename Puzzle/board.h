#pragma once

#include <string>
#include <vector>

struct board {
    board();  //non-parameters constructor

    ~board(); //destructor

    explicit board(const std::vector <std::vector <int>> &givenArray); //explicit constructor which take board

    explicit board(int givenSize);  //explicit constructor which take size and init random board this size

    board(const board &givenBoard); //default constructor

    int size() const; //method returns the size of the board, can`t change object`s poles

    int hamming() const; //method returns the count of unordered blocks

    int manhattan() const; //method returns summary of Manhattan distance between blocks and goal

    bool is_goal() const; //check if current board is the goal

    bool is_solvable() const; //check if current board have any solution

    //Let`s make operators as friends to have the access to private poles
    //So we can initialize them not in the class

    friend bool operator==(const board &first, const board &second);

    friend bool operator!=(const board &first, const board &second);

    friend bool operator<(const board &first, const board &second);

    friend bool operator>(const board &first, const board &second);

    friend std::ostream &operator<<(std::ostream &output, const board &current); //output operator to represent board as a text

    std::string to_string() const;

    //Some helpful methods/operators

    const std::vector<int> &operator[](int ind) const; //operator which helps us to get access in board like in vector

    board &operator=(const board &givenBoard);

    std::pair<int, int> current_emptiness() const;

    std::vector<std::vector<int>> current_goal() const;

    std::vector<std::vector<int>> current_board() const;

private:
    void find_emptiness();
    void initialize();
    std::vector<std::vector<int>> b, goal; //first and solved boards
    std::pair<int, int> emptiness; //the block where`s no number
    int boardSize; //size of the board
};
