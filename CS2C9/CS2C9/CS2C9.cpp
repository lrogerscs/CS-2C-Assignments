// CS 2C Assignment #9. Instructor Solution

// client file --------------------------------------------------
// FHflowGraph client
// CS 2C Foothill College
#include <iostream>
#include <string>
using namespace std;
#include "FHflowGraph.h"

// --------------- main ---------------
int main()
{
    // Sample graph -----------------------------------------------------------------------------------------------------------------------------------------------------

    int finalFlow;

    // build graph
    FHflowGraph<string, int> myG;

    myG.addEdge("a", "b", 10);
    myG.addEdge("a", "d", 6);
    myG.addEdge("a", "c", 3);
    myG.addEdge("b", "e", 4);
    myG.addEdge("d", "e", 9);
    myG.addEdge("c", "d", 2);

    myG.showResAdjTable();
    myG.showFlowAdjTable();

    myG.setStartVert("a");
    myG.setEndVert("e");
    finalFlow = myG.findMaxFlow();

    cout << "Final flow: " << finalFlow << endl;

    myG.showResAdjTable();
    myG.showFlowAdjTable();

    return 0;
}

/* Runs -----------------------------------------------------------------------------------------------------------------------------------------------------

Sample run (the same graph from the sample main in the assignment and maximum flow graph module):

------------------------
Res Adj List for s: a(3) b(2)
Res Adj List for a: s(0) b(1) c(3) d(4)
Res Adj List for b: s(0) a(0) d(2)
Res Adj List for c: a(0) t(2)
Res Adj List for d: a(0) b(0) t(3)
Res Adj List for t: c(0) d(0)

------------------------
Flow Adj List for s: a(0) b(0)
Flow Adj List for a: b(0) c(0) d(0)
Flow Adj List for b: d(0)
Flow Adj List for c: t(0)
Flow Adj List for d: t(0)
Flow Adj List for t:

Final flow: 5
------------------------
Res Adj List for s: a(0) b(0)
Res Adj List for a: s(3) b(1) c(1) d(3)
Res Adj List for b: s(2) a(0) d(0)
Res Adj List for c: a(2) t(0)
Res Adj List for d: a(1) b(2) t(0)
Res Adj List for t: c(2) d(3)

------------------------
Flow Adj List for s: a(3) b(2)
Flow Adj List for a: b(0) c(2) d(1)
Flow Adj List for b: d(2)
Flow Adj List for c: t(2)
Flow Adj List for d: t(3)
Flow Adj List for t:


Custom run 1:

------------------------
Res Adj List for a: b(3) c(2)
Res Adj List for b: a(0) c(0) e(4)
Res Adj List for c: a(0) b(3) e(1)
Res Adj List for e: b(0) c(0)

------------------------
Flow Adj List for a: b(0) c(0)
Flow Adj List for b: e(0)
Flow Adj List for c: b(0) e(0)
Flow Adj List for e:

Final flow: 5
------------------------
Res Adj List for a: b(0) c(0)
Res Adj List for b: a(3) c(1) e(0)
Res Adj List for c: a(2) b(2) e(0)
Res Adj List for e: b(4) c(1)

------------------------
Flow Adj List for a: b(3) c(2)
Flow Adj List for b: e(4)
Flow Adj List for c: b(1) e(1)
Flow Adj List for e:


Custom run 2:

------------------------
Res Adj List for a: b(10) d(6) c(3)
Res Adj List for b: a(0) e(4)
Res Adj List for d: a(0) c(0) e(9)
Res Adj List for c: a(0) d(2)
Res Adj List for e: b(0) d(0)

------------------------
Flow Adj List for a: b(0) d(0) c(0)
Flow Adj List for b: e(0)
Flow Adj List for d: e(0)
Flow Adj List for c: d(0)
Flow Adj List for e:

Final flow: 12
------------------------
Res Adj List for a: b(6) d(0) c(1)
Res Adj List for b: a(4) e(0)
Res Adj List for d: a(6) c(2) e(1)
Res Adj List for c: a(2) d(0)
Res Adj List for e: b(4) d(8)

------------------------
Flow Adj List for a: b(4) d(6) c(2)
Flow Adj List for b: e(4)
Flow Adj List for d: e(8)
Flow Adj List for c: d(2)
Flow Adj List for e:
*/