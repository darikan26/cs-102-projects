 /**
    * Node class methods. 
    * @file node.cc
    * @author(s) Derya Arikan
    * @date April 19, 2023
    */
#include <iostream>
#include <fstream>
#include <vector>
#include "node.h"

using namespace std;

/// @brief Node constructor
/// @param new_key key of the new node
/// @param new_parent parent of the new node
Node::Node(int new_key, Node* new_parent) {
    parent = new_parent;
    key = new_key;
    left = nullptr;
    right = nullptr;
}
