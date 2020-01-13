#pragma once

#include<vector>
#include<algorithm>
#include "autocomplete.h"

autocomplete::autocomplete(std::vector <term> givenArray){
    currentArray = givenArray;
    stable_sort (currentArray.begin(), currentArray.end());
}

autocomplete::~autocomplete(){
    currentArray.clear();
}

std::vector <term> autocomplete::all_matches(std::string prefix){
    term key = term(prefix, 0);
    std::vector <term> answer;
    int firstPlace = binary_search_deluxe::first_index_of (currentArray, key, term::by_prefix_order(prefix.length()));
    if (firstPlace == -1){
        //there`re no words with such a prefix and they`re all less
        return answer;
    }
    //if they`re all greater, then first > last will be
    int lastPlace = binary_search_deluxe::last_index_of (currentArray, key, term::by_prefix_order(prefix.length()));
    for (int i = firstPlace; i <= lastPlace; i++){
        answer.push_back(currentArray[i]);
    }
    stable_sort(answer.begin(), answer.end(), term::by_reverse_weight_order());
    return answer;
}

int autocomplete::number_of_matches(std::string prefix){
    term key = term(prefix, 0);
    int answer = 0;
    int firstPlace = binary_search_deluxe::first_index_of (currentArray, key, term::by_prefix_order(prefix.length()));
    if (firstPlace == -1){
        //there`re no words with such a prefix
        return answer;
    }
    int lastPlace = binary_search_deluxe::last_index_of (currentArray, key, term::by_prefix_order(prefix.length()));
    if (lastPlace < firstPlace){
        return 0; //if there`s no such word
    }
    answer = lastPlace - firstPlace + 1;
    return answer;
}

