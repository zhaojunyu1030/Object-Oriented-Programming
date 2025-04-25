#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace BrooklynPoly {
    class Student;

    class Course {
        friend ostream& operator<<(ostream& os, const Course& rhs);
    public:
        // Course methods needed by Registrar
        Course(const string& courseName);
        const string& getName() const;
        bool addStudent(Student*);

        // Tell the students that they are no longer in the course
        void removeStudentsFromCourse();

    private:
        string name;
        vector<Student*> students;
    }; // Course
}

#endif //COURSE_H
