// Doubly linked list
// rec12.cpp
// Created by Junyu (Leo) Zhao on 4/18/2025
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    friend ostream& operator<<(ostream& os, const List& rhs) {
        Node* index = rhs.header;
        while (index->next->next != nullptr) {
            os << index->next->data << ' ';
            index = index->next;
        } return os;
    }

    struct Node {
        int data;
        Node* next;
        Node* prior;
    };

public:
    // Task 4
    class iterator {
        friend class List;
        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return lhs.ptr == rhs.ptr;
        }
    public:
        iterator(Node* ptr = nullptr) : ptr(ptr) { }

        iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }

        iterator& operator--() {
            ptr = ptr->prior;
            return *this;
        }

        int& operator*() const { return ptr->data; }

    private:
        Node* ptr;
    };

    // Task 1
    List() {
        capacity = 0;
        header = new Node{};
        trailer = new Node{};
        header->next = trailer;
        trailer->prior = header;
    }

    void push_back(int data) {
        Node* nptr = new Node{data};
        nptr->prior = trailer->prior;
        nptr->next = trailer;
        trailer->prior->next = nptr;
        trailer->prior = nptr;
        capacity++;
    }

    void pop_back() {
        Node* toDelete = trailer->prior;
        Node* newLast = toDelete->prior;
        newLast->next = trailer;
        trailer->prior = newLast;
        delete toDelete;
        capacity--;
    }

    int& front() {
        return header->next->data;
    }

    const int front() const {
        return header->next->data;
    }

    int& back() {
        return trailer->prior->data;
    }

    int back() const {
        return trailer->prior->data;
    }

    size_t size() const {
        return capacity;
    }

    // Task 2
    void push_front(int data) {
        Node* toAdd = new Node{data};
        toAdd->next = header->next;
        toAdd->prior = header;
        header->next->prior = toAdd;
        header->next = toAdd;
        capacity++;
    }

    void pop_front() {
        Node* toDelete = header->next;
        Node* newFirst = toDelete->next;
        newFirst->prior = header;
        header->next = newFirst;
        delete toDelete;
        capacity--;
    }

    void clear() {
        Node* index = header;
        while (index->next != trailer) {
            pop_back();
        }
    }

    // Task 3
    int& operator[](size_t ind) {
        if (ind >= capacity) { cerr << "Out of boundary." << endl; }
        Node* index = header;
        for (size_t i = 0; i < ind; i++) {
            index = index->next;
        }
        return index->next->data;
    }

    int operator[](size_t ind) const {
        if (ind >= capacity) { cerr << "Out of boundary." << endl; }
        Node* index = header;
        for (size_t i = 0; i < ind; i++) {
            index = index->next;
        }
        return index->next->data;
    }

    // Task 4
    iterator begin() {
        return iterator(header->next);
    }

    iterator end() {
        return iterator(trailer);
    }

    iterator insert(iterator ptr, int data) {
        Node* toAdd = new Node{data};
        toAdd->next = ptr.ptr;
        toAdd->prior = ptr.ptr->prior;
        ptr.ptr->prior->next = toAdd;
        ptr.ptr->prior = toAdd;
        capacity++;
        return iterator(toAdd);
    }

    iterator erase(iterator ptr) {
        ptr.ptr->next->prior = ptr.ptr->prior;
        ptr.ptr->prior->next = ptr.ptr->next;
        iterator newptr = iterator(ptr.ptr->next);
        delete ptr.ptr;
        capacity--;
        return newptr;
    }

private:
    size_t capacity;
    Node* header;
    Node* trailer;
};

bool operator!=(const List::iterator& lhs, const List::iterator& rhs) {
    return !(lhs == rhs);
}

// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList) {
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}
//
// // Task 8
// void doNothing(List aList) {
//     cout << "In doNothing\n";
//     printListInfo(aList);
//     cout << endl;
//     cout << "Leaving doNothing\n";
// }

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";

    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);


    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // // Task 7
    // cout << "\n------Task Seven------\n";
    // cout << "Copy control\n";
    // cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    // myList.clear();
    // for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    // printListInfo(myList);
    // cout << "Calling doNothing(myList)\n";
    // doNothing(myList);
    // cout << "Back from doNothing(myList)\n";
    // printListInfo(myList);
    //
    // cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    // List listTwo;
    // for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    // printListInfo(listTwo);
    // cout << "listTwo = myList\n";
    // listTwo = myList;
    // cout << "myList: ";
    // printListInfo(myList);
    // cout << "listTwo: ";
    // printListInfo(listTwo);
    // cout << "===================\n";
}
