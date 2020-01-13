#pragma once

#include "term.h"
#include <vector>
#include <functional>

struct binary_search_deluxe{

    binary_search_deluxe() = delete;

    static int first_index_of(std::vector<term> &givenArray, term key, std::function <bool(const term &first, const term &second)> funcComp);

    static int last_index_of(std::vector<term> &givenArray, term key, std::function <bool(const term &first, const term &second)> funcComp);
};
