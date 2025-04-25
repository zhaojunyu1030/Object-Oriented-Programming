/* hw07_single.cpp
 * Created by Junyu (Leo) Zhao on 3/23/2025
 */

// Comment out these two includes for the single file solution
//#include "Noble.h"
//#include "Warrior.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Comment out this "using namespace" for the single file solution
//using namespace WarriorCraft;


class Noble;


// class Warrior
class Warrior {
    friend ostream& operator<<(ostream&, const Warrior&);

public:
    Warrior(const string&, double);

    bool isHired() const;
    double getStrength() const;
    const string& getName() const;

    void setStrength(double);
    void hire(Noble*);
    void fire();
    bool runaway();

private:
    string name;
    double strength;
    bool hired=false;
    Noble* boss=nullptr;
};


// class Noble
class Noble {
    friend ostream& operator<<(ostream&, const Noble&);

public:
    Noble(const string& name);

    const string& getName() const;

    bool hire(Warrior&);
    bool fire(Warrior&);
    void battle(Noble&);
    bool runaway(Warrior&);

private:
    string name;
    double strength=0;
    vector<Warrior*> army;
    bool alive=true;

    size_t find(const Warrior&);
    void removeWarrior(size_t);
    void setWinnerStrength(double);
    void setLoserStrength();
    void validBattle(Noble&);
};


int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
     << lance << endl
     << jim << endl
     << linus << endl
     << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
     << lance << endl
     << jim << endl
     << linus << endl
     << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
     << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
     << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}


// Warrior function definitions
Warrior::Warrior(const string& name, double strength) :
    name(name), strength(strength) { }

// getters
bool Warrior::isHired() const { return hired; }
double Warrior::getStrength() const { return strength; }
const string& Warrior::getName() const { return name; }

// setters
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
    // check whether the warrior is alive
    // and he has been hired by a Noble
    if (strength > 0 && boss != nullptr) {
        // notify the Noble
        boss->runaway(*this);
        return true;
    }
    return false;
}

// Warrior output operator
ostream& operator<<(ostream& os, const Warrior& rhs) {
    os << '\t' << rhs.name << ": " << rhs.strength;
    return os;
}


// Noble function definitions
Noble::Noble(const string& name) : name(name) { }

// getters
const string& Noble::getName() const { return name; }

// setters
bool Noble::hire(Warrior& warrior) {
    // check whether the Noble is dead
    // or the warrior has been hired by the other noble
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

// Noble output operator
ostream& operator<<(ostream& os, const Noble& rhs) {
    os << rhs.name << " has an army of " << rhs.army.size();
    for (const Warrior* ptr : rhs.army) {
        os << "\n" << *ptr;
    }
    return os;
}


// helpers
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
