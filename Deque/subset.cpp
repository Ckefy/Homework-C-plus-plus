#include <iostream>
#include "randomized_queue.h"

int main (int argc, char **argv){
    randomized_queue <std::string> que;
    char *end;
    std::string readed;
    //simply put them in our randomized_queue and them pull them out
    while (std::getline(std::cin, readed)){
        que.enqueue(readed);
    }
    int counter = std::strtol(argv[1], &end, 10);
    for (int i = 0; i < counter; i++){
        std::cout<<que.dequeue()<<' ';
    }
}
