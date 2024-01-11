/// @file prqueue.h
/// @author 
/// @date October 20, 2023
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Fall 2023

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
    
public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    prqueue() {
        root = nullptr;
        sz = 0;
        curr = nullptr;
    }
    
    NODE* copyTreeHelper(NODE* node){
        //base case
        if(node == nullptr){
            return nullptr;
        }

        NODE* copyNode = new NODE;
        copyNode->dup = node->dup;
        copyNode->value = node->value;
        copyNode->priority = node->priority;
        copyNode->parent = nullptr;
        copyNode->left = nullptr;
        copyNode->right = nullptr;
        copyNode->link = nullptr;

        NODE* tempLinkedList = node->link;
        NODE* copyLinkedList = copyNode;
        while(tempLinkedList != nullptr) {
            // create a new linked list
            copyLinkedList->link = new NODE;
            copyLinkedList->link->value = tempLinkedList->value;
            copyLinkedList->link->priority = tempLinkedList->priority;
            copyLinkedList->link->dup = tempLinkedList->dup;
            copyLinkedList->link->parent = copyLinkedList;
            copyLinkedList->link->link = nullptr;
            copyLinkedList->link->left = nullptr;
            copyLinkedList->link->right = nullptr;

            tempLinkedList = tempLinkedList->link;
            copyLinkedList = copyLinkedList->link;
        }

        // Using pre order recursion to copy the elements
        copyNode->left = copyTreeHelper(node->left);
        copyNode->right = copyTreeHelper(node->right);

        return copyNode;
    }

    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    prqueue& operator=(const prqueue& other) {
        if(this == &other) {
            return *this;
        }

        clear();

        this->sz = other.sz;

        if(other.root != nullptr){
            this->root = copyTreeHelper(other.root);
        }

        return *this;
    }

    // helper function for the clear function
    void postOrderClear(NODE* node) {
        if(node == nullptr) {
            return; 
        }
        else {
            postOrderClear(node->left);
            postOrderClear(node->right);

            // deletes linked lists
            while(node != nullptr) {
                NODE* temp = node;
                node = node->link;
                delete temp;
            }
        }
        delete node;
    }

    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {
        sz = 0;
        postOrderClear(root);
        root = nullptr;
    }
    
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~prqueue() {
        clear(); 
    }
    
    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    void enqueue(T value, int priority) {
        NODE* nodeToInsert = new NODE;
        nodeToInsert->value = value;
        nodeToInsert->priority = priority;
        nodeToInsert->dup = false;
        nodeToInsert->parent = nullptr;
        nodeToInsert->link = nullptr;
        nodeToInsert->right = nullptr;
        nodeToInsert->left = nullptr;

        if(root == nullptr) {
            root = nodeToInsert;
            sz++;
            return;
        }
        
        NODE* tempCurr = root;

        // while the curr exists then insert the node in the left or right depending on the priority
        while(tempCurr != nullptr) {
            if(nodeToInsert->priority < tempCurr->priority) {
                if(tempCurr->left == nullptr){
                    tempCurr->left = nodeToInsert;
                    nodeToInsert->parent = tempCurr;
                    sz++;
                    break;
                }
                else {                
                    tempCurr = tempCurr->left;
                }
            }
            else if(nodeToInsert->priority > tempCurr->priority) {
                if(tempCurr->right == nullptr) {
                    tempCurr->right = nodeToInsert;
                    nodeToInsert->parent = tempCurr;
                    sz++;
                    break;
                }
                else {
                    tempCurr = tempCurr->right;
                }
            }
            else {
                // manipulate the parent nodes if there is a duplicate
                if(tempCurr->dup == true){
                    NODE* lastDup = tempCurr;
                    lastDup->dup = true;
                    while(lastDup->link != nullptr){
                        lastDup = lastDup->link;
                    }
                    lastDup->link = nodeToInsert;
                    nodeToInsert->parent = lastDup;
                    nodeToInsert->dup = true;
                }
                else {
                    tempCurr->dup = true;
                    tempCurr->link = nodeToInsert;
                    nodeToInsert->parent = tempCurr;
                    nodeToInsert->dup = true;
                }
                sz++;
                break;
            }
        }
    }

    // Finding the node with the lowest number because that is the highest priority
    void highestPriority(NODE* node){
        if(node == nullptr) {
            return;
        }

        curr = node;
        highestPriority(node->left);
    }

    // Finding the node with the highest number because that is the lowest priority
    int lowestPriorityHelper(NODE* node) {
        if(node == nullptr){
            return 0;
        }
        
        while(node->right != nullptr) {
            node = node->right;
        }

        return node->priority;
    }

    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T dequeue() {
        if(root == nullptr) {
             return T();
        }

        highestPriority(root);
        NODE* highestPriorityNode = curr;
        T valueOut = curr->value;

        NODE* movedNode = nullptr;
        // if there is a duplicate at the highPriorityNode
        if(highestPriorityNode->link != nullptr) {
            movedNode = highestPriorityNode->link;
            movedNode->parent = highestPriorityNode->parent;
            movedNode->right = highestPriorityNode->right;
            movedNode->left = highestPriorityNode->left;

            // if right subtree exists then connect the parent nodes
            if(highestPriorityNode->right != nullptr) {
                highestPriorityNode->right->parent = movedNode;
            }

            // connecting the parent node to the right or left linked list depending on priority
            if(highestPriorityNode->parent != nullptr && highestPriorityNode->priority > highestPriorityNode->parent->priority) {
                highestPriorityNode->parent->right = movedNode;
            }
            else if(highestPriorityNode->parent != nullptr && highestPriorityNode->priority < highestPriorityNode->parent->priority) {
                highestPriorityNode->parent->left = movedNode;
            }
            
            if(highestPriorityNode == root) {
                root = movedNode;
            }

            delete highestPriorityNode;
            curr = movedNode;
        }
        // if the root equals the highestPriorityNode
        else if(highestPriorityNode == root) {
            if(root->right != nullptr) {
                movedNode = root->right;
                movedNode->parent = nullptr;
            }

            delete highestPriorityNode;
            curr = movedNode;
            root = movedNode;
        }
        // if highestPriorityNode has a right subtree
        else if(highestPriorityNode->right != nullptr) {
            movedNode = highestPriorityNode->right;
            movedNode->parent = highestPriorityNode->parent;
            highestPriorityNode->parent->left = movedNode;

            delete highestPriorityNode;
        }
        // if highestPriorityNode has a left subtree
        else {
            movedNode = highestPriorityNode->parent;
            movedNode->left = nullptr;
        
            delete highestPriorityNode;
            curr = movedNode;
        }
        sz--;
        return valueOut;
    }
    
    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    int size() {
        if(root == nullptr){
            return 0;
        }
        return sz;
    }
    
    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree

    void begin() {
        if(root == nullptr){
            return;
        }
        highestPriority(root);
    }
    
    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //

    //parameters take in whatever node and we have to point to the next priority node 
    //handle duplicates
    //return true if there is a next node but return false if there is not
    bool next(T& value, int &priority) {
        if(curr == nullptr) {
            return false;
        }

        int lowestPriority = lowestPriorityHelper(root);

        value = curr->value;
        priority = curr->priority;

        // if there are duplicates at the node with given parameters
        if(curr->link != nullptr) {
            if(curr->parent != nullptr) {
                curr->link->parent = curr->parent;
            }
            if(curr->right != nullptr) {
                curr->link->right = curr->right;
            }
            curr = curr->link;
        }
        // if current priority equals to the root priority and the right subtree exists from the root
        else if(curr->priority == root->priority && curr != root && curr->link == nullptr && root->right != nullptr) {
            curr = curr->right;
            if(curr->left != nullptr) {
                while(curr->left != nullptr) {
                    curr = curr->left;
                }
            }
        }
        // if curr gets to the end of a linked list and is not the final priority check if the right subtree still has elements and if it does curr gets moved to it 
        else if(curr->dup == true && curr->link == nullptr && curr->priority != lowestPriority && curr->right != nullptr ) {
            curr = curr->right;
            if(curr->left != nullptr) {
                while(curr->left != nullptr) {
                    curr = curr->left;
                }
            }
        }
        // if curr gets to the end of a linked list and is not the final priority go back towards the root and the right subtree does not exist
        else if(curr->dup == true && curr->link == nullptr && curr->priority != lowestPriority && curr->right == nullptr) {
            int currPriorityVal = curr->priority;
            while(curr->parent->priority < currPriorityVal){
                curr = curr->parent;
            }
            curr = curr->parent;
        }
        // if curr gets to the end of a linked list and is the final priority
        else if(curr->dup == true && curr->link == nullptr && curr->priority == lowestPriority) {
            curr = nullptr;
        }
        // if curr equals to root and right subtree exists then go to the right, if not then make curr nullptr
        else if(curr == root) {
            if(root->right != nullptr) {
                curr = root->right;
                while(curr->left != nullptr) {
                    curr = curr->left;
                }
            }
            else {
                curr = nullptr;
            }
        }
        // if curr has a right subtree then go down the left side to get the next priority node
        else if(curr->right != nullptr) {
            curr = curr->right;
            while(curr->left != nullptr) {
                curr = curr->left;
            }
        }
        // if the parent has a right child go back up the tree
        else {
            while(curr->parent != nullptr && curr->parent->left != curr) {
                curr = curr->parent;
            }
            curr = curr->parent;
        }

        // making the check to ensure the correct return value is returned
        if(curr == nullptr) {
            return false;
        }
        return true;
    }

    // helper function for toString
    // uses in order recursion to correctly print out the elements in order
    void toStringHelper(NODE* node, ostream& output) {
        
        if(node->left != nullptr){
            toStringHelper(node->left, output);
        }
        if(node != nullptr){
            NODE* tempCurr = node;
            while(tempCurr != nullptr) {
                output << tempCurr->priority << " value: " << tempCurr->value << "\n";
                tempCurr = tempCurr->link;
            }
        }
        if(node->right != nullptr){
            toStringHelper(node->right, output);
        }
    }
    
    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString() {
        stringstream str;
        if(root == nullptr) {
            return "empty";
        }
        else {
            toStringHelper(root, str);
        }
        return str.str();
    }
    
    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T peek() {
        if(root == nullptr) {
            return T();
        }
        highestPriority(root);
        T valueOut = curr->value;
        return valueOut;
    }
    
    // Most of the code from Adam Koehler traversal video
    // Helper function to test if two trees are equal to eachother
    bool inOrderEquality(NODE* thisNode, NODE* otherNode) const {
        if(thisNode == nullptr && otherNode == nullptr) {
            return true;
        }
        else if(thisNode == nullptr) {
            return false;
        }
        else if(otherNode == nullptr) {
            return false;
        }
        else {
            return(thisNode->priority == otherNode->priority && thisNode->value == otherNode->value && inOrderEquality(thisNode->left, otherNode->left) && inOrderEquality(thisNode->right, otherNode->right) && inOrderEquality(thisNode->link, otherNode->link));
        }
    }

    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const prqueue& other) const {
        return inOrderEquality(root, other.root); 
    }
    
    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
