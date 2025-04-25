#include <iostream>

using namespace std;
class Base {
public:
    Base(int num) : num(num) { }
private:
    int num;
};


class Derived : public Base {
public:
    Derived(int num) : Base(num) { }
};

int main() {
    Base base(0);
    Derived derived(1);

    Base* bptr = nullptr;
    Derived* dptr = nullptr;

    // derived = base;  // Derived-specific data may be lost
    base = derived;

    // dptr = bptr;
    bptr = dptr;

    bptr = &base;
    dptr = &derived;
    bptr = &derived;
    // dptr = &base;
}
