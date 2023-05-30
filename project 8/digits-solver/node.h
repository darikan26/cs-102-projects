#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

class Node {
private:
public:
    int key;
    Node* next;
    Node();
    Node(int new_key);
};

#endif