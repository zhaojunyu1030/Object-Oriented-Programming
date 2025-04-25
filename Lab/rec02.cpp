/* Junyu Zhao
 * rec02.cpp
 * Classify and sort chemical elements
 *  by the number of carbon and hydrogen atoms
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
using namespace std;


// structure
struct Hydrocarbon {
    vector<string> names;
    int cNum;
    int hNum;
};


// function prototypes
void openFile(ifstream& file);
size_t findFormula(vector<Hydrocarbon>& hydrocarbons,
    string& name, int c, int h);
void insertFormula(vector<Hydrocarbon>& hydrocarbons,
    string& name, int c, int h);
void fillVector(ifstream& file, vector<Hydrocarbon>& hydrocarbons);
void displayFormula(Hydrocarbon& hydrocarbon);
void displayVector(vector<Hydrocarbon>& hydrocarbons);
void sort(vector<Hydrocarbon>& hydrocarbons);


int main()
{
    ifstream file;
    openFile(file);

    vector<Hydrocarbon> hydrocarbons;
    fillVector(file, hydrocarbons);

    cout << "\nUnsorted:" << endl;
    displayVector(hydrocarbons);

    cout << "\nSorted:" << endl;
    sort(hydrocarbons);
    displayVector(hydrocarbons);

    file.close();
}


// open the file
void openFile(ifstream& file) {
    string filename;
    do {
        cout << "File name? ";
        cin >> filename;
        file.open(filename);
    } while (!file);
}


// find if the formula exists
size_t findFormula(vector<Hydrocarbon>& hydrocarbons,
    const string& name, int c, int h) {
    // if the formula exists, return the index,
    // else return the size of the vector
    for (size_t i = 0; i < hydrocarbons.size(); i++) {
        if (hydrocarbons[i].cNum == c && hydrocarbons[i].hNum == h) {
            return i;
        }
    }
    return hydrocarbons.size();
}


// if the formula exists, insert the name
// into the vector of names of the corresponding item
// if not, add a new item at the end of the vector of hydrocarbons
void insertFormula(vector<Hydrocarbon>& hydrocarbons,
    const string& name, int c, int h) {
    size_t index = findFormula(hydrocarbons, name, c, h);
    if (index == hydrocarbons.size()) {
        hydrocarbons.push_back(Hydrocarbon({name}, c, h));
    } else {
        hydrocarbons[index].names.push_back(name);
    }
}


// fill the vector of hydrocarbons
void fillVector(ifstream& file, vector<Hydrocarbon>& hydrocarbons) {
    string name;
    int cNum;
    char c;
    int hNum;
    char h;
    // find all the formulae in the file
    while (file >> name >> c >> cNum >> h >> hNum) {
        insertFormula(hydrocarbons, name, cNum, hNum);
    }
}


// display a single hydrocarbon
void displayFormula(const Hydrocarbon& hydrocarbon) {
    cout << 'C' << hydrocarbon.cNum << 'H' << hydrocarbon.hNum;
    // display all the names in the vector
    for (const string& name : hydrocarbon.names) {
        cout << ' ' << name;
    }
    cout << endl;
}


// display all the formulae in the vector of hydrocarbons
void displayVector(const vector<Hydrocarbon>& hydrocarbons) {
    // display all the formulae in the certain pattern
    for (const Hydrocarbon& hydrocarbon : hydrocarbons) {
        displayFormula(hydrocarbon);
    }
}


// sort the formulae according to
// the number of carbon atoms and hydrogen atoms respectively
void sort(vector<Hydrocarbon>& hydrocarbons) {
    // check all the items in the vector
    for (size_t i = 0; i < hydrocarbons.size(); i++) {
        // compare the item with all the previous ones
        for (size_t j = i; j > 0; j--) {
            if (hydrocarbons[j - 1].cNum >= hydrocarbons[j].cNum) {
                if (hydrocarbons[j - 1].cNum > hydrocarbons[j].cNum
                    || hydrocarbons[j - 1].hNum > hydrocarbons[j].hNum)
                swap(hydrocarbons[j], hydrocarbons[j - 1]);
            }
        }
    }
}