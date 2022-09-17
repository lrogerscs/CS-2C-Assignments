// Student name: Lee Rogers
// Lab Assignment 2 - Sparce Matrices

#include <iostream>
// Nothing has been changed from the original FHlist and FHvector headers
#include "FHlist.h"
#include "FHvector.h"

using namespace std;

// MatNode prototype ------------------------------------------------------------------------------------------------------
template <class Object>
class MatNode
{
protected:

    int col;

public:

    Object data;
    // we need a default constructor for lists
    MatNode(int cl = 0, Object dt = Object()) : col(cl), data(dt) {}
    int getCol() const { return col; }

    // not optimized yet for set() = defaultVal;  refer to forums
    const Object& operator=(const Object& x) { return (data = x); }
};

// SparseMat prototype ------------------------------------------------------------------------------------------------------
template <class Object>
class SparseMat {

protected:

    typedef FHlist< MatNode<Object> > MatRow;
    typedef FHvector<MatRow> MasterCol;

    MasterCol rows;
    Object defaultVal;
    int rowSize, colSize;

public:

    SparseMat(int r, int c, const Object& defaultVal);
    const Object& get(int r, int c) const;
    bool set(int r, int c, const Object& x);
    void clear();
    void showSubSquare(int start, int size);
    void showSubSquare(int row, int col, int size);
};

// SparseMat method definitions ------------------------------------------------------------------------------------------------------
template <class Object>
SparseMat<Object>::SparseMat(int r, int c, const Object& defaultVal) {

    if (r < 1) {

        rowSize = 1;
        rows.resize(1);
    }
    else {

        rowSize = r;
        rows.resize(r);
    }

    if (c < 1)
        colSize = 1;
    else
        colSize = c;
    SparseMat<Object>::defaultVal = defaultVal;
}

template <class Object>
const Object& SparseMat<Object>::get(int r, int c) const {

    if (r >= rowSize || c >= colSize || r < 0 || c < 0) throw "Exception thrown";

    typename MatRow::const_iterator iter;
    int place = 0;

    for (iter = rows[r].begin(); iter != rows[r].end(); iter++) {

        place = (*iter).getCol();

        if (place == c) {

            return (*iter).data;
        }
    }

    return defaultVal;
}

template <class Object>
bool SparseMat<Object>::set(int r, int c, const Object& x) {

    if (r >= rowSize || c >= colSize || r < 0 || c < 0) return false;

    typename MatRow::iterator iter;
    int place = 0;

    for (iter = rows[r].begin(); iter != rows[r].end(); iter++) {

        place = (*iter).getCol();

        if (place == c) {
            
            if (x == defaultVal) {

                rows[r].erase(iter);
                return true;
            }

            (*iter).data = x;
            return true;
        }
    }

    rows[r].push_back(MatNode<Object>(c, x));
    return true;
}

template <class Object>
void SparseMat<Object>::clear() {

    SparseMat<Object> clearMatrix(rowSize, colSize, defaultVal);
    *this = clearMatrix;
}

template <class Object>
void SparseMat<Object>::showSubSquare(int start, int size) {

    typename MatRow::const_iterator iter;
    bool foundValue = false;

    for (int i = start; i < start + size; i++) {

        for (int j = start; j < start + size; j++) {

            for (iter = rows[i].begin(); iter != rows[i].end(); iter++) {

                if ((*iter).getCol() == j) {

                    cout << (*iter).data << " ";
                    foundValue = true;
                }
            }

            if (foundValue == false) cout << " " << defaultVal << " ";
            foundValue = false;
        }

        cout << endl;
    }

    cout << endl;
}

template <class Object>
void SparseMat<Object>::showSubSquare(int row, int col, int size) {

    if (row >= rowSize || col >= colSize || row < 0 || col < 0) return;

    typename MatRow::const_iterator iter;
    bool foundValue = false;

    for (int i = row; i < row + size; i++) {

        for (int j = col; j < col + size; j++) {

            for (iter = rows[i].begin(); iter != rows[i].end(); iter++) {

                if ((*iter).getCol() == j) {

                    cout << (*iter).data << " ";
                    foundValue = true;
                }
            }

            if (foundValue == false) cout << " " << defaultVal << " ";
            foundValue = false;
        }

        cout << endl;
    }

    cout << endl;
}

/* Runs ------------------------------------------------------------------------------------------------------

Original run -------------------------------------------------------

0
35
21
oops
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0 35  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0 21  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0 21  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0

 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0 99

 Custom runs -------------------------------------------------------

 Set value 64 at (300, MAT_SIZE - 1)
Using the get function, the set value was retrieved as 64
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0 64  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0

Set value 23 at (500, 500)
Using the get function, the set value was retrieved as 23
 0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0 23  0  0  0  0
 0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0

Set value 12 at (MAT_SIZE - 1, 700)
Using the get function, the set value was retrieved as 12
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0 12  0  0  0  0

Set value 77 at (32, 79)
Using the get function, the set value was retrieved as 77
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
77  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0

Set value 99 at (999, 999)
Using the get function, the set value was retrieved as 99
99  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
*/

#define MAT_SIZE 100000
typedef SparseMat<float> SpMat;

// --------------- main ---------------
int main()
{
    SpMat mat(MAT_SIZE, MAT_SIZE, 0); // 100000 x 100000 filled with 0

    // test mutators
    /*mat.set(2, 5, 10);
    mat.set(2, 5, 35);   // should overwrite the 10
    mat.set(3, 9, 21);
    mat.set(MAT_SIZE, 1, 5);  // should fail silently
    mat.set(9, 9, mat.get(3, 9));  // should copy the 21 here
    mat.set(4, 4, -9);
    mat.set(4, 4, 0);   // should remove the -9 node entirely
    mat.set(MAT_SIZE - 1, MAT_SIZE - 1, 99);

    // test accessors and exceptions
    try
    {
        cout << mat.get(7, 8) << endl;
        cout << mat.get(2, 5) << endl;
        cout << mat.get(9, 9) << endl;
        cout << mat.get(-4, 7) << endl;  // should throw an exception
    }
    catch (...)
    {
        cout << "oops" << endl;
    }

    // show top left 15x15
    mat.showSubSquare(0, 15);

    // show bottom right 15x15
    mat.showSubSquare(MAT_SIZE - 15, 15);*/

    mat.set(300, MAT_SIZE - 1, 64);
    cout << "Set value 64 at (300, MAT_SIZE - 1)\nUsing the get function, the set value was retrieved as " << mat.get(300, MAT_SIZE - 1) << endl;
    mat.showSubSquare(290, MAT_SIZE - 10, 20);
    mat.set(500, 500, 23);
    cout << "Set value 23 at (500, 500)\nUsing the get function, the set value was retrieved as " << mat.get(500, 500) << endl;
    mat.showSubSquare(495, 495, 10);
    mat.set(MAT_SIZE - 1, 700, 12);
    cout << "Set value 12 at (MAT_SIZE - 1, 700)\nUsing the get function, the set value was retrieved as " << mat.get(MAT_SIZE - 1, 700) << endl;
    mat.showSubSquare(MAT_SIZE - 15, 690, 15);
    mat.set(32, 79, 77);
    cout << "Set value 77 at (32, 79)\nUsing the get function, the set value was retrieved as " << mat.get(32, 79) << endl;
    mat.showSubSquare(30, 79, 20);
    mat.set(999, 999, 99);
    cout << "Set value 99 at (999, 999)\nUsing the get function, the set value was retrieved as " << mat.get(999, 999) << endl;
    mat.showSubSquare(999, 999, 40);
    mat.set(-102983, 200000, 10);
}