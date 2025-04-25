/*
  rec10.cpp
  Created by Junyu (Leo) Zhao on 4/4/2025
 */

#include <iostream>
#include <vector>
using namespace std;


class Instrument {
    friend ostream& operator<<(ostream& os, const Instrument& rhs) {
        rhs.print(os);
        return os;
    }
public:
    Instrument() { }

    virtual void makeSound() const = 0;

    virtual void print(ostream& os) const = 0;

    virtual void play() = 0;
};

void Instrument::makeSound() const {
    cout << "To make a sound... ";
}


// Brass
class Brass : public Instrument {
public:
    Brass(unsigned size) : size(size) { }

    void makeSound() const override {
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size "
        << size << endl;
    }

    unsigned getSize() const { return size; }


private:
    unsigned size;  // big: 12, med: 9, small: 4
};


class Trumpet : public Brass {
public:
    Trumpet(unsigned size) : Brass(size) { }

    void print(ostream& os) const override {
        os << "\n\t" << "Trumpet: " << this->getSize();
    }

    void play() override { cout << "Toot"; }
};


class Trombone : public Brass {
public:
    Trombone(unsigned size) : Brass(size) { }

    void print(ostream& os) const override {
        os << "\n\t" << "Trombone: " << this->getSize();
    }

    void play() override { cout << "Blat"; }
};


// String
class String : public Instrument {
public:
    String(unsigned pitch) : pitch(pitch) { }

    void makeSound() const override {
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }

    unsigned getPitch() const { return pitch; }

private:
    unsigned pitch;
};


class Violin : public String {
public:
    Violin(unsigned pitch) : String(pitch) { }

    void print(ostream& os) const override {
        os << "\n\t" << "Violin: " << this->getPitch();
    }

    void play() override { cout << "Screech"; }
};


class Cello : public String {
public:
    Cello(unsigned pitch) : String(pitch) { }

    void print(ostream& os) const override {
        os << "\n\t" << "Cello: " << this->getPitch();
    }

    void play() override { cout << "Squawk"; }
};


// Percussion
class Percussion : public Instrument {
public:
    Percussion() { }

    void makeSound() const override {
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
};


class Drum : public Percussion {
public:
    Drum() { }

    void print(ostream& os) const override { os << "\n\t" << "Drum"; }

    void play() override { cout << "Boom"; }
};


class Cymbal : public Percussion {
public:
    Cymbal() { }

    void print(ostream& os) const override { os << "\n\t" << "Cymbal"; }

    void play() override { cout << "Crash"; }
};


// MILL
class MILL {
    friend ostream& operator<<(ostream& os, const MILL& rhs) {
        int count = 0;
        os << "The MILL has the following instruments: ";
        for (const Instrument* instr : rhs.instruments) {
            if (instr != nullptr) {
                cout << *instr;
                count++;
            }
        }
        if (count == 0) {
            os << "None";
        }
        return os;
    }
public:
    MILL() {}

    void receiveInstr(Instrument& instrument) {
        instrument.makeSound();
        bool returned = false;
        for (size_t i = 0; i < instruments.size(); i++) {
            if (instruments[i] == nullptr) {
                instruments[i] = &instrument;
                returned = true;
                break;
            }
        }

        if (!returned) { instruments.push_back(&instrument); }
    }

    Instrument* loanOut() {
        Instrument* loan = nullptr;
        for (Instrument*& instr : instruments) {
            if (instr != nullptr) {
                loan = instr;
                instr = nullptr;
                break;
            }
        } return loan;
    }

    void dailyTestPlay() const {
        for (Instrument* instr: instruments) {
            if (instr != nullptr) {
                instr->makeSound();
            }
        }
    }

private:
    vector<Instrument*> instruments={};
};


//
// Musician class as provided to the students. Requires an Instrument class.
//
class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << name << " has no instr\n";
    }

    // play: play the instrument

    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};


class Orch {
public:
    Orch() { }

    bool addPlayer(Musician& mus) {
        for (const Musician* mptr : musicians) {
            if (mptr == &mus) {
                return false;
            }
        }
        musicians.push_back(&mus);
        return true;
    }

    void play() const {
        for (Musician* mptr : musicians) {
            mptr->play();
        } cout << endl;
    }

private:
    vector<Musician*> musicians;
};


int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";

    cout << "Daily test ----------------------------------------------------\n"
	 << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

    cout << "Define some Musicians------------------------------------------\n";
    Musician harpo("Harpo");
    Musician groucho("Groucho");

    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	 // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

     groucho.testPlay();
     mill.receiveInstr(*groucho.giveBackInstr());
     harpo.acceptInstr(mill.loanOut());
     groucho.acceptInstr(mill.loanOut());
     groucho.testPlay();
     harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL at the end of Part One:\n";
    cout << mill << endl;

    //
    // PART TWO
    //
    cout << "\nP A R T  T W O\n";
    //
    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;
}

