#include <iostream>
#include "solver.h"
#include <vector>
#include <random>

using namespace std;

int main() {
/*vector<vector<vector<int>>> test = {{{1, 2, 3, 4},
                                                     {5, 6, 7, 8},
                                                     {9, 10, 11, 12},
                                                     {13, 14, 0,  15}},

                                             {{1, 2, 3, 4},
                                                     {5, 6, 7, 8},
                                                     {9, 10, 11, 12},
                                                     {13, 14, 15, 0}},

                                             {{1, 2, 3, 4},
                                                     {0, 5, 6, 7},
                                                     {9, 10, 11, 8},
                                                     {13, 14, 15, 12}},

                                             {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                                             {11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
                                             {21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
                                             {31, 32, 33, 34, 35, 36, 37, 38, 39, 40},
                                             {41, 42, 43, 44, 45, 46, 47, 48, 49, 50},
                                             {51, 52, 53, 54, 55, 56, 57, 58, 59, 60},
                                             {61, 62, 63, 64, 65, 66, 67, 68, 69, 70},
                                             {71, 72, 73, 74, 75, 76, 77, 78, 79, 80},
                                             {81, 82, 83, 84, 85, 86, 87, 88, 89, 90},
                                             {91, 92, 93, 94, 95, 96, 97, 98, 0, 99}}};


    for (const auto &i : test) {
        cout << "TEST: " << endl;
        cout << "START BOARD : " << endl;
        for (const auto &j : i) {
            for (const auto &k : j) {
                    cout << k << " ";
            }
            cout << endl;
        }

        cout << endl;

        board b(i);
        solver s(b);

        cout << "moves = " << s.moves() << endl;
        for (const auto &it : s) {
            cout << it.to_string() << endl;
        }

        cout << "---------------------\n";
    }

    cout << "RANDOM TEST: \n";
    board b(4);
    cout << "START BOARD: \n" + b.to_string();
    solver s(b);
    cout << "moves = " << s.moves() << endl;
    for (const auto &it : s) {
        cout << it.to_string() << endl;
    }*/
    board hk = board({{4, 1}, {2, 3}});
    std::cout<<hk.is_solvable();

}
