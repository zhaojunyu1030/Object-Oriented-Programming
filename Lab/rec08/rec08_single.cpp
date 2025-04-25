/*
 * rec08.cpp
 * Created by Junyu (Leo) Zhao on 3/14/2025
 
  Starter Code for required functionality

  Yes, of course, you may add other methods.

  And no, this won't compile. You have to fix the cyclic association
  and implement the methods.

 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

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

int main()
{

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
} // main

Course::Course(const string& courseName) : name(courseName) { }
Student::Student(const string& name) : name(name) { }
Registrar::Registrar() { }


const string& Course::getName() const { return name; }

const string& Student::getName() const { return name;}

bool Course::addStudent(Student* newStu) {
    for (const Student* sptr : students) {
        if (sptr == newStu) {
            return false;
        }
    }
    students.push_back(newStu);
    return true;
}

bool Student::addCourse(Course* newCourse) {
    for (const Course* cptr : courses) {
        if (cptr == newCourse) {
            return false;
        }
    }
    courses.push_back(newCourse);
    return newCourse->addStudent(this);
}

void Course::removeStudentsFromCourse() {
    for (size_t i = 0; i < students.size(); i++) {
        students[i]->removedFromCourse(this);
    }

    students.clear();
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
