/// @file tests.cpp
/// @author Albert Huynh
/// @date October 20, 2023

/// 
/// TODO Update the file header with the appropriate information.
///

/// Provided testing file to implement framework based tests in. The examples
/// below demonstrates a basic empty test in each framework with a single
/// assertion. The version uses the supplied catch.hpp file in starter code.
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Fall 2023

// Catch 2.x - Single Include Framework Testing
#define CATCH_CONFIG_MAIN

#include "prqueue.h"
#include "catch.hpp"

using namespace std;

// This test handles the default constructor
// Requires: < size(), getRoot() >
TEST_CASE("Test 1: Default Constructor Initialization") {
    // In this section we test that the size is properly initialized to 0 when default constructor is used
    SECTION("Section 1: Size is 0"){
        prqueue<int> pq;

        REQUIRE(pq.size() == 0);
    }

    // In this section we test that the root is empty by being nullptr
    SECTION("Section 2: root is nullptr and empty") {
        prqueue<int> pq;

        REQUIRE(pq.getRoot() == nullptr);
    }
}

// This test handles the enqueue function, making sure that the correct priority nodes are inserted in the correct places
// Requires: < size(), getRoot(), peek(), enqueue() >
TEST_CASE("Test 2: Enqueue Function"){
    SECTION("Properly adds a node when the root is empty") {
        prqueue<int> pq;

        pq.enqueue(3, 4);

        REQUIRE(pq.size() == 1);
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.peek() == 3);
    }

    SECTION("Handles multiple enqueues and gets the correct size") {
        prqueue<int> pq;

        pq.enqueue(3, 2);
        pq.enqueue(4, 5);
        pq.enqueue(7, 3);

        REQUIRE(pq.size() == 3);
        REQUIRE(pq.peek() == 3);

        pq.enqueue(1, 6);

        REQUIRE(pq.size() == 4);
        REQUIRE(pq.peek() == 3);
        REQUIRE(pq.getRoot() != nullptr);
        
    }

    SECTION("Ensures that enqueue can handle duplicates"){
        prqueue<int> pq;

        pq.enqueue(3, 8);
        pq.enqueue(5, 2);
        pq.enqueue(1, 2);
        pq.enqueue(7, 2);

        REQUIRE(pq.size() == 4);
        REQUIRE(pq.peek() == 5);
        REQUIRE(pq.getRoot() != nullptr);
    }

    SECTION("Ensures that the enqueue places the nodes in the right spot") {
        prqueue<int> pq;

        pq.enqueue(3, 6);
        pq.enqueue(5, 7);
        pq.enqueue(8, 2);

        REQUIRE(pq.size() == 3);
        REQUIRE(pq.peek() == 8);
    }

    SECTION("Enqueue is properly building the BST tree") {
        prqueue<int> pq;

        pq.enqueue(3, 6);

        REQUIRE(pq.size() == 1);
        REQUIRE(pq.peek() == 3);
        REQUIRE(pq.toString() == "6 value: 3\n");

        pq.enqueue(5, 7);
        REQUIRE(pq.size() == 2);
        REQUIRE(pq.peek() == 3);
        REQUIRE(pq.toString() == "6 value: 3\n7 value: 5\n");

        pq.enqueue(8, 2);
        REQUIRE(pq.size() == 3);
        REQUIRE(pq.peek() == 8);
        REQUIRE(pq.toString() == "2 value: 8\n6 value: 3\n7 value: 5\n");

        pq.enqueue(6, 2);
        REQUIRE(pq.size() == 4);
        REQUIRE(pq.peek() == 8);
        REQUIRE(pq.toString() == "2 value: 8\n2 value: 6\n6 value: 3\n7 value: 5\n");

        pq.enqueue(5, 11);
        REQUIRE(pq.size() == 5);
        REQUIRE(pq.peek() == 8);
        REQUIRE(pq.toString() == "2 value: 8\n2 value: 6\n6 value: 3\n7 value: 5\n11 value: 5\n");

        pq.enqueue(6, 1);
        REQUIRE(pq.size() == 6);
        REQUIRE(pq.peek() == 6);
        REQUIRE(pq.toString() == "1 value: 6\n2 value: 8\n2 value: 6\n6 value: 3\n7 value: 5\n11 value: 5\n");

        pq.enqueue(6, 2);
        REQUIRE(pq.size() == 7);
        REQUIRE(pq.peek() == 6);
        REQUIRE(pq.toString() == "1 value: 6\n2 value: 8\n2 value: 6\n2 value: 6\n6 value: 3\n7 value: 5\n11 value: 5\n");
        REQUIRE(pq.getRoot() != nullptr);
    }
}

// Testing the toString() function to make sure that it properly handles the strings of the BST correctly
// Requires: < toString(), size(), getRoot() >
TEST_CASE("Test 3: toString() function") {
    SECTION("Tests to see that it prints out that the tree is empty"){
        prqueue<int> pq;

        REQUIRE(pq.toString() == "empty");
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.getRoot() == nullptr);
    }

    SECTION("Testing to see ToString working with multiple nodes inserted"){
        prqueue<string> pq;

        pq.enqueue("Matt", 8);
        pq.enqueue("Daisy", 11);
        pq.enqueue("Alex", 2);
        pq.enqueue("Chris", 7);
        pq.enqueue("Albert", 19);

        REQUIRE(pq.toString() == "2 value: Alex\n7 value: Chris\n8 value: Matt\n11 value: Daisy\n19 value: Albert\n");
        REQUIRE(pq.size() == 5);
        REQUIRE(pq.getRoot() != nullptr);
    }

    SECTION("Tests to see ToString with duplicates"){
        prqueue<string> pq;

        pq.enqueue("Matt", 2);
        pq.enqueue("Daisy", 11);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 7);

        REQUIRE(pq.toString() == "2 value: Matt\n7 value: Alex\n7 value: Chris\n11 value: Daisy\n");
        REQUIRE(pq.size() == 4);
        REQUIRE(pq.getRoot() != nullptr);
    }

    SECTION("tests to ensure functionality with only duplicates") {
        prqueue<string> pq;

        pq.enqueue("Alice", 2);
        pq.enqueue("Bob", 2);
        pq.enqueue("Carol", 2);

        REQUIRE(pq.toString() == "2 value: Alice\n2 value: Bob\n2 value: Carol\n");
        REQUIRE(pq.size() == 3);
        REQUIRE(pq.getRoot() != nullptr);
    }
}

// Testing the clear function to make sure that it deletes all the nodes of the BST including duplicates
// Requires: < size(), getRoot(), size(), clear(), enqueue(), toString() >
TEST_CASE("Test 4: clear() function"){
    SECTION("testing clear with empty tree") {
        prqueue<int> pq;

        pq.clear();

        REQUIRE(pq.size() == 0);
        REQUIRE(pq.toString() == "empty");
        REQUIRE(pq.getRoot() == nullptr);
    }

    SECTION("Testing with a tree with only one node") {
        prqueue<int> pq;

        pq.enqueue(3, 1);

        pq.clear();

        REQUIRE(pq.size() == 0);
        REQUIRE(pq.toString() == "empty");
        REQUIRE(pq.getRoot() == nullptr);
    }
    SECTION("Testing to see with multiple nodes") {
        prqueue<string> pq;

        pq.enqueue("Matt", 2);
        pq.enqueue("Daisy", 11);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 7);

        pq.clear();

        REQUIRE(pq.size() == 0);
        REQUIRE(pq.toString() == "empty");
        REQUIRE(pq.getRoot() == nullptr);
    }

    SECTION("Checks to see if the root is nullptr") {
        prqueue<string> pq;

        pq.enqueue("Matt", 2);
        pq.enqueue("Daisy", 11);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 7);

        pq.clear();

        REQUIRE(pq.getRoot() == nullptr);
        REQUIRE(pq.toString() == "empty");
        REQUIRE(pq.size() == 0);
    }
}

// Testing the operator= function, making sure that the tree that is copied is getting the correct values
// Requires: < operator=(), toString(), size(), getRoot() >
TEST_CASE("Test 5: operator= functionality") {
    SECTION("Testing the operator= for empty trees") {
        prqueue<int> pq;
        prqueue<int> pq2;

        pq.operator=(pq2);

        REQUIRE(pq.size() == 0);
        REQUIRE(pq.toString() == "empty");

    }

    SECTION("Testing for the operator to copy one element") {
        prqueue<string> pq;
        prqueue<string> pq2;

        pq.enqueue("Matt", 2);
        pq.enqueue("Daisy", 11);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 7);

        pq2.enqueue("Misha", 9);

        pq.operator=(pq2);

        REQUIRE(pq.size() == 1);
        REQUIRE(pq.toString() == pq2.toString());
    }

    SECTION("Testing for the operator to copy multiple elements") {
        prqueue<string> pq;
        prqueue<string> pq2;

        pq.enqueue("Matt", 2);
        pq.enqueue("Daisy", 11);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 7);

        pq2.enqueue("Misha", 9);

        pq2.operator=(pq);

        REQUIRE(pq2.size() == 4);
        REQUIRE(pq2.toString() == pq.toString());
    }

    SECTION("Testing the operator= to copy the exact same tree") {
        prqueue<string> pq;
        prqueue<string> pq2;

        pq.enqueue("Matt", 2);
        pq.enqueue("Daisy", 11);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 7);

        pq2.enqueue("Matt", 2);
        pq2.enqueue("Daisy", 11);
        pq2.enqueue("Alex", 7);
        pq2.enqueue("Chris", 7);

        pq.operator=(pq2);

        REQUIRE(pq.size() == 4);
        REQUIRE(pq.toString() == "2 value: Matt\n7 value: Alex\n7 value: Chris\n11 value: Daisy\n");

        pq.operator==(pq);

        REQUIRE(pq.size() == 4);
        REQUIRE(pq.toString() == "2 value: Matt\n7 value: Alex\n7 value: Chris\n11 value: Daisy\n");
    }

    SECTION("clearing after using the operator = ") {
        prqueue<string> pq;
        prqueue<string> pq2;

        pq.enqueue("Matt", 2);
        pq.enqueue("Daisy", 11);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 7);

        pq2.enqueue("Matt", 2);
        pq2.enqueue("Daisy", 11);
        pq2.enqueue("Alex", 7);
        pq2.enqueue("Chris", 7);

        pq = pq2;

        pq.clear();
        pq2.clear();

        REQUIRE(pq.getRoot() == nullptr);
        REQUIRE(pq2.getRoot() == nullptr);
        REQUIRE(pq.size() == 0);
        REQUIRE(pq2.size() == 0); 
    }
}

// Testing the begin to ensure that it works properly with all values
// Requires: < begin(), getRoot(), toString(), enqueue() >
TEST_CASE("Test 6: Begin") {
    SECTION("Testing with empty priority queue") {
        prqueue<string> pq;
        prqueue<string> pq2;
        pq.begin();

        REQUIRE(pq.toString() == pq2.toString());
        REQUIRE(pq.getRoot() == nullptr);
    }

    SECTION("Testing with a single-node priority queue") {
        prqueue<string> pq;

        pq.enqueue("Alice", 5);
        pq.begin();

        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.toString() == "5 value: Alice\n");
    }
    
    SECTION("Making sure that the root gets changed to the correct priority node") {
        prqueue<string> pq;
        prqueue<string> pq2;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 8);
        pq.enqueue("Toby", 20);
        pq.enqueue("Emre", 4);

        pq.begin();

        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.toString() == "4 value: Emre\n7 value: Alex\n8 value: Chris\n15 value: Matt\n19 value: Daisy\n20 value: Toby\n");
    }
}

// Testing the next function to ensure that all edge cases are met and next is properly going up and down the BST 
// Requires: < begin(), next(), enqueue() >
TEST_CASE("Test 7: Next") {
    SECTION("next() works with an empty priority queue") {
        prqueue<string> pq;

        pq.begin();

        string tempValue;
        int tempPriority;

        REQUIRE(pq.next(tempValue, tempPriority) == false);
    }
    
    SECTION("next() works with one element") {
        prqueue<int> pq;

        pq.enqueue(5, 1);
        pq.begin();

        int tempValue;
        int tempPriority;

        REQUIRE(pq.next(tempValue, tempPriority) == false);
        REQUIRE(tempValue == 5);
        REQUIRE(tempPriority == 1);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
    }

    SECTION("next() works with only duplicates") {
        prqueue<int> pq;

        pq.enqueue(5, 1);
        pq.enqueue(9, 1);
        pq.begin();

        int tempValue;
        int tempPriority;

        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == 5);
        REQUIRE(tempPriority == 1);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
        REQUIRE(tempValue == 9);
        REQUIRE(tempPriority == 1);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
    }

    SECTION("next() works with multiple elements") {
        prqueue<string> pq;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 8);
        pq.enqueue("Toby", 20);
        pq.enqueue("Emre", 4);
        pq.begin();

        string tempValue;
        int tempPriority;

        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Emre");
        REQUIRE(tempPriority == 4);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Alex");
        REQUIRE(tempPriority == 7);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Chris");
        REQUIRE(tempPriority == 8);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Matt");
        REQUIRE(tempPriority == 15);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Daisy");
        REQUIRE(tempPriority == 19);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
        REQUIRE(tempValue == "Toby");
        REQUIRE(tempPriority == 20);

        // checking if next is called more than once the curr is done
        REQUIRE(false == pq.next(tempValue, tempPriority));
        REQUIRE(false == pq.next(tempValue, tempPriority));
    }

    SECTION("another test for next() with multiple values"){
        prqueue<int> pq;

        pq.enqueue(1, 6);
        pq.enqueue(2, 1);
        pq.enqueue(3, 15);
        pq.enqueue(4, 2);
        pq.enqueue(5, 4);
        pq.enqueue(6, 10);
        pq.enqueue(7, 20);
        pq.begin();

        int tempValue;
        int tempPriority;

        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 2);
        REQUIRE(tempPriority == 1);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 4);
        REQUIRE(tempPriority == 2);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 5);
        REQUIRE(tempPriority == 4);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 1);
        REQUIRE(tempPriority == 6);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 6);
        REQUIRE(tempPriority == 10);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 3);
        REQUIRE(tempPriority == 15);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
        REQUIRE(tempValue == 7);
        REQUIRE(tempPriority == 20);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
    }

    SECTION("next() works with duplicates as the lowest priority") {
        prqueue<string> pq;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 19);
        pq.begin();

        string tempValue;
        int tempPriority;

        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Alex");
        REQUIRE(tempPriority == 7);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Matt");
        REQUIRE(tempPriority == 15);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Daisy");
        REQUIRE(tempPriority == 19);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
        REQUIRE(tempValue == "Chris");
        REQUIRE(tempPriority == 19);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
    }

    SECTION("next() works with duplicates as the root") {
        prqueue<string> pq;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 15);    
        pq.begin();
        
        string tempValue;
        int tempPriority;

        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Alex");
        REQUIRE(tempPriority == 7);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Matt");
        REQUIRE(tempPriority == 15);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Chris");
        REQUIRE(tempPriority == 15);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
        REQUIRE(tempValue == "Daisy");
        REQUIRE(tempPriority == 19);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
    }

    SECTION("next() works with duplicates with the same value and priority") {
        prqueue<string> pq;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 15);
        pq.enqueue("Daisy", 19);
        pq.begin();

        string tempValue;
        int tempPriority;   

        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Alex");
        REQUIRE(tempPriority == 7);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Matt");
        REQUIRE(tempPriority == 15);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Chris");
        REQUIRE(tempPriority == 15);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Daisy");
        REQUIRE(tempPriority == 19);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
        REQUIRE(tempValue == "Daisy");
        REQUIRE(tempPriority == 19);
        REQUIRE(false == pq.next(tempValue, tempPriority));
    }

    SECTION("next() works with multiple duplicates of same priority") {
        prqueue<string> pq;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 19);
        pq.enqueue("Eren", 19);
        pq.enqueue("Misha", 19);
        pq.begin();

        string tempValue;
        int tempPriority;  

        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Alex");
        REQUIRE(tempPriority == 7);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Matt");
        REQUIRE(tempPriority == 15);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Daisy");
        REQUIRE(tempPriority == 19);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Chris");
        REQUIRE(tempPriority == 19);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Eren");
        REQUIRE(tempPriority == 19);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
        REQUIRE(tempValue == "Misha");
        REQUIRE(tempPriority == 19);
        REQUIRE(false == pq.next(tempValue, tempPriority));
    }

    SECTION("next() works with multiple duplicates of different priorities") {
         prqueue<string> pq;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 19);
        pq.enqueue("Eren", 19);
        pq.enqueue("Misha", 19);
        pq.enqueue("Alexandra", 7);
        pq.enqueue("Albert", 7);
        pq.begin();

        string tempValue;
        int tempPriority;  

        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Alex");
        REQUIRE(tempPriority == 7);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Alexandra");
        REQUIRE(tempPriority == 7);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Albert");
        REQUIRE(tempPriority == 7);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Matt");
        REQUIRE(tempPriority == 15);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Daisy");
        REQUIRE(tempPriority == 19);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Chris");
        REQUIRE(tempPriority == 19);
        REQUIRE(pq.next(tempValue, tempPriority) == true);
        REQUIRE(tempValue == "Eren");
        REQUIRE(tempPriority == 19);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
        REQUIRE(tempValue == "Misha");
        REQUIRE(tempPriority == 19);
        REQUIRE(false == pq.next(tempValue, tempPriority));
    }

    SECTION("Testing multiple duplicates of different sizes, same values/priorities, different values + same priorities, different places throughout") {
        prqueue<int> pq;

        pq.enqueue(1, 6);
        pq.enqueue(2, 1);
        pq.enqueue(3, 15);
        pq.enqueue(4, 2);
        pq.enqueue(5, 4);
        pq.enqueue(6, 10);
        pq.enqueue(7, 20);
        pq.enqueue(1, 5);
        pq.enqueue(2, 5);
        pq.enqueue(3, 5);
        pq.enqueue(4, 2);
        pq.enqueue(5, 4);
        pq.enqueue(6, 10);
        pq.enqueue(7, 20);
        pq.enqueue(8, 2);
        pq.enqueue(9, 2);
        pq.begin();

        int tempValue;
        int tempPriority;

        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 2);
        REQUIRE(tempPriority == 1);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 4);
        REQUIRE(tempPriority == 2);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 4);
        REQUIRE(tempPriority == 2);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 8);
        REQUIRE(tempPriority == 2);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 9);
        REQUIRE(tempPriority == 2);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 5);
        REQUIRE(tempPriority == 4);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 5);
        REQUIRE(tempPriority == 4);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 1);
        REQUIRE(tempPriority == 5);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 2);
        REQUIRE(tempPriority == 5);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 3);
        REQUIRE(tempPriority == 5);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 1);
        REQUIRE(tempPriority == 6);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 6);
        REQUIRE(tempPriority == 10);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 6);
        REQUIRE(tempPriority == 10);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 3);
        REQUIRE(tempPriority == 15);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 7);
        REQUIRE(tempPriority == 20);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
        REQUIRE(tempValue == 7);
        REQUIRE(tempPriority == 20);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
    }

    SECTION("Another test of multiple duplicates of different sizes, same values/priorities, different values + same priorities, different places throughout") {
        prqueue<int> pq;

        pq.enqueue(1, 6);
        pq.enqueue(2, 1);
        pq.enqueue(3, 15);
        pq.enqueue(4, 2);
        pq.enqueue(5, 4);
        pq.enqueue(6, 10);
        pq.enqueue(7, 20);
        pq.enqueue(1, 5);
        pq.enqueue(2, 5);
        pq.enqueue(3, 5);
        pq.enqueue(4, 2);
        pq.enqueue(5, 4);
        pq.enqueue(6, 10);
        pq.enqueue(7, 20);
        pq.enqueue(8, 2);
        pq.enqueue(9, 2);
        pq.enqueue(8, 21);
        pq.enqueue(8, 21);
        pq.begin();

        int tempValue;
        int tempPriority;

        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 2);
        REQUIRE(tempPriority == 1);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 4);
        REQUIRE(tempPriority == 2);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 4);
        REQUIRE(tempPriority == 2);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 8);
        REQUIRE(tempPriority == 2);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 9);
        REQUIRE(tempPriority == 2);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 5);
        REQUIRE(tempPriority == 4);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 5);
        REQUIRE(tempPriority == 4);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 1);
        REQUIRE(tempPriority == 5);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 2);
        REQUIRE(tempPriority == 5);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 3);
        REQUIRE(tempPriority == 5);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 1);
        REQUIRE(tempPriority == 6);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 6);
        REQUIRE(tempPriority == 10);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 6);
        REQUIRE(tempPriority == 10);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 3);
        REQUIRE(tempPriority == 15);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 7);
        REQUIRE(tempPriority == 20);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 7);
        REQUIRE(tempPriority == 20);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 8);
        REQUIRE(tempPriority == 21);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
        REQUIRE(tempValue == 8);
        REQUIRE(tempPriority == 21);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
    }

    SECTION("Testing all edge cases for next") {
        prqueue<int> pq;

        pq.enqueue(1, 12);
        pq.enqueue(2, 10);
        pq.enqueue(3, 18);
        pq.enqueue(4, 12);
        pq.enqueue(5, 12);
        pq.enqueue(6, 18);
        pq.enqueue(7, 18);
        pq.enqueue(1, 8);
        pq.enqueue(2, 11);
        pq.enqueue(3, 9);
        pq.enqueue(4, 5);
        pq.enqueue(5, 6);
        pq.enqueue(6, 7);
        pq.enqueue(7, 3);
        pq.enqueue(8, 4);
        pq.enqueue(9, 1);
        pq.enqueue(8, 1);
        pq.enqueue(8, 2);
        pq.enqueue(8, 17);
        pq.enqueue(8, 22);
        pq.enqueue(8, 14);
        pq.enqueue(8, 13);
        pq.enqueue(8, 16);
        pq.enqueue(8, 15);
        pq.enqueue(8, 21);
        pq.enqueue(8, 23);
        pq.begin();

        int tempValue;
        int tempPriority;

        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 9);
        REQUIRE(tempPriority == 1);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 8);
        REQUIRE(tempPriority == 1);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 8);
        REQUIRE(tempPriority == 2);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 7);
        REQUIRE(tempPriority == 3);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 8);
        REQUIRE(tempPriority == 4);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 4);
        REQUIRE(tempPriority == 5);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 5);
        REQUIRE(tempPriority == 6);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 6);
        REQUIRE(tempPriority == 7);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 1);
        REQUIRE(tempPriority == 8);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 3);
        REQUIRE(tempPriority == 9);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 2);
        REQUIRE(tempPriority == 10);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 2);
        REQUIRE(tempPriority == 11);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 1);
        REQUIRE(tempPriority == 12);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 4);
        REQUIRE(tempPriority == 12);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 5);
        REQUIRE(tempPriority == 12);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 8);
        REQUIRE(tempPriority == 13);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 8);
        REQUIRE(tempPriority == 14);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 8);
        REQUIRE(tempPriority == 15);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 8);
        REQUIRE(tempPriority == 16);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 8);
        REQUIRE(tempPriority == 17);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 3);
        REQUIRE(tempPriority == 18);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 6);
        REQUIRE(tempPriority == 18);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 7);
        REQUIRE(tempPriority == 18);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 8);
        REQUIRE(tempPriority == 21);
        REQUIRE(pq.next(tempValue, tempPriority));
        REQUIRE(tempValue == 8);
        REQUIRE(tempPriority == 22);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
        REQUIRE(tempValue == 8);
        REQUIRE(tempPriority == 23);
        REQUIRE(pq.next(tempValue, tempPriority) == false);
    }
}

// Assigning curr to the highest priority node
// Requires: < enqueue(), begin(), next() >
TEST_CASE("Test 8: Highest Priority Helper Function") {
    SECTION("Ensuring that the priority node works with no nodes") {
        prqueue<string> pq;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 8);
        pq.enqueue("Toby", 20);
        pq.enqueue("Emre", 4);

        pq.begin();

        string value;
        int priority;
        pq.next(value, priority);

        REQUIRE(value == "Emre");
        REQUIRE(priority == 4);
    }

    SECTION("Identifying the highest priority in a queue with duplicates") {
        prqueue<string> pq;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 8);
        pq.enqueue("Toby", 20);
        pq.enqueue("Emre", 4);
        pq.enqueue("Riley", 4);

        pq.begin(); 

        string value;
        int priority;
        pq.next(value, priority);

        REQUIRE(value == "Emre");
        REQUIRE(priority == 4);
    }
}

// Testing Dequeue() works properly, removing elements that is the next node in the BST, and moving the parent pointers and left/right pointers
// Requires: < dequeue(), getRoot(), size(), enqueue(), peek()>
TEST_CASE("Test 9: Dequeue()") {
    SECTION("Testing with empty priority queue") {
        prqueue<string> pq;

        REQUIRE(pq.dequeue() == "");
        REQUIRE(pq.getRoot() == nullptr);
        REQUIRE(pq.size() == 0);
    }

    SECTION("Testing with only one element") {
        prqueue<string> pq;

        pq.enqueue("Matt", 2);

        string elementDequeued = pq.dequeue();

        REQUIRE(elementDequeued == "Matt");
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.getRoot() == nullptr);
    }

    SECTION("Testing with 2 elements no dupilcates, left subtree empty") {
        prqueue<string> pq;

        pq.enqueue("Hello", 15);
        pq.enqueue("Trying", 19);

        string elementDequeued = pq.dequeue();

        REQUIRE(elementDequeued == "Hello");
        REQUIRE(pq.size() == 1); 
        REQUIRE(pq.dequeue() == "Trying");
        REQUIRE(pq.size() == 0); 
        REQUIRE(pq.getRoot() == nullptr);
    }

    SECTION("Testing with multiple elements") {
        prqueue<string> pq;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 8);
        pq.enqueue("Toby", 20);
        pq.enqueue("Emre", 4);

        REQUIRE(pq.size() == 6);
        string elementDequeued = pq.dequeue();

        REQUIRE(pq.size() == 5);
        REQUIRE(elementDequeued == "Emre");
        REQUIRE(pq.dequeue() == "Alex");
        REQUIRE(pq.size() == 4);
        REQUIRE(pq.dequeue() == "Chris");
        REQUIRE(pq.size() == 3);
        REQUIRE(pq.dequeue() == "Matt");
        REQUIRE(pq.size() == 2);
        REQUIRE(pq.dequeue() == "Daisy");
        REQUIRE(pq.size() == 1);
        REQUIRE(pq.dequeue() == "Toby");
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.getRoot() == nullptr);
    }

    SECTION("Testing with duplicates and multiple elements") {
        prqueue<string> pq;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 8);
        pq.enqueue("Toby", 20);
        pq.enqueue("Emre", 4);
        pq.enqueue("Abby", 4);
        pq.enqueue("Olivia", 4);
        
        REQUIRE(pq.size() == 8);
        string elementDequeued = pq.dequeue();

        REQUIRE(elementDequeued == "Emre");
        REQUIRE(pq.size() == 7);
        REQUIRE(pq.dequeue() == "Abby");
        REQUIRE(pq.size() == 6);
        REQUIRE(pq.dequeue() == "Olivia");
        REQUIRE(pq.size() == 5);
        REQUIRE(pq.dequeue() == "Alex");
        REQUIRE(pq.size() == 4);
        REQUIRE(pq.dequeue() == "Chris");
        REQUIRE(pq.size() == 3);
        REQUIRE(pq.dequeue() == "Matt");
        REQUIRE(pq.size() == 2);
        REQUIRE(pq.dequeue() == "Daisy");
        REQUIRE(pq.size() == 1);
        REQUIRE(pq.dequeue() == "Toby");
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.getRoot() == nullptr);
    }

    SECTION("Testing with duplicates at the root and multiple elements w/ left sub tree empty") {
        prqueue<string> pq;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Toby", 20);
        pq.enqueue("Abby", 15);
        pq.enqueue("Olivia", 15);
        
        REQUIRE(pq.size() == 5);
        string elementDequeued = pq.dequeue();

        REQUIRE(elementDequeued == "Matt");
        REQUIRE(pq.size() == 4);
        REQUIRE(pq.dequeue() == "Abby");
        REQUIRE(pq.size() == 3);
        REQUIRE(pq.dequeue() == "Olivia");
        REQUIRE(pq.size() == 2);
        REQUIRE(pq.dequeue() == "Daisy");
        REQUIRE(pq.size() == 1);
        REQUIRE(pq.dequeue() == "Toby");
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.getRoot() == nullptr);
    }

    SECTION("Testing using dequeue multiple times with duplicates") {
        prqueue<string> pq;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Toby", 20);
        pq.enqueue("Abby", 15);
        pq.enqueue("Olivia", 15);
        pq.enqueue("Eren", 20);
        pq.enqueue("Timothy", 20);

        REQUIRE(pq.size() == 7);
        string elementDequeued = pq.dequeue();
        REQUIRE(pq.size() == 6);
        string elementDequeued2 = pq.dequeue();
        REQUIRE(pq.size() == 5);
        REQUIRE(elementDequeued == "Matt");
        REQUIRE(elementDequeued2 == "Abby");
        REQUIRE(pq.dequeue() == "Olivia");
        REQUIRE(pq.size() == 4);
        REQUIRE(pq.dequeue() == "Daisy");
        REQUIRE(pq.size() == 3);
        REQUIRE(pq.dequeue() == "Toby");
        REQUIRE(pq.size() == 2);
        REQUIRE(pq.dequeue() == "Eren");
        REQUIRE(pq.size() == 1);
        REQUIRE(pq.dequeue() == "Timothy");
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.getRoot() == nullptr);
    }

    SECTION("Testing using dequeue to erase the whole priority queue") {
        prqueue<string> pq;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Toby", 20);
        pq.enqueue("Abby", 15);
        pq.enqueue("Olivia", 15);

        REQUIRE(pq.peek() == "Matt");
        string elementDequeued = pq.dequeue();
        REQUIRE(pq.peek() == "Abby");
        string elementDequeued2 = pq.dequeue();
        REQUIRE(pq.peek() == "Olivia");
        string elementDequeued3 = pq.dequeue();
        REQUIRE(pq.peek() == "Daisy");
        string elementDequeued4 = pq.dequeue();
        REQUIRE(pq.peek() == "Toby");
        string elementDequeued5 = pq.dequeue();
        REQUIRE(pq.peek() == "");


        REQUIRE(elementDequeued == "Matt");
        REQUIRE(elementDequeued2 == "Abby");
        REQUIRE(elementDequeued3 == "Olivia");
        REQUIRE(elementDequeued4 == "Daisy");
        REQUIRE(elementDequeued5 == "Toby");
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.getRoot() == nullptr);
    }

    SECTION("Testing using dequeue on different types of data (int)") {
        prqueue<int> pq;
        prqueue<char> pq2;

        pq.enqueue(9, 20);
        pq.enqueue(11, 31);
        pq.enqueue(13, 19);
        pq.enqueue(61, 10);
        pq.enqueue(41, 55);
        pq.enqueue(54, 9);

        pq2.enqueue('a', 7);
        pq2.enqueue('c', 9);
        pq2.enqueue('g', 3);

        int intDequeued = pq.dequeue();
        int intDequeued2 = pq.dequeue();
        int intDequeued3 = pq.dequeue();
        int intDequeued4 = pq.dequeue();
        int intDequeued5 = pq.dequeue();
        int intDequeued6 = pq.dequeue();

        char charDequeued = pq2.dequeue();
        char charDequeued2 = pq2.dequeue();
        char charDequeued3 = pq2.dequeue();


        REQUIRE(intDequeued == 54);
        REQUIRE(intDequeued2 == 61);
        REQUIRE(intDequeued3 == 13);
        REQUIRE(intDequeued4 == 9);
        REQUIRE(intDequeued5 == 11);
        REQUIRE(intDequeued6 == 41);
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.getRoot() == nullptr);

        REQUIRE(charDequeued == 'g');
        REQUIRE(charDequeued2 == 'a');
        REQUIRE(charDequeued3 == 'c');
        REQUIRE(pq2.size() == 0);
    }
}

// Equality operator returns true if two trees are the same size, value, and priorities
// Requires: < size(), toString() >
TEST_CASE("Test 10: Equality Operator Operator==") {
    SECTION("Testing with empty priority queue") {
        prqueue<string> pq;
        prqueue<string> pq2;

        REQUIRE(pq == pq2);
        REQUIRE(pq.size() == pq2.size());
    }

    SECTION("Testing with a same priority and value node on each tree") {
        prqueue<string> pq;
        prqueue<string> pq2;

        pq.enqueue("matt", 1);
        pq2.enqueue("matt", 1);

        REQUIRE(pq.size() == pq2.size());
        REQUIRE(pq == pq2);
        REQUIRE(pq.toString() == pq2.toString());
    }

    SECTION("Testing with a different priority same value node on each tree") {
        prqueue<string> pq;
        prqueue<string> pq2;

        pq.enqueue("matt", 1);
        pq2.enqueue("matt", 2);

        REQUIRE(pq.size() == pq2.size());
        REQUIRE(pq.toString() != pq2.toString());
    }

    SECTION("Testing with a same priority different value node on each tree") {
        prqueue<string> pq;
        prqueue<string> pq2;

        pq.enqueue("matt", 1);
        pq2.enqueue("alex", 1);

        REQUIRE(pq.size() == pq2.size());
        REQUIRE(pq.toString() != pq2.toString());
    }

    SECTION("Testing with multiple nodes of the same tree") {
        prqueue<string> pq;
        prqueue<string> pq2;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 8);
        pq.enqueue("Toby", 20);
        pq.enqueue("Emre", 4);

        pq2.enqueue("Matt", 15);
        pq2.enqueue("Daisy", 19);
        pq2.enqueue("Alex", 7);
        pq2.enqueue("Chris", 8);
        pq2.enqueue("Toby", 20);
        pq2.enqueue("Emre", 4);

        REQUIRE(pq.size() == pq2.size());
        REQUIRE(pq == pq2);
        REQUIRE(pq.toString() == pq2.toString());
    }

    SECTION("Testing with multiple nodes and duplicates of the same tree") {
        prqueue<string> pq;
        prqueue<string> pq2;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 8);
        pq.enqueue("Toby", 20);
        pq.enqueue("Emre", 4);
        pq.enqueue("Toby", 4);

        pq2.enqueue("Matt", 15);
        pq2.enqueue("Daisy", 19);
        pq2.enqueue("Alex", 7);
        pq2.enqueue("Chris", 8);
        pq2.enqueue("Toby", 20);
        pq2.enqueue("Emre", 4);
        pq2.enqueue("Toby", 4);

        REQUIRE(pq.size() == pq2.size());
        REQUIRE(pq == pq2);
        REQUIRE(pq.toString() == pq2.toString());
    }

    SECTION("Testing with multiple nodes of same value but different priority duplicates of the same tree") {
        prqueue<string> pq;
        prqueue<string> pq2;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 8);
        pq.enqueue("Toby", 20);
        pq.enqueue("Emre", 4);
        pq.enqueue("Toby", 4);

        pq2.enqueue("Matt", 15);
        pq2.enqueue("Daisy", 19);
        pq2.enqueue("Alex", 7);
        pq2.enqueue("Chris", 8);
        pq2.enqueue("Toby", 20);
        pq2.enqueue("Emre", 4);
        pq2.enqueue("Alexandra", 4);

        REQUIRE(pq.size() == pq2.size());
        REQUIRE(pq.toString() != pq2.toString());
    }
}

// Peek() returns the highest priority node
// Requires: < peek(), enqueue(), size(), toString() >
TEST_CASE("Test 11: Peek() functionality") {
    SECTION("Peek() works with empty tree") {
        prqueue<int> pq;

        int priority = pq.peek();

        REQUIRE(priority == 0);
        REQUIRE(pq.getRoot() == nullptr);
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.toString() == "empty");
    }

    SECTION("Peek() works with one element") {
        prqueue<int> pq;

        pq.enqueue(42, 5);

        int priority = pq.peek();

        REQUIRE(priority == 42);
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.size() == 1);
        REQUIRE(pq.toString() == "5 value: 42\n");
    }

    SECTION("Peek() works with multiple elements") {
        prqueue<string> pq;

        pq.enqueue("Matt", 8);
        pq.enqueue("Daisy", 11);
        pq.enqueue("Alex", 2);
        pq.enqueue("Chris", 7);
        pq.enqueue("Albert", 19);

        string priority = pq.peek();

        REQUIRE(pq.toString() == "2 value: Alex\n7 value: Chris\n8 value: Matt\n11 value: Daisy\n19 value: Albert\n");
        REQUIRE(pq.size() == 5);
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(priority == "Alex");
    }

    SECTION("Peek() works with multiple elements and duplicates as the highest priority") {
        prqueue<string> pq;

        pq.enqueue("Matt", 8);
        pq.enqueue("Daisy", 11);
        pq.enqueue("Alex", 2);
        pq.enqueue("Chris", 7);
        pq.enqueue("Albert", 19);
        pq.enqueue("Christopher", 2);
        string priority = pq.peek();

        REQUIRE(pq.toString() == "2 value: Alex\n2 value: Christopher\n7 value: Chris\n8 value: Matt\n11 value: Daisy\n19 value: Albert\n");
        REQUIRE(pq.size() == 6);
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(priority == "Alex");
    }

    SECTION("Peek() works with multiple elements and duplicates at the root") {
        prqueue<string> pq;

        pq.enqueue("Matt", 8);
        pq.enqueue("Daisy", 11);
        pq.enqueue("Alex", 2);
        pq.enqueue("Chris", 7);
        pq.enqueue("Albert", 19);
        pq.enqueue("Christopher", 8);
        string priority = pq.peek();

        REQUIRE(pq.toString() == "2 value: Alex\n7 value: Chris\n8 value: Matt\n8 value: Christopher\n11 value: Daisy\n19 value: Albert\n");
        REQUIRE(pq.size() == 6);
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(priority == "Alex");
    }
}

// Dequeue can work very well with peek as peek changes as dequeue is used
// Require: < dequeue(), peek(), size(), toString(), getRoot() >
TEST_CASE("Test 12: Dequeue with Peek()") {
    SECTION("Dequeue on empty tree with peek") {
        prqueue<int> pq;
        
        REQUIRE(pq.dequeue() == 0);
        REQUIRE(pq.getRoot() == nullptr);
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.peek() == 0);
        REQUIRE(pq.toString() == "empty");
    }

    SECTION("Dequeue on one element with peek") {
        prqueue<int> pq;

        pq.enqueue(4, 5);

        REQUIRE(pq.peek() == 4);
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.size() == 1);
        REQUIRE(pq.toString() == "5 value: 4\n");
        REQUIRE(pq.dequeue() == 4);
        REQUIRE(pq.peek() == 0);
        REQUIRE(pq.getRoot() == nullptr);
        REQUIRE(pq.toString() == "empty");
        REQUIRE(pq.size() == 0);
    }

    SECTION("Dequeue on multiple elements") {
        prqueue<string> pq;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 8);
        pq.enqueue("Toby", 20);
        pq.enqueue("Emre", 4);

        REQUIRE(pq.size() == 6);
        REQUIRE(pq.peek() == "Emre");
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.toString() == "4 value: Emre\n7 value: Alex\n8 value: Chris\n15 value: Matt\n19 value: Daisy\n20 value: Toby\n");
        REQUIRE(pq.dequeue() == "Emre");
        REQUIRE(pq.size() == 5);
        REQUIRE(pq.peek() == "Alex");
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.toString() == "7 value: Alex\n8 value: Chris\n15 value: Matt\n19 value: Daisy\n20 value: Toby\n");
        REQUIRE(pq.dequeue() == "Alex");
        REQUIRE(pq.size() == 4);
        REQUIRE(pq.peek() == "Chris");
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.toString() == "8 value: Chris\n15 value: Matt\n19 value: Daisy\n20 value: Toby\n");
        REQUIRE(pq.dequeue() == "Chris");
        REQUIRE(pq.size() == 3);
        REQUIRE(pq.peek() == "Matt");
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.toString() == "15 value: Matt\n19 value: Daisy\n20 value: Toby\n");
        REQUIRE(pq.dequeue() == "Matt");
        REQUIRE(pq.size() == 2);
        REQUIRE(pq.peek() == "Daisy");
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.toString() == "19 value: Daisy\n20 value: Toby\n");
        REQUIRE(pq.dequeue() == "Daisy");
        REQUIRE(pq.size() == 1);
        REQUIRE(pq.peek() == "Toby");
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.toString() == "20 value: Toby\n");
        REQUIRE(pq.dequeue() == "Toby");
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.getRoot() == nullptr);
    }

    SECTION("Dequeue on multiple elements with duplicates") {
        prqueue<string> pq;

        pq.enqueue("Matt", 15);
        pq.enqueue("Daisy", 19);
        pq.enqueue("Alex", 7);
        pq.enqueue("Chris", 8);
        pq.enqueue("Toby", 20);
        pq.enqueue("Emre", 4);
        pq.enqueue("Matthew", 20);

        REQUIRE(pq.size() == 7);
        REQUIRE(pq.peek() == "Emre");
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.toString() == "4 value: Emre\n7 value: Alex\n8 value: Chris\n15 value: Matt\n19 value: Daisy\n20 value: Toby\n20 value: Matthew\n");
        REQUIRE(pq.dequeue() == "Emre");
        REQUIRE(pq.size() == 6);
        REQUIRE(pq.peek() == "Alex");
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.toString() == "7 value: Alex\n8 value: Chris\n15 value: Matt\n19 value: Daisy\n20 value: Toby\n20 value: Matthew\n");
        REQUIRE(pq.dequeue() == "Alex");
        REQUIRE(pq.size() == 5);
        REQUIRE(pq.peek() == "Chris");
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.toString() == "8 value: Chris\n15 value: Matt\n19 value: Daisy\n20 value: Toby\n20 value: Matthew\n");
        REQUIRE(pq.dequeue() == "Chris");
        REQUIRE(pq.size() == 4);
        REQUIRE(pq.peek() == "Matt");
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.toString() == "15 value: Matt\n19 value: Daisy\n20 value: Toby\n20 value: Matthew\n");
        REQUIRE(pq.dequeue() == "Matt");
        REQUIRE(pq.size() == 3);
        REQUIRE(pq.peek() == "Daisy");
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.toString() == "19 value: Daisy\n20 value: Toby\n20 value: Matthew\n");
        REQUIRE(pq.dequeue() == "Daisy");
        REQUIRE(pq.size() == 2);
        REQUIRE(pq.peek() == "Toby");
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.toString() == "20 value: Toby\n20 value: Matthew\n");
        REQUIRE(pq.dequeue() == "Toby");
        REQUIRE(pq.size() == 1);
        REQUIRE(pq.peek() == "Matthew");
        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.toString() == "20 value: Matthew\n");
        REQUIRE(pq.dequeue() == "Matthew");
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.getRoot() == nullptr);
    }
}