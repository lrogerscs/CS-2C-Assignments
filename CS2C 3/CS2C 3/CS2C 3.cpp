#include <iostream>
#include <iomanip>

using namespace std;

#define MAT_SIZE 50
typedef float* DynMat[MAT_SIZE];

void matMultDyn(const DynMat& matA, const DynMat& matB, DynMat& matC, int size);
void matShowDyn(const DynMat& matA, int start, int size);

int main()
{
    int r, c;
    clock_t startTime, stopTime;
    double randFrac;
    int randRow, randCol, smallPercent;

    // non-sparse dynamic matrix
    DynMat matDyn, matDynAns;


    // allocate rows and initialize to 0
    for (r = 0; r < MAT_SIZE; r++)
    {
        
        matDyn[r] = new float[MAT_SIZE];
        matDynAns[r] = new float[MAT_SIZE];

        for (c = 0; c < MAT_SIZE; c++)
        {
            
            matDyn[r][c] = 0;
            matDynAns[r][c] = 0;
        }
    }

    // generate small% (bet .1 and 10%) non-default values (bet 0 and 1)
    smallPercent = round(MAT_SIZE / 20.);  // div by 20. means 5%, of course (had to alter line because smallPercent was being set to values above MAT_SIZE)
    for (r = 0; r < smallPercent; r++)
    {
        
        // generate random sparse matrix 5% the size of the original inside of matDyn
        randRow = rand() % smallPercent;
        randCol = rand() % smallPercent;
        matDyn[randRow][randCol] = ((double)rand() / (RAND_MAX));
    }

    // 10x10 submatrix in lower right
    matShowDyn(matDyn, MAT_SIZE - 10, 10);

    startTime = clock();  // ------------------ start
    matMultDyn(matDyn, matDyn, matDynAns, MAT_SIZE);
    stopTime = clock();  // ---------------------- stop

    matShowDyn(matDynAns, MAT_SIZE - 10, 10);
    cout << "\nSize = " << MAT_SIZE << " Dyn Array Mult Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;

    return 0;
}

void matMultDyn(const DynMat& matA, const DynMat& matB, DynMat& matC, int size) {

    // loop through the elements of matA and matB and multiply their values
    for (int i = 0; i < size; i++) {

        for (int j = 0; j < size; j++) {

            matC[i][j] = 0;

            for (int k = 0; k < size; k++) {

                matC[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
}

void matShowDyn(const DynMat& matA, int start, int size) {

    cout << fixed;
    cout << setprecision(2);

    for (int i = 0; i < size; i++) {

        for (int j = 0; j < size; j++) {

            if (matA[i][j] < 0)
                cout << "  " << matA[i][j];
            else
                cout << "   " << matA[i][j];
        }

        cout << endl;
    }

    cout << endl;
}

/*
Questions -----------------------------------------------------------------------------------------

Q. Determine the time complexity of multiplying two matrices together (should get a Big-Oh and a theta estimation).
A. Judging from the matrix multiplication algorithm, I will have to have 1 outer loop and 2 nested loops, which means the Big-Oh estimate would be O = (N^3).
   Subsequently, the theta estimate would also end up being (N^3).

Q. What was the smallest M that gave you a non-zero time?
A. 116.

Q. What happened when you doubled M , tripled it, quadrupled it, etc?  Give several M values and their times in a table.
A. They continuously got larger.
   M = 150 | M = 300 | M = 450 | M = 600 | M = 750
    0.01      0.08      0.28      0.65      1.32

Q. How large an M can you use before the program refuses to run (exception or run-time error due to memory overload) or it takes so long you can't wait for the run?
A. Once M reaches around 2000, the waiting times start to become unbearable. After M gets into the tens of thousands, the compiler refuses to complete the program.

Q. How did the data agree or disagree with your original time complexity estimate?
A. It behaved about how I expected.

Runs -----------------------------------------------------------------------------------------

Test run to make sure matMultDyn is working

First Matrix, n:
   1.00   2.00   3.00   4.00   5.00
  -1.00  -2.00  -3.00  -4.00  -5.00
   1.00   3.00   1.00   3.00   1.00
   0.00   1.00   0.00   1.00   0.00
  -1.00  -1.00  -1.00  -1.00  -1.00

Second Matrix, m:
   2.00   1.00   5.00   0.00   2.00
   1.00   4.00   3.00   2.00   7.00
   4.00   4.00   4.00   4.00   4.00
   7.00   1.00  -1.00  -1.00  -1.00
   0.00   0.00   8.00  -1.00  -6.00

Product Matrix, n x m:
   44.00   25.00   59.00   7.00  -6.00
  -44.00  -25.00  -59.00  -7.00   6.00
   30.00   20.00   23.00   6.00   18.00
   8.00   5.00   2.00   1.00   6.00
  -14.00  -10.00  -19.00  -4.00  -6.00


Example run with full implementation

   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.48
   0.00   0.00   0.00   0.00   0.00   0.36   0.00   0.30   0.00   0.00
   0.00   0.00   0.53   0.00   0.00   0.00   0.00   0.00   0.00   0.00
   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00
   0.00   0.00   0.00   0.00   0.00   0.86   0.00   0.00   0.00   0.00
   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00
   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.61   0.00
   0.00   0.00   0.00   0.00   0.00   0.00   0.99   0.00   0.00   0.00
   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.82   0.00
   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00

   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00
   0.00   0.00   0.00   0.00   0.00   0.00   0.30   0.00   0.00   0.00
   0.00   0.00   0.28   0.00   0.00   0.00   0.00   0.00   0.00   0.00
   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00
   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00
   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00
   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.50   0.00
   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.60   0.00
   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.68   0.00
   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00   0.00


Size = 200 Dyn Array Mult Elapsed Time: 0.02 seconds.
*/