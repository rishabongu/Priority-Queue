/*------------------------------------------- 
Program 4: Priority Queue
Course: CS 211, Fall 2023,UIC 
file: tests.cpp
Date: November 8, 2033
Author: Risha Bongu 
------------------------------------------- */
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

TEST_CASE("default constructor") 
{
    SECTION("checks empty constructor ")
    {
        prqueue<int> pq;
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.getRoot() == nullptr);
        REQUIRE(pq.toString() == "");
    }
  
}

TEST_CASE("size") 
{
    SECTION("testing with empty queue")
    {
        prqueue<int> pq;
        REQUIRE(pq.size() == 0);
    }
    SECTION("testing with enqueue")
    {
      prqueue<int> pq;
      pq.enqueue(20, 2);
      pq.enqueue(30, 1);
      pq.enqueue(40, 3);
      REQUIRE(pq.size() == 3);
    }
    SECTION("testing with enqueue and dups")
    {
      prqueue<int> pq;
      pq.enqueue(20, 2);
      pq.enqueue(30, 1);
      pq.enqueue(40, 2);
      pq.enqueue(50, 1);
      
      REQUIRE(pq.size() == 4);
    }
  
    SECTION("testing with dequeue")
    {
      prqueue<int> pq;
      pq.enqueue(20, 2);
      pq.enqueue(30, 1);
      pq.enqueue(40, 2);

      REQUIRE(pq.size() == 3);

      int value = pq.dequeue();

      REQUIRE(pq.size() == 2);

      value = pq.dequeue();
      value = pq.dequeue();

      REQUIRE(pq.size() == 0);
    }
    SECTION("testing with clearing")
    {
      prqueue<int> pq;
      pq.enqueue(20, 2);
      pq.enqueue(30, 1);
      pq.enqueue(40, 2);
  
      REQUIRE(pq.size() == 3);
  
      pq.clear();
  
      REQUIRE(pq.size() == 0);

    }
    SECTION("testing with operator=")
    {
      prqueue<int> pq1;
      prqueue<int> pq2;
      
      pq2.enqueue(20, 2);
      pq2.enqueue(30, 1);
      pq2.enqueue(40, 2);

      REQUIRE(pq2.size() == 3);

       pq1 = pq2;

      REQUIRE(pq1.size() == pq2.size());

    }    
}

TEST_CASE("enqueue") 
{
    SECTION("empty trees")
    {
      prqueue<int>pq;
      
      REQUIRE(pq.size() == 0);

      pq.enqueue(15, 2);
      
      REQUIRE(pq.size() == 1);

      REQUIRE(pq.peek() == 15);
    }

    SECTION("enqueue with multiple prioirties")
    {
      prqueue<string>pq;

      pq.enqueue("risha", 2);
      pq.enqueue("Apple", 4);
      pq.enqueue("Banana", 1);
      pq.enqueue("Cherry", 3);
      
      REQUIRE(pq.size() == 4);

      REQUIRE(pq.peek() == "Banana");
    }

    SECTION("enqueue with multiple prioirties and dups ")
    {
      prqueue<string>pq;

      pq.enqueue("risha", 2);
      pq.enqueue("Apple", 4);
      pq.enqueue("Banana", 1);
      pq.enqueue("Cherry", 3);
      pq.enqueue("josh", 1);

      REQUIRE(pq.size() == 5);

      REQUIRE(pq.peek() == "Banana");
    }
}

TEST_CASE("toString") 
{
  SECTION("empty queue")
  {
   prqueue<int>pq;
  
   REQUIRE(pq.toString() == "");
    
  }
  
  SECTION("toString with elements")
  {
   prqueue<int>pq;

   REQUIRE(pq.toString() == "");
    
   pq.enqueue(10, 2);
   pq.enqueue(20, 1);
   pq.enqueue(30, 2);
   pq.enqueue(40, 1);

   REQUIRE(pq.toString() == "1 value: 20\n1 value: 40\n2 value: 10\n2 value: 30\n");
  
  }

  SECTION("toString with elements with names")
  {
   prqueue<string>pq;

   REQUIRE(pq.toString() == "");

   pq.enqueue("risha", 2);
   pq.enqueue("josh", 1);
   pq.enqueue("kate", 2);
   pq.enqueue("ella", 1);

   REQUIRE(pq.toString() == "1 value: josh\n1 value: ella\n2 value: risha\n2 value: kate\n");

  }

}

TEST_CASE("clear") 
{
  SECTION("clears empty queue"){
    prqueue<int>pq;

    pq.clear();

    REQUIRE(pq.size() == 0);

    REQUIRE(pq.getRoot() == nullptr);

    REQUIRE(pq.toString() == "");

    REQUIRE(pq.dequeue() == 0);
  }
  SECTION("clears queue with elements"){
    prqueue<int>pq;

    pq.enqueue(20, 2);
    pq.enqueue(30, 1);
    pq.enqueue(40, 2);
  
    pq.clear();

    REQUIRE(pq.size() == 0);
    REQUIRE(pq.getRoot() == nullptr);
    REQUIRE(pq.toString() == "");
  }
  SECTION("clears empty queue with operator="){
    prqueue<int> pq1;
    prqueue<int> pq2;

    pq1.clear();
  
    pq1 = pq2;

    REQUIRE(pq1.size() == 0);
    
    REQUIRE(pq1.toString() == "");
  }
  SECTION("clears queue with operator="){
    prqueue<string> pq1;
    prqueue<string> pq2;

    pq2.enqueue("josh", 2);
    pq2.enqueue("kate", 1);
    pq2.enqueue("emily", 2);
    
    pq1.clear();

    pq1 = pq2;
    
    REQUIRE(pq1.size() == 3);
    REQUIRE(pq1.toString() == "1 value: kate\n2 value: josh\n2 value: emily\n");
  }
  
}

TEST_CASE("operator=") 
{
  SECTION("empty queue"){
    prqueue<int> pq1;
    prqueue<int> pq2;

    pq1 = pq2;

    REQUIRE(pq1.size() == 0);

    REQUIRE(pq1.toString() == "");
  
  }
  SECTION("assign a priority queue to an empty queue"){
    prqueue<int> pq1;
    prqueue<int> pq2;
    
    pq2.enqueue(40, 2);
    pq2.enqueue(50, 1);


    pq1 = pq2;

    REQUIRE(pq1.size() == 2);

    REQUIRE(pq1.toString() == "1 value: 50\n2 value: 40\n");

  }
  SECTION("assign a priority queue to another queue"){
    prqueue<int> pq1;
    prqueue<int> pq2;

    pq2.enqueue(60, 3);
    pq2.enqueue(70, 2);


    pq1 = pq2;

    REQUIRE(pq1.size() == 2);

    REQUIRE(pq1.toString() == "2 value: 70\n3 value: 60\n");
  }
  SECTION("clearing"){
    prqueue<int> pq1;
    prqueue<int> pq2;

    pq2.enqueue(40, 2);
    pq2.enqueue(50, 1);

    pq1 = pq2;

    REQUIRE(pq1.size() == 2);
    
    pq1.clear();
    
    REQUIRE(pq1.size() == 0);
    
    REQUIRE(pq1.toString() ==  "");
  }
  
}
TEST_CASE("dequeue") 
{
  SECTION("empty queue"){
    prqueue<int> pq;
    
    int dequeuedValue = pq.dequeue();
    
    REQUIRE(dequeuedValue == 0);
    
    REQUIRE(pq.size() == 0);
    
  }
  SECTION("complicated tree"){
    prqueue <string> pq;
    int p = 0;
    string str;
    
    pq.enqueue("Dolores", 5);
    pq.enqueue("Bernard", 4);
    pq.enqueue("Ford", 2);
    pq.enqueue("Arnoald", 8);
    pq.enqueue("jasmine", 6);
    pq.enqueue("Carlos", 11);
    pq.enqueue("risha", 5);
    pq.enqueue("josh", 5);
    pq.enqueue("kate", 8);

    while(pq.getRoot())
    {

      pq.begin();
       while (pq.next(str, p)) {
         cout << p << " value: " << str << endl;
       }
       cout << p << " value: " << str << endl;
       pq.dequeue();
    }

  }
   
}
TEST_CASE("begin/next") 
{
   SECTION("complicated tree"){
     prqueue <string> pq;
     int p = 0;
     string str;
     
     pq.enqueue("Dolores", 5);
     pq.enqueue("Bernard", 4);
     pq.enqueue("Ford", 2);
     pq.enqueue("Arnoald", 8);
     pq.enqueue("jasmine", 6);
     pq.enqueue("Carlos", 11);
     pq.enqueue("risha", 5);
     pq.enqueue("josh", 5);
     pq.enqueue("kate", 8);

      pq.begin();
      while (pq.next(str, p)) {
        cout << endl;
        cout << p << " value: " << str << endl;
      }
      cout << p << " value: " << str << endl;   
   }
}
//collaborate with friend just for this test case: csam3
TEST_CASE("peak -")//netID - csam3 
{
  SECTION("empty"){

    prqueue<int>pq;
    prqueue<int>pq2;
    
    int peek = pq.peek();
    int dequeue = pq2.dequeue();
    
    peek = pq2.peek();
    
    REQUIRE(pq.size() == 0);

    dequeue = pq.dequeue();
    REQUIRE(pq == pq2);
    
  }
  SECTION("testing with duplicates"){

    prqueue<int>pq;
    
    int peek = pq.peek();
    int dequeue = pq.dequeue();

    pq.enqueue(4, 1);
    pq.enqueue(3, 2);
    pq.enqueue(7, 1);
    pq.enqueue(7, 1);
    pq.enqueue(10, 1);


    REQUIRE(pq.size() == 5); 
    
    REQUIRE(peek == dequeue);

  }
  SECTION("testing with no duplicates"){

    prqueue<int>pq;
    int peek = pq.peek();
    int dequeue = pq.dequeue();

    pq.enqueue(4, 1);
    pq.enqueue(3, 2);
    pq.enqueue(7, 4);
    pq.enqueue(7, 5);
    pq.enqueue(10, 9);
    
    REQUIRE(pq.size() == 5); 

    REQUIRE(peek == dequeue);

  }

}
  
TEST_CASE("operator==") 
{
  SECTION("empty queue"){
    prqueue<int> pq1;
    prqueue<int> pq2;
    
    REQUIRE(pq1 == pq2);

  }
  SECTION("testing on a queue"){
    prqueue<string> pq1;
    pq1.enqueue("Alice", 3);
    pq1.enqueue("Bob", 2);

    prqueue<string> pq2;
    pq2.enqueue("Alice", 3);
    pq2.enqueue("Bob", 2);

    REQUIRE(pq1 == pq2);

  }
  
}