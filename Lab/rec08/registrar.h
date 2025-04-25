#ifndef REGISTER_H
#define REGISTER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace BrooklynPoly {
    class Course;
    class Student;

    class Registrar {
        friend ostream& operator<<(ostream& os, const Registrar& rhs);
    public:
        Registrar();

        // Creates a new course, if none with that name
        bool addCourse(const string&);
        // Creates a new student, if none with that name
        bool addStudent(const string&);

        // If the student and the course exist, then enroll the student.
        bool enrollStudentInCourse(const string& studentName,
                                   const string& courseName);

        // Unenroll the students from the course and remove the course
        // from the Registrar.
        bool cancelCourse(const string& courseName);

        // Get rid of everything!!!
        void purge();

    private:
        size_t findStudent(const string&) const;
        size_t findCourse(const string&) const;

        vector<Course*> courses;
        vector<Student*> students;
    }; // Registrar
}
#endif //REGISTER_H
