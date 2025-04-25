/*
  rec01.cpp
  Created by Junyu (Leo) Zhao on 1/24/2025
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int j = 2; j < n; j++) {
        if (n % j == 0) {
            return false;
        }
    }
    return true;
}

//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"
    std::cout << "Hello, World!" << std::endl;


    // Task 2  Printing hello ...  Using "using namespace"
    cout << "Hello, World!" << endl;



    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
    int x;
    cout << x << endl;


    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
    int y = 17;
    int z = 2000000017;
    double pie = 3.14159;
    cout << sizeof(x) << endl;
    cout << sizeof(y) << endl;
    cout << sizeof(z) << endl;
    cout << sizeof(pie) << endl;


    // Task 5  Attempt to assign the wrong type of thing to a variable
    //x = "felix"; // compilation error



    //
    // Conditions
    //

    // Task 6  Testing for a range
    if (y > 10 && y < 20) {
        cout << "y is between 10 and 20" << endl;
    } else {
        cout << "y is not between 10 and 20" << endl;
    }



    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    // First with a for loop
    for (int i = 10; i <= 20; i++) {
        cout << i << ' ';
    } cout << endl;

    // Then with a while loop
    int i = 10;
    while (i <= 20) {
        cout << i << ' ';
        i++;
    }

    // Finally with a do-while loop
    int j = 10;
    do {
        cout << j << ' ';
        j++;
    }
    while (j <= 20);
    cout << endl;



    // Task 8  Looping to successfully open a file, asking user for the name
    fstream ifs;
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    ifs.open(filename);
    while (!ifs.is_open()) {
        cout << "Invalid input, enter again: ";
        cin >> filename;
        ifs.open(filename);
    }


    // Task 9  Looping, reading file word by "word".
    string word;
    while (ifs >> word) {
        cout << word << endl;
    }
    ifs.close();


    // Task 10 Open a file of integers, read it in, and display the sum.
    fstream ofs;
    ofs.open("integers.txt");
    if (!ofs.is_open()) {
        cerr << "Can't open file " << endl;
    }
    int num;
    int sum = 0;
    while (ofs >> num) {
        sum += num;
    }
    cout << sum << endl;
    ofs.close();


    // Taks 11 Open and read a file of integers and words. Display the sum.
    fstream file;
    file.open("mixed.txt");
    if (!file.is_open()) {
        cerr << "Can't open file " << endl;
        exit(1);
    }
    int num2;
    int sum2 = 0;
    while (file >> num2) {
        sum2 += num2;
    }
    cout << sum2 << endl;
    file.close();


    //
    // Vectors
    //

    // Task 12 Filling a vector of ints
    vector<int> v;
    for (int i = 10; i <= 100; i++) {
        if (i % 2 == 0) {
            v.push_back(i);
        }
    }


    // Task 13 Displaying the vector THREE times
    //         a) using the indices,
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << ' ';
    }
    cout << endl;

    //         b) using a "ranged for"
    for (int num : v) {
        cout << num << ' ';
    }
    cout << endl;

    //         c) using indices again but backwards
    for (size_t i = v.size(); i > 0; i--) {
        cout << v[i-1] << ' ';
    }
    cout << endl;

    // Task 14. Initialize a vector with the primes less than 20.
    vector<int> v2;
    for (int i = 0; i <= 20; i++) {
        if (isPrime(i))
        v2.push_back(i);
    }
    for (size_t i = 0; i < v2.size(); i++) {
        cout << v2[i] << ' ';
    }
    cout << endl;


} // main


