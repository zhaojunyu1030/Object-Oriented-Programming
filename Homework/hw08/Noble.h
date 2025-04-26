#ifndef NOBLE_H
#define NOBLE_H

#include "Noble.h"
#include "Protector.h"

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

namespace WarriorCraft {

    class Protector;


    // Noble
    class Noble {
        friend ostream& operator<<(ostream&, const Noble&);
    public:
        // Initializer
        Noble(const string&);

        // getters
        const string& getName() const;
        bool isAlive() const;
        virtual double getStrength() const = 0;

        // setters
        void beenKilled();
        virtual void setWinnerStrength(double) = 0;
        virtual void setLoserStrength() = 0;

        // output methods
        virtual void display() const = 0;
        virtual void print(ostream&) const = 0;

        // other methods
        void battle(Noble&);

    private:
        string name;
        bool alive=true;

        // helper
        void validBattle(Noble&);
    };


    // Lord
    class Lord : public Noble {
    public:
        // Initializer
        Lord(const string&);

        // getter
        double getStrength() const override;

        // setters
        bool hires(Protector&);
        bool fires(Protector&);
        void setWinnerStrength(double) override;
        void setLoserStrength() override;

        // output methods
        void display() const override;
        void print(ostream&) const override;

        // other methods
        bool runaway(Protector&);

    private:
        vector<Protector*> army;

        // helpers
        size_t find(const Protector&);
        void removeProtector(size_t);
    };


    // PersonWithStrengthToFight
    class PersonWithStrengthToFight : public Noble {
    public:
        // Initializer
        PersonWithStrengthToFight(const string&, double);

        // getter
        double getStrength() const override;

        // setters
        void setWinnerStrength(double) override;
        void setLoserStrength() override;

        // output methods
        void display() const override;
        void print(ostream&) const override;

    private:
        double strength;
    };
}

#endif //NOBLE_H
