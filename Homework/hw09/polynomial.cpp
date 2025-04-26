/* polynomial.cpp - Junyu (Leo) Zhao */
#include "polynomial.h"
#include <iostream>

using namespace std;


bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    // check whether they have same highest degree
    if (lhs.degree != rhs.degree) {
        return false;
    }
    Polynomial::Node* temp = lhs.header->next;
    Polynomial::Node* otherTemp = rhs.header->next;
    // now they should have same length of Nodes
    // compare values in two vectors one by one
    while (otherTemp) {
        // compare the coefficients in order
        if (temp->coefficient != otherTemp->coefficient) {
            return false;
        }
        temp = temp->next;
        otherTemp = otherTemp->next;
    } return true;
}  // ==

ostream& operator<<(ostream& os, const Polynomial& rhs) {
    Polynomial::Node* temp = rhs.header->next;
    // print the value of polynomial if it is a constant
    if (rhs.degree == 0) {
        os << temp->coefficient;
    } else {
        // output each term by a specific format
        for (int i = rhs.degree; i >= 0; i--) {
            // skip if the coefficient is 0
            // if coefficient is positive
            if (temp->coefficient > 0) {
                // add "+" before the term if it's not the first term
                if (i != rhs.degree) { os << '+'; }
                // not printing "1" unless it's the constant term
                if (temp->coefficient > 1 || i == 0) {
                    os << temp->coefficient;
                }
                // if coefficient is negative
            } else if (temp->coefficient < 0){
                // not printing "1" unless it's the constant term
                if (temp->coefficient < -1 || i == 0) {
                    os << temp->coefficient;
                } else { os << '-'; }
            }
            // print the unknown "x" if it's not the constant term
            if (i > 0) { os << 'x'; }
            // print the value of degree if it's not degree of 1 or the constant term
            if (i > 1) { os << '^' << i; }
            temp = temp->next;
        }
    } return os;
}  // output operator

Polynomial::Polynomial() {
    header = new Node{};
    header->next = new Node{0};
    degree = 0;
}  // default constructor

Polynomial::Polynomial(const vector<int>& coefficients) {
    degree = -1;
    header = new Node{};
    Node* cur = header;
    // convert each term in vector to linked list
    for (const int val : coefficients) {
        cur->next = new Node{val};
        cur = cur->next;
        degree++;
    } removeLeadingZeros();
}  // constructor

Polynomial::Polynomial(const Polynomial& other) {
    degree = -1;
    header = new Node{};
    Node* cur = header;
    Node* temp = other.header;
    // deep copy every term in the other one
    while (temp->next) {
        cur->next = new Node{temp->next->coefficient};
        cur = cur->next;
        temp = temp->next;
        degree++;
    } removeLeadingZeros();
}  // copy constructor

Polynomial::~Polynomial() {
    Node* cur = header;
    // delete every term on heap one by one
    while (cur->next) {
        Node* temp = cur->next;
        cur->next = temp->next;
        delete temp;
    }
}  // Destructor

Polynomial& Polynomial::operator=(const Polynomial& other) {
    // check whether trying to = itself
    if (this != &other) {
        Node* cur = header;
        // delete every term on heap
        while (cur->next) {
            Node* temp = cur->next;
            cur->next = temp->next;
            delete temp;
        }
        Node* temp = other.header;
        // deep copy every term in the other one
        while (temp->next) {
            cur->next = new Node{temp->next->coefficient};
            cur = cur->next;
            temp = temp->next;
        }
        degree = other.degree;
    } removeLeadingZeros();
    return *this;
}  // copy assignment operator

Polynomial& Polynomial::operator+=(const Polynomial& other) {
    Node* temp = header->next;
    Node* otherTemp = other.header->next;
    int dif = abs(degree - other.degree);
    // check whether both sides have same highest degree
    if (degree > other.degree) {
        // move temp until temp and otherTemp are pointing
        // to the coefficients of the same degree
        while (dif > 0) {
            temp = temp->next;
            --dif;
        }
    } else if (degree < other.degree) {
        Node* cur = header;
        // move otherTemp until temp and otherTemp are pointing
        // to the coefficients of the same degree
        while (dif > 0) {
            cur->next = new Node(otherTemp->coefficient);
            otherTemp = otherTemp->next;
            cur = cur->next;
            --dif;
        }
        cur->next = temp;
    }
    addCoefficients(temp, otherTemp);
    removeLeadingZeros();
    return *this;
}  // +=

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial temp = lhs;
    return temp += rhs;
}  // +

bool Polynomial::operator!=(const Polynomial& other) {
    return !(*this == other);
}  // !=

int Polynomial::evaluate(int val) {
    int result = 0;
    Node* temp = header->next;
    // calculate every term and add up
    for (int i = degree; i >= 0; i--) {
        result += temp->coefficient * pow(val, i);
        temp = temp->next;
    } return result;
}  // evaluate()


// helpers
void Polynomial::removeLeadingZeros() {
    Node* temp = header->next;
    // remove all zero terms at the beginning unless it's the constant term
    while (temp->coefficient == 0 && temp->next) {
        temp = temp->next;
        delete header->next;
        header->next = temp;
        --degree;
    }
}

void Polynomial::addCoefficients(Node* lhs, Node* rhs) {
    // when lhs and rhs have the same highest degree
    // add coefficients respectively
    while (rhs) {
        lhs->coefficient += rhs->coefficient;
        lhs = lhs->next;
        rhs = rhs->next;
    }
}
