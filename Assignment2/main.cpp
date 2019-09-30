//Copyright 2018, Bradley Peterson, Weber State University, All rights reserved.

#include <sstream>
#include <map>
#include <chrono>
#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::stringstream;

//************************************************************************
//A class I designed to help keep track of how much memory you allocate
//Do not modify, this is not part of your assignment, it just helps test it.
//For this to work, a class needs to inherit off of this one.
//Then this does the rest of the work, since it
//overloads new, new[], delete, and delete[].
//************************************************************************
class ManageMemory {
public:

    static std::size_t getTotalSize() {
        std::size_t total = 0;
        std::map<void *, std::size_t>::iterator iter;
        for (iter = mapOfAllocations.begin(); iter != mapOfAllocations.end(); ++iter) {
            total += iter->second;
        }
        return total;
    }

    //I overloaded the new and delete keywords so I could manually track allocated memory.
    void* operator new(std::size_t x){
        void *ptr = ::operator new(x);
        mapOfAllocations[ptr] = x;
        return ptr;
    }
    void* operator new[](std::size_t x) {
        void *ptr = ::operator new[](x);
        mapOfAllocations[ptr] = x;
        return ptr;
    }
    void operator delete(void* x) {
        mapOfAllocations.erase(x);
        ::operator delete(x);
    }
    void operator delete[](void* x) {
        mapOfAllocations.erase(x);
        ::operator delete[](x);
    }
private:
    static std::map<void *, std::size_t> mapOfAllocations;
};
std::map<void *, std::size_t> ManageMemory::mapOfAllocations;



//******************
//The node class
//******************
template <typename T>
class Node : public ManageMemory {
public:
    T data;
    Node *link{ nullptr };
};


//******************
//The linked list base class
//This contains within it a class declaration for an iterator
//******************
template <typename T>
class SinglyLinkedListBase : public ManageMemory {
public:

    //public members of the SinglyLinkedList class
    ~SinglyLinkedListBase();
    string getStringFromList();
    void insertFront(const T&);
    void insertBack(const T&);
    T getAtIndex(const unsigned int index) const { cerr << "Error: You didn't override this base class method yet" << endl; T temp{}; return temp; }
    T& operator[](const unsigned int index) const { cerr << "Error: You didn't override this base class method yet" << endl; T temp{}; return temp; }
    void insertAtIndex(const unsigned int index, const T& value) { cerr << "Error: You didn't override this base class method yet" << endl; }
    void insertAtIndex(const unsigned int index, T&& value) { cerr << "Error: You didn't override this base class method yet" << endl; }
    void deleteAtIndex(const unsigned int index) { cerr << "Error: You didn't override this base class method yet" << endl; }
    void deleteAllInstances(const T& value) { cerr << "Error: You didn't override this base class method yet" << endl; }

protected:

    Node<T> *front{ nullptr };
    Node<T> *back{ nullptr };
    int count{ 0 };

};

template <typename T>// destructor
SinglyLinkedListBase<T>::~SinglyLinkedListBase() {
    Node<T> *temp;
    while (front != nullptr) {
        temp = front;
        front = front->link;
        delete temp;
    }
    back = nullptr;
    count = 0;
}

template <typename T>
void SinglyLinkedListBase<T>::insertFront(const T& value) {
    Node<T> *temp = new Node<T>();
    temp->data = value;

    //empty list scenario
    if (front == nullptr) {
        back = temp;
    }
    else {
        temp->link = front;
    }

    front = temp;
    count++;
}

template <typename T>
void SinglyLinkedListBase<T>::insertBack(const T& value) {
    Node<T> *temp = new Node<T>;
    temp->data = value;
    if (front == nullptr) {
        front = temp;
    }
    else {
        //put it on
        back->link = temp;
    }
    back = temp;
    count++;
}


//This method helps return a string representation of all nodes in the linked list, do not modify.
template <typename T>
string SinglyLinkedListBase<T>::getStringFromList() {
    stringstream ss;
    if (front == nullptr) {
        ss << "The list is empty.";
    }
    else {

        Node<T> *currentNode = front;
        ss << currentNode->data;
        currentNode = currentNode->link;

        while (currentNode != nullptr) {
            ss << " " << currentNode->data;
            currentNode = currentNode->link;
        };
    }
    return ss.str();
}

//**********************************
//Write your code below here
//**********************************

template <typename T>
class SinglyLinkedList : public SinglyLinkedListBase<T>  {
public:
    //TODO: Declare your 6 methods here.
    T getAtIndex(const unsigned int index) const;
    T& operator[](const unsigned int index) const;
    void insertAtIndex(const unsigned int index, const T& value);
    void insertAtIndex(const unsigned int index, T&& value);
    void deleteAtIndex(const unsigned int index);
    void deleteAllInstances(const T& value);
};



//TODO: Define your 6 methods here.

/*!
 * getAtIndex returns the value that contains the index in the parameter.
 * @tparam T
 * @param index
 * @return
 */
template <typename T>
T SinglyLinkedList<T>::getAtIndex(const unsigned int index) const {
    Node<T> *temp = this->front;
    int index2 = 0;
    while(temp != this->back)
    {
        if(index2 == index)
        {
            return temp->data;
        }
        temp = temp->link;
        index2++;
    }
    if(index2 == index)
    {
        return temp->data;
    }
    else{
        throw 1;
    }
}

/*!
 * It returns the value at the requested index when the method getAtIndex is called by []
 * @tparam T
 * @param index
 * @return
 */
template <typename T>
T& SinglyLinkedList<T>::operator[](const unsigned int index) const {
    Node<T> *temp = this->front;
    int index2 = 0;
    while(temp!= this->back)
    {
        if(index2 == index)
        {
            return temp->data;
        }
        temp = temp->link;
        index2++;
    }
    if(index2 == index)
    {
        return temp->data;
    }
    else{
        cout << "Invalid Index"<< endl;
        throw 1;
    }
}

template <typename T>
void SinglyLinkedList<T>::insertAtIndex(const unsigned int index, const T &value) {
    Node<T> *temp;
    int index2 = 0;
    while(this->front != this->back)
    {
        if(index2 == index){
            Node<T> *temp2 = new Node<T>;
            temp2->data = value;
            temp = this->front->link;
            this->front=temp2;
            this->front->link = temp;
        }
        this->front = this->front->link;
    }

}

/*!
 * Inserts the value that is sent at the requested index
 * @tparam T
 * @param index
 * @param value
 */
template <typename T>
void SinglyLinkedList<T>::insertAtIndex(const unsigned int index, T &&value) {
    Node<T> *temp=this->front;
    int index2 = 0;
    if (index == 0) {
        Node<T> *temp2 = new Node<T>;
        temp2->data = std::move(value);
        temp2->link = this->front;
        this->front = temp2;
    } else {
        index2++;
        while (temp!=this->back) {
            if (index == index2) {
                Node<T> *temp2 = new Node<T>;
                Node<T> *x = temp->link;
                temp2->data = std::move(value);;
                temp->link=temp2;
                temp2->link=x;
                return;
            }
            index2++;
            temp = temp->link;
        }
        Node<T> *temp2 = new Node<T>;
        temp2->data = std::move(value);;
        temp->link=temp2;
        this->back=temp2;
        return;
    }
}

/*!
 * Deletes the value in the index
 * @tparam T
 * @param index
 */
template <typename T>
void SinglyLinkedList<T>::deleteAtIndex(const unsigned int index) {
    int index2 = 0;
    if(!this->front)
        return;
    if(index == 0){
        Node<T> *NodeToDelete=this->front;
        this->front = this->front->link;
        delete NodeToDelete;
    }
    else{
        Node<T> *temp=this->front;
        if(!temp->link)
            return;
        while(temp!=this->back){
            if ((index-1) == index2) {
                Node<T> *NodeToDelete=temp->link;
                Node<T> *temp2=temp->link;
                temp2=temp2->link;
                delete NodeToDelete;
                temp->link=temp2;
                return;
            }
            index2++;
            if(!temp->link)
                return;
            temp=temp->link;
        }
        cout<<"The index does not exist"<<endl;
        return;
    }

}

/*!
 * Deletes all the values in the list of the value requested
 * @tparam T
 * @param value
 */
template <typename T>
void SinglyLinkedList<T>::deleteAllInstances(const T &value) {
    if(!this->front)
        return;
    while(this->front->data == value){
        Node<T> *NodeToDelete=this->front;
        this->front = this->front->link;
        delete NodeToDelete;
        if(!this->front)
            return;
    }
    Node<T> *temp=this->front;
   // Node<T> *lastValid;
    Node<T> *temp2=temp->link;
    if(!temp->link)
        return;
    while(temp!=this->back){
        if (temp2->data == value) {
            Node<T> *NodeToDelete=temp->link;
            if(!temp2->link)
            {
                NodeToDelete = this->back;
                this->back = temp;
                //temp = lastValid;
                delete NodeToDelete;
                this->back->link = nullptr;

                return;;
            }
            temp2 = temp2->link;
            delete NodeToDelete;
            temp->link=temp2;
        }
        else {
            temp = temp->link;
            temp2 = temp2->link;
           // lastValid = temp;
        }
    }
}
//**********************************
//Write your code above here
//**********************************


//This helps with testing, do not modify.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

    if (whatItShouldBe == whatItIs) {
        cout << "Passed " << testName << endl;
        return true;
    }
    else {
        cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
        return false;
    }
}

//This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

    if (whatItShouldBe == whatItIs) {
        cout << "Passed " << testName << endl;
        return true;
    }
    else {
        cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
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
        cout << "***Failed test " << testName << " *** " << endl << "  You lost track of " << whatItIs << " bytes in memory!" << endl;
        return false;
    }
}

//This helps with testing, do not modify.
void testGetAtIndex() {
    SinglyLinkedList<int> *d = new SinglyLinkedList<int>;
    for (int i = 10; i < 20; i++) {
        d->insertBack(i);
    }

    //Test just to make sure the data went in the list.
    checkTest("testGetAtIndex #1", "10 11 12 13 14 15 16 17 18 19", d->getStringFromList());

    //Test retrieving items.
    int item = d->getAtIndex(0);
    checkTest("testGetAtIndex #2", 10, item);

    item = d->getAtIndex(5);
    checkTest("testGetAtIndex #3", 15, item);

    item = d->getAtIndex(9);
    checkTest("testGetAtIndex #4", 19, item);

    //Make sure the list was undisturbed during this time
    checkTest("testGetAtIndex #5", "10 11 12 13 14 15 16 17 18 19", d->getStringFromList());

    //Try to access out of bounds.
    string caughtError = "";
    try {
        int item = d->getAtIndex(-1);
    }
    catch (int) {
        caughtError = "caught";
    }
    checkTest("testGetAtIndex #6", "caught", caughtError);

    try {
        int item = d->getAtIndex(100);
    }
    catch (int) {
        caughtError = "caught";
    }
    checkTest("testGetAtIndex #7", "caught", caughtError);

    delete d;

    d = new SinglyLinkedList<int>;
    d->insertBack(18);
    item = d->getAtIndex(0);
    checkTest("testGetAtIndex #8", 18, item);
    delete d;
}

//This helps with testing, do not modify.
void testSquareBrackets() {
    SinglyLinkedList<int> d;
    for (int i = 10; i < 20; i++) {
        d.insertBack(i);
    }

    //Test just to make sure the data went in the list.
    checkTest("testSquareBrackets #1", "10 11 12 13 14 15 16 17 18 19", d.getStringFromList());

    //Test retrieving items.
    int item = d[0];
    checkTest("testSquareBrackets #2", 10, item);

    item = d[5];
    checkTest("testSquareBrackets #3", 15, item);

    item = d[9];
    checkTest("testSquareBrackets #4", 19, item);

    //Make sure the list was undisturbed during this time
    checkTest("testSquareBrackets #5", "10 11 12 13 14 15 16 17 18 19", d.getStringFromList());

    //now test the return by reference
    d[1] = 1000;

    checkTest("testSquareBrackets #6", "10 1000 12 13 14 15 16 17 18 19", d.getStringFromList());

    //Try to access out of bounds.
    string caughtError = "";
    try {
        int item = d[-1];
    }
    catch (int) {
        caughtError = "caught";
    }
    checkTest("testSquareBrackets #7", "caught", caughtError);

    try {
        int item = d[100];
    }
    catch (int) {
        caughtError = "caught";
    }
    checkTest("testSquareBrackets #8", "caught", caughtError);

}

//This helps with testing, do not modify.
void testInsertAtIndex() {
    SinglyLinkedList<int> *s = new SinglyLinkedList<int>();
    for (int i = 10; i < 20; i++) {
        s->insertBack(i);
    }

    //Test just to make sure the data went in the list.
    checkTest("testInsertAtIndex #1", "10 11 12 13 14 15 16 17 18 19", s->getStringFromList());

    s->insertAtIndex(3, 33);

    checkTest("testInsertAtIndex #2", "10 11 12 33 13 14 15 16 17 18 19", s->getStringFromList());

    s->insertAtIndex(0, 9);

    checkTest("testInsertAtIndex #3", "9 10 11 12 33 13 14 15 16 17 18 19", s->getStringFromList());

    s->insertAtIndex(12, 20);

    checkTest("testInsertAtIndex #4", "9 10 11 12 33 13 14 15 16 17 18 19 20", s->getStringFromList());

    delete s;

    s = new SinglyLinkedList<int>();

    s->insertAtIndex(0, 42);
    checkTest("testInsertAtIndex #5", "42", s->getStringFromList());

    s->insertAtIndex(1, 82);
    checkTest("testInsertAtIndex #6", "42 82", s->getStringFromList());

    delete s;

    SinglyLinkedList<string> *stringList = new SinglyLinkedList<string>();
    string temp = "Value1";
    stringList->insertAtIndex(0, std::move(temp));
    checkTest("testInsertAtIndex #7", "Value1", stringList->getStringFromList());
    if (temp == "") {
        cout << "Passed testInsertAtIndex #8" << endl;
    }
    else {
        cout << "*** Failed testInsertAtIndex #8, the string still retained its value and wasn't moved." << endl;
    }

    temp = "Value2";
    stringList->insertAtIndex(1, std::move(temp));
    checkTest("testInsertAtIndex #9", "Value1 Value2", stringList->getStringFromList());
    if (temp == "") {
        cout << "Passed testInsertAtIndex #10" << endl;
    }
    else {
        cout << "*** Failed testInsertAtIndex #10, the string still retained its value and wasn't moved." << endl;
    }
    delete stringList;

}

//This helps with testing, do not modify.
void testDeleteAtIndex() {
    SinglyLinkedList<int> *d = new SinglyLinkedList<int>;
    for (int i = 10; i < 17; i++) {
        d->insertBack(i);
    }

    //Test just to make sure the data went in the list.
    checkTest("testDeleteAtIndex #1", "10 11 12 13 14 15 16", d->getStringFromList());

    //Test deleting front items.
    d->deleteAtIndex(0);
    checkTest("testDeleteAtIndex #2", "11 12 13 14 15 16", d->getStringFromList());

    d->deleteAtIndex(0);
    checkTest("testDeleteAtIndex #3", "12 13 14 15 16", d->getStringFromList());

    //Test deleting a middle item
    d->deleteAtIndex(2);
    checkTest("testDeleteAtIndex #4", "12 13 15 16", d->getStringFromList());

    //Test deleting back itmes
    d->deleteAtIndex(3);
    checkTest("testDeleteAtIndex #5", "12 13 15", d->getStringFromList());

    d->deleteAtIndex(2);
    checkTest("testDeleteAtIndex #6", "12 13", d->getStringFromList());

    //Test deleting a Kth element that doesn't exist.
    d->deleteAtIndex(500);
    checkTest("testDeleteAtIndex #7", "12 13", d->getStringFromList());

    //Test deleting a back item
    d->deleteAtIndex(1);
    checkTest("testDeleteAtIndex #8", "12", d->getStringFromList());

    //Test deleting item that doesn't exist
    d->deleteAtIndex(1);
    checkTest("testDeleteAtIndex #9", "12", d->getStringFromList());

    //Test deleting item on the front
    d->deleteAtIndex(0);
    checkTest("testDeleteAtIndex #10", "The list is empty.", d->getStringFromList());

    //Test attempting to delete from an empty list
    d->deleteAtIndex(0);
    checkTest("testDeleteAtIndex #11", "The list is empty.", d->getStringFromList());

    delete d;
}


//This helps with testing, do not modify.
void testdeleteAllInstances() {

    SinglyLinkedList<int> *d = new SinglyLinkedList<int>;

    d->insertBack(4);
    d->insertBack(2);
    d->insertBack(6);
    d->insertBack(5);
    d->insertBack(6);
    d->insertBack(9);

    //Do a delete, test it.
    d->deleteAllInstances(6);
    checkTest("testdeleteAllInstances #1", "4 2 5 9", d->getStringFromList());

    delete d;
    d = new SinglyLinkedList<int>;
    d->insertBack(4);
    d->insertBack(2);
    d->insertBack(3);
    d->insertBack(4);
    d->insertBack(4);
    d->insertBack(4);
    d->insertBack(9);
    d->deleteAllInstances(4);
    checkTest("testdeleteAllInstances #2", "2 3 9", d->getStringFromList());

    delete d;
    d = new SinglyLinkedList<int>;
    d->insertBack(3);
    d->insertBack(3);
    d->insertBack(3);
    d->insertBack(8);
    d->insertBack(2);
    d->insertBack(3);
    d->insertBack(3);
    d->insertBack(3);
    d->deleteAllInstances(3);
    checkTest("testdeleteAllInstances #3", "8 2", d->getStringFromList());

    delete d;
    d = new SinglyLinkedList<int>;
    d->insertBack(9);
    d->insertBack(9);
    d->insertBack(4);
    d->insertBack(2);
    d->insertBack(9);
    d->insertBack(9);
    d->insertBack(5);
    d->insertBack(1);
    d->insertBack(9);
    d->insertBack(2);
    d->insertBack(9);
    d->insertBack(9);

    //Do a delete, test it.
    d->deleteAllInstances(9);
    checkTest("testdeleteAllInstances #4", "4 2 5 1 2", d->getStringFromList());

    //Test deleting something that doesn't exist
    d->deleteAllInstances(7);
    checkTest("testdeleteAllInstances #5", "4 2 5 1 2", d->getStringFromList());

    //A few more tests
    d->deleteAllInstances(2);
    checkTest("testdeleteAllInstances #6", "4 5 1", d->getStringFromList());

    d->deleteAllInstances(4);
    checkTest("testdeleteAllInstances #7", "5 1", d->getStringFromList());

    d->deleteAllInstances(5);
    checkTest("testdeleteAllInstances #8", "1", d->getStringFromList());

    d->deleteAllInstances(1);
    checkTest("testdeleteAllInstances #9", "The list is empty.", d->getStringFromList());

    //retest deleting something that doesn't exist.
    d->deleteAllInstances(7);
    checkTest("testdeleteAllInstances #10", "The list is empty.", d->getStringFromList());
    delete d;

    //Now ramp it up and do some huge tests.  Start by timing how long a smaller approach takes.
    d = new SinglyLinkedList<int>;
    //Fill the list with a pattern of
    //1 2 2 3 3 3 4 4 4 4 1 2 2 3 3 3 4 4 4 4 ...
    cout << endl << "Preparing for testdeleteAllInstances #11, placing 75,000 numbers into the linked list to see how long things take." << endl;
    for (int i = 0; i < 30000; i++) {
        for (int j = 0; j < i % 4 + 1; j++) {
            d->insertBack(i % 4 + 1);
        }
    }
    cout << "    Calling deleteAtIndex to remove 22,500 3s in the list." << endl;
    //delete all the 3s.
    auto start = std::chrono::high_resolution_clock::now();
    d->deleteAllInstances(3);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> diff = end - start;
    double benchmarkTime = diff.count() / 1000.0;
    cout << "    Removing 22,500 3s took " << benchmarkTime << " milliseconds." << endl;
    cout << "    So we will assume removing 45,000 3s then should be double that..." << endl;
    cout << "	 about " << benchmarkTime << " * 2 = " << (benchmarkTime * 2) << " milliseconds if done correctly." << endl;
    delete d;

    cout << "Starting testdeleteAllInstances #11, filling in 150,000 numbers into the linked list to get it started." << endl;
    d = new SinglyLinkedList<int>;
    //Fill the list with a pattern of
    //1 2 2 3 3 3 4 4 4 4 1 2 2 3 3 3 4 4 4 4 ...
    for (int i = 0; i < 60000; i++) {
        for (int j = 0; j < i % 4 + 1; j++) {
            d->insertBack(i % 4 + 1);
        }
    }
    cout << "    Finished inserting 150,000 numbers." << endl;
    cout << "    Calling deleteAtIndex to remove 45,000 3s.  This should take about " << (benchmarkTime * 2) << " milliseconds." << endl;
    //delete all the 3s.
    start = std::chrono::high_resolution_clock::now();
    d->deleteAllInstances(3);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    double actualTime = diff.count() / 1000.0;
    if (actualTime < (benchmarkTime * 2 * 1.5)) { //The 1.5 gives an extra 50% wiggle room
        cout << "Passed testdeleteAllInstances #11, completed deleteAtIndex in " << actualTime << " milliseconds." << endl;

    }
    else {
        cout << "*** Failed testdeleteAllInstances #11, deleteAtIndex took " << actualTime
             << " milliseconds." << endl;
        cout << "*** This which is much worse than the expected " << (benchmarkTime * 2) << " milliseconds." << endl;
    }
    delete d;

}


void pressAnyKeyToContinue() {
    cout << "Press enter to continue...";

    //Linux and Mac users with g++ don't need this
    //But everyone else will see this message.
    cin.get();

}


int main() {


    //Each of these checks how many bytes you have used.
    checkTestMemory("Memory Leak/Allocation Test #1", 0, ManageMemory::getTotalSize());

    //For your assignment, write the code to make these three methods work
    //You should not modify the code here in main.
    testGetAtIndex();

    checkTestMemory("Memory Leak/Allocation Test #2", 0, ManageMemory::getTotalSize());

    testSquareBrackets();

    checkTestMemory("Memory Leak/Allocation Test #3", 0, ManageMemory::getTotalSize());

    testInsertAtIndex();

    checkTestMemory("Memory Leak/Allocation Test #4", 0, ManageMemory::getTotalSize());

    testDeleteAtIndex();

    checkTestMemory("Memory Leak/Allocation Test #5", 0, ManageMemory::getTotalSize());

    testdeleteAllInstances();

    checkTestMemory("Memory Leak/Allocation Test #6", 0, ManageMemory::getTotalSize());

    pressAnyKeyToContinue();


    return 0;
}