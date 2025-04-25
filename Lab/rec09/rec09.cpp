/* rec09.cpp
 * Created by Junyu (Leo) Zhao on 3/21/2025
 */

#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numPages)
	: numOfPages(numPages)
    {}

    virtual void displayNumPages() const = 0;

private:
    unsigned numOfPages;
};

void PrintedMaterial::displayNumPages() const {
    cout << "PrintedMaterial::displayNumPages() " << numOfPages << endl;
} //  PrintedMaterial::displayNumPages

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numPages)
	: PrintedMaterial(numPages)
    {}

    // virtual NOTE even without writing "virtual"
    // again, this overriden method IS virtual
    // viruality cannot be removed once installed
    // Also note that the = 0 has is not there
    void displayNumPages() const
    {
        cout << "Magazine::displayNumPages() ";
        PrintedMaterial::displayNumPages();
    } // displayNumPages

private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numPages)
	: PrintedMaterial(numPages)
    {}

private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numPages, unsigned numIndxPgs)
	: Book(numPages),
	  numOfIndexPages(numIndxPgs)
    {}

    void displayNumPages() const
    {
        cout << "textbook::displayNumPages()";
        PrintedMaterial::displayNumPages();
        cout << "Index pages: ";
        cout << numOfIndexPages << endl;
    } //  displayNumPages

private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned numPages)
        : Book(numPages)
    {}

    void displayNumPages() const
    {
        cout << "Novel::displayNumPages() ";
        PrintedMaterial::displayNumPages();
    } // displayNumPages

private:
};


// tester/modeler code
int main() {
    TextBook text(5430, 23);
    Novel novel(213);
    Magazine mag(6);

    // as direct method calls
    cout << "\nEach will now be asked directly,\n"
	 << "using the dot member operator to\n"
	 << "display its number of pages:\n";
    text.displayNumPages();
    novel.displayNumPages();
    mag.displayNumPages();
    cout << "===========\n";

    // Storing generic objects in a vector
    cout << "\n\nNow we'll use a container. Yea!!!\n\n";
    vector< PrintedMaterial* > allThemPrinties;
    allThemPrinties.push_back(&text);
    allThemPrinties.push_back(&novel);
    allThemPrinties.push_back(&mag);

    // Looping using an index
    for(size_t ndx=0; ndx < allThemPrinties.size(); ++ ndx) {
	allThemPrinties[ndx]->displayNumPages();
	cout << endl;
    }
    cout << "===========\n";
    // Looping using ranged-for
    for (const PrintedMaterial* pmPtr : allThemPrinties) {
	pmPtr->displayNumPages();
	cout << endl;
    }
} // main
