#pragma once

#include <vector>
#include <algorithm>
#include <random>
#define pb push_back

using RING = std::mt19937_64; //Random integer number generator

template<typename T>
struct randomized_queue{
    randomized_queue() = default;

    ~randomized_queue() = default;

    int size() const;

    T sample();

    void enqueue(const T &current);

    T dequeue();

    bool empty()  const;

    //Let`s copy iterator from my_deque but with little changes
    //Now, we don`t need to use two poles for size because size of vector == number of elements
    //But here`s one little change - because of definition of randomized_queue
    //We have to implement smth like random iterator - now we have special vector
    //With random order of indexes, itIndex now will contain the index in that vector
    //So it`ll be unordered with high chance
    //Because we need to get different queues (with high but not 100% chance) we`ll generate vector of indexes randomly

    struct iterator {
        using vecIt = typename std::vector <T>::iterator;

        iterator (vecIt begin, int sizeQue, bool finish);

        iterator() = default;

        ~iterator() = default;

        iterator (const iterator &givenIterator);

        iterator operator++(int);

        iterator &operator++();

        iterator &operator=(const iterator &givenIterator);

        bool operator==(const iterator &givenIterator);

        bool operator!=(const iterator &givenIterator);

        T &operator*();

    private:
        int itSizeQue = 0;

        int itIndex = 0;

        vecIt itBegin;

        void makeRandomIndexesMap();

        std::vector <int> randomIndexesMap;

    };

    iterator begin();

    iterator end();

private:
    static RING get_generator(); //make new RING, once in program

    RING currentRING = get_generator(); //that`s our current generator which we`ll use

    void changeLimits(); //to make distribution`s limits from 0 to size of queue

    std::uniform_int_distribution <int> limits;

    std::vector <T> que;
};

template<typename T>
int randomized_queue <T>::size() const{
    return que.size();
}

template<typename T>
T randomized_queue <T>::sample(){
    if (!empty()){
        int currentIndex = limits(currentRING); //received random integer number from 0 to size()
        return que[currentIndex];
    } else {
        std::cout<<"Can`t use sample with empty queue"<<std::endl;
    }
}

template<typename T>
void randomized_queue <T>::enqueue(const T &current){
    que.pb(current);
    //we need to increase right limit because of adding of the element
    changeLimits();
}

template<typename T>
T randomized_queue <T>::dequeue(){
    if (!empty()){
        int currentIndex = limits(currentRING);
        T temporary = que[currentIndex];
        std::swap(que[que.size() - 1], que[currentIndex]);
        que.pop_back();
        //we need to decrease right limit because of deleting of the element
        changeLimits();
        return temporary;
    } else {
        std::cout<<"Can`t use dequeue with empty queue"<<std::endl;
    }
}

template<typename T>
bool randomized_queue <T>::empty()  const{
    if (size() == 0){
        return true;
    } else {
        return false;
    }
}

//iterators

template<typename T>
randomized_queue <T>::iterator::iterator (vecIt begin, int sizeQue, bool finish) :
    itBegin (begin), itSizeQue (sizeQue){
        itIndex = (finish ? sizeQue : 0);
        makeRandomIndexesMap();
    }

template<typename T>
randomized_queue <T>::iterator::iterator (const randomized_queue::iterator &givenIterator) :
    itBegin (givenIterator.itBegin), itSizeQue (givenIterator.itSizeQue),
    randomIndexesMap (std::move(givenIterator.randomIndexesMap)), itIndex (givenIterator.itIndex){}

template<typename T>
typename randomized_queue <T>::iterator randomized_queue <T>::begin(){
    iterator it(que.begin(), size(), false);
    return it;
}

template <typename T>
void randomized_queue <T>::iterator::makeRandomIndexesMap(){
    randomIndexesMap.resize(itSizeQue);
    for (int i = 0; i < itSizeQue; i++){
        randomIndexesMap[i] = i;
    }
    std::shuffle(randomIndexesMap.begin(), randomIndexesMap.end(), RING(std::random_device()()));
    randomIndexesMap.pb(itSizeQue); //to understand where`s the end quickly, don`t shuffle it
}

template<typename T>
typename randomized_queue <T>::iterator randomized_queue <T>::end(){
    iterator it(que.begin(), size(), true);
    return it;
}

template<typename T>
typename randomized_queue <T>::iterator randomized_queue <T>::iterator::operator++(int){
    iterator answer(*this);
    itIndex++;
    return answer;
}

template<typename T>
typename randomized_queue <T>::iterator &randomized_queue <T>::iterator::operator++(){
    itIndex++;
    return *this;
}

template<typename T>
typename randomized_queue <T>::iterator& randomized_queue <T>::iterator::operator=(const randomized_queue::iterator &givenIterator){
    itBegin = givenIterator.itBegin;
    itSizeQue = givenIterator.itSizeQue;
    itIndex = givenIterator.itIndex;
    randomIndexesMap = givenIterator.randomIndexesMap;
}

template<typename T>
bool randomized_queue <T>::iterator::operator==(const randomized_queue::iterator &givenIterator){
    return (itBegin + randomIndexesMap[itIndex]) == (givenIterator.itBegin + givenIterator.randomIndexesMap[givenIterator.itIndex]);
}

template<typename T>
bool randomized_queue <T>::iterator::operator!=(const randomized_queue::iterator &givenIterator){
    return (itBegin + randomIndexesMap[itIndex]) != (givenIterator.itBegin + givenIterator.randomIndexesMap[givenIterator.itIndex]);
}

template<typename T>
T &randomized_queue <T>::iterator::operator*(){
    return *(itBegin + randomIndexesMap[itIndex]);
}

////
template<typename T>
RING randomized_queue <T>::get_generator(){
    std::random_device something;
    return RING(something());
}

template<typename T>
void randomized_queue <T>::changeLimits(){
    limits = std::uniform_int_distribution <int> (0, size() - 1);
}
