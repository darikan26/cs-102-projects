#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "node.h"
using namespace std;

class Stack {
private:
    Node* head;
    int size;
public:
    Stack();
    bool empty();
    void push(int new_key);
    int pop();
    void display();
    int get_size();
};

#endif