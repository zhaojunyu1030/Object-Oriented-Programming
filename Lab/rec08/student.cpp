#include "course.h"
#include "student.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace BrooklynPoly {
    Student::Student(const string& name) : name(name) { }

    const string& Student::getName() const { return name;}

    bool Student::addCourse(Course* newCourse) {
        for (const Course* cptr : courses) {
            if (cptr == newCourse) {
                return false;
            }
        }
        courses.push_back(newCourse);
        return newCourse->addStudent(this);
    }

    void Student::removedFromCourse(Course* cptr) {
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i] == cptr) {
                courses[i] = nullptr;
                for (size_t j = i; j < courses.size()-1; j++) {
                    courses[j] = courses[j+1];
                }
                courses.pop_back();
                break;
            }
        }
    }

    ostream& operator<<(ostream& os, const Student& rhs) {
        os << rhs.name << ": ";
        if (rhs.courses.size() == 0) {
            cout << "No courses" << endl;
        } else {
            for (const Course* cptr : rhs.courses) {
                os << cptr->getName() << ' ';
            }
            os << endl;
        }
        return os;
    }
}