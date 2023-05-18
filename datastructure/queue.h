/**
 * @file queue.h
 * Definition of the Queue class.
 *
 */
#ifndef QUEUE_H
#define QUEUE_H

#include "deque.h"

/**
 * Queue class: represents a standard queue. Templated to hold elements of
 * any type.
 */
template <class T>
class Queue 
{
  public:
    /**
     * Adds the parameter object to the back of the Queue.
     *
     * @note O(1)
     *
     * @param newItem object to be added to the Queue.
     */
    void enqueue(T newItem);

    /**
     * Removes the object at the front of the Queue, and returns it to
     * the caller.
     *
     * @note O(1)
     *
     * @return The item that used to be at the front of the Queue.
     */
    T dequeue();


    /**
     * Finds the object at the front of the Queue, and returns it to
     * the caller.
     *
     * @note O(1)
     *
     * @return The item at the front of the queue.
     */
    T peek();

    /**
     * Determines if the Queue is empty.
     *
     * @note O(1)
     *
     * @return bool which is true if the Queue is empty, false
     *	otherwise.
     */
    bool isEmpty() const;

  private:
    Deque<T> myQueue;
};


#include "queue.cpp"
#endif
