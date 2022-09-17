// Student name: Lee Rogers

// Part A ----------------------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

// Sublist prototype
class Sublist {

public:

    Sublist(vector<int>* orig = NULL)
        : sum(0), originalObjects(orig) { }
    Sublist addItem(int indexOfItemToAdd);
    void showSublist() const;
    int getSum() const { return sum; }

private:

    int sum;
    vector<int>* originalObjects;
    vector<int> indices;
};

// main
int main() {

    int TARGET = 180;
    vector<int> dataSet;
    vector<Sublist> col;
    int colSize = 0, endSum = 0, index = 0, maxSum = 0;
    bool foundPerfect = false;

    dataSet.push_back(20); dataSet.push_back(12); dataSet.push_back(22);
    dataSet.push_back(15); dataSet.push_back(25);
    dataSet.push_back(19); dataSet.push_back(29);
    dataSet.push_back(18);
    dataSet.push_back(11); dataSet.push_back(13); dataSet.push_back(17);

    col.clear();
    cout << "Target time: " << TARGET << endl;

    // code provided by student

    Sublist default_sublist(&dataSet); // initialize default sublist with original set of values

    for (int i = 0; i < dataSet.size(); i++) maxSum += dataSet[i];

    // check if the target is too big
    if (maxSum < TARGET) {

        cout << "The target is too large." << endl;

        return 0;
    }

    col.push_back(default_sublist);
    colSize = col.size();

    for (int i = 0; i < dataSet.size(); i++) {

        for (int j = 0; j < colSize; j++) {

            if (col[j].getSum() + dataSet[i] <= TARGET) {

                col.push_back(col[j].addItem(i));
            }

            if (col[j].getSum() + dataSet[i] == TARGET) {

                foundPerfect = true;
                break;
            }
        }

        if (foundPerfect == true) {

            break;
        }

        colSize = col.size();
    }

    for (int i = 0; i < col.size(); i++) {

        // start at base values
        if (i == 0) {

            endSum = col[i].getSum(); 
            index = i;
        }

        // if the sum of another subset is higher, replace the values
        if (col[i].getSum() > endSum) {

            endSum = col[i].getSum();
            index = i;
        }
    }

    col[index].showSublist();

    return 0;
}

// Sublist method definitions
Sublist Sublist::addItem(int indexOfItemToAdd) {

    Sublist new_sublist = *this;
    vector<int> copy = *originalObjects;

    new_sublist.indices.push_back(indexOfItemToAdd);
    new_sublist.sum = sum + copy[indexOfItemToAdd];

    return new_sublist;
}

void Sublist::showSublist() const {

    vector<int> copy = *originalObjects;

    cout << "Sublist-----------------------------\n  sum:" << sum << "\n";

    for (int i = 0; i < indices.size(); i++) {

        cout << "  array [" << indices[i] << "] = " << copy[indices[i]] << ", ";
    }

    cout << endl;
}

/* runs

Please let me know if there are any problems with the runs. I wasn't completely certain on the requirements.

Target time: 180
Sublist -----------------------------
  sum:179
  array [0] = 20,   array [1] = 12,   array [3] = 15,   array [4] = 25,   array [5] = 19,   array [6] = 29,   array [7] = 18,
  array [8] = 11,   array [9] = 13,   array [10] = 17,

Target time: 1
Sublist -----------------------------
  sum:0

Target time: 67
Sublist -----------------------------
  sum:67
  array [0] = 20,   array [2] = 22,   array [4] = 25,

Target time: 200
Sublist -----------------------------
  sum:190
  array [0] = 20,   array [1] = 12,   array [2] = 22,   array [3] = 15,   array [4] = 25,   array [5] = 19,
  array [6] = 29,   array [7] = 18,   array [9] = 13,   array [10] = 17,

Target time: 1000
The target is too large.

Target time: 134
Sublist -----------------------------
  sum:134
  array [0] = 20,   array [1] = 12,   array [2] = 22,   array [3] = 15,   array [4] = 25,   array [6] = 29,   array [8] = 11,

Target time: 88
Sublist -----------------------------
  sum:88
  array [0] = 20,   array [1] = 12,   array [2] = 22,   array [3] = 15,   array [5] = 19,

Target time: 16
Sublist -----------------------------
  sum:15
  array [3] = 15,
*/

// Part B ----------------------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// iTunesEntry prototype (from provided files)
class iTunesEntry
{
public:

private:
    string title, artist;
    int tuneTime;

public:
    static const unsigned int MIN_STRING = 1;
    static const unsigned int MAX_STRING = 300;
    static const int MAX_TIME = 10000000;

    iTunesEntry();

    //mutators
    bool setTitle(string sArg);
    bool setArtist(string sArg);
    bool setTime(int nArg);

    // accessors
    string getTitle() const { return title; }
    string getArtist() const { return artist; }
    int getTime() const { return tuneTime; }

    // helpers
    static int convertStringToSeconds(string sToCnvrt);
    string convertTimeToString() const;

    // comparator tools
    // could use static const int, instead:
private:
    static int sortKey;

public:
    static enum { SORT_BY_TITLE, SORT_BY_ARTIST, SORT_BY_TIME } eSortType;
    static bool setSortType(int whichType);
    bool operator<(const iTunesEntry& other) const;
    bool operator>(const iTunesEntry& other) const;
    bool operator==(const iTunesEntry& other) const;
    bool operator!=(const iTunesEntry& other) const;
    string getArtistLastName() const;
};

// iTunesEntryReader prototype (from provided files)
class iTunesEntryReader
{
private:
    vector <iTunesEntry> tunes;
    int numTunes;
    bool fileOpenError;
    string tuneFile;
    bool readOneEntry(ifstream& infile, iTunesEntry& tune);
    bool isDataLine(string line);

public:
    iTunesEntryReader(string fileName);
    iTunesEntry& operator[](int k);
    string getFileName() { return tuneFile; }
    bool readError() { return fileOpenError; }
    int getNumTunes() { return numTunes; }
};

// Sublist prototype
class Sublist {

public:

    Sublist(vector<iTunesEntry>* orig = NULL)
        : sum(0), originalObjects(orig) { }
    Sublist addItem(int indexOfItemToAdd);
    void showSublist() const;
    int getSum() const { return sum; }

private:

    int sum;
    vector<iTunesEntry>* originalObjects;
    vector<int> indices;
};

// main
int main()
{
    const int TARGET = 3600;
    vector<iTunesEntry> dataSet;
    vector<Sublist> col;
    int colSize = 0, endSum = 0, index = 0, maxSum = 0, array_size = 0;
    bool foundPerfect = false;

    // read the data
    iTunesEntryReader tunes_input("itunes_file.txt");
    if (tunes_input.readError())
    {
        cout << "couldn't open " << tunes_input.getFileName()
            << " for input.\n";
        exit(1);
    }

    // time the algorithm -------------------------
    clock_t startTime, stopTime;
    startTime = clock();

    // create a vector of objects for our own use:
    array_size = tunes_input.getNumTunes();
    for (int k = 0; k < array_size; k++)
        dataSet.push_back(tunes_input[k]);

    cout << "Target time: " << TARGET << endl;

    // code provided by student

    Sublist default_sublist(&dataSet); // initialize default sublist with original set of values

    for (int i = 0; i < dataSet.size(); i++) maxSum += dataSet[i].getTime();

    // check if the target is too big
    if (maxSum < TARGET) {

        cout << "The target is too large." << endl;

        return 0;
    }

    col.push_back(default_sublist);
    colSize = col.size();

    for (int i = 0; i < dataSet.size(); i++) {

        for (int j = 0; j < colSize; j++) {

            if (col[j].getSum() + dataSet[i].getTime() <= TARGET) {

                col.push_back(col[j].addItem(i));
            }

            if (col[j].getSum() + dataSet[i].getTime() == TARGET) {

                foundPerfect = true;
                break;
            }
        }

        if (foundPerfect == true) {
            
            break;
        }

        colSize = col.size();
    }

    for (int i = 0; i < col.size(); i++) {

        // start at base values
        if (i == 0) {

            endSum = col[i].getSum();
            index = i;
        }

        // if the sum of another subset is higher, replace the values
        if (col[i].getSum() > endSum) {

            endSum = col[i].getSum();
            index = i;
        }
    }

    col[index].showSublist();

    // how we determine the time elapsed -------------------
    stopTime = clock();
    // report algorithm time
    cout << "\nAlgorithm Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;

    return 0;
}

// Sublist method definitions
Sublist Sublist::addItem(int indexOfItemToAdd) {

    Sublist new_sublist = *this;
    vector<iTunesEntry> copy = *originalObjects;

    new_sublist.indices.push_back(indexOfItemToAdd);
    new_sublist.sum = sum + copy[indexOfItemToAdd].getTime();

    return new_sublist;
}

void Sublist::showSublist() const {

    vector<iTunesEntry> copy = *originalObjects;

    cout << "Sublist-----------------------------\n  sum:" << sum << "\n";

    for (int i = 0; i < indices.size(); i++) {

        cout << "  array [" << indices[i] << "] = " << copy[indices[i]].getTitle() << " by " << copy[indices[i]].getArtist() << "(" << copy[indices[i]].getTime() << ") ,";
    }

    cout << endl;
}

// iTunesEntry and iTunesEntryReader method definitions
bool iTunesEntryReader::isDataLine(string line)
{
    string s;
    if (line.length() < 1)
        return false;
    if (line == "#")
        return true;
    return false;
}

iTunesEntry& iTunesEntryReader::operator[](int k)
{
    static iTunesEntry dummyReturn;
    if (k < 0 || k >= numTunes)
        return dummyReturn;
    return tunes[k];
}

/* reads 3 lines from the input stream, for example

Eric Clapton
Pretending
283

*/

bool iTunesEntryReader::readOneEntry(ifstream& infile, iTunesEntry& tune)
{
    string nextLine, fileTitle, fileArtist, fileTime;
    int tuneTime;

    if (!infile.eof())
        getline(infile, fileArtist);
    else
        return false;

    if (!infile.eof())
        getline(infile, fileTitle);
    else
        return false;

    if (!infile.eof())
        getline(infile, fileTime);
    else
        return false;
    // convert string to int
    istringstream(fileTime) >> tuneTime;

    tune.setArtist(fileArtist);
    tune.setTitle(fileTitle);
    tune.setTime(tuneTime);

    return true;
}

// constructor which does entire read operation
iTunesEntryReader::iTunesEntryReader(string fileName)
{
    string name;
    string line;
    iTunesEntry tune;

    numTunes = 0;
    fileOpenError = false;
    tuneFile = "NO FILE NAME PROVIDED";

    if (fileName.length() == 0)
    {
        fileOpenError = true;
        return;
    }
    tuneFile = fileName;

    // open file for reading
    ifstream infile(fileName.c_str());
    if (!infile)
    {
        fileOpenError = true;
        return;
    }

    // for each line that starts #. read and add to vector
    numTunes = 0;
    while (!infile.eof())
    {
        getline(infile, line);
        if (isDataLine(line))
        {
            if (!readOneEntry(infile, tune))
            {
                fileOpenError = true;
                break;
            }
            tunes.push_back(tune);
            numTunes++;
        }
    }
    infile.close();
}

// iTunesEntry methods ---------------------------------------------------
int iTunesEntry::sortKey = iTunesEntry::SORT_BY_ARTIST;

// default constructor
iTunesEntry::iTunesEntry()
    : title(""), artist(""), tuneTime(0)
{
}

// mutators
bool iTunesEntry::setTitle(string sArg)
{
    if (sArg.length() < MIN_STRING || sArg.length() > MAX_STRING)
        return false;
    title = sArg;
    return true;
}
bool iTunesEntry::setArtist(string sArg)
{
    if (sArg.length() < MIN_STRING || sArg.length() > MAX_STRING)
        return false;
    artist = sArg;
    return true;
}
bool iTunesEntry::setTime(int nArg)
{
    if (nArg < 0 || nArg > MAX_TIME)
        return false;
    tuneTime = nArg;
    return true;
}


int iTunesEntry::convertStringToSeconds(string sToCnvrt)
{
    unsigned int colonPos;
    int minutes, seconds, lengthOfSecString;

    if (sToCnvrt.length() < 1)
        return 0;
    colonPos = sToCnvrt.find_first_of(":");
    if (colonPos < 0 || colonPos > iTunesEntry::MAX_STRING)
        return 0;

    istringstream(sToCnvrt.substr(0, colonPos)) >> minutes;
    lengthOfSecString = sToCnvrt.length() - 1 - colonPos;
    istringstream(sToCnvrt.substr(colonPos + 1, lengthOfSecString))
        >> seconds;

    return minutes * 60 + seconds;
}

string iTunesEntry::convertTimeToString() const
{
    int minutes, seconds;
    ostringstream cnvrt1, cnvrt2;
    string retString = "", strSeconds, strMinutes;

    minutes = tuneTime / 60;
    seconds = tuneTime % 60;

    cnvrt1 << minutes;
    cnvrt2 << seconds;

    strMinutes += cnvrt1.str();
    strSeconds = cnvrt2.str();

    if (strSeconds.length() < 2)
        strSeconds = "0" + strSeconds;

    return strMinutes + ":" + strSeconds;
}

bool iTunesEntry::setSortType(int whichType)
{
    switch (whichType)
    {
    case SORT_BY_TITLE:
    case SORT_BY_ARTIST:
    case SORT_BY_TIME:
        sortKey = whichType;
        return true;
    default:
        return false;
    }
    return true;
}

bool iTunesEntry::operator<(const iTunesEntry& other) const
{
    switch (sortKey)
    {
    case SORT_BY_TITLE:
        return (title < other.title);
    case SORT_BY_ARTIST:
        // get last name from string
        // stack the last name before the first - no worries about trailing last
        return
            (
                getArtistLastName() + artist
                <
                other.getArtistLastName() + other.getArtist()
                );
    case SORT_BY_TIME:
        return (tuneTime < other.tuneTime);
    default:
        return false;
    }
    return true;
}

bool iTunesEntry::operator>(const iTunesEntry& other) const
{
    return (other < *this);
}

bool iTunesEntry::operator==(const iTunesEntry& other) const
{
    return !(other < *this) && !(*this < other);
}

bool iTunesEntry::operator!=(const iTunesEntry& other) const
{
    return !(other == *this);
}

string iTunesEntry::getArtistLastName() const
{
    // search for first blank from end of string
    // assume no trailing spaces
    string retString;
    int k, length;

    length = artist.length();
    if (length < 1)
        return "";

    for (k = length - 1; k >= 0; k--)
    {
        if (artist[k] == ' ')
            break;
    }

    if (k >= length - 1)
        return "";

    return artist.substr(k + 1, artist.length() - 1 - k);
}

/* runs

Please let me know if there are any problems with the runs. I wasn't completely certain on the requirements.

Target time: 0
Sublist-----------------------------
  sum:0


Algorithm Elapsed Time: 0 seconds.

Target time: 1200
Sublist-----------------------------
  sum:1200
  array [0] = Cowboy Casanova by Carrie Underwood(236) ,  array [1] = Quitter by Carrie Underwood(220) ,  array [2] = Russian Roulette by Rihanna(228) ,  
  array [6] = Bad Love by Eric Clapton(308) ,  array [11] = Hot Cha by Roy Buchanan(208) ,

Algorithm Elapsed Time: 0.006 seconds.

Target time: 3600
Sublist-----------------------------
  sum:3600
  array [0] = Cowboy Casanova by Carrie Underwood(236) ,  array [1] = Quitter by Carrie Underwood(220) ,  array [2] = Russian Roulette by Rihanna(228) ,  
  array [4] = Monkey Wrench by Foo Fighters(230) ,  array [5] = Pretending by Eric Clapton(283) ,  array [6] = Bad Love by Eric Clapton(308) ,  
  array [7] = Everybody's In The Mood by Howlin' Wolf(178) ,  array [8] = Well That's All Right by Howlin' Wolf(175) ,  
  array [9] = Samson and Delilah by Reverend Gary Davis(216) ,  array [11] = Hot Cha by Roy Buchanan(208) ,  array [12] = Green Onions by Roy Buchanan(443) ,  
  array [13] = I'm Just a Prisoner by Janiva Magness(230) ,  array [14] = You Were Never Mine by Janiva Magness(276) ,  array [15] = Hobo Blues by John Lee Hooker(187) ,  
  array [16] = I Can't Quit You Baby by John Lee Hooker(182) ,

Algorithm Elapsed Time: 0.404 seconds.

Target time: 4799
Sublist-----------------------------
  sum:4799
  array [0] = Cowboy Casanova by Carrie Underwood(236) ,  array [1] = Quitter by Carrie Underwood(220) ,  array [2] = Russian Roulette by Rihanna(228) ,  
  array [3] = All My Life by Foo Fighters(263) ,  array [4] = Monkey Wrench by Foo Fighters(230) ,  array [5] = Pretending by Eric Clapton(283) ,  
  array [6] = Bad Love by Eric Clapton(308) ,  array [8] = Well That's All Right by Howlin' Wolf(175) ,  array [9] = Samson and Delilah by Reverend Gary Davis(216) ,  
  array [10] = Twelve Sticks by Reverend Gary Davis(194) ,  array [11] = Hot Cha by Roy Buchanan(208) ,  array [12] = Green Onions by Roy Buchanan(443) ,  
  array [13] = I'm Just a Prisoner by Janiva Magness(230) ,  array [14] = You Were Never Mine by Janiva Magness(276) ,  array [15] = Hobo Blues by John Lee Hooker(187) ,  
  array [16] = I Can't Quit You Baby by John Lee Hooker(182) ,  array [17] = That's The Homie by Snoop Dogg(343) ,  array [19] = Ladies and Gentleman by The Rubyz(201) ,  
  array [20] = Watch the Girl by The Rubyz(192) ,  array [21] = Donuts for Benny by Veggie Tales(184) ,

Algorithm Elapsed Time: 12.108 seconds.

Target time: 100000
The target is too large.

Target time: 2746
Sublist-----------------------------
  sum:2746
  array [0] = Cowboy Casanova by Carrie Underwood(236) ,  array [1] = Quitter by Carrie Underwood(220) ,  array [3] = All My Life by Foo Fighters(263) ,  
  array [4] = Monkey Wrench by Foo Fighters(230) ,  array [5] = Pretending by Eric Clapton(283) ,  array [6] = Bad Love by Eric Clapton(308) ,  
  array [7] = Everybody's In The Mood by Howlin' Wolf(178) ,  array [8] = Well That's All Right by Howlin' Wolf(175) ,  
  array [9] = Samson and Delilah by Reverend Gary Davis(216) ,  array [10] = Twelve Sticks by Reverend Gary Davis(194) ,  array [12] = Green Onions by Roy Buchanan(443) ,

Algorithm Elapsed Time: 0.023 seconds.

Target time: 1834
Sublist-----------------------------
  sum:1834
  array [0] = Cowboy Casanova by Carrie Underwood(236) ,  array [2] = Russian Roulette by Rihanna(228) ,  array [3] = All My Life by Foo Fighters(263) ,  
  array [4] = Monkey Wrench by Foo Fighters(230) ,  array [6] = Bad Love by Eric Clapton(308) ,  array [7] = Everybody's In The Mood by Howlin' Wolf(178) ,  
  array [8] = Well That's All Right by Howlin' Wolf(175) ,  array [9] = Samson and Delilah by Reverend Gary Davis(216) ,

Algorithm Elapsed Time: 0.005 seconds.

Target time: 4124
Sublist-----------------------------
  sum:4124
  array [0] = Cowboy Casanova by Carrie Underwood(236) ,  array [1] = Quitter by Carrie Underwood(220) ,  array [2] = Russian Roulette by Rihanna(228) ,  
  array [3] = All My Life by Foo Fighters(263) ,  array [4] = Monkey Wrench by Foo Fighters(230) ,  array [5] = Pretending by Eric Clapton(283) ,  
  array [6] = Bad Love by Eric Clapton(308) ,  array [7] = Everybody's In The Mood by Howlin' Wolf(178) ,  array [8] = Well That's All Right by Howlin' Wolf(175) ,  
  array [9] = Samson and Delilah by Reverend Gary Davis(216) ,  array [10] = Twelve Sticks by Reverend Gary Davis(194) ,  array [11] = Hot Cha by Roy Buchanan(208) ,  
  array [12] = Green Onions by Roy Buchanan(443) ,  array [13] = I'm Just a Prisoner by Janiva Magness(230) ,  array [15] = Hobo Blues by John Lee Hooker(187) ,  
  array [16] = I Can't Quit You Baby by John Lee Hooker(182) ,  array [17] = That's The Homie by Snoop Dogg(343) ,

Algorithm Elapsed Time: 0.767 seconds.

*/