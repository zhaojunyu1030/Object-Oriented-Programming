/* hw06.cpp
 * Created by Junyu (Leo) Zhao on 3/9/2025
 * Operator Overloading for class BigUnsigned
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Put your BigUnsigned class definition here.
class BigUnsigned {
     // Output Operator
     friend ostream& operator<<(ostream&, const BigUnsigned&);
     // ==
     friend bool operator==(const BigUnsigned&, const BigUnsigned&);
     // <
     friend bool operator<(const BigUnsigned&, const BigUnsigned&);

public:
     // Int Operator
     BigUnsigned(int num=0) {
          if (num <= 0) {
               number.push_back(0);
          } else {
               // push in the last digit each time
               while (num != 0) {
                    number.push_back(num % 10);
                    num /= 10;
               }
          }
          removeLeadingZeros();
     }

     // String Operator
     BigUnsigned(const string& str) {
          vector<int> temp;
          // check whether the first char is digit
          if (str[0] < '0' || str[0] > '9') {
               temp.push_back(0);
          } else {
               // pass in each char in string
               // and push in every digit until the first non-digit
               for (size_t i = 0; i < str.length(); i++) {
                    if (str[i] < '0' || str[i] > '9') {
                         break;
                    }
                    temp.push_back(str[i]-'0');
               }
          }
          // push values into number reversely
          for (size_t i = temp.size(); i > 0; i--) {
               number.push_back(temp[i-1]);
          }
          removeLeadingZeros();
     }

     // +=
     BigUnsigned& operator+=(const BigUnsigned& rhs) {
          // self has more digits than rhs
          if (number.size() >= rhs.number.size()) {
               // add digit one by one
               for (size_t i = 0; i < rhs.number.size(); i++) {
                    number[i] += rhs.number[i];
               }
               // self has fewer digits than rhs
          } else {
               // add digit one by one
               for (size_t i = 0; i < number.size(); i++) {
                    number[i] += rhs.number[i];
               }
               // add additional digits in rhs to self
               for (size_t i = number.size(); i < rhs.number.size(); i++) {
                    number.push_back(rhs.number[i]);
               }
          }
          modify();
          return *this;
     }

     // ++val
     BigUnsigned& operator++() {
          number[0]++;
          modify();
          return *this;
     }

     // val++
     BigUnsigned operator++(int) {
          BigUnsigned temp = *this;
          number[0]++;
          modify();
          return temp;
     }

     // return false if number is 0
     // otherwise return true
     explicit operator bool() const {
          // check whether number only has one digit
          if (number.size() == 1) {
               // check whether the digit is 0
               if (number[0] == 0) {
                    return false;
               }
          }
          // if not, it must not be 0
          return true;
     }

private:
     vector<int> number;

     void removeLeadingZeros() {
          size_t ind = number.size()-1;
          while (number[ind] == 0 && number.size() > 1) {
               ind--;
               number.pop_back();
          }
     }

     // modify the vector if any item is greater than 9
     void modify() {
          for (size_t i = 0; i < number.size(); i++) {
               if (number[i] > 9) {
                    if (i == number.size()-1) {
                         number.push_back(1);
                    } else {
                         number[i+1] += 1;
                    }
                    number[i] -= 10;
               }
          }
     }
};

// Output Operator
ostream& operator<<(ostream& os, const BigUnsigned& rhs) {
     for (size_t i = rhs.number.size(); i > 0; i--) {
          os << rhs.number[i-1];
     } return os;
}

// ==
bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     // they are not equal if the length is not equal
     if (lhs.number.size() != rhs.number.size()) {
          return false;
     }
     // check whether each digit is equal
     for (size_t i = 0; i < lhs.number.size(); i++) {
          if (lhs.number[i] != rhs.number[i]) {
               return false;
          }
     } return true;
}

// !=
bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     return !(lhs == rhs);
}

// <
bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     // if lhs is shorter than rhs, lhs < rhs
     if (lhs.number.size() < rhs.number.size()) {
          return true;
     }
     // if lhs is longer than rhs, lhs > rhs
     if (lhs.number.size() > rhs.number.size()) {
          return false;
     }
     // if they are equal to each other, lhs == rhs
     if (lhs == rhs) {
          return false;
     }
     // compare each corresponding digit
     for (size_t i = 0; i < lhs.number.size(); i++) {
          if (lhs.number[i] > rhs.number[i]) {
               return false;
          }
     } return true;
}

// <=
bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     return lhs < rhs || lhs == rhs;
}

// >
bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     return !(lhs <= rhs);
}

// >=
bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     return !(lhs < rhs);
}

// Any functions that are not members and not friends should have
// prototypes here.

// +
BigUnsigned operator+(BigUnsigned, const BigUnsigned&);

// All non-member functions should have their definitions after main.

int main()
{
     BigUnsigned zero;
     BigUnsigned one(1);

     cout << "zero: " << zero << endl;
     cout << "one: " << one << endl;

     BigUnsigned val = 1;
     cout << "val: " << val << endl;
     cout << "++val: " << ++val << endl;
     cout << "val: " << val << endl;
     cout << "val++: " << val++ << endl;
     cout << "val: " << val << endl;

     cout << "(one + zero): " << (one + zero) << endl;
     cout << "(one + one): " <<  (one + one) << endl;

     cout << boolalpha;
     cout << "one < one: " << (one < one) << endl;
     cout << "zero < one: " << (zero < one) << endl;

     BigUnsigned a = 123;
     BigUnsigned b = 1234;
     BigUnsigned c = 124;
     BigUnsigned d = 12345;

     cout << "a: " << a << ", b: " << b
         << ", c: " << c << ", d: " << d << endl;
     cout << "a + d: " << (a + d) << endl;
     cout << "d + d: " << (d + d) << endl;
     cout << "a < d: " << (a < d) << endl;
     cout << "d < a: " << (d < a) << endl;
     cout << "zero == zero: " << (zero == zero) << endl
         << "zero == one: " << (zero == one) << endl
         << "a == a: " << (a == a) << endl
         << "a == d: " << (a == d) << endl
         << "d == a: " << (d == a) << endl;

     cout << "(zero == 0): " << (zero == 0) << endl
         << "(one == 0): " << (one == 0) << endl
         << "(1 == one): " << (1 == one) << endl;

     // +=
     cout << "b: " << b << ", c: " << c << endl;
     cout << "(c += b): " << (c += b) << endl;
     cout << "b: " << b << ", c: " << c << endl;


     BigUnsigned x = a;
     cout << "x: " << x << ", a: " << a << endl
         << "x == a: " << (x == a) << endl
         << "a == x: " << (a == x) << endl
         << "a < x: " << (a < x) << endl
         << "a > x: " << (a > x) << endl;

     cout << "x > a: " << (x > a) << endl
         << "x >= a: " << (x >= a) << endl
         << "x <= a: " << (x <= a) << endl
         << "x != a: " << (x != a) << endl;


     BigUnsigned big("987654321000");
     BigUnsigned big2("  ");
     BigUnsigned big3("felix");
     BigUnsigned big4("00987654321");

     cout << "big: " << big << endl
         << "big2: " << big2 << endl
         << "big3: " << big3 << endl
         << "big4: " << big4 << endl;

     BigUnsigned big5(98765);
     BigUnsigned big6(2457);
     cout << "big5: " << big5  << ", big6: " <<  big6 << endl
         << "(big5 + big6): " << (big5 + big6) << endl
         << "(big6 + big5): " << (big6 + big5) << endl;


     // How does this work?
     cout << zero << " is " << (zero ? "true" : "false") << endl;
     cout << one << " is " << (one ? "true" : "false") << endl;
     cout << big4 << " is " << (big4 ? "true" : "false") << endl;
} // main


// +
BigUnsigned operator+(BigUnsigned lhs, const BigUnsigned& rhs) {
     return lhs += rhs;
}
