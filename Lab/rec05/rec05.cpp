/*
  rec05.cpp
  Created by Junyu (Leo) Zhao on 2/21/2025
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;


// Section Class
class Section {
    // StudentRecord Class
    class StudentRecord {
        friend ostream& operator<<(ostream& os, const Section::StudentRecord& rhs);
    public:
        StudentRecord(const string& stuName) : name(stuName), grades(14, -1) { }

        const string& getName() const { return name; }

        void setGrade(size_t ind, int newVal) { grades[ind] = newVal; }

    private:
        string name;
        vector<int> grades;
    };

    // Time class
    class Time {
        friend ostream& operator<<(ostream& os, const Section::Time& rhs);
    public:
        Time(const string& day, unsigned hour) : day(day), hour(hour) { }

    private:
        string day;
        unsigned hour;
    };

    friend ostream& operator<<(ostream& os, const Section& rhs);
    friend ostream& operator<<(ostream& os, const Section::Time& rhs);
    friend ostream& operator<<(ostream& os, const Section::StudentRecord& rhs);

public:
    Section(const string& secName, const string& day, unsigned hour) : name(secName), slot(day, hour) { }

    Section(const Section& other) : name(other.name), slot(other.slot) {
        for (const StudentRecord* stuptr : other.students) {
            students.push_back(new StudentRecord(stuptr->getName()));
        }
    }

    ~Section() {
        cout << "Section " << name << " is being deleted" << endl;
        for (size_t i = 0; i < students.size(); i++) {
            cout << "deleting " << students[i]->getName() << endl;
            delete students[i];
            students[i] = nullptr;
        }
    }

    const string& getName() const { return name; }

    void addStudent(const string& stuName) {
        students.push_back(new StudentRecord(stuName));
    }

    bool addGrade(const string& stuName, int grade, int num) {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i]->getName() == stuName) {
                students[i]->setGrade(num-1, grade);
                return true;
            }
        } return false;
    }

private:
    string name;
    Time slot;
    vector<StudentRecord*> students;
};


ostream& operator<<(ostream& os, const Section::Time& rhs) {
    os << "[Day: " << rhs.day << ", Start time: ";
    if (rhs.hour > 12) {
        os << rhs.hour-12 << ' ' << "pm]";
    } else {
        os << rhs.hour << ' ' << "am]";
    } return os;
}

ostream& operator<<(ostream& os, const Section::StudentRecord& rhs) {
    os << "Name: " << rhs.name << ", Grades: ";
    for (int grade : rhs.grades) {
        os << grade << ' ';
    } return os;
}

ostream& operator<<(ostream& os, const Section& rhs) {
    os << "Section: " << rhs.name << ", Time Slot: " << rhs.slot << ", Students: " << endl;
    if (rhs.students.size() == 0) { os << "None"; }
    for (size_t i = 0; i < rhs.students.size(); i++) {
        os << *(rhs.students[i]) << endl;
    }
    return os;
}


// LabWorker Class
class LabWorker {
    friend ostream& operator<<(ostream& os, const LabWorker& rhs);
public:
    LabWorker(const string& lName) : name(lName) { }

    const string& getName() const { return name; }

    bool hasSec() const {
        return !(section == nullptr);
    }

    bool addSection(Section& newSec) {
        if (section == nullptr) {
            section = &newSec;
            return true;
        } return false;
    }

    bool addGrade(const string& stuName, int grade, int num) {
        return section->addGrade(stuName, grade, num);
    }

private:
    string name;
    Section* section=nullptr;
};


ostream& operator<<(ostream& os, const LabWorker& rhs) {
    if (!rhs.section) {
        os << rhs.name << " does not have a section" << endl;
    } else {
        os << rhs.name << " has " << rhs.section;
    } return os;
}


// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main()
{

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Copy Constructor: make sure the following calls work:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n" << secA2 << endl;
} // main
