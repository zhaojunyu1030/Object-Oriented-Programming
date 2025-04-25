//
//
// hw05.cpp - aims to practice dynamic memory
// Created by Zhao Junyu on 2/23/25
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


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
    
    // getters
    const string getName() const { return name; }

    // setters
    bool hire(Warrior& warrior) {
        // check if the Noble is alive and the Warrior is not hired yet
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
        // remove warrior from army
        removeWarrior(ind);
        cout << warrior.getName() << ", you don't work for me any more! -- "
            << name << '.' << endl;
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
    size_t find(const Warrior& warrior) {
        // if warrior is in army, return the index
        // otherwise, return the size of army
        for (size_t i = 0; i < army.size(); i++) {
            if (&warrior == army[i]) {
                return i;
            }
        } return army.size();
    }
    
    void removeWarrior(size_t ind) {
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

    void setWinnerStrength(double ratio) {
        strength = 0;
        // reduce strength of each warrior in the army
        // and set new strength for the Noble
        for (Warrior* ptr : army) {
            ptr->setStrength(ptr->getStrength() - ptr->getStrength() * ratio);
            strength += ptr->getStrength();
        }
    }

    void setLoserStrength() {
        strength = 0;
        alive = false;
        // reduce strength of each warrior in the army to 0
        for (Warrior* ptr : army) {
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
    os << '\t' << rhs.name << ": " << rhs.strength;
    return os;
}

// output operator for Noble
ostream& operator<<(ostream& os, const Noble& rhs) {
    os << rhs.name << " has an army of " << rhs.army.size();
    for (const Warrior* ptr : rhs.army) {
        os << "\n" << *ptr;
    }
    return os;
}


// function prototypes
size_t nfind(const string& name, const vector<Noble*>& nobles);
size_t wfind(const string& name, const vector<Warrior*>& warriors);


// main()
int main() {
    // open file
    ifstream ifs;
    ifs.open("nobleWarriors.txt");

    // check if the file opened successfully
    if (!ifs) {
        cerr << "Failed to open file." << endl;
        exit(1);
    }

    string command;
    vector<Noble*> nobles;
    vector<Warrior*> warriors;
    // identify all the commands in the file
    while (ifs >> command) {
        if (command == "Noble") {
            string name;
            ifs >> name;
            // check if the noble with the same name doesn't exist
            if (nfind(name, nobles) == nobles.size()) {
                // set up a noble on heap and push it into nobles
                nobles.push_back(new Noble(name));
            } else {
                cout << "Noble already exists." << endl;
            }

        } else if (command == "Warrior") {
            string name;
            int strength;
            ifs >> name >> strength;
            // check if the warrior with the same name doesn't exist
            if (wfind(name, warriors) == warriors.size()) {
                // set up a warrior on heap and push it into warriors
                warriors.push_back(new Warrior(name, strength));
            } else {
                cout << "Warrior already exists." << endl;
            }

        } else if (command == "Hire") {
            string noble;
            string warrior;
            ifs >> noble >> warrior;
            // find the index of noble in nobles
            size_t nind = nfind(noble, nobles);
            // find the index of warrior in warriors
            size_t wind = wfind(warrior, warriors);
            // check if the noble and the warrior exist already
            if (nind < nobles.size() && wind < warriors.size()) {
                // call noble's method hire()
                nobles[nind]->hire(*warriors[wind]);
            } else {
                // check which one or both not exist
                if (nind == nobles.size()) {
                    cout << "Attempting to hire by unknown noble: "
                        << noble << endl;
                }
                if (wind == warriors.size()) {
                    cout << "Attempting to hire using unknown warrior: "
                        << warrior << endl;
                }
            }

        } else if (command == "Fire") {
            string noble;
            string warrior;
            ifs >> noble >> warrior;
            // find the index of noble in nobles
            size_t nind = nfind(noble, nobles);
            // find the index of warrior in warriors
            size_t wind = wfind(warrior, warriors);
            // check if the noble and the warrior exist already
            if (nind < nobles.size() && wind < warriors.size()) {
                // call noble's method fire()
                nobles[nind]->fire(*warriors[wind]);
            } else {
                // check which one or both not exist
                if (nind == nobles.size()) {
                    cout << "Attempting to fire by unknown noble: "
                        << noble << endl;
                }
                if (wind == warriors.size()) {
                    cout << "Attempting to fire using unknown warrior: "
                        << warrior << endl;
                }
            }

        } else if (command == "Battle") {
            string former;
            string latter;
            ifs >> former >> latter;
            // find the index of former noble
            size_t ind1 = nfind(former, nobles);
            // find the index of latter noble
            size_t ind2 = nfind(latter, nobles);
            // check if both sides of the battle exist
            if (ind1 < nobles.size() && ind2 < nobles.size()) {
                // call former noble's method battle() with latter noble
                nobles[ind1]->battle(*nobles[ind2]);
            } else {
                // check which one or both not exist
                if (ind1 == nobles.size()) {
                    cout << "Attempting to battle by unknown noble: "
                        << former << endl;
                }
                if (ind2 == nobles.size()) {
                    cout << "Attempting to battle by unknown noble: "
                        << latter << endl;
                }
            }

        } else if (command == "Status") {
            cout << "Status\n" << "======\n" << "Nobles:" << endl;
            // check if there has nobles in the vector
            if (nobles.size() == 0) {
                cout << "NONE" << endl;
            }
            // print out all nobles in the vector
            for (Noble* nptr : nobles) {
                cout << *nptr << endl;
            }
            cout << "Unemployed Warriors: " << endl;
            int wcount = 0;
            // print out all unemployed warriors
            for (Warrior* wptr : warriors) {
                if (!wptr->isHired()) {
                    wcount++;
                    cout << *wptr << endl;
                }
            }
            // check if there has no unemployed warrior in the vector
            if (wcount == 0) {
                cout << "NONE" << endl;
            }

        } else if (command == "Clear") {
            // release all the memory on heap
            // and delete all the pointers in nobles
            for (size_t i = nobles.size(); i > 0; i--) {
                delete nobles[i-1];
                nobles.pop_back();
            }
            // release all the memory on heap
            // and delete all the pointers in the warriors
            for (size_t i = warriors.size(); i > 0; i--) {
                delete warriors[i-1];
                warriors.pop_back();
            }
        }
    }
    
    // close the file
    ifs.close();

    // in case no command "Clear" in the file
    for (size_t i = nobles.size(); i > 0; i--) {
        delete nobles[i-1];
        nobles.pop_back();
    }
    for (size_t i = warriors.size(); i > 0; i--) {
        delete warriors[i-1];
        warriors.pop_back();
    }
}


// functions
// if name is the name of a noble in nobles,
// return the index of the noble
// otherwise, return the size of nobles
size_t nfind(const string& name, const vector<Noble*>&  nobles) {
    for (size_t i = 0; i < nobles.size(); i++) {
        if (nobles[i]->getName() == name) {
            return i;
        }
    } return nobles.size();
}


// if name is the name of a warrior in warriors,
// return the index of the warrior
// otherwise, return the size of warriors
size_t wfind(const string& name, const vector<Warrior*>& warriors) {
    for (size_t i = 0; i < warriors.size(); i++) {
        if (warriors[i]->getName() == name) {
            return i;
        }
    } return warriors.size();
}
