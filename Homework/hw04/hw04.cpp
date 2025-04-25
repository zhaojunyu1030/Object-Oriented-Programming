/* hw04.cpp
 * Created by Junyu (Leo) Zhao on 2/20/2025
 * Association: Noble - Warrior
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Your Noble and Warrior classes should go here.
// ...
// class Warrior
class Warrior {
    // output operator
    friend ostream& operator<<(ostream& os, const Warrior& rhs);

public:
    // initializer
    Warrior(const string& Wname, double Wstrength) :
    name(Wname), strength(Wstrength) { }

    // getters
    bool isHired() const { return hired; }
    double getStrength() const { return strength; }
    const string& getName() const { return name; }

    // setters
    void setStrength(double val) { strength = val; }
    void hire() { hired = true; }
    void fire() { hired = false; }

private:
    string name;
    double strength;
    bool hired=false;
};


// class Noble
class Noble {
    // output operator
    friend ostream& operator<<(ostream& os, const Noble& rhs);

public:
    // initializer
    Noble(const string& Nname) : name(Nname) { }

    // setters
    bool hire(Warrior& warrior) {
        // check if the Noble is alive and the Warrior is not hired yet
        if (alive == false || warrior.isHired()) {
            cout << name << " failed to hire "
            << warrior.getName() << endl;
            return false;
        }
        strength += warrior.getStrength();
        army.push_back(&warrior);
        warrior.hire();
        return true;
    }

    bool fire(Warrior& warrior) {
        // check if the Noble is alive and the Warrior is in the army
        size_t ind = find(warrior);
        if (alive == false || !warrior.isHired() || ind == army.size()) {
            cout << name << " failed to fire "
            << warrior.getName() << endl;
            return false;
        }
        // remove the warrior from army and adjust Noble strength
        strength -= army[ind]->getStrength();
        army[ind]->fire();
        for (size_t j = ind; j < army.size()-1; j++) {
            army[j] = army[j+1];
        }
        army.pop_back();
        cout << warrior.getName() << ", you don't work for me any more! -- "
        << name << endl;
        return true;
    }

    void battle(Noble& another) {
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

private:
    string name;
    double strength=0;
    vector<Warrior*> army;
    bool alive=true;

    // helpers
    size_t find(Warrior& warrior) {
        for (size_t i = 0; i < army.size(); i++) {
            if (&warrior == army[i]) {
                return i;
            }
        } return army.size();
    }

    void setWinnerStrength(double ratio) {
        strength = 0;
        // reduce strength of each warrior in the army
        // and set new strength for the Noble
        for (Warrior* ptr : army) {
            ptr->setStrength(ptr->getStrength()
                -ptr->getStrength()*ratio);
            strength += ptr->getStrength();
        }
    }

    void setLoserStrength() {
        strength = 0;
        alive = false;
        // reduce strength of each warrior in the army
        for (const Warrior* ptr : army) {
            ptr->setStrength(0);
        }
    }

    void validBattle(Noble& another) {
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
};


// output operator for Warrior
ostream& operator<<(ostream& os, const Warrior& rhs) {
    os << rhs.name << ": " << rhs.strength;
    return os;
}

// output operator for Noble
ostream& operator<<(ostream& os, const Noble& rhs) {
    os << rhs.name << " has an army of " << rhs.army.size();
    for (Warrior* ptr : rhs.army) {
        os << "\n\t" << *ptr;
    }
    return os;
}


int main()
{

    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);

    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";

    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

} // main
