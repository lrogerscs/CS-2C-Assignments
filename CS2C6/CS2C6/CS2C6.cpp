// Client methods and definitions ---------------------------------------------------------------------------------------------------------------------------------------------
#include <vector>
#include "EBookEntry.h"

using namespace std;

// Prototypes ----------------------------------------------------------------------------------------------------------

int Hash(int key);
int Hash(const string& key); // had to move prototypes above #include "FHhashQPwFind.h" to allow the header to access the functions
int Hash(const EBookEntry& item);
int getKey(const EBookEntry& item);
//string getKey(const EBookEntry & item);

#include "FHhashQPwFind.h"

#define NUM_RANDOM_INDICES 25

// Main  ---------------------------------------------------------------------------------------------------------------

int main()
{

    EBookEntryReader bookInput("catalog-short4.txt");
    EBookEntry book;
    vector<int> randomIndices; // small vector to store the random numbers for hash table's find()
    
    FHhashQPwFind<EBookEntry, int> hashTable; // for ID equality

    //FHhashQPwFind<EBookEntry, string> hashTable; // for any string equality

    // we want two books to be identical in different ways:  ID or author
    EBookEntry::setSortType(EBookEntry::SORT_BY_ID);

    //EBookEntry::setSortType(EBookEntry::SORT_BY_CREATOR);

    cout << "File name: " << bookInput.getFileName() << endl;
    cout << "Number of books in file: " << bookInput.getNumBooks() << endl;
    cout << "\nThe 25 random books are:\n" << endl;

    srand(time(NULL));
    for (int i = 0; i < NUM_RANDOM_INDICES; i++) {

        randomIndices.push_back(rand() % bookInput.getNumBooks());
        hashTable.insert(bookInput[randomIndices[i]]);

        cout << "Book " << i + 1 << " with number " << bookInput[randomIndices[i]].getETextNum() << " is by " << bookInput[randomIndices[i]].getCreator() << endl;
    }

    // attempt to find on the selected key
    cout << "\nUsing the find function to find the same 25 books in the hash table:\n" << endl;
    for (int k = 0; k < NUM_RANDOM_INDICES; k++)
    {
        try
        {
            book = hashTable.find(bookInput[randomIndices[k]].getETextNum());

            //book = hashTable.find(bookInput[randomIndices[k]].getCreator());

            cout << "Book " << k + 1 << " with number " << bookInput[randomIndices[k]].getETextNum() << " is by " << bookInput[randomIndices[k]].getCreator() << endl;
        }
        catch (...)
        {
            cout << "Not found" << endl;
        }
    }

    // test known failures exceptions:
    cout << "\nThe next 3 tests of find should fail" << endl;
    try
    {
        book = hashTable.find(-3);

        //book = hashTable.find("Jack Kerouac");
    }
    catch (...)
    {
        cout << "Not found" << endl;
    }

    // more failures
    try
    {
        book = hashTable.find(67);

        //book = hashTable.find("Kanata Livington");
    }
    catch (...)
    {
        cout << "Not found" << endl;
    }

    try
    {
        book = hashTable.find(199);

        //book = hashTable.find("Luis Lowry");
    }
    catch (...)
    {
        cout << "Not found" << endl;
    }
}

// Method definitions -------------------------------------------------------------------------------------------------------

int Hash(int key)
{

    return key; // hash code from modules (works for all integers)
}

int Hash(const string& key)
{

    unsigned int k, retVal = 0; // hash code from modules (works for all strings)

    for (k = 0; k < key.length(); k++)
        retVal = 37 * retVal + key[k];

    return retVal;
}

int Hash(const EBookEntry& item)
{

    return Hash(item.getETextNum());

    //return Hash(item.getCreator());
}


// used for author equality
/*string getKey(const EBookEntry & item)
{

   return item.getCreator() ;
}*/


// used for ID equality
int getKey(const EBookEntry& item)
{

    return item.getETextNum();
}

/* Runs -----------------------------------------------------------------------------------------------------------------

Run 1: int key ---------------------------------

File name: catalog-short4.txt
Number of books in file: 4863

The 25 random books are:

Book 1 with number 28351 is by (no data found)
Book 2 with number 26271 is by Newell, Peter, 1862-1924
Book 3 with number 28911 is by Okakura, Kakuzo, 1862-1913
Book 4 with number 11250 is by Sylvester, Charles Herbert
Book 5 with number 25186 is by Altsheler, Joseph A. (Joseph Alexander), 1862-1919
Book 6 with number 19833 is by Bruno, Giordano, 1548-1600
Book 7 with number 29533 is by Birmingham, George A., 1865-1950
Book 8 with number 28135 is by Various
Book 9 with number 4319 is by Clontz, J.
Book 10 with number 28958 is by Merwin, Samuel, 1874-1936
Book 11 with number 27963 is by Seeley, Levi, 1847-1928
Book 12 with number 26324 is by Fletcher, J. S. (Joseph Smith), 1863-1935
Book 13 with number 26327 is by Crawford, F. Marion (Francis Marion), 1854-1909
Book 14 with number 16459 is by Saint-Sa??(replaced invalid characters with question marks)ns, Camille, 1835-1921
Book 15 with number 28421 is by Vasari, Giorgio, 1511-1574
Book 16 with number 28438 is by Shea, Robert, 1933-1994
Book 17 with number 27740 is by Haslam, John, 1764-1844
Book 18 with number 6636 is by Ryder, Annie H
Book 19 with number 24793 is by Day, Holman, 1865-1935
Book 20 with number 28883 is by Vincent, Harl, 1893-1968
Book 21 with number 27368 is by Faguet, ??(replaced invalid characters with question marks)mile, 1847-1916
Book 22 with number 28823 is by Meredith, George, 1828-1909
Book 23 with number 26245 is by Thucydides, 455? BC-395 BC
Book 24 with number 28964 is by Keene, Louis
Book 25 with number 30271 is by Murphy, Arthur, 1727-1805

Using the find function to find the same 25 books in the hash table:

Book 1 with number 28351 is by (no data found)
Book 2 with number 26271 is by Newell, Peter, 1862-1924
Book 3 with number 28911 is by Okakura, Kakuzo, 1862-1913
Book 4 with number 11250 is by Sylvester, Charles Herbert
Book 5 with number 25186 is by Altsheler, Joseph A. (Joseph Alexander), 1862-1919
Book 6 with number 19833 is by Bruno, Giordano, 1548-1600
Book 7 with number 29533 is by Birmingham, George A., 1865-1950
Book 8 with number 28135 is by Various
Book 9 with number 4319 is by Clontz, J.
Book 10 with number 28958 is by Merwin, Samuel, 1874-1936
Book 11 with number 27963 is by Seeley, Levi, 1847-1928
Book 12 with number 26324 is by Fletcher, J. S. (Joseph Smith), 1863-1935
Book 13 with number 26327 is by Crawford, F. Marion (Francis Marion), 1854-1909
Book 14 with number 16459 is by Saint-Sa??(replaced invalid characters with question marks)ns, Camille, 1835-1921
Book 15 with number 28421 is by Vasari, Giorgio, 1511-1574
Book 16 with number 28438 is by Shea, Robert, 1933-1994
Book 17 with number 27740 is by Haslam, John, 1764-1844
Book 18 with number 6636 is by Ryder, Annie H
Book 19 with number 24793 is by Day, Holman, 1865-1935
Book 20 with number 28883 is by Vincent, Harl, 1893-1968
Book 21 with number 27368 is by Faguet, ??(replaced invalid characters with question marks)mile, 1847-1916
Book 22 with number 28823 is by Meredith, George, 1828-1909
Book 23 with number 26245 is by Thucydides, 455? BC-395 BC
Book 24 with number 28964 is by Keene, Louis
Book 25 with number 30271 is by Murphy, Arthur, 1727-1805

The next 3 tests of find should fail
Not found
Not found
Not found

Run 2: string key ---------------------------------

File name: catalog-short4.txt
Number of books in file: 4863

The 25 random books are:

Book 1 with number 27645 is by Hasse, Henry, 1913-1977
Book 2 with number 29612 is by Pinkham, Lydia Estes, 1819-1883
Book 3 with number 27591 is by Hocking, Joseph, 1860-1937
Book 4 with number 29416 is by Burks, Arthur J., 1898-1974
Book 5 with number 26618 is by Leslie, Madeline, 1815-1893
Book 6 with number 28133 is by Various
Book 7 with number 25520 is by Cameron, Charles Alexander, Sir, 1830-1921
Book 8 with number 365 is by Austin, Mary Hunter, 1868-1934
Book 9 with number 27375 is by Pain, Barry, 1864-1928
Book 10 with number 27662 is by Various
Book 11 with number 27187 is by Martin, George Madden, 1866-1936
Book 12 with number 7898 is by Prentice, Amy
Book 13 with number 26803 is by (no data found)
Book 14 with number 28926 is by De Gurowski, Adam G., count, 1805-1866
Book 15 with number 26083 is by Alger, Horatio, 1832-1899
Book 16 with number 28733 is by Doyle, Arthur Conan, Sir, 1859-1930
Book 17 with number 20737 is by Chalmers, Amy D. V.
Book 18 with number 27271 is by Jones, Henry Arthur, 1851-1929
Book 19 with number 10149 is by Cooper, James Fenimore, 1789-1851
Book 20 with number 954 is by Appleton, Victor [pseud.]
Book 21 with number 28025 is by Paton, John Gibson, 1824-1907
Book 22 with number 29916 is by Trueba y Cos??(replaced invalid characters with question marks)o, Joaqu??(replaced invalid characters with question marks)n Telesforo de, 1799?-1835
Book 23 with number 27338 is by Chadwick, Lester
Book 24 with number 25852 is by Dickens, Charles, 1812-1870
Book 25 with number 24909 is by Fenn, George Manville, 1831-1909

Using the find function to find the same 25 books in the hash table:

Book 1 with number 27645 is by Hasse, Henry, 1913-1977
Book 2 with number 29612 is by Pinkham, Lydia Estes, 1819-1883
Book 3 with number 27591 is by Hocking, Joseph, 1860-1937
Book 4 with number 29416 is by Burks, Arthur J., 1898-1974
Book 5 with number 26618 is by Leslie, Madeline, 1815-1893
Book 6 with number 28133 is by Various
Book 7 with number 25520 is by Cameron, Charles Alexander, Sir, 1830-1921
Book 8 with number 365 is by Austin, Mary Hunter, 1868-1934
Book 9 with number 27375 is by Pain, Barry, 1864-1928
Book 10 with number 27662 is by Various
Book 11 with number 27187 is by Martin, George Madden, 1866-1936
Book 12 with number 7898 is by Prentice, Amy
Book 13 with number 26803 is by (no data found)
Book 14 with number 28926 is by De Gurowski, Adam G., count, 1805-1866
Book 15 with number 26083 is by Alger, Horatio, 1832-1899
Book 16 with number 28733 is by Doyle, Arthur Conan, Sir, 1859-1930
Book 17 with number 20737 is by Chalmers, Amy D. V.
Book 18 with number 27271 is by Jones, Henry Arthur, 1851-1929
Book 19 with number 10149 is by Cooper, James Fenimore, 1789-1851
Book 20 with number 954 is by Appleton, Victor [pseud.]
Book 21 with number 28025 is by Paton, John Gibson, 1824-1907
Book 22 with number 29916 is by Trueba y Cos??(replaced invalid characters with question marks)o, Joaqu??(replaced invalid characters with question marks)n Telesforo de, 1799?-1835
Book 23 with number 27338 is by Chadwick, Lester
Book 24 with number 25852 is by Dickens, Charles, 1812-1870
Book 25 with number 24909 is by Fenn, George Manville, 1831-1909

The next 3 tests of find should fail
Not found
Not found
Not found
*/