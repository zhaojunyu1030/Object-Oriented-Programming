#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace BrooklynPoly {
    class Course;

    class Student {
        friend ostream& operator<<(ostream& os, const Student& rhs);
    public:
        // Student methods needed by Registrar
        Student(const string& name);
        const string& getName() const;
        bool addCourse(Course*);

        // Student method needed by Course::removeStudentsFromCourse
        void removedFromCourse(Course*);

    private:
        string name;
        vector<Course*> courses;
    }; // Student
}
#endif //STUDENT_H
