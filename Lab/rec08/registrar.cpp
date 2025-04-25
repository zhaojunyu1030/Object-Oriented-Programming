#include "student.h"
#include "course.h"
#include "registrar.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace BrooklynPoly {
    Registrar::Registrar() { }

    bool Registrar::addCourse(const string& courseName) {
        if (findCourse(courseName) != courses.size()) {
            return false;
        }
        courses.push_back(new Course(courseName));
        return true;
    }

    bool Registrar::addStudent(const string& studentName) {
        if (findStudent(studentName) != students.size()) {
            return false;
        }
        students.push_back(new Student(studentName));
        return true;
    }

    bool Registrar::enrollStudentInCourse(const string& studentName,
                                   const string& courseName) {
        size_t sind = findStudent(studentName);
        size_t cind = findCourse(courseName);
        if (sind == students.size() || cind == courses.size()) { return false; }

        return students[sind]->addCourse(courses[cind]);;
    }

    bool Registrar::cancelCourse(const string& courseName) {
        size_t ind = findCourse(courseName);
        if (ind == courses.size()) { return false; }
        courses[ind]->removeStudentsFromCourse();
        delete courses[ind];
        for (size_t i = ind; i < courses.size()-1; i++) {
            courses[i] = courses[i+1];
        }
        courses.pop_back();
        return true;
    }

    void Registrar::purge() {
        for (Course* cptr : courses) {
            delete cptr;
        }
        for (Student* sptr : students) {
            delete sptr;
        }
        courses.clear();
        students.clear();
    }

    size_t Registrar::findStudent(const string& studentName) const {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i]->getName() == studentName) { return i; }
        } return students.size();
    }

    size_t Registrar::findCourse(const string& courseName) const {
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i]->getName() == courseName) { return i; }
        } return courses.size();
    }

    ostream& operator<<(ostream& os, const Registrar& rhs) {
        os << "Registrar's Report" << endl;
        os << "Courses: " << endl;
        for (const Course* cptr : rhs.courses) {
            os << *cptr;
        }
        os << "Students: " << endl;
        for (const Student* sptr : rhs.students) {
            os << *sptr;
        }
        return os;
    }
}