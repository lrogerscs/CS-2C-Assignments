

// Assignment #5 Instructor Solution
// CS 2C, Foothill College, Michael Loceff

// Client / Splay Tree ----------------------------------------------

#include <iostream>
#include "FHsplayTree.h"
using namespace std;

template <typename Object>
class PrintObject
{
public:
    void operator()(Object obj)
    {
        cout << obj << " ";
    }
};

int main()
{
    int k, k2;
    FHsplayTree<int> searchTree;
    //FHsearch_tree<int> searchTree;
    PrintObject<int> intPrinter;

    searchTree.traverse(intPrinter);
    //cout << searchTree.showRoot() << endl;

    cout << "Initial size: " << searchTree.size() << endl;
    for (k = 1; k <= 78; k++)
        searchTree.insert(k);
    cout << "New size: " << searchTree.size() << endl;

    cout << "\nTraversal: \n";
    searchTree.traverse(intPrinter);
    cout << endl << endl;

    for (k = -1; k < 16; k++)
    {
        // test contains()
        k2 = 20 - k;
        if (!searchTree.contains(k2))
            cout << " oops on contains " << k2 << endl;
        cout << "contains " << k2 << " --> root: " << searchTree.showRoot()
            << " height: " << searchTree.showHeight() << endl;

        // test find()
        try
        {
            searchTree.find(k);
        }
        catch (...)
        {
            cout << " oops on find " << k << endl;
        }
        cout << "find " << k << " --> root: " << searchTree.showRoot()
            << " height: " << searchTree.showHeight() << endl;
    }

    return 0;
}

/* --------- output -----------
Initial size: 0
New size: 32

Traversal:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
 31 32

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
Press any key to continue . . .
----------------------------- 
*/