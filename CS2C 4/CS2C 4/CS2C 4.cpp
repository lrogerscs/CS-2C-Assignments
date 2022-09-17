// Assignment #4 Instructor Solution
// CS 2C, Foothill College, Michael Loceff

// --------------- main ---------------

// CS 2C  Simple Search Tree Client - Lazy Deletion, int data
#include <iostream>
#include <string>
#include <stack>
#include "FHlazySearchTree.h"
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
    int k;
    FHlazySearchTree<int> searchTree;
    PrintObject<int> intPrinter;

    searchTree.traverse(intPrinter);

    cout << "\ninitial size: " << searchTree.size() << endl;
    searchTree.insert(15);
    searchTree.insert(30);
    searchTree.insert(45);
    searchTree.insert(60);
    searchTree.insert(75);
    searchTree.insert(90);
    searchTree.insert(105);
    searchTree.insert(120);
    searchTree.insert(135);
    searchTree.insert(150);
    searchTree.insert(165);
    searchTree.insert(180);
    searchTree.insert(195);
    searchTree.insert(210);


    cout << "\nAfter populating -- traversal and sizes: \n";
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "Collecting garbage on new tree - should be no garbage." << endl;
    searchTree.collectGarbage();
    cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "\nAttempting 1 removal: \n";
    if (searchTree.remove(30))
        cout << "removed " << 30 << endl;
    cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "\nAttempting 1 removal: \n";
    if (searchTree.remove(120))
        cout << "removed " << 120 << endl;
    cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "\nAttempting 1 removal: \n";
    if (searchTree.remove(75))
        cout << "removed " << 75 << endl;
    cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "\nSoft insertion. Hard size should not change. " << endl;
    searchTree.insert(75);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "\nCollecting Garbage - should clean 2 items. " << endl;
    searchTree.collectGarbage();
    cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "\nAdding 'hard' 225 - should see new sizes. " << endl;
    searchTree.insert(225);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "\n\nAttempting 200 soft removals: \n";
    for (k = 200; k > 0; k--)
    {
        if (searchTree.remove(k))
            cout << "removed " << k << endl;
    }

    cout << "\nsearchTree now:\n";
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "\nAttempting 1 removal: \n";
    if (searchTree.remove(210))
        cout << "removed " << 210 << endl;
    cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "\nAttempting 1 removal: \n";
    if (searchTree.remove(225))
        cout << "removed " << 225 << endl;
    cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    return 0;
}

/* ---------------------- Run --------------------------
initial size: 0
After populating -- traversal and sizes:
10 20 30 50 60 70
tree 1 size: 6  Hard size: 6
Collecting garbage on new tree - should be no garbage.
tree 1 size: 6  Hard size: 6


Attempting 1 removal:
removed 20
tree 1 size: 5  Hard size: 6
Collecting Garbage - should clean 1 item.
tree 1 size: 5  Hard size: 5
Collecting Garbage again - no change expected.
tree 1 size: 5  Hard size: 5
Adding 'hard' 22 - should see new sizes.
10 22 30 50 60 70
tree 1 size: 6  Hard size: 6

After soft removal.
10 30 50 60 70
tree 1 size: 5  Hard size: 6
Repeating soft removal. Should see no change.
10 30 50 60 70
tree 1 size: 5  Hard size: 6
Soft insertion. Hard size should not change.
10 22 30 50 60 70
tree 1 size: 6  Hard size: 6


Attempting 100 removals:
removed 70
removed 60
removed 50
removed 30
removed 22
removed 10

searchTree now:

tree 1 size: 0  Hard size: 0

searchTree2:
10 20 30 50 60 70 100 200 300 500 600 700
tree 2 size: 12  Hard size: 12
Press any key to continue . . .
---------------------------------------------------------------------- */