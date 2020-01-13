#pragma once

#include <vector>
#include "binary_search_deluxe.h"

struct autocomplete{
    explicit autocomplete (std::vector <term> givenArray);

    ~autocomplete();

    std::vector <term> all_matches (std::string prefix);

    int number_of_matches (std::string prefix);

private:
    std::vector <term> currentArray;
};
