/**
 * @file stack.cpp
 * Implementation of the Stack class.
 *
 */

/**
 * Adds the parameter object to the top of the Stack. 
 *
 *
 * @param newItem The object to be added to the Stack.
 */
template<class T>
void Stack<T>::push(T newItem)
{
    myStack.pushR(newItem);
}

/**
 * Removes the object on top of the Stack, and returns it. 
 * @return The element that used to be at the top of the Stack.
 */
template <class T>
T Stack<T>::pop()
{
    return myStack.popR();
}

/**
 * Finds the object on top of the Stack, and returns it to the caller.
 *
 * @return The value of the element at the top of the Stack.
 */
template <class T>
T Stack<T>::peek()
{
    return myStack.peekR();
}

/**
 * Determines if the Stack is empty.
 *
 * @return Whether or not the stack is empty (bool).
 */
template <class T>
bool Stack<T>::isEmpty() const
{
    return myStack.isEmpty();
}
