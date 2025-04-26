#include "Noble.h"
#include "Protector.h"

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

namespace WarriorCraft {
    // Protector
    // Initializer
    Protector::Protector(const string& name, double strength) :
        name(name), strength(strength) { }

    // getters
    const string& Protector::getName() const { return name; }
    double Protector::getStrength() const { return strength; }
    bool Protector::isHired() const { return hired; }
    const string &Protector::getBossName() const { return boss->getName(); }

    // setters
    void Protector::setStrength(double val) { strength = val; }

    void Protector::hiredBy(Lord* nobptr) {
        boss = nobptr;
        hired = true;
    }

    void Protector::fired() {
        boss = nullptr;
        hired = false;
    }

    // output methods
    /// display()

    // other methods
    bool Protector::runaway() {
        if (strength > 0 && boss != nullptr) {
            boss->runaway(*this);
            return true;
        }
        return false;
    }

    // output operator
    ostream& operator<<(ostream& os, const Protector& rhs) {
        cout << rhs.name << " has strength " << rhs.strength;
        return os;
    }


    // Wizard
    // Initializer
    Wizard::Wizard(const string& name, double strength) :
    Protector(name, strength) { }

    // output method
    void Wizard::display() const {
        cout << "POOF!" << endl;
    }


    // Warrior
    // Initializer
    Warrior::Warrior(const string& name, double strength) :
    Protector(name, strength) { }


    // Archer
    // Initializer
    Archer::Archer(const string& name, double strength) :
    Warrior(name, strength) { }

    // output method
    void Archer::display() const {
        cout << "TWANG! " << getName()
        << " says: Take that in the name of my lord, " << getBossName() << endl;
    }


    // Swordsman
    // Initializer
    Swordsman::Swordsman(const string& name, double strength) :
    Warrior(name, strength) { }

    // output method
    void Swordsman::display() const {
        cout << "CLANG! " << getName()
        << " says: Take that in the name of my lord, " << getBossName() << endl;
    }

}