#ifndef PROTECTOR_H
#define PROTECTOR_H

#include "Protector.h"

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

namespace WarriorCraft {

    class Lord;


    // Protector
    class Protector {
        // output operator
        friend ostream& operator<<(ostream&, const Protector&);

    public:
        // Initializer
        Protector(const string&, double);

        // getters
        const string& getName() const;
        double getStrength() const;
        bool isHired() const;
        const string& getBossName() const;

        // setters
        void setStrength(double);
        void hiredBy(Lord*);
        void fired();

        // output methods
        virtual void display() const = 0;

        // other methods
        bool runaway();

    private:
        string name;
        double strength;
        bool hired=false;
        Lord* boss=nullptr;
    };


    // Wizard
    class Wizard : public Protector {
    public:
        // Initializer
        Wizard(const string&, double);

        // output methods
        void display() const override;
    };


    // Warrior
    class Warrior : public Protector {
    public:
        // Initializer
        Warrior(const string&, double);
    };

    // Archer
    class Archer : public Warrior {
    public:
        // Initializer
        Archer(const string&, double);

        // output method
        void display() const override;
    };


    // Swordsman
    class Swordsman : public Warrior {
    public:
        // Initializer
        Swordsman(const string&, double);

        // output method
        void display() const override;
    };
}

#endif //PROTECTOR_H
