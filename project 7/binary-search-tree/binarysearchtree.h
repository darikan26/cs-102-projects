#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Binary_Search_Tree {
private:
    Node* recursive_locate(int target, Node* &current);
    void recursive_insert(Node* current, int new_key);
    static Node* largest_to_left(Node* n);
public:
    Node* root;
    Binary_Search_Tree();
    bool empty();
    Node* locate(int target);
    void insert(int new_key);
    void display();
    void recursive_display(Node* current);
    bool search(int target);
    void remove(int target);
    void JR_remove(int target);
    int calculate_depth(Node *root_node);
};
