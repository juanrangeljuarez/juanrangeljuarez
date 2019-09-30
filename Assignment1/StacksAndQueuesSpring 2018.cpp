//Copyright 2018, Bradley Peterson, Weber State University, All rights reserved.
#include <iostream>
#include <string>
#include <cstdio>

//To prevent those using g++ from trying to use a library
//they don't have
#ifndef __GNUC__
#include <conio.h>
#endif

using std::cout;
using std::cerr;
using std::endl;
using std::string;

//These two base classes help the assignment compile and run without any changes.  
//Dot not modify these.  You will instead override the methods in the derived classes below.
template <typename T>
class CS2420StackBase {
public:
  CS2420StackBase() {}
  CS2420StackBase(const unsigned int size) {}                       //These methods just contain filler code to help the code compile on the initial run.  
  void push(const T& item) {}                                       //In the derived classes below, you will be overriding these with your own versions.  
  void push(T&& item) {}
  T popAndCopy() { T temp{}; return temp; }
  T&& popAndMove() { T* temp = new T; return std::move(*temp); }
  const unsigned int size() const { return 0; }
protected:
  T* arr{ nullptr };
};

template <typename T>
class CS2420QueueBase {
public:
  CS2420QueueBase() {}
  CS2420QueueBase(const unsigned int size) {}
  void pushBack(const T& item) {}
  T popFront() { T temp{}; return temp; }
  const unsigned int size() const { return 0; }
protected:
  T* arr{ nullptr };

};

//**********************************
//Write your code below here
//**********************************
template <typename T>
class CS2420Stack : public CS2420StackBase<T> {
public:
  CS2420Stack(const unsigned int size) { }
};

template <typename T>
class CS2420Queue : public CS2420QueueBase<T> {
public:
  CS2420Queue(const unsigned int size) {}
};

//**********************************
//Write your code above here
//**********************************

//This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
    return false;
  }
}


//This helps with testing, comment it in when ready, but do not modify the code.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    if (whatItShouldBe == "") {
      cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been blank. " << endl;
    }
    else {
      cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
    }
    return false;
  }
}

//This helps with testing, do not modify.
bool checkTestMemory(string testName, int whatItShouldBe, int whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testName << " *** " << endl << ".  ";
    cout << "You are manually managing " << whatItIs << " bytes in memory, but it should be " << whatItShouldBe << " bytes." << endl;
    return false;
  }
}



//This helps with testing, do not modify.
void testCS2420Stack() {

  string result;
  string caughtError;
  CS2420Stack< int > *stack = new CS2420Stack<int>(5);

  stack->push(1);

  int data = stack->popAndCopy();
  checkTest("testCS2420Stack #1", 1, data);

  stack->push(1);
  stack->push(2);
  stack->push(3);
  stack->push(4);
  stack->push(5);
  checkTest("testCS2420Stack #2", 5, stack->popAndCopy());
  checkTest("testCS2420Stack #3", 4, stack->popAndCopy());
  checkTest("testCS2420Stack #4", 3, stack->popAndCopy());
  checkTest("testCS2420Stack #5", 2, stack->popAndCopy());
  checkTest("testCS2420Stack #6", 1, stack->popAndCopy());

  //now cover error handling
  try {
    result = stack->popAndCopy();
  }
  catch (int e) {
    caughtError = "caught";
  }
  checkTest("testCS2420Stack #7", "caught", caughtError);

  //check currentSize
  checkTest("testCS2420Stack #8", 0, stack->size());
  stack->push(12);
  stack->push(32);
  checkTest("testCS2420Stack #9", 2, stack->size());

  //now test filling it up
  stack->push(14);
  stack->push(53);
  stack->push(47);
  checkTest("testCS2420Stack #10", 5, stack->size());

  //This should simply not let the 20 go in, as it is out of room.
  stack->push(20);

  //Grab all the items again.
  checkTest("testCS2420Stack #11", 47, stack->popAndCopy());
  checkTest("testCS2420Stack #12", 53, stack->popAndCopy());
  checkTest("testCS2420Stack #13", 14, stack->popAndCopy());
  checkTest("testCS2420Stack #14", 32, stack->popAndCopy());
  checkTest("testCS2420Stack #15", 12, stack->popAndCopy());

  //now do error handling again
  try {
    result = stack->popAndCopy();
  }
  catch (int e) {
    caughtError = "caught";
  }
  checkTest("testCS2420Stack #16", "caught", caughtError);

  delete stack;

  //test some strings
  CS2420Stack<string> *sstack = new CS2420Stack<string>(10);

  sstack->push("pencil");
  sstack->push("pen");
  sstack->push("marker");

  checkTest("testCS2420Stack #17", 3, sstack->size());

  //remove pen from the stack.
  string temp = sstack->popAndCopy(); // Get marker
  sstack->popAndCopy();               // Remove pen
  sstack->push(temp);                 // Push marker back in

                                      //see if it worked 
  checkTest("testCS2420Stack #18", "marker", sstack->popAndCopy());
  checkTest("testCS2420Stack #19", "pencil", sstack->popAndCopy());

  checkTest("testCS2420Stack #20", 0, sstack->size());

  //Now try a to move a string
  temp = "Some really, really, really long string that I want to be moved and not copied so it is more efficient";
  //for (int i = 0; i < 1000000; i++) {
  //  temp += "******************************************************************************************";
  //}
  const char* letter_ptr = temp.c_str();       // Store where the letter 's' in "string to move" is stored.  
  sstack->push(std::move(temp));               // Move the string into the stack.
  checkTest("testCS2420Stack #21", "", temp);  // temp should now be empty as it points to a new empty buffer

  temp = std::move(sstack->popAndMove());             // Move the string back out of the sstack

                                                      // See if we have it back
  checkTest("testCS2420Stack #22", "Some really, really, really long string that I want to be moved and not copied so it is more efficient", temp);

  // See if the memory addresses match, meaning we never copied the string anywhere
  if (letter_ptr == temp.c_str()) {
    result = "Memory matched, no copies made!";
  }
  else {
    result = "Memory did NOT matched, a copy was made";
  }
  checkTest("testCS2420Stack #23", "Memory matched, no copies made!", result);
  delete sstack;

}

//This helps with testing, comment it in when ready, but do not modify the code.
void testCS2420Queue() {

  string result;
  string caughtError;
  CS2420Queue<string> *pQueue = new CS2420Queue<string>(5);

  //Tests pushBack
  pQueue->pushBack("penny");
  pQueue->pushBack("nickel");
  pQueue->pushBack("dime");
  pQueue->pushBack("quarter");

  checkTest("testCS2420Queue #1", 4, pQueue->size());

  checkTest("testCS2420Queue #2", "penny", pQueue->popFront());
  checkTest("testCS2420Queue #3", 3, pQueue->size());

  checkTest("testCS2420Queue #4", "nickel", pQueue->popFront());
  checkTest("testCS2420Queue #5", "dime", pQueue->popFront());
  checkTest("testCS2420Queue #6", "quarter", pQueue->popFront());
  checkTest("testCS2420Queue #7", 0, pQueue->size());

  caughtError = "not caught";
  try {
    result = pQueue->popFront();
  }
  catch (int e) {
    caughtError = "caught";
  }
  checkTest("testCS2420Queue #8", "caught", caughtError);
  checkTest("testCS2420Queue #9", 0, pQueue->size());

  //Try it again.  This should make it wrap around, and fill up.
  pQueue->pushBack("penny");
  pQueue->pushBack("nickel");
  pQueue->pushBack("dime");
  pQueue->pushBack("quarter");

  checkTest("testCS2420Queue #10", "penny", pQueue->popFront());
  pQueue->pushBack("half dollar");
  pQueue->pushBack("silver dollar");

  //It should be full, no more room to add more.
  pQueue->pushBack("million dollar bill");

  checkTest("testCS2420Queue #11", "nickel", pQueue->popFront());
  checkTest("testCS2420Queue #12", "dime", pQueue->popFront());
  checkTest("testCS2420Queue #13", "quarter", pQueue->popFront());
  checkTest("testCS2420Queue #14", "half dollar", pQueue->popFront());
  checkTest("testCS2420Queue #15", "silver dollar", pQueue->popFront());
  caughtError = "not caught";
  try {
    result = pQueue->popFront();
  }
  catch (int e) {
    caughtError = "caught";
  }
  checkTest("testCS2420Queue #16", "caught", caughtError);

  //Test adding and removing back and forth
  pQueue->pushBack("penny");
  checkTest("testCS2420Queue #17", "penny", pQueue->popFront());
  pQueue->pushBack("nickel");
  checkTest("testCS2420Queue #18", "nickel", pQueue->popFront());
  pQueue->pushBack("dime");
  checkTest("testCS2420Queue #19", "dime", pQueue->popFront());
  pQueue->pushBack("quarter");
  checkTest("testCS2420Queue #20", "quarter", pQueue->popFront());
  pQueue->pushBack("half dollar");
  checkTest("testCS2420Queue #21", "half dollar", pQueue->popFront());
  pQueue->pushBack("silver dollar");
  checkTest("testCS2420Queue #22", 1, pQueue->size());

  checkTest("testCS2420Queue #23", "silver dollar", pQueue->popFront());
  caughtError = "not caught";
  try {
    result = pQueue->popFront();
  }
  catch (int e) {
    caughtError = "caught";
  }
  checkTest("testCS2420Queue #24", "caught", caughtError);

  delete pQueue;

}

void pressAnyKeyToContinue() {
  cout << "Press any key to continue...";

  //Linux and Mac users with g++ don't need this
  //But everyone else will see this message.
#ifndef __GNUC__
  _getch();

#else
  int c;
  fflush(stdout);
  do c = getchar(); while ((c != '\n') && (c != EOF));
#endif
  cout << endl;
}


int main() {

  {
    testCS2420Stack();
    pressAnyKeyToContinue();
    testCS2420Queue();
    pressAnyKeyToContinue();
  }
  cout << "Shutting down the program" << endl;
  return 0;
}