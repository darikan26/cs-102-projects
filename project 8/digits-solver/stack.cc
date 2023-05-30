#include <iostream>
#include "stack.h"

/// @brief Constructor.
Stack::Stack() {
    head = nullptr;
    size = 0;
}

/// @brief Checks whether stack is empty.
/// @return Returns true if empty. 
bool Stack::empty() {
    return head == nullptr;
}

/// @brief Pushes new_key onto the stack. 
/// @param new_key Key of the new node.
void Stack::push(int new_key) {
    size += 1;
    Node* new_node = new Node(new_key);
    new_node->next = head;
    head = new_node;
}

/// @brief Pops the last node off the stack. 
/// @return Key of the node being popped. 
int Stack::pop() {
    size -= 1;
    int item = head->key;
    head = head->next;
    return item;
}

/// @brief Displays the stack. 
void Stack::display() {
    Node* current = head;
    while (current != nullptr) {
        cout << current->key << ' ';
        current = current->next;
    }
    cout << endl;
}

/// @brief Returns the size of the stack. 
/// @return Size of the stack. 
int Stack::get_size() {
    return size;
}