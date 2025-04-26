/* polynomial.h - Junyu (Leo) Zhao */
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>

using namespace std;


class Polynomial {
    // output operator
    friend ostream& operator<<(ostream&, const Polynomial&);
    // ==
    friend bool operator==(const Polynomial&, const Polynomial&);

    // Node
    struct Node {
        int coefficient;
        Node* next;
    };

public:
    // default constructor
    Polynomial();
    // constructor
    Polynomial(const vector<int>&);
    // copy constructor
    Polynomial(const Polynomial&);
    // destructor
    ~Polynomial();
    // copy assignment operator
    Polynomial& operator=(const Polynomial&);
    // +=
    Polynomial& operator+=(const Polynomial&);
    // +
    friend Polynomial operator+(const Polynomial&, const Polynomial&);
    // !=
    bool operator!=(const Polynomial&);
    // evaluate()
    int evaluate(int);

private:
    Node* header;
    int degree;

    // helpers
    void removeLeadingZeros();
    void addCoefficients(Node*, Node*);
};

#endif //POLYNOMIAL_H
