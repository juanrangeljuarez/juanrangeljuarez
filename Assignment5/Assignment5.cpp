//Copyright 2018, Bradley Peterson, Weber State University, all rights reserved.

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <memory>


//To prevent those using g++ from trying to use a library
//they don't have
#ifndef __GNUC__
#include <conio.h>
#else
#include <cstdio>
#endif


//forward declarations
template <typename T> class HashTable;

using std::cout;
using std::endl;
using std::map;
using std::unique_ptr;
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


//************************************************************************************
//A quick and simple class that simulates a product object.
//************************************************************************************
class product {
public:
    void setCost(int cost);
    void setName(const string&);
    string getName();
    int getCost();
    string getAllInfo();
private:
    string name;
    int cost;
};
void product::setCost(int cost) {
    this->cost = cost;
}
void product::setName(const string& name) {
    this->name = name;
}
string product::getName() {
    return name;
}
int product::getCost() {
    return cost;
}
string product::getAllInfo() {
    stringstream ss;
    ss << "Name: " << name << ", Cost: " << cost;
    return ss.str();
}



//****************************
//The keyvalue pair class
//****************************
template <typename T>
class KeyValuePair {
public:
    //Default constructor
    KeyValuePair() {}

    //Copy assignment operator
    KeyValuePair& operator=(const KeyValuePair& obj) {
        KeyValuePair temp;
        return temp;
    }

    //Copy constructor
    KeyValuePair(const KeyValuePair<T>& obj) {
        this->key = obj.key;
        this->value = obj.value;
    }

    //Move consturctor
    KeyValuePair(KeyValuePair<T>&& obj) {
        this->key = std::move(obj.key);
        this->value = std::move(obj.value);
    }

    //Constructor to copy L-values
    KeyValuePair(const string& key, const T& value) {
        this->key = key;
        this->value = value;
    }

    //Constructor to move R-values
    KeyValuePair(const string& key, T&& value) {

        this->key = key;
        this->value = std::move(value);
    }

    string key;
    T value;
};


//******************
//The HashTable class
//******************
template <typename T>
class HashTable : public ManageMemory
{
public:;
    unsigned int getNumBuckets() { return capacity; }
    unsigned int getTotalCount() const;
    unsigned int getWorstClump() const;

    // TODO: Create the array and initialize the 3 arrays
    // (note that you don't have to initialize the array values to default values, make_unique does that for you!)
    HashTable();

    HashTable(const HashTable<T>& obj) {
        cout << "Failed homework issue:  You hit the HashTable copy constructor.  That's bad!" << endl;
    }
    HashTable& operator=(const HashTable& obj) {
        cout << "Failed homework issue:  You hit the HashTable copy assignment.  That's bad!" << endl;
        HashTable temp;
        return temp;
    }

    //TODO: Add an operator= move method.  This involves moving all the unique pointers.  Also copying over the ints and setting the source ints to zero.
    HashTable& operator=(HashTable<T>&& obj);


    //TODO: supply these methods
    void create(const string& key, T&& item);   //method for R - values
    T retrieve(const string& key);           //method(return by value, acts as a read only retrieve)
    T& operator[](const string& key);         //method(return by reference which can allow for modification of values)
    bool exists(const string& key);             //method(returns a boolean)
    void remove(const string& key);             //method

    //Note, for simplicity, don't do a by reference create method.


private:

    //TODO: This private method can be helpful to reduce code duplication
    //void create(const string& key, T&& item, std::unique_ptr<int[]>& status_arr, std::unique_ptr<string[]>& key_arr, std::unique_ptr<T[]>& value_arr);
    void create(const string& key, T&& item, std::unique_ptr<int[]>& status_arr, std::unique_ptr<string[]>& key_arr, std::unique_ptr<T[]>& value_arr);
    unsigned int hash(const string& key) const;

    //TODO, create a capcity, count, int array called status_arr, string array called key_arr, and a T array called value_arr.  The arrays should be unique_ptr data types
    int capacity;
    int count;
    std::unique_ptr<int[]> status_arr;
    std::unique_ptr<string[]> key_arr;
    std::unique_ptr<T[]> value_arr;

};// end class HashTable


template <typename T>
unsigned int HashTable<T>::hash(const string& key) const {

    return std::hash<std::string>{}(key) % capacity;

}

template <typename T>
unsigned int HashTable<T>::getTotalCount() const {
    unsigned int count = 0;
    for (int i = 0; i < capacity; i++) {
        if (status_arr[i] == 1) {
            count++;
        }
    }
    return count;
}

template <typename T>
unsigned int HashTable<T>::getWorstClump() const {
    unsigned int clumpCount = 0;
    unsigned int maxClump = 0;
    for (int i = 0; i < capacity; i++) {
        if (status_arr[i] == 1) {
            clumpCount++;
        }
        else {
            if (clumpCount > maxClump) {
                maxClump = clumpCount;
                clumpCount = 0;
            }
        }
    }
    if (clumpCount > maxClump) {
        maxClump = clumpCount;
    }
    return maxClump;
}

template <typename T>
HashTable<T>::HashTable() {
    capacity = 10;
    count = 0;
    status_arr = std::make_unique<int[]>(capacity);
    key_arr = std::make_unique<string[]>(capacity);
    value_arr = std::make_unique<T[]>(capacity);
}

template <typename T>
HashTable<T> &HashTable<T>::operator=(HashTable<T> &&obj){
    this->status_arr = std::move(obj.status_arr);
    this->value_arr = std::move(obj.value_arr);
    this->key_arr = std::move(obj.key_arr);
    this->capacity = std::move(obj.capacity);
    this->count = std::move(obj.count);
    obj.capacity= 0;
    obj.count = 0;
    return obj;
}

template <typename T>
T& HashTable<T>::operator[](const string &key) {
    auto index = hash(key);
    bool flag = true;
    for (int i = index; i < this->capacity; ++i) {
        if(this->status_arr[i] == 1)
        {
            if(this->key_arr[i] == key)
            {
                return this->value_arr[i];
            }
        }
         if(this->status_arr[i] == 0)
         {
             throw 1;
         }
        if(i == this->capacity && flag)
        {
            flag = false;
            i = 0;
        }
    }
    throw 1;
}

template <typename T>
T HashTable<T>::retrieve(const string &key) {
    auto index = hash(key);
    bool flag = true;
    for (int i = index; i < this->capacity; ++i)
    {
        if(this->status_arr[i] == 1)
        {
            if(this->key_arr[i] == key)
            {
                return this->value_arr[i];
            }
        }
        if(this->status_arr[i] == 0)
        {
            throw 1;
        }
        if(i == this->capacity && flag)
        {
            flag = false;
            i = 0;
        }
    }
    throw 1;
}

template <typename T>
void HashTable<T>::remove(const string &key) {
    auto index = hash(key);
    bool flag = true;
    for (int i = index; i < this->capacity; ++i) {
        if(this->status_arr[i] == 1)
        {
            if(this->key_arr[i] == key)
            {
                this->status_arr[i] = -1;
                this->count--;
                return;
            }
        }
        if(this->status_arr[i] == 0)
        {
            return;
        }
        if(i == this->capacity && flag)
        {
            flag = false;
            i = 0;
        }
    }
    return;
}



template <typename T>
bool HashTable<T>::exists(const string &key) {
    auto index = hash(key);
    bool flag = true;
    for (int i = index; i < this->capacity; ++i) {
        if(this->status_arr[i] == 1)
        {
            if(this->key_arr[i] == key)
            {
                return true;
            }
        }
        if(this->status_arr[i] == 0)
        {
            return false;
        }
        if(i == this->capacity && flag)
        {
            flag = false;
            i = 0;
        }
    }
    return false;
}


template <typename T>
void HashTable<T>::create(const string &key, T &&item) {
    int oldCapacity;
    float percentage = ((this->count+1)/(this->capacity*1.0));
    if(percentage > 0.75)
    {
        oldCapacity = this->capacity;
        this->capacity = this->capacity * 2;
        std::unique_ptr<int[]>array1;
        std::unique_ptr<string[]> array2;
        std::unique_ptr<T[]> array3;
        array1 = std::make_unique<int[]>(this->capacity);
        array2 = std::make_unique<string[]>(this->capacity);
        array3 = std::make_unique<T[]>(this->capacity);
        for (int i = 0; i < oldCapacity; ++i) {
            if(this->status_arr[i]==1)
            {
                auto position = hash(this->key_arr[i]);
                bool flag = true;
                do {
                    if (array1[position] == 0 || array1[position] == -1) {
                        array1[position] = std::move(this->status_arr[i]);
                        array2[position] = std::move(this->key_arr[i]);
                        array3[position] = std::move(this->value_arr[i]);
                        flag = false;
                    } else {
                        position++;
                        if(position == capacity)
                            position = 0;
                    }
                }while (flag);
            }
        }
        this->status_arr = std::move(array1);
        this->key_arr = std::move(array2);
        this->value_arr = std::move(array3);
    }
    int position = hash(key);
    bool flag = true;
    int count = position;
    while (flag) {
        if (this->status_arr[count] == 0 || this->status_arr[count] == -1) {
            this->status_arr[count] = 1;
            this->key_arr[count] = std::move(key);
            this->value_arr[count] = std::move(item);
            this->count++;
            flag = false;
        }
        count++;
        if (count == capacity && flag)
            count = 0;
    }
}


//This helps with testing, do not modify.
template <typename T>
string NumberToString(T Number)
{
    stringstream ss;
    ss << Number;
    return ss.str();
}

//This helps with testing, do not modify.
bool checkEmpty(string testName, string whatItIs) {

    if (whatItIs != "") {
        cout << "Passed " << testName << ", the data was " << whatItIs << endl;
        return true;
    }
    else {
        cout << "***Failed test " << testName << " *** " << endl << "   No data was found! " << endl;
        return false;
    }
}

//This helps with testing, do not modify.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

    if (whatItShouldBe == whatItIs) {
        cout << "Passed " << testName << endl;
        return true;
    }
    else if (whatItShouldBe == "") {
        cout << "****** Failed test " << testName << " ****** " << endl << "     Output was '" << whatItIs << endl << "'     Output should have been blank" << endl;
        return false;

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
        cout << "***Failed test " << testName << " *** " << endl << "  There are " << whatItIs << " bytes of memory yet to be reclaimed!" << endl;
        return false;
    }
}


//This helps with testing, do not modify.
void testSimpleIntHash() {

    HashTable<string> myHash;

    //Test #1, add "Jazz" into our hash with a key of 6.  Try to retrieve it.
    myHash.create("6", "Jazz");
    checkTest("testSimpleIntHash #1", "Jazz", myHash.retrieve("6"));

    //Test #2, attempt to get the Jazz using the operator[] code.
    checkTest("testSimpleIntHash #2", "Jazz", myHash["6"]);

    //Test #3, attempt to change the value at this location:
    myHash["6"] = "Nuggets";

    checkTest("testSimpleIntHash #3", "Nuggets", myHash["6"]);

    //Test #4,
    //See if we can find it
    if (myHash.exists("6")) {
        checkTest("testSimpleIntHash #4", "", "");
    }
    else {
        checkTest("testSimpleIntHash #4", "This test should have found an item with key \"6\"", "This test did NOT find an item with key \"6\"");
    }

    //Test #5, see if we can find something that doesn't exist yet.
    if (myHash.exists("1234")) {
        checkTest("testSimpleIntHash #5", "This test should NOT have found an item with key \"1234\".", "This test found an item with key \"1234\"");
    }
    else {
        checkTest("testSimpleIntHash #5", "", "");
    }

    //Test #6, removing it from the hash
    myHash.remove("6");
    if (myHash.exists("6")) {
        checkTest("testSimpleIntHash #6", "This test should NOT have found an item with key \"6\".", "This test found an item with key \"6\"");
    }
    else {
        checkTest("testSimpleIntHash #6", "", "");
    }

    //Add more into the hash
    myHash.create("13", "Lakers");
    myHash.create("25", "Bulls");
    myHash.create("101", "Pelicans");
    myHash.create("77", "Bucks");
    myHash.create("12", "Thunder");
    myHash.create("42", "Nets");
    myHash.create("97", "Timberwolves");
    myHash.create("123", "Hornets");
    myHash.create("500", "Mavericks");

    //Attempt to retrieve some
    checkTest("testSimpleIntHash #7", "Thunder", myHash.retrieve("12"));
    checkTest("testSimpleIntHash #8", "Bucks", myHash.retrieve("77"));
    checkTest("testSimpleIntHash #9", "Hornets", myHash.retrieve("123"));

    //Now count up how many are in there
    checkTest("testSimpleIntHash #10", 9, myHash.getTotalCount());

    //Now just verify that they aren't clumping up badly.
    int worst = 0;
    worst = myHash.getWorstClump();
    if (worst > 10) {
        cout << "Failed testSimpleIntHash #11!  There exists a clump of " << worst << " consecutive items, it shouldn't be worse than 10." << endl;
    }
    else {
        cout << "Passed testSimpleIntHash #11.  Your worst clump was " << worst << " items." << endl;
    }

}


void testHashOfObjects() {

    //Create a HashTable. We want this to be a hash table with int keys, string object values,
    //And we also supply the hash function we want to use for integers..

    HashTable<product> myHash;

    //Test #1, add in a studentObject.  Try to retrive it.
    product tempProduct;
    tempProduct.setCost(5);
    tempProduct.setName("Silly string");
    myHash.create("12341-51231", std::move(tempProduct));
    checkTest("testHashOfObjects #1", "Silly string", myHash.retrieve("12341-51231").getName());

    //Test #2, attempt to get the product using its ID code
    checkTest("testHashOfObjects #2", "Silly string", myHash["12341-51231"].getName());

    //Test #3, see what happens if two products have the same ID code.  This should overwrite the former.
    tempProduct.setCost(18);
    tempProduct.setName("Novelty foam hat");
    myHash["12341-51231"] = tempProduct;
    checkTest("testHashOfObjects #3", "Novelty foam hat", myHash["12341-51231"].getName());

    //Test #4,
    //See if we can find it
    if (myHash.exists("12341-51231")) {
        checkTest("testHashOfObjects #4", "", "");
    }
    else {
        checkTest("testHashOfObjects #4", "This test should have found an item with key 12341-51231", "This test did NOT find an item with key 12341-51231");
    }

    //Test #5, see if we can find something that doesn't exist yet.
    if (myHash.exists("56756-75675")) {
        checkTest("testHashOfObjects #5", "This test should NOT have found an item with key 56756-75675.", "This test found an item with key56756-75675");
    }
    else {
        checkTest("testHashOfObjects #5", "", "");
    }

    //Test #6, removing it from the hash
    myHash.remove("12341-51231");
    if (myHash.exists("12341-51231")) {
        checkTest("testHashOfObjects #6", "This test should NOT have found an item with key 12341-51231.", "This test found an item with key 12341-51231");
    }
    else {
        checkTest("testHashOfObjects #6", "", "");
    }

    //Now throw in many more items.
    int value = 0;
    string key;
    stringstream out;
    for (unsigned int i = 0; i < 10000; i++) {
        //this next part just helps create some variation for our produce ID codes.
        if (i % 2 == 0) {
            value += 107;
        }
        else if (i % 3 == 0) {
            value += 83;
        }
        else if (i % 5 == 0) {
            value += 47;
        }
        else if (i % 7 == 0) {
            value += 131;
        }
        else {
            value += 53;
        }
        key = "12345-";
        out.str("");
        if (value < 100000)
            key = key + "0";
        if (value < 10000)
            key = key + "0";
        if (value < 1000)
            key = key + "0";
        if (value < 100)
            key = key + "0";
        if (value < 10)
            key = key + "0";
        out << value;
        string temp = out.str();
        if (temp.length() > 5) {
            temp = temp.substr(0, 5);
        }
        key = key + temp;
        //Whew, that took a while, but the W# is in key, and is ready to go

        //Create the student record, and load in values.
        tempProduct.setName("Acme product");
        tempProduct.setCost(rand() % 41);

        //Testing the hash table "add" method
        myHash.create(key, std::move(tempProduct));
    }

    //Make sure one went in correctly.  Retrieve it.
    checkEmpty("testHashOfObjects #7", myHash["12345-002112"].getAllInfo());

    //Make sure they all go in there.
    checkTest("testHashOfObjects #8", 10000, myHash.getTotalCount());

    //Now test how good your int hash function is.
    int worst = myHash.getWorstClump();
    if (worst > 1000) {
        cout << "Failed testSimpleIntHash #9!  There exists a clump of " << worst << " consecutive items, it shouldn't be worse than 1000." << endl;
    }
    else {
        cout << "Passed testSimpleIntHash #9.  Your worst clump was " << worst << " items." << endl;
    }

}


//This helps with testing, do not modify.
void testHashofHashes() {

    HashTable< HashTable<int> > studentAssignments;
    studentAssignments.create("Alice", HashTable<int>());

    HashTable<int> tempHash2;
    studentAssignments.create("Bob", HashTable<int>());

    HashTable<int> tempHash3;
    studentAssignments.create("Karl", HashTable<int>());

    //Give alice some assignment scores
    studentAssignments["Alice"].create("1", 73);
    studentAssignments["Alice"].create("2", 65);
    studentAssignments["Alice"].create("4", 91);
    //Ensure it went in
    checkTest("testHashofHashes #1", 65, studentAssignments["Alice"]["2"]);

    //And Bob
    studentAssignments["Bob"].create("1", 90);
    studentAssignments["Bob"].create("3", 84);
    studentAssignments["Bob"].create("4", 99);

    //And Karl
    studentAssignments["Karl"].create("1", 92);
    studentAssignments["Karl"].create("2", 92);
    studentAssignments["Karl"].create("3", 87);
    studentAssignments["Karl"].create("4", 10);

    //Now find the average of assignment 4 scores
    int average = (studentAssignments["Alice"]["4"] + studentAssignments["Bob"]["4"] + studentAssignments["Karl"]["4"]) / 3;
    checkTest("testHashofHashes #2", 66, average);

}

void testRehashing() {

    HashTable<string> myHash;

    //Throw in more items.
    int key = 0;
    stringstream out;
    for (unsigned int i = 0; i < 10000; i++) {

        //this next part just helps create some variation in generated W#s...
        if (i % 2 == 0) {
            key += 17;
        }
        else if (i % 3 == 0) {
            key += 23;
        }
        else if (i % 5 == 0) {
            key += 51;
        }
        else if (i % 7 == 0) {
            key += 13;
        }
        else {
            key += 71;
        }
        //convert an int to a string via help from the stringstream class
        out.str("");
        out << key;
        string temp = out.str();

        out.str("");
        out << "a-" << i;
        string value = out.str();
        myHash.create(temp, std::move(value)); //Just add a bunch of letter a's
    }

    //Make sure they all go in there.
    checkTest("testRehashing #1", 10000, myHash.getTotalCount());

    //Make sure the capacity is large enough
    checkTest("testRehashing #2", 20480, myHash.getNumBuckets());

    //Verify one of the values in the hash table.
    checkTest("testRehashing #3", "a-2345", myHash.retrieve("76154"));

    int worst = myHash.getWorstClump();
    if (worst > 1000) {
        cout << "Failed testRehashing #4!  There exists a clump of " << worst << " consecutive items, it shouldn't be worse than 1000." << endl;
    }
    else {
        cout << "Passed testRehashing #4.  Your worst clump was " << worst << " items." << endl;
    }

    //Remove the key "184275".
    myHash.remove("184275");
    if (myHash.exists("184275")) {
        checkTest("testRehashing #5", "This test should NOT have found an item with key \"2437968\".", "This test found an item with key \"2437968\"");
    }
    else {
        checkTest("testRehashing #5", "", "");
    }
    //There should be one less value now
    checkTest("testRehashing #6", 9999, myHash.getTotalCount());

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

    testSimpleIntHash();
    checkTestMemory("Memory Leak/Allocation Test #1", 0, ManageMemory::getTotalSize());
    //pressAnyKeyToContinue();

    testHashOfObjects();
    checkTestMemory("Memory Leak/Allocation Test #2", 0, ManageMemory::getTotalSize());
    //pressAnyKeyToContinue();

    testHashofHashes();
    checkTestMemory("Memory Leak/Allocation Test #3", 0, ManageMemory::getTotalSize());
    // pressAnyKeyToContinue();

    testRehashing();
    checkTestMemory("Memory Leak/Allocation Test #4", 0, ManageMemory::getTotalSize());
    pressAnyKeyToContinue();

    return 0;
}