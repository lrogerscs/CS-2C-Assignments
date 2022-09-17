// Student name: Lee Rogers
// LAB Assignment 6

// FHhashQPwFind.h prototypes and method definitions -------------------------------------------------------------------------------------------------------------------

#ifndef FHHASHQPWFIND_H
#define FHHASHQPWFIND_H
#include <iostream>
#include <iomanip>
#include "FHhashQP.h"

// Prototypes ------------------------------------------------------------------------------------------------

template <class Object, typename KeyType>
class FHhashQPwFind : public FHhashQP<Object>
{

public:

    const Object find(const KeyType& key);

protected:

    int myHashKey(const KeyType& key) const;
    int findPosKey(const KeyType& key) const;

public:

    class NotFoundException {};
};

// Method definitions -------------------------------------------------------------------------------------------

template <class Object, typename KeyType>
const Object FHhashQPwFind<Object, KeyType>::find(const KeyType& key) {

    if (this->mArray[findPosKey(key)].state == FHhashQP<Object>::ACTIVE)
        return this->mArray[findPosKey(key)].data;
    else
        throw NotFoundException();
}


template <class Object, typename KeyType>
int FHhashQPwFind<Object, KeyType>::myHashKey(const KeyType& key) const {

    int hashVal;

    hashVal = Hash(key) % this->mTableSize;
    if (hashVal < 0)
        hashVal += this->mTableSize;

    return hashVal;
}

template <class Object, typename KeyType>
int FHhashQPwFind<Object, KeyType>::findPosKey(const KeyType& key) const {

    int kthOddNum = 1;
    int index = myHashKey(key);

    while (this->mArray[index].state != FHhashQP<Object>::EMPTY
        && getKey(this->mArray[index].data) != key)
    {
        index += kthOddNum;  // k squared = (k-1) squared + kth odd #
        kthOddNum += 2;   // compute next odd #
        if (index >= this->mTableSize)
            index -= this->mTableSize;
    }

    return index;
}

#endif