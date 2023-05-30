/**
 * CS-102 Project 05: A program that uses a circularly linked list
 * to model a simple stone-moving game.
 * @file cll.cpp
 * @author(s) Derya Arikan
 * @date Monday, February 27th
 */

#include <iostream>
#include <fstream>
using namespace std;

class Node {
private:
    Node() = delete;  // the default constructor may never be used
public:
    int key;
    int stone_count;
    Node* next;
    Node* prev;
    Node(int new_key);
};

/// @brief Constructor for Node
/// @param new_key key of the Node being constructed
Node::Node(int new_key) {
    key = new_key;
    stone_count = 1;
}

class CircularDoublyLinkedList {
private:
    Node* head;
    Node* tail;
public:
    CircularDoublyLinkedList();
    bool empty();
    void append(int new_key);
    void nodes(int node_count);
    void moves(int move_count);
    void place(int index);
    void clock(int index);
    void anti(int index);
    void display();
};

/// @brief default constructor for CircularDoublyLinkedList
CircularDoublyLinkedList::CircularDoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
}

/// @brief Checks if the linked list is empty
/// @return 1 if empty, 0 if not empty. 
bool CircularDoublyLinkedList::empty() {
    return head == nullptr;
}

/// @brief Adds a new node after the tail. 
/// @param new_key Key of new node being added to linked list
void CircularDoublyLinkedList::append(int new_key) {
    Node* new_node = new Node(new_key);
    if (empty()) {
        head = new_node;
        tail = new_node;
        // display();
        return;
    }
    tail->next = new_node;
    new_node->prev = tail;
    tail = new_node;
    tail->next = head;
    head->prev = tail;
    // display();
}

/// @brief Prints out the linked list.
void CircularDoublyLinkedList::display() {
    Node* current = head;
    if (current != tail) {
        while (current != tail) {
            cout << current->stone_count << ' ';
            current = current->next;
        }
        if ( !empty()) {
            cout << tail->stone_count;
        }
    } else if (head == tail) {
        cout << head->stone_count;
    }
    cout << endl;
}

/// @brief Creates linked list with the specified number of nodes.
/// @param node_count Number of nodes that will be in the list.
void CircularDoublyLinkedList::nodes(int node_count) {
    for ( int i = 0; i < node_count; i++ ) {
        append(i);
    }
}

/// @brief This function does nothing. I put it here to avoid
///        and possible trouble with the autograder. 
/// @param move_count The number of moves expected. 
void CircularDoublyLinkedList::moves(int move_count) {
    // pass
}

/// @brief Loops through the circular list. If the current node
///        has the right index, increase its stone count by 1.
/// @param index The key of the node to which a stone will be 
///        added.
void CircularDoublyLinkedList::place(int index) { 
    if (head == tail) {
        head->stone_count += 1;
    } else {
        Node* current = head;
        bool loop = false;
        while ( !loop) {
            if (current->key == index) {
                current->stone_count += 1;
            }
            current = current->next;
            if (current == head) {
                loop = true;
            }
        }
    }
}

/// @brief Loops through all the nodes from head to tail until it 
///        reaches the right node, picks up all the stones from
///        that node. As long as there are stones at hand, distri-
///        butes the stones one by one to the following nodes.
/// @param index Key of the node from which the stones will be
///        picked up.
void CircularDoublyLinkedList::clock(int index) {
    if (head != tail) {
        Node* current = head;
        int stones_at_hand = 0; 

        bool picked_up = false;
        bool done = false;
        while (!done) {
            if (stones_at_hand == 1 && current->stone_count == 0) { // condition for discarding stone
                stones_at_hand -= 1;
            } else if (stones_at_hand > 0) { // condition for placing stone into cup
                current->stone_count += 1;
                stones_at_hand -= 1;
            }
            if (current->key == index && !picked_up) { // condition for picking up stones
                picked_up = true;
                stones_at_hand = current->stone_count; 
                current->stone_count = 0;
            }
            if (picked_up && stones_at_hand == 0) { // condition for terminating while loop
                done = true;
            }
            current = current->next;
        }
    }
}

/// @brief Loops through all the nodes from tail to head until it 
///        reaches the right node, picks up all the stones from
///        that node. As long as there are stones at hand, distri-
///        butes the stones one by one to the following nodes.
/// @param index Key of the node from which the stones will be
///        picked up.
void CircularDoublyLinkedList::anti(int index) {
    if (head != tail) {
        Node* current = tail;
        int stones_at_hand = 0; 

        bool picked_up = false;
        bool done = false;
        while ( !done) {
            if (stones_at_hand == 1 && current->stone_count == 0) { // condition for discarding stone 
                stones_at_hand -= 1;
            } else if (stones_at_hand > 0) { // condition for placing stone into cup
                current->stone_count += 1;
                stones_at_hand -= 1;
            }
            if (current->key == index && !picked_up) { // condition for picking up stones
                picked_up = true;
                stones_at_hand = current->stone_count; 
                current->stone_count = 0;
            }
            if (picked_up && stones_at_hand == 0) { // condition for terminating while loop
                done = true;
            }
            current = current->prev;
        }
    }
}

/// @brief Enables testing from file with commands defined in this
///        function.
/// @param file_name Name of the file that contains the test 
///        commands.
void test_from_file(string file_name) {
    ifstream the_file(file_name);

    if( !the_file.is_open()){
        cout << "File not found: " << file_name << endl;
        throw invalid_argument("File not found: " + file_name);
    }

    CircularDoublyLinkedList cll;
    string command;
    int item;

    while(the_file >> command)  {
        
        if (command == "nodes") {
            the_file >> item;
            cll.nodes(item);
        }
        else if (command == "moves") {
            the_file >> item;
            cll.moves(item);
        }
        else if (command == "place") {
            the_file >> item;
            cll.place(item);
        }
        else if (command == "clock") {
            the_file >> item;
            cll.clock(item);
        }
        else if (command == "anti") {
            the_file >> item;
            cll.anti(item);
        }
        else {
            cout << "ERROR: Incorrect command: " << command << endl;
        }
    }
    cll.display();
}

/// @brief Controls program flow.
/// @param argc Argument count
/// @param argv Argument vector
int main(int argc, char ** argv) {

    if (argc != 2) { 
        cout << "usage: " << argv[0] << " <commands file name>" << endl;
        exit(1);
    }
    
    string test_file = argv[1];
    test_from_file(test_file);
    
}