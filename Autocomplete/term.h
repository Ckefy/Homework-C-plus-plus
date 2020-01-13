#pragma once

#include <vector>
#include <functional>

struct term {
    term(std::string givenString, int givenWeight);

    term(const term &givenTerm);

    term();

    friend bool operator==(const term &first, const term &second);

    friend bool operator!=(const term &first, const term &second);

    friend bool operator<(const term &first, const term &second);

    friend bool operator<=(const term &first, const term &second);

    friend bool operator>(const term &first, const term &second);

    friend bool operator>=(const term &first, const term &second);

    std::string to_string() const;

    friend std::ostream &operator<<(std::ostream &output, const term &current);

    //Some helpful methods/operators

    term &operator=(const term &givenTerm);

    ////Functors

    static std::function <bool(const term &first, const term &second)> by_reverse_weight_order();

    static std::function <bool(const term &first, const term &second)> by_prefix_order(const int r);

private:
    std::string str; //string value of the term
    int weight; //weight of the term
};
