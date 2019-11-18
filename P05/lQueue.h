//
// Tomás Oliveira e Silva, AED, October 2014, September 2015
//
// Generic queue (First In First Out) implementation based on an linked list
//

#ifndef _AED_lQueue_
#define _AED_lQueue_

#include <cassert>
#include <math.h>

#define MAX_SIZE 1024

template<typename T>
class lQueue {
private:
    T buffer[MAX_SIZE];
    int head;
    int tail;

    int next_index(int i) {
        return (i + 1) % MAX_SIZE;
    }

public:
    lQueue(void) {
        head = -1;
        tail = 0;
    }

    ~lQueue(void) {
    }

    void clear(void) {
        head = -1;
    }

    int size(void) const {
        if (head == -1)
            return 0;
        if (head > tail)
            return (MAX_SIZE - 1 + tail - head);
        return tail - head;
    }

    int is_full(void) const {

    }

    int is_empty(void) const {
        return head == tail;
    }

    void enqueue(T &v) {
    }

    T dequeue(void) {
    }

    T peek(void) {
    }
};

#endif
