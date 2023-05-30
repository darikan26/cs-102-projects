 /**
    * Node class header file. 
    * @file node.h
    * @author(s) Derya Arikan
    * @date April 19, 2023
    */
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Node {
private:
    Node() = delete;
public:
    int key;
    Node* left;
    Node* right;
    Node* parent;
    Node(int new_key, Node* parent);
};
