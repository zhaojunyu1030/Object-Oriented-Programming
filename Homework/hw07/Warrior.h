#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft {
     class Noble;

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
}

#endif //WARRIOR_H
