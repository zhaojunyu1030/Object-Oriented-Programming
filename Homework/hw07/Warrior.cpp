/* Junyu (Leo) Zhao
 * Warrior.cpp
 */


#include "Noble.h"
#include "Warrior.h"

#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft {
    Warrior::Warrior(const string& name, double strength) :
    name(name), strength(strength) { }

    bool Warrior::isHired() const { return hired; }

    double Warrior::getStrength() const { return strength; }

    const string& Warrior::getName() const { return name; }

    void Warrior::setStrength(double val) { strength = val; }

    void Warrior::hire(Noble* nptr) {
        boss = nptr;
        hired = true;
    }

    void Warrior::fire() {
        boss = nullptr;
        hired = false;
    }

    bool Warrior::runaway() {
        if (strength > 0 && boss != nullptr) {
            boss->runaway(*this);
            return true;
        }
        return false;
    }

    ostream& operator<<(ostream& os, const Warrior& rhs) {
        os << '\t' << rhs.name << ": " << rhs.strength;
        return os;
    }
}