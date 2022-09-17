// Student name: Lee Rogers
// LAB Assignment 7

#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>
#include "FHvector.h" // file provided from CS2C files

#define ARRAY_SIZE 200000

using namespace std;

// shellSort #1 -- using shell's outer loop (from FHsort.h)
template <typename Comparable>
void shellSort1(FHvector<Comparable>& a)
{
    int k, pos, arraySize, gap;
    Comparable tmp;

    arraySize = a.size();
    for (gap = arraySize / 2; gap > 0; gap /= 2)  // outer gap loop
        for (pos = gap; pos < arraySize; pos++)   // middle loop (outer of "insertion-sort")
        {
            tmp = a[pos];
            for (k = pos; k >= gap && tmp < a[k - gap]; k -= gap)   // inner loop
                a[k] = a[k - gap];
            a[k] = tmp;
        }
}

template <typename Comparable>
void shellSortX(FHvector<Comparable>& a, int gapSequence[], int sequenceSize) {

    int k, pos, arraySize, gap, gapPos;
    Comparable tmp;

    arraySize = a.size();

    for (int i = 0; i < sequenceSize; i++) { // find the closest number in the sequence to arraySize / 2

        if (gapSequence[i] > arraySize / 2)
            break;

        gap = gapSequence[i];
        gapPos = i;
    }

    for (gap; gap > 0; gap = gapSequence[gapPos--])  // outer gap loop (iterate through the sequence while gap > 0)
        for (pos = gap; pos < arraySize; pos++)   // middle loop
        {
            tmp = a[pos];
            for (k = pos; k >= gap && tmp < a[k - gap]; k -= gap) // inner loop
                a[k] = a[k - gap];
            a[k] = tmp;
        }
}

int main() {

    int temp, gapArraySize;
    clock_t startTime, stopTime;
    int gapArray[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
      2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
      1048576 };
    int optimalGapArray[26]; // generate later
    int sedgewickArray[28];  // to be computed using formulas
    FHvector<int> fhVectorOfInts1;
    FHvector<int> fhVectorOfInts2;
    FHvector<int> fhVectorOfInts3;
    FHvector<int> fhVectorOfInts4;

    // generate sedgewickArray values
    temp = 0;
    gapArraySize = sizeof(sedgewickArray) / sizeof(sedgewickArray[0]);

    for (int i = 0; i < 20; i++) {

        if (temp < gapArraySize) {

            sedgewickArray[temp] = (9 * (pow(4, i))) - (9 * (pow(2, i))) + 1;
            temp += 2;
        }
        else
            break;
    }

    temp = 1;

    for (int i = 2; i < 20; i++) {

        if (temp < gapArraySize) {

            sedgewickArray[temp] = (pow(4,i)) - (3*(pow(2,i))) + 1;
            temp += 2;
        }
        else
            break;
    }

    // generate optimalGapArray
    optimalGapArray[0] = 1; // generate ciura's gap sequence
    optimalGapArray[1] = 4;
    optimalGapArray[2] = 10;
    optimalGapArray[3] = 23;
    optimalGapArray[4] = 57;
    optimalGapArray[5] = 132;
    optimalGapArray[6] = 301;
    optimalGapArray[7] = 701;
    optimalGapArray[8] = 1750;

    // use formula to generate the rest
    for (int i = 0; i < 17; i++) {

        optimalGapArray[i + 9] = floor(optimalGapArray[i + 8] * 2.25);
    }

    // generate the contents of 4 identical random vectors
    srand(time(NULL));

    for (int i = 0; i < ARRAY_SIZE; i++) {

        temp = rand() % 1000000;

        fhVectorOfInts1.push_back(temp);
        fhVectorOfInts2.push_back(temp);
        fhVectorOfInts3.push_back(temp);
        fhVectorOfInts4.push_back(temp);
    }

    // print information
    cout << "Random integer array size: " << ARRAY_SIZE << endl;

    // use to check the contents of gap sequences
    /*cout << "\nSedgewick array: " << endl;
    gapArraySize = sizeof(sedgewickArray) / sizeof(sedgewickArray[0]);
    for (int i = 0; i < gapArraySize; i++)
        cout << sedgewickArray[i] << endl;

    cout << "\nOptimal gap array: " << endl;
    gapArraySize = sizeof(optimalGapArray) / sizeof(optimalGapArray[0]);
    for (int i = 0; i < gapArraySize; i++)
        cout << optimalGapArray[i] << endl;*/

    // test implied version of shellSort
    startTime = clock();
    shellSort1(fhVectorOfInts1);
    stopTime = clock();

    cout << "\nImplied shellSort completed in " << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC << " seconds!" << endl;

    // test explicit version of shellSort
    gapArraySize = sizeof(gapArray) / sizeof(gapArray[0]);

    startTime = clock();
    shellSortX(fhVectorOfInts2, gapArray, gapArraySize);
    stopTime = clock();

    cout << "\nExplicit shellSort completed in " << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC << " seconds!" << endl;

    // test Sedgewick's gap sequence
    gapArraySize = sizeof(sedgewickArray) / sizeof(sedgewickArray[0]);

    startTime = clock();
    shellSortX(fhVectorOfInts3, sedgewickArray, gapArraySize);
    stopTime = clock();

    cout << "\nSedgewick's gap sequence completed in " << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC << " seconds!" << endl;

    // test optimal gap sequence
    gapArraySize = sizeof(optimalGapArray) / sizeof(optimalGapArray[0]);

    startTime = clock();
    shellSortX(fhVectorOfInts4, optimalGapArray, gapArraySize);
    stopTime = clock();

    cout << "\nOptimal gap sequence completed in " << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC << " seconds!" << endl;

    for (int k = 0; k < ARRAY_SIZE; k += ARRAY_SIZE / 10)
    {
        cout << "implicit shell gap #" << k << ": "
            << fhVectorOfInts1[k] << ", ";
        cout << "explicit shell gap #" << k << ": "
            << fhVectorOfInts2[k] << ",\n";
        cout << "Sedgewick gap #" << k << ": " << fhVectorOfInts3[k] << ", ";
        cout << "Tokuda gap #" << k << ": " << fhVectorOfInts4[k] << endl;
    }

    return 0;
}

/* Questions ------------------------------------------------------------------------------------------------------------------------------------------------------

Q. Why does Shell's gap sequence implied by shellSort1() give a different timing result than the explicit array described 
   above and passed to shellSortX()? Which is faster and why?

A. The explicit array takes much longer than the implied gap sequence because it is essentially the implied gap sequence's
   worst case scenario. The even numbers in the explicit sequence never mix with the odd numbers until 1, so the array stays 
   very unsorted for a long time. Following the same logic, because of the better mix of even and odd numbers in Sedgewick's 
   array and the optimal array, they are the fastest sequences.

Table ------------------------------------------------------------------------------------------------------------------------------------------------------

Note: the optimal gap sequence that I used is a version of Ciura's gap sequence. I found it by researching on the internet.

| ARRAY_SIZE | Implied | Explicit | Sedgewick | Optimal |
|------------|---------|----------|-----------|---------|
| 10000      | 0.019   | 0.046    | 0.015     | 0.015   |
| 31250      | 0.074   | 0.283    | 0.053     | 0.052   |
| 50000      | 0.128   | 0.409    | 0.089     | 0.086   |
| 100000     | 0.305   | 1.344    | 0.188     | 0.185   |
| 150000     | 0.464   | 1.809    | 0.291     | 0.287   |
| 200000     | 0.673   | 3.647    | 0.4       | 0.392   |

Runs ------------------------------------------------------------------------------------------------------------------------------------------------------

Run 1:

Random integer array size: 10000

Implied shellSort completed in 0.019 seconds!

Explicit shellSort completed in 0.046 seconds!

Sedgewick's gap sequence completed in 0.015 seconds!

Optimal gap sequence completed in 0.014 seconds!


Run 2:

Random integer array size: 31250

Implied shellSort completed in 0.074 seconds!

Explicit shellSort completed in 0.283 seconds!

Sedgewick's gap sequence completed in 0.053 seconds!

Optimal gap sequence completed in 0.052 seconds!


Run 3:

Random integer array size: 50000

Implied shellSort completed in 0.128 seconds!

Explicit shellSort completed in 0.409 seconds!

Sedgewick's gap sequence completed in 0.089 seconds!

Optimal gap sequence completed in 0.086 seconds!


Run 4:

Random integer array size: 100000

Implied shellSort completed in 0.305 seconds!

Explicit shellSort completed in 1.344 seconds!

Sedgewick's gap sequence completed in 0.188 seconds!

Optimal gap sequence completed in 0.185 seconds!


Run 5:

Random integer array size: 150000

Implied shellSort completed in 0.464 seconds!

Explicit shellSort completed in 1.809 seconds!

Sedgewick's gap sequence completed in 0.291 seconds!

Optimal gap sequence completed in 0.287 seconds!


Run 6:

Random integer array size: 200000

Implied shellSort completed in 0.673 seconds!

Explicit shellSort completed in 3.647 seconds!

Sedgewick's gap sequence completed in 0.4 seconds!

Optimal gap sequence completed in 0.392 seconds!
*/