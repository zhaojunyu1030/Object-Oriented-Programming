#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace WarriorCraft {

    class Warrior;

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
}

#endif //NOBLE_H
