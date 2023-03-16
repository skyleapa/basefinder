/**
 * @file queue.h
 * Definition of the Deque class.
 *
 */
#ifndef DEQUE_H
#define DEQUE_H

#include<vector>
using namespace std;

/**
 * Deque class: represents a standard deque, templated to hold elements of
 * any type.
 */
template <class T>
class Deque
{
  public:

    /* Constructor, initializes member variables appropriately. */
    Deque();

    /**
     * Adds the parameter object to the "right" end of the Deque.
     *
     * @param newItem object to be added to the Deque.
     */
    void pushR(T newItem);

    /**
     * Removes the object at the left of the Deque, and returns it to
     * the caller.
     * @return The item that used to be at the left of the Deque.
     */
    T popL();

    /**
     * Removes the object at the right of the Deque, and returns it to
     * the caller.
     *
     * @return The item that used to be at the right of the Deque.
     */
    T popR();

    /**
     * Finds the object at the left of the Deque, and returns it to
     * the caller. Unlike popL(), this operation does not alter the
     * deque. You may assume that this function is only called when the
     * Deque is non-empty.
     *
     * @return The item at the left of the deque.
     */
    T peekL();

    /**
     * Finds the object at the right of the Deque, and returns it to
     * the caller. Unlike popR(), this operation does not alter the
     * deque. You may assume that this function is only called when the
     * Deque is non-empty.
     *
     * @return The item at the right of the deque.
     */
    T peekR();

    /**
     * Determines if the Deque is empty.
     *
     * @return bool which is true if the Deque is empty, false
     *	otherwise.
     */
    bool isEmpty() const;

  private:
    vector<T> data;  /* Store the deque data here! */
    int n1;  
    int n2; 
};

#include "deque.cpp"
#endif
