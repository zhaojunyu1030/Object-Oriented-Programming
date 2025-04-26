#include "Noble.h"
#include "Protector.h"

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

namespace WarriorCraft {
    // Noble
    // Initializer
    Noble::Noble(const string& name) : name(name) { }

    // getters
    const string& Noble::getName() const { return name; }
    bool Noble::isAlive() const { return alive; }
    /// getStrength()

    // setters
    void Noble::beenKilled() { alive = false; }
    /// setWinnerStrength(double)
    /// setLoserStrength()

    // output methods
    /// display()
    /// print()

    // other methods
    void Noble::battle(Noble& another) {
        cout << getName() << " battles " << another.getName() << endl;
        // check who is still alive
        if (alive && another.alive) {
            this->display();  // only call alive Noble's display() method
            another.display();
            validBattle(another);
        } else if (!alive && !another.alive) {
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        } else if (!alive) {
            another.display();
            cout << "He's dead, " << another.name << endl;
        } else {
            this->display();
            cout << "He's dead, " << name << endl;
        }
    }

    // helper
    void Noble::validBattle(Noble& another) {
        // check who has more strength
        if (getStrength() > another.getStrength()) {
            // modify the winner's strength
            setWinnerStrength(another.getStrength() / getStrength());
            // set the loser to be dead
            another.setLoserStrength();
            cout << name << " defeats "
                << another.name << endl;
        } else if (getStrength() < another.getStrength()) {
            another.setWinnerStrength(getStrength() / another.getStrength());
            setLoserStrength();
            cout << another.name << " defeats "
                << name << endl;
        } else if (getStrength() == another.getStrength()) {
            // they are both dead
            setLoserStrength();
            another.setLoserStrength();
            cout << "Mutual Annihilation: " << name << " and "
                << another.name << " die at each other's hands" << endl;
        }
    }

    // output operator
    ostream& operator<<(ostream& os, const Noble& rhs) {
        rhs.print(os);
        return os;
    }


    // Lord
    // Initializer
    Lord::Lord(const string& name) : Noble(name) { }

    // getter
    double Lord::getStrength() const {
        double strength = 0;
        for (const Protector* proptr : army) {
            strength += proptr->getStrength();
        } return strength;
    }

    // setters
    bool Lord::hires(Protector& protector) {
        if (!isAlive() || protector.isHired()) {
            cout << getName() << " failed to hire "
                << protector.getName() << endl;
            return false;
        }
        army.push_back(&protector);
        protector.hiredBy(this);
        return true;
    }

    bool Lord::fires(Protector& protector) {
        size_t ind = find(protector);
        if (isAlive() == false || !protector.isHired() || ind == army.size()) {
            cout << getName() << " failed to fire "
                << protector.getName() << endl;
            return false;
        }
        protector.fired();
        removeProtector(ind);
        cout << protector.getName() << ", you don't work for me any more! -- "
            << getName() << '.' << endl;
        return true;
    }

    void Lord::setWinnerStrength(double ratio) {
        for (Protector* proptr : army) {
            proptr->setStrength(proptr->getStrength()
                - proptr->getStrength() * ratio);
        }
    }

    void Lord::setLoserStrength() {
        beenKilled();
        for (Protector* protr : army) {
            protr->setStrength(0);
        }
    }

    // output methods
    void Lord::display() const {
        for (const Protector* proptr : army) {
            proptr->display();
        }
    }

    void Lord::print(ostream& os) const {
        cout << getName() << " has an army of size: " << army.size();
        for (const Protector* proptr : army) {
            cout << "\n\t" << *proptr;
        }
    }

    // other methods
    bool Lord::runaway(Protector& protector) {
        size_t ind = find(protector);
        if (ind == army.size()) {
            return false;
        }
        cout << protector.getName() << " flees in terror, abandoning his lord, "
                << getName() << endl;
        removeProtector(ind);
        return true;
    }

    // helpers
    size_t Lord::find(const Protector& target) {
        for (size_t i = 0; i < army.size(); i++) {
            if (&target == army[i]) {
                return i;
            }
        } return army.size();
    }

    void Lord::removeProtector(size_t ind) {
        army[ind]->fired();
        for (size_t j = ind; j < army.size()-1; j++) {
            army[j] = army[j+1];
        }
        army.pop_back();
    }


    // PersonWithStrengthToFight
    // Initializer
    PersonWithStrengthToFight::PersonWithStrengthToFight
    (const string& name, double strength) : Noble(name), strength(strength) { }

    // getter
    double PersonWithStrengthToFight::getStrength() const { return strength; }

    // setters
    void PersonWithStrengthToFight::setWinnerStrength(double ratio) {
        strength *= 1 - ratio;
    }

    void PersonWithStrengthToFight::setLoserStrength() {
        beenKilled();
        strength = 0;
    }

    // output methods
    void PersonWithStrengthToFight::display() const {
        cout << "Ugh!" << endl;
    }

    void PersonWithStrengthToFight::print(ostream& os) const {
        cout << getName() << " has strength: " << getStrength();
    }
}