#include <iostream>
#include "autocomplete.h"

void test() {
    std::cout<<"++++=====______---_---_---******_+++++"<<std::endl<<std::endl;
    std::cout<<"CONSTRUCTORS"<<std::endl;
    term initTerm("best wishes!", 666);
    term fromTerm(initTerm);
    term copyTerm = initTerm;
    std::cout<<"If you see equal terms, constructors work fine"<<std::endl;
    std::cout<<"If you see terms, than ostream works fine"<<std::endl;
    std::cout<<initTerm<<' '<<fromTerm<<' '<<copyTerm<<std::endl;


    std::cout<<std::endl<<"++++=====______---_---_---******_+++++"<<std::endl<<std::endl;
    std::cout<<"OPERATORS"<<std::endl;
    term firstEqualTerm ("first", 228), secondEqualTerm ("first", 666);
    if (firstEqualTerm == secondEqualTerm) {
        std::cout<<firstEqualTerm<<' '<<"=="<<' '<<secondEqualTerm<<std::endl;
    }
    if (firstEqualTerm <= secondEqualTerm) {
      std::cout<<firstEqualTerm<<' '<<"<="<<' '<<secondEqualTerm<<std::endl;
    }
    if (firstEqualTerm < secondEqualTerm) {
        std::cout<<"That`s not true, may be it`s just a bug, move along"<<std::endl;
    } else {
        if (term("first", 5) < term("second", 5)){
            std::cout<<term("first", 5)<<' '<<"<"<<' '<<term ("second", 6)<<std::endl;
        }
    }
    if (firstEqualTerm >= secondEqualTerm) {
        std::cout<<firstEqualTerm<<' '<<">="<<' '<<secondEqualTerm<<std::endl;
    }
    if (firstEqualTerm > secondEqualTerm) {
        std::cout<<"That`s not true, may be it`s just a bug, move along"<<std::endl;
    } else {
        if (term("second", 5) > term("first", 6)){
        std::cout<<term("second", 5)<<' '<<">"<<' '<<term ("first", 6)<<std::endl;
        }
    }
    if (term("first", 5) != term("second", 5)){
        std::cout<<term("first", 5)<< "!= "<<term("second", 5)<<std::endl;
    }

    std::cout<<std::endl<<"++++=====______---_---_---******_+++++"<<std::endl<<std::endl;
    std::cout<<"METHODS"<<std::endl;
    std::cout<<"Method to_string"<<std::endl;
    term toStringTerm ("toStringTerm", 5);
    std::cout<<toStringTerm.to_string()<<std::endl;
    std::cout<<"By prefix_order"<<std::endl;
    auto cmp = term::by_prefix_order(4);
    term first("bestness", 32), second("best", 4);
    if (!cmp(first, second)) {
            std::cout <<second<<" < "<<first<<" by prefix 4"<<std::endl;
    }
    std::cout<<"By reverse_order"<<std::endl;
    auto comp = term::by_reverse_weight_order();
    if (comp(first, second)) {
            std::cout <<second<<" < "<<first<<" by reverse"<<std::endl;
    }

    std::cout<<std::endl<<"++++=====______---_---_---******_+++++"<<std::endl<<std::endl;
    std::cout<<"BINARY SEARCH DELUX"<<std::endl;
    std::vector <term> mas {
        {"etop", 5},
        {"mu", 4},
        {"r", 55},
        {"top", 56},
        {"topest", 5555},
        {"topic", 5858},
    };
    for (int i = 0; i < mas.size(); i++){
        std::cout<<mas[i]<<std::endl;
    }
    int firstPlace = binary_search_deluxe::first_index_of(mas, term("top", 555), term::by_prefix_order(3));
    int lastPlace = binary_search_deluxe::last_index_of(mas, term("top", 555), term::by_prefix_order(3));
    std::cout<<"For prefix \"top\""<<std::endl;
    std::cout<<"firstPlace = "<<firstPlace<<std::endl;
    std::cout<<"lastPlace = "<<lastPlace<<std::endl;

    int firstPlace2 = binary_search_deluxe::first_index_of(mas, term("tope", 555), term::by_prefix_order(4));
    int lastPlace2 = binary_search_deluxe::last_index_of(mas, term("tope", 555), term::by_prefix_order(4));
    std::cout<<"For prefix \"tope\""<<std::endl;
    std::cout<<"firstPlace = "<<firstPlace2<<std::endl;
    std::cout<<"lastPlace = "<<lastPlace2<<std::endl;


    std::cout<<std::endl<<"++++=====______---_---_---******_+++++"<<std::endl<<std::endl;
    std::cout<<"AUTOCOMPLETE"<<std::endl;
    autocomplete qwerty(mas);

    std::cout<<"All match prefix \"top\":"<<std::endl;
    std::vector<term> newMas = qwerty.all_matches("top");
    for (int i = 0; i < newMas.size(); i++){
        std::cout<<newMas[i]<<std::endl;
    }
    std::cout<<std::endl;

    std::cout<<"All match prefix \"ogo\":"<<std::endl;
    std::vector<term> newMas2 = qwerty.all_matches("ogo");
    for (int i = 0; i < newMas2.size(); i++){
        std::cout<<newMas2[i]<<std::endl;
    }
    std::cout<<std::endl;

    std::cout<<"Number of words match prefix \"top\""<<std::endl;
    std::cout<<qwerty.number_of_matches("top")<<std::endl;

    std::cout<<std::endl;

    std::cout<<"Number of words match prefix \"ogo\""<<std::endl;
    std::cout<<qwerty.number_of_matches("ogo")<<std::endl;
}

int main() {
    test();
}
