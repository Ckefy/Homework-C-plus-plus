#include <iostream>
#include "my_deque.hpp"

void test(){
    std::cout<<"Let`s check methods with different size"<<std::endl<<std::endl;
    my_deque <int> deq;
    for (int i = 0; i < 11; i+=2){
        std::cout<<"CURRENT SIZE: "<<i<<std::endl;
        for (int j = 0; j < i; j++){
            deq.push_front(j);
        }
        if (!deq.empty()){
            std::cout<<"Push_front and empty work fine"<<std::endl;
        }
        for (int j = 0; j < i; j++){
            deq.push_back(j);
        }
        if (!deq.empty()){
            std::cout<<"Push_back and empty work fine"<<std::endl;
        }
        std::cout<<"FRONT"<<' '<<deq.front()<<std::endl;
        std::cout<<"BACK"<<' '<<deq.back()<<std::endl;
        std::cout<<"SIZE"<<' '<<deq.size()<<std::endl;
        for (int j = 0; j < i; j++){
            deq.pop_back();
            deq.pop_front();
        }
        if (deq.empty()){
            std::cout<<"Pop_back and pop_front work fine"<<std::endl;
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"Now let`s use some doubles and iterators"<<std::endl;
    my_deque <double> deq2;
    for (int i = 0; i < 10; i++){
        deq2.push_back(double(i) - 0.5);
    }
    for (my_deque <double>::iterator it = deq2.begin(); it != deq2.end(); it++){
        std::cout<<*it<<std::endl;
    }
    std::cout<<"If u see ten non-integer numbers - all work fine"<<std::endl<<std::endl;
    std::cout<<"TESTS FINISHED FINE"<<std::endl;
    std::cout<<"+++++++____--__-_-_+=__=-=-_+=_=______=+++++++";
}

int main() {
   test();
}
