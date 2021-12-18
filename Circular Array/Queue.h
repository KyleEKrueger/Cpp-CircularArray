// San Diego State University
// CS210/CS496: Data Structures
//
// File: Queue.h
// Defines the required methods for a First-In-First-Out data structure.

// version 0.2 Change: Added size method to clear up casting
#define VERSION_QUEUE 0.2

#ifndef PROG1_QUEUE_H
#define PROG1_QUEUE_H

namespace sdsu {
    template<typename T>
    class Queue {

    public:

        virtual ~Queue() {} ;

        // Resets the Queue to an empty state.
        //
        // Complexity: Constant (This is not a crypt-clear)
        virtual void clear() = 0;

        // Returns the item at the front of the queue and removes it from the
        // queue. If the queue is empty, this method returns nullptr.
        //
        // Complexity: Constant
        virtual T dequeue() = 0;

        // Inserts the parameter item into the queue at its end. If the queue
        // has capacity, this operation results in the size increasing by one
        // and this function returns true. If, for some reason, the queue
        // cannot store the parameter object, it returns false.
        //
        // Complexity: Constant
        // Input Parameters: The typename T object to insert into the Queue
        // Returns: true if successful and false if the queue lacks capacity
        //
        // Note: This function is written to look similar to Java's style,
        // but this method SCREAMS for C++ style coding optimization. There is
        // a totally unnecessary copy operation happening here.
        virtual bool enqueue(T) = 0;

        // Tests if the Queue contains any items.
        //
        // This method is equivalent to:
        //   (size()==0) ? true: false;
        //
        // Complexity: Constant
        // Returns: true if the queue holds no items and false otherwise
        virtual bool isEmpty() const = 0;

        // Provides a look at the first item in the queue without removing
        // it from the structure.
        //
        // Complexity: Constant
        // Returns: A copy of the first item
        virtual T& peek()  = 0;

        // Reports size
        // Added version 0.2 to eliminate unnecessary casting
        virtual int size() const = 0;
    };

}
#endif //PROG1_QUEUE_H
