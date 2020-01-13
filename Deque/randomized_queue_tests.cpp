#include <iostream>
#include "randomized_queue.h"

void test(){
    std::cout<<"Let`s check methods with different size"<<std::endl<<std::endl;
    randomized_queue <int> que;
    for (int i = 2; i < 11; i+=2){
        std::cout<<"CURRENT SIZE: "<<i<<std::endl;
        for (int j = 0; j < i; j++){
            que.enqueue(j);
        }
        if (!que.empty()){
            std::cout<<"Enqueue and empty work fine"<<std::endl;
        }
        std::cout<<"SAMPLE"<<' '<<que.sample()<<std::endl;
        std::cout<<"SIZE"<<' '<<que.size()<<std::endl;
        for (int j = 0; j < i; j++){
            int temporary = que.dequeue();
            std::cout<<temporary<<' ';
        }
        std::cout<<std::endl;
        if (que.empty()){
            std::cout<<"Dequeue works fine"<<std::endl;
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"Now let`s use some doubles and iterators"<<std::endl;
    randomized_queue <double> que2;
    for (int i = 0; i < 10; i++){
        que2.enqueue(double(i) - 0.5);
    }

    auto it = que2.begin();
    for (; it != que2.end(); it++){
        std::cout<<*it<<' ';
    }
    std::cout<<std::endl<<std::endl;
    std::cout<<"If u see ten non-integer numbers - all work fine"<<std::endl<<std::endl;
    std::cout<<"TESTS FINISHED FINE"<<std::endl;
    std::cout<<"+++++++____--__-_-_+=__=-=-_+=_=______=+++++++";
}

int main() {
    test();
}
