#pragma once

#include <vector>

template<typename T>
struct my_deque {
    my_deque();

    ~my_deque() = default;

    int size() const;

    const T &front() const; //if we don`t need to change - compiler will choose automatically

    T &front(); //if we need something to change

    const T &back() const;

    T &back();

    void pop_front();

    void pop_back();

    void push_back(const T &current);

    void push_front(const T &current);

    bool empty() const;

    struct iterator {
        using vecIt = typename std::vector <T>::iterator;

        iterator(const iterator &givenIterator) = default;

        iterator (vecIt begin, int sizeVect, int head, int sizeDeq, bool finish);

        iterator() = default;

        iterator operator+(int value);

        iterator operator-(int value);

        iterator operator++(int);

        iterator &operator++();

        iterator &operator+=(int value);

        iterator &operator-=(int value);

        iterator &operator=(const iterator &givenIterator) = default;

        bool operator==(const iterator &givenIterator);

        bool operator!=(const iterator &givenIterator);

        T &operator*();

    private:
        int itHead = 0;

        int itIndex = 0;

        int itSizeVect = 0;

        vecIt itBegin;
    };

    iterator begin();

    iterator end();
 private:
     int tail;

     int head;

     int add(int value) const;

     int sub(int value) const;

     std::vector <T> deq;

     void changeSizeVec (int current);

    static const int start_size = 128;
};



template<typename T>
my_deque <T>::my_deque(){
    deq.resize(start_size);
    head = 0;
    tail = 0;
}

template<typename T>
int my_deque<T>::size() const{
    return (head > tail ? (deq.size() - head + tail) : (tail - head));
}

template<typename T>
const T &my_deque<T>::front() const{
    return deq[head];
}

template<typename T>
T &my_deque<T>::front(){
    return deq[head];
}

template<typename T>
const T &my_deque<T>::back() const{
    int temporary = sub(tail);
    return deq[temporary];
}

template<typename T>
T &my_deque<T>::back(){
    int temporary = sub(tail);
    return deq[temporary];
}

template<typename T>
void my_deque<T>::pop_front(){
    if (!empty()){
        changeSizeVec(size());
        //clear memory with destructor and then reserve it again
        deq[head].~T();
        new(&deq[head]) T;
        head = add(head);
    } else {
        std::cout<<"Can`t use pop_front with empty deque"<<std::endl;
        return;
    }
}

template<typename T>
void my_deque<T>::pop_back(){
    if (!empty()){
        changeSizeVec(size());
        //clear memory with destructor and then reserve it again
        tail = sub(tail);
        deq[tail].~T();
        new(&deq[tail]) T;
    } else {
        std::cout<<"Can`t use pop_back with empty deque"<<std::endl;
    }
}

template<typename T>
void my_deque<T>::push_back(const T &current){
    changeSizeVec(size() + 1);
    int temporary = add(tail);
    deq[tail] = current;
    tail = temporary;
}

template<typename T>
void my_deque<T>::push_front(const T &current){
    changeSizeVec(size() + 1);
    head = sub(head);
    deq[head] = current;
}

template<typename T>
bool my_deque <T>::empty() const{
    if (size() == 0){
        return true;
    } else {
        return false;
    }
}

//struct of Iterators;

template <typename T>
typename my_deque <T>::iterator my_deque <T>::iterator::operator+(int value){
    iterator answer = *this;
    return answer += value;
}

template <typename T>
typename my_deque <T>::iterator my_deque <T>::iterator::operator-(int value){
    iterator answer = *this;
    return answer -= value;
}

template <typename T>
typename my_deque <T>::iterator my_deque <T>::iterator::operator++(int){
    iterator answer = *this;
    itIndex++;
    return answer;
}

template <typename T>
typename my_deque <T>::iterator &my_deque <T>::iterator::operator++(){
    itIndex++;
    return *this;
}

template <typename T>
typename my_deque <T>::iterator &my_deque <T>::iterator::operator+=(int value){
    itIndex += value;
    return *this;
}

template <typename T>
typename my_deque <T>::iterator &my_deque <T>::iterator::operator-=(int value){
    itIndex -= value;
    return *this;
}

template <typename T>
bool my_deque <T>::iterator::operator==(const my_deque::iterator &givenIterator){
    return (itBegin + (itHead + itIndex) % itSizeVect) == (givenIterator.itBegin + (givenIterator.itHead + givenIterator.itIndex) % givenIterator.itSizeVect);
}

template <typename T>
bool my_deque <T>::iterator::operator!=(const my_deque::iterator &givenIterator){
    return (itBegin + (itHead + itIndex) % itSizeVect) != (givenIterator.itBegin + (givenIterator.itHead + givenIterator.itIndex) % givenIterator.itSizeVect);
}

template <typename T>
T &my_deque <T>::iterator::operator*() {
    auto shift = (itHead + itIndex) % itSizeVect;
    return *(itBegin + shift);
}

template <typename T>
my_deque <T>::iterator::iterator (vecIt begin, int sizeVect, int head, int sizeDeq, bool finish) :
        itBegin (begin), itSizeVect (sizeVect), itHead(head){
            itIndex = (finish ? sizeDeq : 0);
} //last pole is for choosing between iterator::begin and iterator::end

//Iterators

template <typename T>
typename my_deque <T>::iterator my_deque <T>::begin(){
    iterator it (deq.begin(), deq.size(), head, size(), false);
    return it;
}

template <typename T>
typename my_deque <T>::iterator my_deque <T>::end(){
    iterator it (deq.begin(), deq.size(), head, size(), true);
    return it;
}

template <typename T>
int my_deque <T>::add(int value) const{
    return (value + 1) % deq.size();
}

template <typename T>
void my_deque <T>::changeSizeVec(int current){
    if (current < start_size) return;
    if (deq.size() > 4 * current || deq.size() <= current){
        std::vector <T> temporary;
        temporary = deq;
        deq.clear(); deq.resize(2 * current + 1);
        int i = 0;
        if (head > tail){
            for (int j = head; j < temporary.size(); j++){
                deq[i] = temporary[j];
                i++;
            }
            for (int j = 0; j < tail; j++){
                deq[i] = temporary[j];
                i++;
            }
        } else {
            for (int j = head; j < tail; j++){
                deq[i] = temporary[j];
                i++;
            }
        }
        tail = (head > tail ? temporary.size() - head + tail : tail - head);
        head = 0;
    }
}

template <typename T>
int my_deque <T>::sub(int value) const{
    return (value != 0 ? value - 1 : deq.size() - 1);
}

