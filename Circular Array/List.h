// San Diego State University
// CS210/CS496: Data Structures
//
// File: List.h
// Defines the required methods for an collection with ordering.

#define VERSION_LIST 0.1

#ifndef PROG1_LIST_H
#define PROG1_LIST_H

namespace sdsu {
    template<typename T>
    class List {
    public:
        virtual ~List(){};

        // Inserts the parameter item into the list at the 0th equivalent index
        //
        // Complexity: Constant for circular arrays (Linear otherwise).
        // Parameter: the item to insert at the front of the list
        // Return: true if the operation was successful, false if unable to
        // allocate enough memory.
        //
        // Note: For circular arrays, the list's 0 index will rarely correspond
        // the storage array's 0 index. This is important to understand as it
        // the fundamental nature of a circular array
        virtual bool addFirst(T) = 0;

        // Inserts the parameter item at the end of the list.
        //
        // Equivalent to:
        //     lstPtr->append(item);
        //
        // Complexity: Constant for dynamic lists
        // Parameter: the item to insert at the list's end
        // Return: true if successful or false if it fails to find memory
        virtual bool addLast(T) = 0;

        // Returns a reference to the object stored at the specified position
        // in the list.
        //
        // Parameter: the LIST index to reference
        // exceptions: if index out of range
        // Return: A &reference (alias) to the item held at the list index
        virtual T& get(int) = 0;

        // Inserts the specified item into the list at the specified list
        // position. This increases the list's size.
        //
        // Inserting into the middle of a list is not, typically, a major
        // operation of the data structure. As such, performance for this
        // operation is usually secondary to adding to front or back. As a
        // result, we tolerate Linear performance when inserting at the
        // size()/2 position.
        //
        // Inserting into any position between the front and rear requires
        // the data structure to shuffle its existing contents over (for
        // random access) or sequentially dereference links (linked lists).
        // In both cases, performance struggles.
        //
        // Complexity: O(n).
        // Parameters: the list position for the new item to occupy and the
        //   item to store at the new location.
        // exceptions: if index out of range
        // Return: true if the operation succeeded.
        virtual bool insert(int, T) = 0;

        // Extracts the item held at the specified location from the list
        // and returns the result. This obviously shrinks the list by one
        // item.
        //
        // Complexity: As insert(int,T), O(n).
        // Parameter: the index of the item to remove from the list.
        // exceptions: if index out of range
        // Return: the item previously at the list position specified
        virtual T remove(int) = 0;

        // Extracts the item held at front the list and returns the
        // result. This obviously shrinks the list by one item.
        //
        // Complexity: Circular Array: Constant
        // Return: the item previously at the front.
        virtual T removeFirst() = 0;

        // Extracts the item held at rear the list and returns the
        // result. This obviously shrinks the list by one item.
        //
        // Complexity: Circular Array: Constant
        // Return: the item previously at the rear.
        virtual T removeLast() = 0;

        // Modifies the contents of the list at the specified location.
        // This method does not increase the list size.
        //
        // Parameters: the list position to modify and the new value to use
        // exceptions: if the index out of range
        virtual void set(int, T) = 0;

        // Returns the total number of type T items contained in the list.
        virtual int size() const = 0;
    };
}

#endif //PROG1_LIST_H
