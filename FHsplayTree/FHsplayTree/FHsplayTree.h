// Student name: Lee Rogers
// LAB Assignment 5

#ifndef FHSPLAYTREE_H
#define FHSPLAYTREE_H
#include <iostream>
#include <iomanip>
#include "FHsearch_tree.h"

// Derived class prototype -----------------------------------------------------------------------------------------------------------------------------------------------

template <class Comparable>
class FHsplayTree : public FHsearch_tree<Comparable> {
    
public:

    bool insert(const Comparable& x);
    bool remove(const Comparable& x);
    bool contains(const Comparable& x);
    const Comparable& find(const Comparable& x);

    const Comparable& showRoot();

protected:

    void splay(FHs_treeNode<Comparable>*& root, const Comparable& x);
    void rotateWithLeftChild(FHs_treeNode<Comparable>*& k2);
    void rotateWithRightChild(FHs_treeNode<Comparable>*& k2);
};

// Method definitions -----------------------------------------------------------------------------------------------------------------------------------------------

template <class Comparable>
bool FHsplayTree<Comparable>::insert(const Comparable& x) {

    if (this->mRoot == nullptr) {

        this->mRoot = new FHs_treeNode<Comparable>(x);
        this->mSize++;
        return true;
    }

    splay(this->mRoot, x);

    if (x < this->mRoot->data) {

        FHs_treeNode<Comparable>* treeNode = new FHs_treeNode<Comparable>(x);
        treeNode->lftChild = this->mRoot->lftChild;
        treeNode->rtChild = this->mRoot;
        this->mRoot = treeNode;
        this->mSize++;

        return true;
    }
    else if (x > this->mRoot->data) {

        FHs_treeNode<Comparable>* treeNode = new FHs_treeNode<Comparable>(x);
        treeNode->lftChild = this->mRoot;
        treeNode->rtChild = this->mRoot->rtChild;
        this->mRoot = treeNode;
        this->mSize++;

        return true;
    }

    return false;
}

template <class Comparable>
bool FHsplayTree<Comparable>::remove(const Comparable& x) {

    FHs_treeNode<Comparable>* newRoot;

    if (this->mRoot)
        return false;

    splay(this->mRoot, x);

    if (x < this->mRoot->data || x > this->mRoot->data)
        return false;

    if (this->mRoot->lftChild)
        newRoot = this->mRoot->rtChild;
    else {

        newRoot = this->mRoot->lftChild;
        splay(newRoot, x);
        newRoot->rtChild = this->mRoot->rtChild;
    }

    delete this->mRoot;
    this->mRoot = newRoot;
    this->mSize--;

    return true;
}

template <class Comparable>
bool FHsplayTree<Comparable>::contains(const Comparable& x) {

    try {

        find(x);
        return true;
    }
    catch (...) {

        return false;
    }
}

template <class Comparable>
const Comparable& FHsplayTree<Comparable>::find(const Comparable& x) {

    if(this->mRoot == nullptr)
        throw typename FHsearch_tree<Comparable>::NotFoundException();

    splay(this->mRoot, x);

    // if x does not equal the closest match, throw exception
    if(x < this->mRoot->data || x > this->mRoot->data)
        throw typename FHsearch_tree<Comparable>::NotFoundException();

    return this->mRoot->data;
}

template <class Comparable>
const Comparable& FHsplayTree<Comparable>::showRoot() {

    if (this->mRoot != nullptr)
        return this->mRoot->data;
}

template <class Comparable>
void FHsplayTree<Comparable>::splay(FHs_treeNode<Comparable>*& root, const Comparable& x) {

    FHs_treeNode<Comparable>* rightTree = nullptr, * leftTree = nullptr, * rightTreeMin = nullptr, * leftTreeMax = nullptr;

    while (root != nullptr) {

        if (x < root->data) {

            if (root->lftChild == nullptr)
                break;

            if (x < root->lftChild->data) {

                rotateWithLeftChild(root);

                if (root->lftChild == nullptr)
                    break;
            }

            if (rightTree == nullptr) {

                rightTree = root;
                rightTreeMin = rightTree;
                root = root->lftChild;
            }
            else {

                rightTreeMin->lftChild = root;
                rightTreeMin = root;
                root = root->lftChild;
            }
        }
        else if (x > root->data) {

            if (root->rtChild == nullptr)
                break;

            if (x > root->rtChild->data) {

                rotateWithRightChild(root);

                if (root->rtChild == nullptr)
                    break;
            }

            if (leftTree == nullptr) {

                leftTree = root;
                leftTreeMax = leftTree;
                root = root->rtChild;
            }
            else {

                leftTreeMax->rtChild = root;
                leftTreeMax = root;
                root = root->rtChild;
            }
        }
        else
            break;
    }

    if (leftTree != nullptr) {

        leftTreeMax->rtChild = root->lftChild;
        root->lftChild = leftTree;
    }

    if (rightTree != nullptr) {

        rightTreeMin->lftChild = root->rtChild;
        root->rtChild = rightTree;
    }
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithLeftChild(FHs_treeNode<Comparable>*& k2) {

    FHs_treeNode<Comparable>* k1 = k2->lftChild;
    k2->lftChild = k1->rtChild;
    k1->rtChild = k2;
    k2 = k1;
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithRightChild(FHs_treeNode<Comparable>*& k2) {

    FHs_treeNode<Comparable>* k1 = k2->rtChild;
    k2->rtChild = k1->lftChild;
    k1->lftChild = k2;
    k2 = k1;
}
#endif

/* Runs -----------------------------------------------------------------------------------------------------------------------------------------------

Default run:

Initial size: 0
New size: 32

Traversal:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32

contains 11 --> root: 11 height: 11
 oops on find -1
find -1 --> root: 1 height: 13
contains 10 --> root: 10 height: 12
 oops on find 0
find 0 --> root: 1 height: 13
contains 9 --> root: 9 height: 13
find 1 --> root: 1 height: 14
contains 8 --> root: 8 height: 14
find 2 --> root: 2 height: 15
contains 7 --> root: 7 height: 15
find 3 --> root: 3 height: 16
contains 6 --> root: 6 height: 16
find 4 --> root: 4 height: 17
contains 5 --> root: 5 height: 17
find 5 --> root: 5 height: 17
contains 4 --> root: 4 height: 18
find 6 --> root: 6 height: 16
contains 3 --> root: 3 height: 18
find 7 --> root: 7 height: 15
contains 2 --> root: 2 height: 17
find 8 --> root: 8 height: 14
contains 1 --> root: 1 height: 16
find 9 --> root: 9 height: 13
 oops on contains 0
contains 0 --> root: 1 height: 15
find 10 --> root: 10 height: 12
 oops on contains -1
contains -1 --> root: 1 height: 14
find 11 --> root: 11 height: 11
 oops on contains -2
contains -2 --> root: 1 height: 13
find 12 --> root: 12 height: 7



Custom Run 1:

Initial size: 0
New size: 78

Traversal:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 
56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78

contains 21 --> root: 21 height: 29
 oops on find -1
find -1 --> root: 1 height: 31
contains 20 --> root: 20 height: 30
 oops on find 0
find 0 --> root: 1 height: 31
contains 19 --> root: 19 height: 31
find 1 --> root: 1 height: 32
contains 18 --> root: 18 height: 32
find 2 --> root: 2 height: 33
contains 17 --> root: 17 height: 33
find 3 --> root: 3 height: 34
contains 16 --> root: 16 height: 34
find 4 --> root: 4 height: 35
contains 15 --> root: 15 height: 35
find 5 --> root: 5 height: 36
contains 14 --> root: 14 height: 36
find 6 --> root: 6 height: 37
contains 13 --> root: 13 height: 37
find 7 --> root: 7 height: 38
contains 12 --> root: 12 height: 38
find 8 --> root: 8 height: 39
contains 11 --> root: 11 height: 39
find 9 --> root: 9 height: 40
contains 10 --> root: 10 height: 40
find 10 --> root: 10 height: 40
contains 9 --> root: 9 height: 41
find 11 --> root: 11 height: 39
contains 8 --> root: 8 height: 41
find 12 --> root: 12 height: 38
contains 7 --> root: 7 height: 40
find 13 --> root: 13 height: 37
contains 6 --> root: 6 height: 39
find 14 --> root: 14 height: 36
contains 5 --> root: 5 height: 38
find 15 --> root: 15 height: 35



Custom run 2:

Initial size: 0
New size: 11

Traversal:
1 2 3 4 5 6 7 8 9 10 11

contains 6 --> root: 6 height: 5
 oops on find -1
find -1 --> root: 1 height: 5
contains 5 --> root: 5 height: 4
 oops on find 0
find 0 --> root: 1 height: 5
contains 4 --> root: 4 height: 5
find 1 --> root: 1 height: 6
contains 3 --> root: 3 height: 6
find 2 --> root: 2 height: 7
contains 2 --> root: 2 height: 7
find 3 --> root: 3 height: 6
contains 1 --> root: 1 height: 8
find 4 --> root: 4 height: 5
 oops on contains 0
contains 0 --> root: 1 height: 7
find 5 --> root: 5 height: 4
*/