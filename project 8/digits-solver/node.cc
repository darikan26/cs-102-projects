#include <iostream>
#include "node.h"

/// @brief Default constructor. 
Node::Node() {
    key = 0;
    next = nullptr;
}

/// @brief Normal constructor. 
/// @param new_key Key of the new node.
Node::Node(int new_key) {
    key = new_key;
    next = nullptr;
}