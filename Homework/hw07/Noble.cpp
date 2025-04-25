/* Junyu (Leo) Zhao
 * Noble.cpp
 */


#include "Noble.h"
#include "Warrior.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;


namespace WarriorCraft {
    Noble::Noble(const string& name) : name(name) { }

    const string& Noble::getName() const { return name; }

    bool Noble::hire(Warrior& warrior) {
        if (alive == false || warrior.isHired()) {
            cout << name << " failed to hire "
                << warrior.getName() << endl;
            return false;
        }
        // add warrior's strength to noble's
        strength += warrior.getStrength();
        // add warrior into army
        army.push_back(&warrior);
        // mark warrior as employed
        warrior.hire(this);
        return true;
    }

    bool Noble::fire(Warrior& warrior) {
        // check if the Noble is alive and the Warrior is in the army
        size_t ind = find(warrior);
        if (alive == false || !warrior.isHired() || ind == army.size()) {
            cout << name << " failed to fire "
                << warrior.getName() << endl;
            return false;
        }
        warrior.fire();
        // remove warrior from army
        removeWarrior(ind);
        cout << warrior.getName() << ", you don't work for me any more! -- "
            << name << '.' << endl;
        return true;
    }

    void Noble::battle(Noble& another) {
        cout << name << " battles " << another.name << endl;
        // check if both sides are alive
        if (alive == true && another.alive == true) {
            validBattle(another);
        } else if (alive == false && another.alive == false) {
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        } else if (alive == false) {
            cout << "He's dead, " << another.name << endl;
        } else {
            cout << "He's dead, " << name << endl;
        }
    }

    bool Noble::runaway(Warrior& warrior) {
        size_t ind = find(warrior);
        if (ind == army.size()) {
            return false;
        }
        cout << warrior.getName() << " flees in terror, abandoning his lord, "
                << name << endl;
        removeWarrior(ind);
        return true;
    }

    ostream& operator<<(ostream& os, const Noble& rhs) {
        os << rhs.name << " has an army of " << rhs.army.size();
        for (const Warrior* ptr : rhs.army) {
            os << "\n" << *ptr;
        }
        return os;
    }

    size_t Noble::find(const Warrior& warrior) {
        for (size_t i = 0; i < army.size(); i++) {
            if (&warrior == army[i]) {
                return i;
            }
        } return army.size();
    }

    void Noble::removeWarrior(size_t ind) {
        // substract noble's strength by warrior's strength
        strength -= army[ind]->getStrength();
        // set warrior as unemployed
        army[ind]->fire();
        // put the pointer of warrior to the end of army
        for (size_t j = ind; j < army.size()-1; j++) {
            army[j] = army[j+1];
        }
        // pop back the pointer in army
        army.pop_back();
    }

    void Noble::setWinnerStrength(double ratio) {
        strength = 0;
        // reduce strength of each warrior in the army
        // and set new strength for the Noble
        for (Warrior* ptr : army) {
            ptr->setStrength(ptr->getStrength() - ptr->getStrength() * ratio);
            strength += ptr->getStrength();
        }
    }

    void Noble::setLoserStrength() {
        strength = 0;
        alive = false;
        // reduce strength of each warrior in the army to 0
        for (Warrior* ptr : army) {
            ptr->setStrength(0);
        }
    }

    void Noble::validBattle(Noble& another) {
        // check which side has larger strength
        if (strength > another.strength) {
            setWinnerStrength(another.strength / strength);
            another.setLoserStrength();
            cout << name << " defeats "
                << another.name << endl;
        } else if (strength < another.strength) {
            another.setWinnerStrength(strength / another.strength);
            setLoserStrength();
            cout << another.name << " defeats "
                << name << endl;
        } else if (strength == another.strength) {
            setLoserStrength();
            another.setLoserStrength();
            cout << "Mutual Annihilation: " << name << " and "
                << another.name << " die at each other's hands" << endl;
        }
    }
}