/* hw02.cpp
 * Created by Junyu (Leo) Zhao on 2/4/2025
 * This program aims to design a game which asks warriors to
 * battle with each other under particular rules,
 * in order to practice struct, functions, and vectors
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


// struct Warrior, stores name and strength of warriors
struct Warrior {
    string name;
    int strength;
};


// function prototypes
void openFile(ifstream& ifs);
size_t find(vector<Warrior>& warriors, const string& name);
void warrior(ifstream& ifs, vector<Warrior>& warriors);
void validBattle (Warrior& former, Warrior& later);
void battle(ifstream& ifs, vector<Warrior>& warriors);
void status(vector<Warrior>& warriors);


int main()
{
    ifstream ifs;
    openFile(ifs);

    vector<Warrior> warriors;

    string command;
    // identify all the commands in the file and do the corresponding tasks
    while (ifs >> command) {
        if (command == "Warrior") {
            warrior(ifs, warriors);
        } else if (command == "Battle") {
            battle(ifs, warriors);
        } else if (command == "Status") {
            status(warriors);
        }
    }
    ifs.close();
}


// open file and generate error if the file name is invalid
void openFile(ifstream& ifs) {
    ifs.open("warriors.txt");
    if (!ifs) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
}


// return the index of the warrior in the vector of warriors
// by inputing his name
// if there's no such a warrior in the vector
// return the size of the vector of warriors
size_t find(vector<Warrior>& warriors, const string& name) {
    // pass through all items in the vector of warriors
    // unless find the matching name
    for (int i = 0; i < warriors.size(); i++) {
        if (warriors[i].name == name) {
            return i;
        }
    } return warriors.size();
}


// if the command is Warrior,
// add a warrior by its name and strength if the name is unique
// generate an error message and continue executing following commands
// if the name isn't unique
void warrior(ifstream& ifs, vector<Warrior>& warriors) {
    string name;
    int strength;
    ifs >> name >> strength;
    if (find(warriors, name) != warriors.size()) {
        cout << "The warrior already existed" << endl;
    } else {
        warriors.push_back(Warrior(name, strength));
    }
}


// if both sides of the battle are alive,
// the strength of both sides subtracted by the value of smaller strength
// and print out corresponding message
void validBattle (Warrior& former, Warrior& later) {
    if (former.strength > later.strength) {
        former.strength -= later.strength;
        later.strength -= later.strength;
        cout << former.name << " defeats " << later.name << endl;
    } else if (former.strength < later.strength) {
        former.strength -= former.strength;
        later.strength -= former.strength;
        cout << later.name << " defeats " << former.name << endl;
    } else {
        former.strength -= former.strength;
        later.strength -= later.strength;
        cout << "Mutual Annihilation: " << former.name
        << " and " << later.name << " die at each other's hands"<< endl;
    }
}


// if the command is Battle,
// check whether both sides exist
// if exist, start a battle
// if not, generate an error message and continue executing following commands
// then,
// if both sides are alive, execute valid_battle() function
// if only one side is alive, print out corresponding message
// if neither is alive, print out corresponding message
void battle(ifvs) {
    string name1;
    string name2;
    ifs >> name1 >> name2;
    if (find(warriors, name1) == warriors.size()
        || find(warriors, name2) == warriors.size()
        || find(warriors, name1) == find(warriors, name2)) {
        cerr << "The battle is not valid" << endl;
        return;
    }
    cout << name1 << " battles " << name2 << endl;
    Warrior& former = warriors[find(warriors, name1)];
    Warrior& latter = warriors[find(warriors, name2)];
    if (former.strength > 0 && latter.strength > 0) {
        validBattle(former, latter);
    } else if (former.strength == 0 && latter.strength == 0) {
        cout << "Oh NO! They're both dead! Yuck!" << endl;
    } else {
        if (former.strength > latter.strength) {
            cout << "He's dead, " << former.name << endl;
        } else { cout << "He's dead, " << latter.name << endl; }
    }
}


// if the command is Status,
// print out the number of warriors in the vector
// and list all the warriors in a particular format
void status(vector<Warrior>& warriors) {
    cout << "There are " << warriors.size() << " warriors";
    // pass through all the warriors in the vector of warriors
    // and print in a particular format
    for (size_t i = 0; i < warriors.size(); i++) {
        cout << "\nWarrior: " << warriors[i].name << ", "
        << "Strength: " << warriors[i].strength;
    }
}


