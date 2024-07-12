/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Fall 2023
/*------------------------------------------- 
Program 4: Priority Queue
Course: CS 211, Fall 2023,UIC 
file: prqueue.h
Date: November 8, 2033
Author: Risha Bongu 
------------------------------------------- */
#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class prqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;       // stored data for the p-queue
        bool dup;      // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;    // links to linked list of NODES with duplicate priorities
        NODE* left;    // links to left child
        NODE* right;   // links to right child

    };

    NODE* root; // pointer to root node of the BST
    int sz;     // # of elements in the prqueue
    NODE* curr; // pointer to next item in prqueue (see begin and next)

    //helper function for toString() which recursively traverses the tree and prints out priorities and values of each node in order
    void _recursiveToString(NODE* node, ostream& output) {
      //if the current node is null, returns
      if (node == nullptr) {
        return;
      }
      //traverses the left subtree recursively
      _recursiveToString(node->left, output);
      //temperary node for traversing linked duplicates 
      NODE* temp = node;
      //goes through the linked list of duplicates 
      while(temp != nullptr){
        output << temp->priority << " value: " << temp->value << endl;
        temp = temp->link;
      }
      //traverses the right subtree recursively
      _recursiveToString(node->right, output);
    }
    
    //helper function for the clear(), which clears all the memory
    void clearHelper(NODE* node) {
    //if current node empty, returns
    if (node == nullptr) {
      return;
    }
    //recursively clears the left subtree
    clearHelper(node->left);
    //recursively clears the linked list of dups
    clearHelper(node->link);
    //recursively clears the right subtree
    clearHelper(node->right);
    //frees the memory by deleting the current node
    delete node;
    }
    
    //helper fucntion for operator=, which creates a copy tree and returns the root of the copy tree
    NODE* _copyTree(NODE*temp) {
    //if current node is empty then returns null
    if (temp == nullptr) {
      return nullptr;
    } 
    //creates a new node for the copied tree
    NODE* anotherNode = new NODE;
    //copies the data from the current tree to the new node
    anotherNode->priority = temp->priority;
    anotherNode->value = temp->value;
    anotherNode->dup = temp->dup;
    anotherNode->parent = nullptr;
    anotherNode->link = nullptr;
    //recursively copies the left subtree
    anotherNode->left = _copyTree(temp->left);
    //recursively copies the linked list
    anotherNode->link = _copyTree(temp->link);
    //recursively copies the right subtree
    anotherNode->right = _copyTree(temp->right);
    //returns the root
    return anotherNode;
    }
    
    //helper function for operator==, which recursively checks if two nodes are equal 
    bool _equal(NODE* curr, NODE* othercurr)const{
    //if both nodes are empty or null, they are equal
    if(curr == nullptr && othercurr == nullptr){
      return true;
    }
    //if one node is empty or null and the other node is not, they are not equal
    else if(curr != nullptr && othercurr == nullptr){
      return false;
    }
    else if(curr == nullptr && othercurr != nullptr){
      return false;
    }
    //if priorities or values are not equal, the trees are not equal
    else if(curr->priority != othercurr->priority ){
      return false;
    }
    else if(curr->value != othercurr->value ){
      return false;
    }
    else {
      //checks left subtree
      if(!_equal(curr->left, othercurr->left)){
        return false;
      }
      //checks duplicates
      if(!_equal(curr->right, othercurr->right)){
        return false;
      }
      //checks right subtree
      if(!_equal(curr->link, othercurr->link)){
        return false;
      }
    }
    //returns true if all trees are equal
    return true;
    }

public:
    // default constructor:
    // Creates an empty priority queue.
    // O(1)
    prqueue() {
      root = nullptr;
      sz = 0;
      curr = nullptr;
    }

    // operator=
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    prqueue& operator=(const prqueue& other) {
      if(this!= &other){
        clear();
        root = _copyTree(other.root);
        sz = other.sz;
      }
      return *this;
    }

    // clear:
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    void clear() {
      clearHelper(root);
      root = nullptr;
      curr = nullptr; 
      sz = 0;
    }

    // destructor:
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    ~prqueue() {
      clear();
    }

    // enqueue:
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    void enqueue(T value, int priority) {
      //creates a node with the given value and priority
      NODE* newNode = new NODE;
      newNode->priority = priority;
      newNode->value = value;
      newNode->dup = false;
      newNode->parent = nullptr;
      newNode->link = nullptr;
      newNode->left = nullptr;
      newNode->right = nullptr;
      //checks if the tree is empty and makes the new node the root
      if (root == nullptr) {
        root = newNode;
        sz++;
        return;
      }
      NODE* currNode = root;
      NODE* parent = nullptr;
      //traveses the tree to find the location for the new node
      while (currNode != nullptr) {
        parent = currNode;
        //checks if the priority of the new node new node is equal to the current node's priority
        if (priority == currNode->priority) {
          newNode->dup = true;
          newNode->parent = currNode;
          //checks if there are no links and adds the new node
          if (currNode->link == nullptr) {
            currNode->link = newNode;
          }
          else {
            currNode = currNode->link;
            while (currNode->link != nullptr) {
              currNode = currNode->link;
            }
            currNode->link = newNode;
          }
          sz++;
          return;
          //moves to the left subtree
        } 
        else if (priority < currNode->priority) {
          currNode = currNode->left;
          //moves to the right subtree
        } 
        else {
          currNode = currNode->right;
        }
      }
      //adds a new node based on its priority
      if (priority < parent->priority) {
        parent->left = newNode;
      } 
      else if (priority > parent->priority) {
        parent->right = newNode;
      } 
      else {
        //if priority is equal to the parrent's priority, then it is a duplicate 
        parent->dup = true;
        newNode->dup = true;
        parent->link = newNode;
      }
      //sets the parent of the new node
      newNode->parent = parent;
      sz++;
    }

    // dequeue:
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    T dequeue() {
      if(root == nullptr){
        return T();
      }
      //finds the left most node
      NODE* deleteNode = root;
      while (deleteNode->left != nullptr) {
            deleteNode = deleteNode->left;
      }
      //sets the value 
      T valueOut = deleteNode->value;
      // handles duplicates
      if (deleteNode->link != nullptr) {
        //updates the parent 
        deleteNode->link->parent = deleteNode->parent;
        //checks for the root 
        if(deleteNode == root){
          root = deleteNode->link;
        }
        else{
          //updates the left child 
          deleteNode->parent->left = deleteNode->link;
        }
        //updates the parent of the right child 
        deleteNode->link->right = deleteNode->right;
        if(deleteNode->right != nullptr){
          deleteNode->right->parent = deleteNode->link;
        }
        //checks if empty and updates the duplicates
        if(deleteNode->link->link == nullptr){
          deleteNode->link->dup = false;
        }
        //disconnects the left child 
        deleteNode->link->left = nullptr;
        //deletes the left most node 
        delete deleteNode;
        sz--;
        return valueOut;
      }
      //checks if left most node is the root 
      else if (deleteNode == root) {
        root = deleteNode->right;
        //if not root then updates the parent
        if(root != nullptr){
          deleteNode->right->parent = nullptr;
        }
        //deletes the left most node
        delete deleteNode;
        sz--;
        return valueOut;
      }
      //checks if left most node has a right child
      else if(deleteNode->right != nullptr){
        //updates the parent of the right child
        deleteNode->right->parent = deleteNode->parent;
        //updates the parent of the left child
        deleteNode->parent->left = deleteNode->right;
        //deletes the left most node
        delete deleteNode;
        sz--;
        return valueOut;
      }
      //when left most node is a lead node
      deleteNode->parent->left = nullptr;
      //deletes the left most node 
      delete deleteNode;
      sz--;
      //returns the value 
      return valueOut;
    }

    // Size:
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    int size() {
      return sz; 
    }

    // begin
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    // O(logn), where n is number of unique nodes in tree
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin() {
      //sets current to the root of the tree
      curr = root;
      //if the tree is not empty, traverses to the left most node
      if(curr != nullptr){
        while (curr->left != nullptr) {
          curr = curr->left;
        }
      }
    }

    // next:
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    // O(logn), where n is the number of unique nodes in tree
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int &priority) {
      // if empty, return false
      if (curr == nullptr) {
         return false;
      }
      //gets data from the current node
      priority = curr->priority;
      value = curr->value;
      //checks for duplicates 
      if (curr->link != nullptr) {
          curr = curr->link;
      } 
      //checks for the right subtree and moves to the left most node
      else if(curr->right != nullptr) {
        curr = curr->right;
        while (curr->left != nullptr) {
          curr = curr->left;
        }
      }
      //checks if there are no duplicates and no right subtree and moves to the parents right child 
      else {
        while(curr->dup){
          curr = curr->parent;
      }
        if(curr->right != nullptr) {
          curr = curr->right;
          while (curr->left != nullptr) {
            curr = curr->left;
          }
        }
      // checks if there is no right child and moves to the parent 
      else {
        while (curr->parent != nullptr && priority > curr->parent->priority) {
          curr = curr->parent;
        }
        curr = curr->parent;
      }
    }
      //if curr is now null, returns false
      if (curr == nullptr) {
        return false;
      }
      return true;
    }

    // toString:
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    string toString() {
      stringstream ss;
      _recursiveToString(root, ss);
      return ss.str();
    }

    // peek:
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    T peek() {
      //if empty, returns default 
      if(root == nullptr){
        return T();
      }
      //traverses to find the left most node 
      NODE* temp = root;
      while (temp->left != nullptr) {
        temp = temp->left;
      }
      //value set to the left most node
      T valueOut = temp->value;
      //returns the value 
      return valueOut; 
    }

    // ==operator
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    bool operator==(const prqueue& other) const {
      return _equal(root, other.root);
    }

    // getRoot - Do not edit/change!
    // Used for testing the BST.
    // return the root node for testing.
    void* getRoot() {
      return root;
    }
};