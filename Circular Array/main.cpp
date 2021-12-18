// San Diego State University
// CS210/CS496: Data Structures
//
// File: main.cpp
// Exercises and tests a CircularArray based Queue
//
// This project uses the files:
//    main.cpp    <- Driver
//    Queue.hpp   <- Interface / Pure Class
//    List.hpp    <- Interface / Pure Class
// -> CircularArray.cpp <-(student's code)
//
// Note: This file is VOLATILE in that it will change during lectures as Healey
// adds additional tests. The changes made here should not impact your working
// CircularArray, for this class.

#define VERSION         0.2

#define TARGET_VALUE    210496
#define TEST_START_SIZE 1024
#define NUM_TEST_PAIRS  1000000

#define PRINT_PASS_FAIL(__VAL)  {std::cout << (__VAL == true ? "PASS\n":"FAIL\n");}

// This comment is stupid and normally wouldn't be here, but since you are new
// to the language, it can't hurt to describe a little about the #include.
// This is a c-style instruction to something called a pre-processor which
// instructs it to literally cut and paste the text it finds in that file at
// this spot in the file. As a result, the order of these includes can impact
// if your program compiles and works correctly. It does not for these two,
// but it absolutely can with other .h files -- especially when you start
// including custom header files.
// This particular #include allows us access to the input/output stream
// for std::cout and std::cin
#include <iostream>
// This particular #include gives us access to the std::setw() function
#include <iomanip>

// The #include files below are 'custom' header files, and they are the files
// that this module directly uses (each one may end up including other files).
// The quotation marks tell teh pre-processor to look in the project directory.
#include "Queue.h"
#include "List.h"
#include "CircularArray.h"

// This would be a great spot to forward-declare the test functions, but I am
// not doing that just to show it's not required. Also, Google recommends
// those declarations appear in a header file anyway, so putting them here is
// questionable.
// What is a forward-declaration? Check below:
// sdsu::Queue<T> *getSequentialQueue(int);

// This function does the repetitive task of instantiating and building a new
// queue entirely from nothing. One may cast the return value to a List in
// this program.
//
// Parameters: size of queue to build
// Return: The address (a pointer) to a Queue on the heap
template<typename T>
sdsu::Queue<T> *getSequentialQueue(int size) {
    sdsu::Queue<T> *uut = new sdsu::CircularArray<int>();
    // Build up the test . . . prep.
    for (int i = 0; i < size; i++) {
        uut->enqueue((T) i);
    }
    return uut;
}
template<typename T>
sdsu::List<T> *getSequentialList(int size) {
    sdsu::List<T> *uut = new sdsu::CircularArray<int>();
    // Build up the test . . . prep.
    for (int i = 0; i < size; i++) {
        uut->addLast((T) i);
    }
    return uut;
}

template<typename T, int SIZE>
bool testClear_addSIZE_isEmptyTrue() {

    sdsu::Queue<int> *uut = getSequentialQueue<int>(SIZE);

    bool status = false;
    if(uut->isEmpty() == false ) {
        uut->clear();
        status = uut->isEmpty();
    }

    delete uut;
    return status;
}

template<typename T, int SIZE>
bool testSize_addSIZEitems_correctAtStop() {

    sdsu::Queue<int> *uut = getSequentialQueue<int>(SIZE);
    int actualSize = uut->size();

    delete uut;
    return SIZE == actualSize;
}

template<typename T, int SIZE>
bool testSize_addSIZEitemsRemoveOne_correctAtStop() {

// todo: healey will produce this test in a future lecture video
return false;
}

template<typename T, int SIZE>
bool testPeek_addSIZEitems_correctFirst(T exp, T modifiedValue){

    sdsu::Queue<int> *uut = getSequentialQueue<int>(SIZE);
    T& datum = uut->peek();
    datum = modifiedValue;
    datum = uut->peek();

    bool status = (modifiedValue == datum);
    delete uut;
    return status;
}

void versionReport(){
    std::cout << std::string(4,'-') << " Version Report " << std::string(4,'-');
    std::cout << std::endl;
    std::cout << "|" << std::setw(16) << "Main Version: " <<
    std::setw(4) << VERSION << "  |" << std::endl;

    std::cout << "|" << std::setw(16) << "Queue ADT: " <<
    std::setw(4) << VERSION_QUEUE <<  "  |" << std::endl;
    std::cout << "|" << std::setw(16) << "List ADT: " <<
    std::setw(4) << VERSION_LIST << "  |" << std::endl;
    std::cout << std::string(24,'-') << std::endl;
}

// SPOT THE MEMORY LEAK
template <int SIZE>
bool testDequeue_enqueueSIZEitems_dequeueCorrectOrder(){
    // build it up
    sdsu::Queue<int> *uut = new sdsu::CircularArray<int>();
    for(int i = 0; i < SIZE; i++){
        uut->enqueue(i);
    }

    // run the test
    for(int i = 0; i < SIZE; i++){
        if( uut->dequeue() != i ) return false;
    }
    return true;
}

// SPOT THE MEMORY LEAK . . . this would be great in Java
template <int SIZE>
bool testEnqueue_SIZEitems_correctListOrder(){
    sdsu::Queue<int> *uut = new sdsu::CircularArray<int>();
    for( int i = 0; i < SIZE; i++){
        uut->enqueue(i);
    }

    // Verify!
    sdsu::List<int> *castUut = (sdsu::CircularArray<int> *)(uut);
    for(int i = 0; i < SIZE; i++){
        try {
            if (castUut->get(i) != i) return false;
        }
        catch (std::out_of_range &e){
            std::cout << "[Range Exception]";
            return false;
        }
    }
    return true;
}

template <int SIZE>
void testQueueMethods(){

    std::cout << "Testing Clear " << SIZE << " int . . . ";
    bool status = testClear_addSIZE_isEmptyTrue<int, SIZE>();
    PRINT_PASS_FAIL(status);
    std::cout << "Testing Clear " << SIZE << " char . . . ";
    status = testClear_addSIZE_isEmptyTrue<char, SIZE>();
    PRINT_PASS_FAIL(status);

    std::cout << "Testing Size " << SIZE << " items . . . ";
    status = testSize_addSIZEitems_correctAtStop<int,SIZE>();
    PRINT_PASS_FAIL(status);
    std::cout << "Testing Size " << SIZE -1 << " items . . . ";
    status = testSize_addSIZEitemsRemoveOne_correctAtStop<int,SIZE>();
    PRINT_PASS_FAIL(status);

    std::cout << "Testing Peek " << SIZE << " items . . . ";
    status = testPeek_addSIZEitems_correctFirst<int,SIZE>(0,-210);
    PRINT_PASS_FAIL(status);

    std::cout << "Testing Dequeue " << SIZE << " items . . . ";
    status = testDequeue_enqueueSIZEitems_dequeueCorrectOrder<SIZE>();
    PRINT_PASS_FAIL(status);

    std::cout << "Testing Enqueue " << SIZE << " items . . . ";
    status = testEnqueue_SIZEitems_correctListOrder<SIZE>();
    PRINT_PASS_FAIL(status);
}

bool testGet_addItemsFrontBack_middleCorrectValue(int numPairs){

    // Build up a list of 2*numPairs items + 1
    sdsu::List<int> *uut  = new sdsu::CircularArray<int>();
    uut->addFirst(TARGET_VALUE);
    for( int i = 0; i < numPairs; i++){
        uut->addFirst(i);
        uut->addLast(i);
    }

    // Test GET by inspecting known value
    int value = 0;
    try{
        value = uut->get(numPairs);
    }
    catch (std::out_of_range &e){
        std::cout << "[Range Exception]";
    }
    bool status = (value == TARGET_VALUE);

    delete uut;
    return status;
}

bool testRemove_InvalidRange_ExceptionThrown(){
    sdsu::List<int> *uut = new sdsu::CircularArray<int>();

    bool status = false;

    try{
        uut->remove(-1);
    }
    catch (std::out_of_range &e){
        std::cout << "["<< e.what() << "]";
        status = true;
    }
    delete uut;
    return status;
}

bool testRemoveLast_oneItemInList_getThrowsException(){

    bool status = false;
    sdsu::List<int> *uut = new sdsu::CircularArray<int>();
    uut->addFirst(TARGET_VALUE);


    // test 1: Verify get yields the target value.
    try {
        if( uut->get(0) == TARGET_VALUE ) status = true;
    }
    catch(std::out_of_range &e){
        std::cout << "[Test 1]";
        delete uut;
        return false;
    }

    // setup for test2: delete the only item in the list
    uut->removeLast();

    try{
        uut->get(0);
        std::cout << "[Test 2]";
    }
    catch (std::out_of_range &e){
        status = true;
    }

    delete uut;
    return status;
}

template <int SIZE>
void testListMethods(){

    bool curStatus;

    std::cout << "Testing Get(int) " << (NUM_TEST_PAIRS*2) +1 << " items . . . ";
    curStatus = testGet_addItemsFrontBack_middleCorrectValue(NUM_TEST_PAIRS);
    PRINT_PASS_FAIL(curStatus);

    std::cout << "Testing Remove(-1) . . . ";
    curStatus = testRemove_InvalidRange_ExceptionThrown();
    PRINT_PASS_FAIL(curStatus);

    std::cout << "Testing removeLast . . . ";
    curStatus = testRemoveLast_oneItemInList_getThrowsException();
    PRINT_PASS_FAIL(curStatus)
}

template <typename T>
bool testCopyConstructor(){

    std::cout << "Testing Copy Constructor . . ";
    sdsu::CircularArray<int> a;
    sdsu::CircularArray<int> b = a;

    // mutate b
    b.enqueue(1);
    // make sure a is unchanged
    bool status = (a.size() == 0 && b.size() == 1);
    PRINT_PASS_FAIL(status);

    return status;
}

// This is where the program begins execution after initializing globals.
int main() {

    versionReport();

    testCopyConstructor<int>();

    testQueueMethods<TEST_START_SIZE>();
    testListMethods<TEST_START_SIZE>();

    std::cout << "Complete!" << std::endl;

    // returning from main terminates the program. Any non-zero number
    // indicates an error.
    return 0;
}
