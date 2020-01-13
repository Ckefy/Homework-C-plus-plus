#pragma once

#include <vector>
#include <functional>
#include <algorithm>
#include <bits/stdc++.h>
#include "binary_search_deluxe.h"

int binary_search_deluxe::first_index_of(std::vector <term> &givenArray, term key, std::function <bool(const term &first, const term &second)> funcComp){
    auto found = lower_bound(givenArray.begin(), givenArray.end(), key, funcComp);
    if (found == givenArray.end()){
        return -1;
    } //if we didn`t find need one and they`re all less
    int answer = std::distance(givenArray.begin(), found);
    return answer;
}

int binary_search_deluxe::last_index_of(std::vector <term> &givenArray, term key, std::function <bool(const term &first, const term &second)> funcComp){
    auto found = upper_bound(givenArray.begin(), givenArray.end(), key, funcComp);
    int answer = std::distance(givenArray.begin(), found);
    answer--;
    return answer;
}
