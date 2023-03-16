/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque(){
    n1 = 0;
    n2 = data.size();
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
    data.push_back(newItem);
    n2++;
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    T itemToPop = data.at(n1);
    n1++;

    // resizing
    if (n2 - n1 <= n1)
    {
        data.erase(data.begin(), data.begin() + n1);
        n2 = data.size();
        n1 = 0;
    }
    
    return itemToPop;
}

/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    T itemToPop = data.at(n2 - 1);
    n2--;
    data.pop_back();


    //resizing
    if (n2 - n1 <= n1)
    {
        data.erase(data.begin(), data.begin() + n1);
        n2 = data.size();
        n1 = 0;
    } 

    return itemToPop;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    return data.at(n1);
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    return data.at(n2 - 1);   
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    return n1 == n2;
}
