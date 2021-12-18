// STUDENT ORGANIC WAGYU CODE
// Author: Kyle Krueger
// San Diego State University
// CS210: Data Structures
//
// File: CircularArray.h
// Defines the CircularArray collection class.

#define VERSION_CIRARRAY 0.1

// STUDENT CODE
#ifndef PROG1_CIRCULARARRAY_H
#define PROG1_CIRCULARARRAY_H
#define  STARTING_CAPACITY 10

#include "Queue.h"
#include "List.h"
#include <cstring>

namespace sdsu {
    template<typename T>
    class CircularArray : public sdsu::Queue<T>, public sdsu::List<T> {

    private:
        // Size represents how many T items the structure holds
        int curSize;

        // Capacity represents how many T items the structure CAN hold
        int curCapacity;

        // todo: head and tail counters for the circular nature
        int iHead, iTail;

        // the array on the heap
        T *storage;

        int defaultCapacity = 10;


    public:

        // This is the default class constructor. It sets the current size to 0
        CircularArray() : curSize(0) {
            // todo: initialize a default capacity storage array on the heap
            iHead = 0;
            iTail = 0;
            curCapacity = STARTING_CAPACITY;
            storage = new T[STARTING_CAPACITY];

        }

        // The copy constructor!
        CircularArray(const CircularArray<T> &other) : CircularArray() {
            std::cout << "Copying . . .";
            //I couldn't figure out how to use memcpy, directly copying the properties instead
            //memcpy(&storage,&other,sizeof(other));
            curSize = other.curSize;
            curCapacity = other.curCapacity;
            storage = new T[curCapacity];
            iHead = other.iHead;
            iTail = other.iTail;
            for (int i = iHead; i < iHead + curSize; i++) {
                storage[i % curCapacity] = other.storage[i % curCapacity];
            }
        }

        ~CircularArray() override {
            delete[] storage;
        }


        void clear() override {
            // size == 0, and the capacity and dynamic array should
            // shrink back to its default size. There is a potential
            // for a memory leak here.
            curCapacity = defaultCapacity;
            curSize = 0;
            iHead = 0;
            iTail = 0;
            delete[] storage;
            storage = new T[defaultCapacity];
        }

        T dequeue() override {
            return removeFirst();
        }

        bool enqueue(T t) override {
            return addLast(t);
        }

        bool isEmpty() const override {
            return size() == 0;
        }

        bool isFull() {
            if (curSize == curCapacity) {
                T *temp = storage;
                curCapacity = 2 * curCapacity;
                storage = new T[curCapacity];
                for (int i = 0; i < curSize; i++) {
                    storage[i] = temp[(i + iHead) % curSize];
                    //storage[i] = temp[(i + head) % curCapacity];
                }
                iHead = 0;
                iTail = curSize - 1;
                delete[] temp;
                return false;
            }
            return false;
        }

        bool isHalf() {
            if (curSize == curCapacity / 2) {
                T *temp = storage;
                storage = new T[curCapacity];
                for (int i = 0; i < curSize; i++) {
                    storage[i] = temp[(i + iHead) % curCapacity];
                }
                iHead = 0;
                iTail = curSize - 1;
                curCapacity = curCapacity / 2;
                delete[] temp;
                return true;
            }
            return false;
        }

        T &peek() override {
            // todo: this is here to make it compile, but it is wrong.
            return get(0);
        }

        bool addFirst(T t) override {
            // a well written insert method makes this a single line.
            //insert(0,t); This caused a memory leak unfortunately
            if (isFull() == false) {
                if (curSize != 0 || iTail != 0 || iHead != 0) {
                    iHead = (iHead - 1 + curCapacity) % curCapacity;
                }
                storage[iHead] = t;
                curSize++;
                return true;
            } else return false;
        }

        bool addLast(T t) override {
            // a well written insert method makes this a single line.
            //insert(curSize,t); This caused a memory leak unfortunately
            if (isFull() == false) {
                if (curSize != 0 || iTail != 0 || iHead != 0) {
                    iTail = (iTail + 1) % curCapacity;
                }
                storage[iTail] = t;
                curSize++;
                return true;
            } else return false;
        }

        T &get(int idx) override {
            // todo: we need idx range checking. In C++, this is dangerous.
            if (idx > curSize || idx < 0) {
                throw std::out_of_range("CircularArray<T>::get(idx) : index out of range.");
            }
            return storage[(idx + iHead) % curCapacity];
        }

        bool insert(int idx, T t) override {
            // if you figure out if you are closer to the head or tail, you can
            // minimize the amount of array manipulation you need to perform.

            //we use %curCapacity whenever we are shifting the tail, so that if it reaches capacity, modulus will = 0, and it will loop back around.
            if (isEmpty()) {
                storage[0] = t;
                curSize++;
                return true;
            } else if (curSize == 1) {
                iTail = (iHead + 1) % curCapacity;
                storage[iTail] = t;
                curSize++;
                return true;
            }

            isFull();
            if (idx > curSize || idx < 0) {
                throw std::out_of_range("CircularArray<T>::Insert(idx) : index out of range.");
            }
            if (isCloserToTail(idx)) {
                if (idx == curSize) {
                    storage[(iTail + 1) % curCapacity] = t;
                    iTail = (iTail + 1) % curCapacity;
                    curSize++;
                    return true;
                }
                for (int i = iTail; i < iTail - curSize + idx; i--) {
                    storage[(i + curCapacity + 1) % curCapacity] = storage[(i + curCapacity) % curCapacity];
                }
                iTail = (iTail + 1) % curCapacity;
            } else {
                if (idx == 0) {
                    storage[(iHead - 1) % curCapacity] = t;
                    iHead = (iHead - 1 + curCapacity) % curCapacity;
                    curSize++;
                    return true;
                }
                for (int i = iHead; i < iHead + idx + 1; i++) {
                    storage[(i - 1 + curCapacity) % curCapacity] = storage[(i + curCapacity) % curCapacity];
                }
                iHead = (iHead - 1 + curCapacity) % curCapacity;
            }
            storage[(idx + iHead) % curCapacity] = t;
            curSize++;
            //Is Full will check if we need to increase capacity, and do so if needed, then we range check
            //If we are closer to the tail, then we shift the data from the index to one to the right of the tail over 1
            // Then we shift the tail
            //If we are closer to the head, then we shift the data from the index to one to the left of the head over 1
            //Then we shift the head
            //Finally we insert our data into our desired index and increase the size.
            return true;
        }

        bool isCloserToTail(int idx) {

            if (idx >= curSize / 2) {
                return true;
            }
            return false;
        }

        T remove(int idx) override {
            // Figure out if the target index is closer to the front or back
            // and then shuffle from that index (tail or head).
            isHalf();
            T tRemoved = storage[(idx + iHead) % curCapacity];
            if (idx >= curSize || idx < 0) {
                throw std::out_of_range("CircularArray<T>::remove(idx) : index out of range.");
            }
            if (isEmpty()) {
                return false;
            }
            if (iHead == iTail) {
                clear();
                return tRemoved;
            }
            if (idx == curSize - 1) {
                iTail = (iTail - 1 + curCapacity) % curCapacity;
                curSize--;
                return tRemoved;
            }
            if (idx == 0) {
                iHead = (iHead + 1) % curCapacity;
                curSize--;
                return tRemoved;
            }

            if (isCloserToTail(idx)) {
                for (int i = iTail; i > iTail - curSize + idx; i--) {
                    storage[(i - 1 + curCapacity) % curCapacity] = storage[(i + curCapacity) % curCapacity];
                }
                iTail = (iTail - 1 + curCapacity) % curCapacity;
            } else {
                for (int i = iHead; i < idx + iHead + 1; i++) {
                    storage[(i + 1) % curCapacity] = storage[i % curCapacity];
                }
                iHead = (iHead + 1) % curCapacity;
            }
            curSize--;
            return tRemoved;
        }

        T removeFirst() override {
            // If you wrote remove correctly, this can be a single line.
            // you *might* want to clean up any exception handling though . . . .
            if (isEmpty()) {
                return false;
            }
            return remove(0);
        }

        T removeLast() override {
            // If you wrote remove correctly, this can be a single line.
            // you *might* want to clean up any exception handling though . . . .
            if (isEmpty()) {
                return false;
            }
            return remove(curSize - 1);
        }

        void set(int idx, T value) override {
            if (idx > curSize || idx < 0) {
                throw std::out_of_range("CircularArray<T>::set(idx) : index out of range.");
            }
            storage[(idx + iHead) % curCapacity] = value;
        }

        int size() const override {
            return curSize;
        }
    };
}
#endif //PROG1_CIRCULARARRAY_H