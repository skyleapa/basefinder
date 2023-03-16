/**
 * @file stack.h
 * Definition of the Stack class.
 */
#ifndef STACK_H
#define STACK_H

#include "deque.h"

/**
 * Stack class: represents a standard stack. Templated to hold elements of
 * any type.
 *
 *
 */
template <class T>
class Stack 
{
  public:
    /**
     * Adds the parameter object to the top of the Stack. 
     *
     * @param newItem The object to be added to the Stack.
     */
    void push(T newItem);

    /**
     * Removes the object on top of the Stack, and returns it. 
     *
     * @return The element that used to be at the top of the Stack.
     */
    T pop();

    /**
     * Finds the object on top of the Stack, and returns it to the caller.
     * @return The element at the top of the Stack.
     */
    T peek();

    /**
     * Determines if the Stack is empty.
     *
     * @return Whether or not the stack is empty (bool).
     */
    bool isEmpty() const;

  private:
    /**
     * The deque representing the Stack. 
     **/
    Deque<T> myStack;
};

#include "stack.cpp" // needed for template instantiation
#endif
