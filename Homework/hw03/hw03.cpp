/* hw03.cpp
 * Created by Junyu (Leo) Zhao on 2/11/2025
 * This program aims to design a battle game
 * to practice data hiding, encapsulation, delegation,
 * and overloading the output operator
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


// Warrior contains a name and a weapon in its private field
// in public field, Warrior has:
//      output operator;
//      getName(): return the name of the warrior
//      getStrength(): asks the weapon to get the strength value
//      setStrength(int newStrength): asks the weapon to modify
//          the strength value into newStrength
// Weapon contains a name and a strength in its private field
// in public field, Warrior has:
//      output operator;
//      getName(): return the name of the weapon
//      getStrength(): return the strength value
//      setStrength(int newStrength): modify the strength value
//          into newStrength
class Warrior {
    class Weapon {
        friend ostream& operator<<(ostream& os, const Weapon& rhs);

    public:
        Weapon(const string& weaponName, int strength) :
        weaponName(weaponName), strength(strength) {}

        const string& getName() const { return weaponName; }
        int getStrength() const { return strength; }
        void setStrength(int newStrength) { strength = newStrength; }

    private:
        string weaponName;
        int strength;
    };

    friend ostream& operator<<(ostream& os, const Warrior& rhs);
    friend ostream& operator<<(ostream& os, const Warrior::Weapon& rhs);

public:
    Warrior(const string& warriorName, const string& weaponName, int strength)
    : warriorName(warriorName), weapon(Weapon(weaponName, strength)) {}

    const string& getName() const { return warriorName; }
    int getStrength() const { return weapon.getStrength(); }
    void setStrength(int newStrength) { weapon.setStrength(newStrength); }

    void battleWith(Warrior& another) {
        if (this->getStrength() > 0 && another.getStrength() > 0) {
            if (this->getStrength() > another.getStrength()) {
                this->setStrength(this->getStrength() - another.getStrength());
                another.setStrength(0);
                cout << this->getName() << " defeats "
                    << another.getName() << endl;
            } else if (this->getStrength() < another.getStrength()) {
                another.setStrength(another.getStrength() - this->getStrength());
                this->setStrength(0);
                cout << another.getName() << " defeats "
                    << this->getName() << endl;
            } else {
                this->setStrength(0);
                another.setStrength(0);
                cout << "Mutual Annihilation: " << this->getName() << " and "
                    << another.getName() << " die at each other's hands" << endl;
            }
        } else if (this->getStrength() == 0 && another.getStrength() == 0) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (this->getStrength() == 0) {
            cout << "He's dead, " << another.getName() << endl;
        } else {
            cout << "He's dead, " << this->getName() << endl;
        }
    }

private:
    string warriorName;
    Weapon weapon;
};


// output operators
ostream& operator<<(ostream& os, const Warrior::Weapon& rhs) {
    os << "Weapon: " << rhs.weaponName << ", " << rhs.strength;
    return os;
}

ostream& operator<<(ostream& os, const Warrior& rhs) {
    os << "Warrior: " << rhs.warriorName << ", " << rhs.weapon;
    return os;
}


// function prototypes
void displayStatus(const vector<Warrior>& warriors);
size_t find(const string& name, const vector<Warrior>& warriors);
void createWarrior(ifstream& ifs, vector<Warrior>& warriors);


// main()
int main()
{
    // open the file
    ifstream ifs;
    ifs.open("warriors.txt");
    // check if the file is successfully opened
    if (!ifs) { cerr << "File not exist"; exit(1); }
    // read the file
    vector<Warrior> warriors;
    string command;
    // identify the command and do the corresponding work according to
    // the following words in the same line
    // then go to the next line and so the same thing until
    // all the lines in the file are read and executed
    while (ifs >> command) {
        if (command == "Warrior") {
            createWarrior(ifs, warriors);
        } else if (command == "Status") {
            displayStatus(warriors);
        } else if (command == "Battle") {
            string name1;
            string name2;
            ifs >> name1 >> name2;
            size_t ind1 = find(name1, warriors);
            size_t ind2 = find(name2, warriors);
            if (ind1 < warriors.size() && ind2 < warriors.size()) {
                warriors[ind1].battleWith(warriors[ind2]);
            } else {
                if (ind1 == warriors.size()) {
                    cout << "Warrior " << name1 << " does not exist" << endl;
                }
                if (ind2 == warriors.size()) {
                    cout << "Warrior " << name2 << " does not exist" << endl;
                }
            }
        }
    }
    // close the file
    ifs.close();
}


// if the command is "Status,"
// display all the warriors by a specific format
void displayStatus(const vector<Warrior>& warriors) {
    cout << "There are " << warriors.size() << " warriors" << endl;
    // display all the warriors in vector warriors by a specific format
    for (const Warrior& warrior : warriors) {
        cout << warrior << endl;
    }
}


// return the index of the warrior in vector warriors according to its name
// return the size of warriors if there's no warrior has the target name
size_t find(const string& name, const vector<Warrior>& warriors) {
    // check if there is already a warrior named by name
    for (size_t i = 0; i < warriors.size(); i++) {
        if (warriors[i].getName() == name) {
            return i;
        }
    } return warriors.size();
}


// if the command is "Warrior,"
// create a warrior according to a specific format
// and push it into vector warriors
// generate an error message if a warrior occupied the warrior's name
// and continue reading the file
void createWarrior(ifstream& ifs, vector<Warrior>& warriors) {
    string warriorName;
    string weaponName;
    int strength;
    ifs >> warriorName >> weaponName >> strength;
    if (find(warriorName, warriors) < warriors.size()) {
        cout << "The warrior existed" << endl;
    } else {
        warriors.emplace_back(warriorName, weaponName, strength);
    }
}
