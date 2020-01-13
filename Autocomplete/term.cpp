#pragma once
#include "term.h"

#include <vector>
#include <functional>

term::term(std::string givenString, int givenWeight) : weight(givenWeight), str(std::move(givenString)) {}

term::term(const term &givenTerm) = default; //default constructor;

term::term() = default;

bool operator==(const term &first, const term &second){
    return first.str == second.str;
}

bool operator!=(const term &first, const term &second){
    return first.str != second.str;
}

bool operator<(const term &first, const term &second){
    return first.str < second.str;
}

bool operator<=(const term &first, const term &second){
    return first.str <= second.str;
}

bool operator>(const term &first, const term &second){
    return first.str > second.str;
}

bool operator>=(const term &first, const term &second){
    return first.str >= second.str;
}

std::string term::to_string() const{
    std::string toString;
    toString += std::to_string(weight);
    toString += ' ';
    toString += str;
    return toString;
}

std::ostream &operator<<(std::ostream &output, const term &current){
    output << current.to_string();
    return output;
}

term &term::operator=(const term &givenTerm) = default;

////Functors

std::function <bool(const term &first, const term &second)> term::by_reverse_weight_order(){
    return [](const term &first, const term &second){
            return first.weight > second.weight;
        };
}

std::function <bool(const term &first, const term &second)> term::by_prefix_order(const int r){
    return [r](const term &first, const term &second){
        for (int i = 0; i < r; i++){
            if (first.str.length() == i){
                return true;
            }
            if (second.str.length() == i){
                return false;
            }
            if (first.str[i] == second.str[i]){
                continue;
            }
            return first.str[i] < second.str[i];
        }
        return false; //SUBSTRING MAYBE
    };
}
