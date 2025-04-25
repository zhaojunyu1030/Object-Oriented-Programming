/* Junyu (Leo) Zhao
  rec07.cpp
  CS2124
  Implement the class Rational, so that the following program works.
 */

#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);

// Put your Rational class here.
class Rational {
    friend istream& operator>>(istream&, Rational&);
    friend ostream& operator<<(ostream&, const Rational&);
    friend bool operator==(const Rational&, const Rational&);
    friend bool operator<(const Rational&, const Rational&);

public:
    Rational(int num=0, int den=1) : num(num), den(den) {
        normalize();
    }

    Rational& operator+=(const Rational& other) {
        num = num * other.den + den * other.num;
        den = den * other.den;
        return *this;
    }

    Rational& operator++() {
        num += den;
        return *this;
    }

    Rational operator++(int) {
        Rational temp = *this;
        num += den;
        return temp;
    }

    explicit operator bool() const { return num != 0; }

private:
    int num;
    int den;

    void normalize() {
        int divisor = greatestCommonDivisor(abs(num), abs(den));
        num /= divisor;
        den /= divisor;
        if (den < 0) {
            num = -num;
            den = -den;
        }
    }
};


// double add(double lhs, double rhs) {
//     return lhs + rhs;
// }
//
// int three = 3;
// int four = 4;
// add(three, four);

istream& operator>>(istream& is, Rational& rhs) {
    char slash;
    is >> rhs.num >> slash >> rhs.den;
    rhs.normalize();
    return is;
}

ostream& operator<<(ostream& os, const Rational& rhs) {
    os << rhs.num << '/' << rhs.den;
    return os;
}

Rational operator+(Rational lhs, const Rational& rhs) {
    return lhs += rhs;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.num * rhs.den == lhs.den * rhs.num;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.num * rhs.den < lhs.den * rhs.num;
}

Rational& operator--(Rational& lhs) {
    lhs += -1;
    return lhs;
}

Rational operator--(Rational& lhs, int) {
    Rational temp = lhs;
    lhs += -1;
    return temp;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
 return !(lhs < rhs);
}

// Any functions that are not members and not friends should have
// prototypes here and their definitions after main.

int main()
{
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement += as a member
    cout << "a = " << a << endl;

    // Implement + as non-member, but NOT as a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;

    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    //
    // PLEASE CHECK OUT NOW
    //

     cout << "a = " << a << endl;
     cout << "++a = " << (++a) << endl;
     cout << "a = " << a << endl;
     cout << "a++ = " << (a++) << endl;
     cout << "a = " << a << endl;
     cout << "--a = " << (--a) << endl;
     cout << "a = " << a << endl;
     cout << "a-- = " << (a--) << endl;
     cout << "a = " << a << endl;

     cout << "++ ++a = " << (++ ++a) << endl;
     cout << "a = " << a << endl;
     cout << "-- --a = " << (-- --a) << endl;
     cout << "a = " << a << endl;

     cout << "a++ ++ = " << (a++ ++) << endl;
     cout << "a = " << a << endl;

     // Even though the above example, (a++ ++), compiled, the
     // following shouldn't.
     // But some compiler vendors might let it...  Is your compiler
     // doing the right thing? Why SHOULDN'T it compile?
     //cout << "a-- -- = " << (a-- --) << endl;
     cout << "a = " << a << endl;


     // Should report that 1 is true
     if (Rational(1)) {
         cout << "1 is true" << endl;
     } else {
         cout << "1 is false" << endl;
     }

     // Should report that 0 is false
     if (Rational(0)) {
         cout << "0 is true" << endl;
     } else {
         cout << "0 is false" << endl;
     }

     cout << "Comparisons\n";
     Rational twoFifths(2, 5);
     Rational threeHalves(3, 2);
     Rational minusFive(-5);
     cout << twoFifths << " < " << threeHalves << " : "
          << (twoFifths < threeHalves) << endl;
     cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
     cout << threeHalves << " < " << twoFifths << " : "
          << (threeHalves < twoFifths) << endl;
     cout << threeHalves << " > " << threeHalves << " : "
          << (threeHalves > threeHalves) << endl;
     cout << threeHalves << " >= " << threeHalves << " : "
          << (threeHalves >= threeHalves) << endl;
     cout << minusFive << " >= " << threeHalves << " : "
          << (minusFive >= threeHalves) << endl;
} // main

int greatestCommonDivisor(int x, int y)
{
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
} // greatestCommonDivisor

// Any functions that are not members and not friends should have
// their definitions here...


