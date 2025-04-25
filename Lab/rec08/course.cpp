#include "student.h"
#include "course.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace BrooklynPoly {
    Course::Course(const string& courseName) : name(courseName) { }

    const string& Course::getName() const { return name; }

    bool Course::addStudent(Student* newStu) {
        for (const Student* sptr : students) {
            if (sptr == newStu) {
                return false;
            }
        }
        students.push_back(newStu);
        return true;
    }

    void Course::removeStudentsFromCourse() {
        for (size_t i = 0; i < students.size(); i++) {
            students[i]->removedFromCourse(this);
        }

        students.clear();
    }

    ostream& operator<<(ostream& os, const Course& rhs) {
        os << rhs.name << ": ";
        if (rhs.students.size() == 0) {
            os << "No Students" << endl;
        } else {
            for (const Student* sptr : rhs.students) {
                os << sptr->getName() << ' ';
            }
            os << endl;
        }
        return os;
    }
}