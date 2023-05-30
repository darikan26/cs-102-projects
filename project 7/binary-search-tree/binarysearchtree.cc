 /**
    * Binary_Search_Tree class methods. 
    * @file binarysearchtree.cc
    * @author(s) Derya Arikan
    * @date April 19, 2023
    */
#include <iostream>
#include <fstream>
#include <vector>
#include "binarysearchtree.h"

using namespace std;

/// @brief recursively locates node with the target key and returns it
/// @param target key of target node
/// @param current current node pointer
/// @return target node
Node* Binary_Search_Tree::recursive_locate(int target, Node* &current) {
    if (target == current->key) {
        return current;
    } else if (target > current->key) {
        if (current ->right != nullptr) {
            current = current->right;
        } else {
            return nullptr;
        }
    } else {
        if (current ->left != nullptr) {
            current = current->left;
        } else {
            return nullptr;
        }
    }
    return (recursive_locate(target, current));
    cout << "You aren't supposed to be here! Recursive locate error." << endl;
}

/// @brief recursively inserts the new node into the BST.
/// @param current pointer to current node
/// @param new_key key of the new node
void Binary_Search_Tree::recursive_insert(Node* current, int new_key) {
    if (current->key > new_key) {
        if (current->left == nullptr) {
            current->left = new Node(new_key, current);
            return;
        }
        recursive_insert(current->left, new_key);
    } else {
        if (current->right == nullptr) {
            current->right = new Node(new_key, current);
            return;
        }
        recursive_insert(current->right, new_key);
    }
}

/// @brief returns the node with the largest to left (ltl) key value of a given node.
/// @param n node whose ltl we are looking for
/// @return the ltl node of n
Node* Binary_Search_Tree::largest_to_left(Node* n) {
    if (n->left == nullptr) {
        cout << "There is no left subtree. Nice try." << endl;
        return nullptr;
    }
    Node* current = n->left;
    while (current->right != nullptr) {
        current = current -> right;
    }
    return current;
}

/// @brief constructor for Binary_Search_Tree
Binary_Search_Tree::Binary_Search_Tree() {
    root = nullptr;
}

/// @brief checks whether the BST is empty or not.
/// @return true if BST is empty.
bool Binary_Search_Tree::empty() {
    return root == nullptr;
}

/// @brief locates node with the target key and returns it
/// @param target key of the node we are trying to locate
/// @return node that has the target key
Node* Binary_Search_Tree::locate(int target) {
    Node* current = root;
    current = recursive_locate(target, current);
    return current;
}

/// @brief inserts node with new key into BST if BST is not empty. 
/// initializes BST with new key if empty.
/// @param new_key key of new node that is to be inserted. 
void Binary_Search_Tree::insert(int new_key) {
    if (empty()) {
        root = new Node(new_key, nullptr);
        return;
    }
   recursive_insert(root, new_key);
}

/// @brief neatly displays the BST.
void Binary_Search_Tree::display() {
    recursive_display(root);
    cout << endl;
}

/// @brief recursively displays the BST. 
/// @param current current node. 
void Binary_Search_Tree::recursive_display(Node* current) {
    cout << "key: " << current->key << " parent: ";
    if (current->parent != nullptr) {
        cout << current->parent->key << endl;
    } else {
        cout << "none" << endl;
    }
    if (current->left != nullptr) {
        recursive_display(current->left);
    }  
    if (current->right != nullptr) {
        recursive_display(current->right);
    } 
}

/// @brief determines whether the BST contains the target key.
/// @param target the target key
/// @return true if the BST contains target
bool Binary_Search_Tree::search(int target) {
    Node* locate_result = locate(target);
    return locate_result != nullptr;
}

/// @brief NORMALLy removes node with target key from BST
/// @param target key of target node
void Binary_Search_Tree::remove(int target) {
   Node* target_node = locate(target);
   //if there are no children
   if (target_node->right == nullptr && target_node->left == nullptr) {
        Node* target_parent = target_node->parent;
        if (target_parent->left->key == target_node->key) {
            //delete
            target_parent->left = nullptr;
        } else {
            target_parent->right = nullptr;
        }
   } else if (target_node -> right != nullptr && target_node->left == nullptr) { 
        
        //there is one child on the right
        Node* target_parent = target_node->parent;
        if (target_parent-> key < target_node->key) {
            target_parent->right = target_node->right;
            target_parent->right->parent = target_parent;
        } else {
            target_parent->left = target_node->right;
            target_parent->left->parent = target_parent;

        }
   } else if (target_node -> left != nullptr && target_node->right == nullptr) { 
        //there is one child on the left
        Node* target_parent = target_node->parent;
        if (target_parent-> key > target_node->key) {
            target_parent->left = target_node->left;
            target_parent->left->parent = target_parent;
        } else {
            target_parent->right = target_node->left;
            target_parent->right->parent = target_parent;

        }
        
   } else {
        //there are two children
        Node* ltl = largest_to_left(target_node);
        target_node->key = ltl->key;
        if (ltl->parent->key == target_node->key) {
            ltl->parent->left = nullptr;
        } else {
            ltl->parent->right = nullptr;
        }
   }
}

/// @brief JR-REMOVES the target node from the BST.
/// @param target key of the target node
void Binary_Search_Tree::JR_remove(int target) {
   Node* target_node = locate(target);
   //if there are no children
   if (target_node->right == nullptr && target_node->left == nullptr) {
        Node* target_parent = target_node->parent;
        if (target_parent->left->key == target_node->key) {
            //delete
            target_parent->left = nullptr;
        } else {
            target_parent->right = nullptr;
        }
   } else if (target_node -> right != nullptr && target_node->left == nullptr) { 
        //there is one child on the right
        Node* target_parent = target_node->parent;
        if (target_parent-> key < target_node->key) {
            target_parent->right = target_node->right;
            target_parent->right->parent = target_parent;
        } else {
            target_parent->left = target_node->right;
            target_parent->left->parent = target_parent;

        }
   } else if (target_node -> left != nullptr && target_node->right == nullptr) { 
        //there is one child on the left
        Node* target_parent = target_node->parent;
        if (target_parent-> key > target_node->key) {
            target_parent->left = target_node->left;
            target_parent->left->parent = target_parent;
        } else {
            target_parent->right = target_node->left;
            target_parent->right->parent = target_parent;

        }
        
   } else { //there are two children
        Node* target_parent = target_node->parent;
        Node* ltl = largest_to_left(target_node);

        if (target_node->parent->left = target_node) {//target_node is a left child
            target_node->parent->left = target_node->left;
        } else {//target node is a right child
            target_node->parent->right = target_node->left;
        }
        target_node->left->parent = target_node->parent;
    
        //right child of node to be removed becomes the ltl's right child
        ltl->right = target_node->right;
        target_node->right->parent = ltl;
   } 
}

/// @brief calculates the depth of the BST recursively
/// @param root_node the node whose subtrees we will be looking at
/// @return the depth of the BST
int Binary_Search_Tree::calculate_depth(Node *root_node) {
    // base case: we have reached a leaf
    if (root_node->left == nullptr && root_node->right == nullptr) {
        return 1;
    }

    int right_depth, left_depth;
    // checking right subtree depth (if right subtree exists)
    if (root_node->right != nullptr) {
        right_depth = calculate_depth(root_node->right);
    } else {
        right_depth = 0;
    }
    // checking left subtree depth (if left subtree exists)
    if (root_node->left != nullptr) {
        left_depth = calculate_depth(root_node->left);
    }
    else {
        left_depth = 0;
    }

    // compare right and left subtree depths
    if (right_depth >= left_depth) {
        return right_depth + 1;
    } else {
        return left_depth + 1;
    }
}

/*
The following is the pseudocode Peter and I wrote for the depth function:

def depth(node):
  if is_leaf(node):
    return 1

  if right->right is not nullptr:
    right = depth(node->right)
  else: right = 0

  if left->left is not nullptr:
    left = depth(node->left)
  else: left = 0

  if right >= left:
    return right + 1
  if left  > right:
     return left + 1

Our code looks very similar, because we started with the same algorithm we developed
on a whiteboard. 
*/