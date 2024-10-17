#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>
using namespace std;

class Student {
public:
    string first_name, last_name, student_id;
    unordered_map<string, int> grades;  

    Student(const string& first, const string& last, const string& id)
        : first_name(first), last_name(last), student_id(id) {}

    void set_grade(const string& assignment_name, int grade) {
        grades[assignment_name] = grade;
    }
};

class Assignment {
public:
    string name;
    int total_points;

    Assignment(const string& assignment_name, int points)
        : name(assignment_name), total_points(points) {}
};

class Gradebook {
private:
    vector<Student> students;
    vector<Assignment> assignments;


    Student* find_student(const string& student_id) {
        for (auto& student : students) {
            if (student.student_id == student_id) {
                return &student;
            }
        }
        return nullptr;
    }

public:

    void add_student(const string& first_name, const string& last_name, const string& student_id) {
        students.emplace_back(first_name, last_name, student_id);
    }
    void add_assignment(const string& assignment_name, int total_points) {
        assignments.emplace_back(assignment_name, total_points);
    }

    void enter_grade(const string& student_id, const string& assignment_name, int grade) {
        Student* student = find_student(student_id);
        if (!student) {
            cerr << "Error: Student with ID " << student_id << " not found.\n";
            return;
        }

        bool assignment_found = false;
        for (const auto& assignment : assignments) {
            if (assignment.name == assignment_name) {
                if (grade >= 0 && grade <= assignment.total_points) {
                    student->set_grade(assignment_name, grade);
                    assignment_found = true;
                } else {
                    cerr << "Error: Invalid grade for assignment " << assignment_name << ".\n";
                }
                break;
            }
        }

        if (!assignment_found) {
            cerr << "Error: Assignment " << assignment_name << " not found.\n";
        }
    }

    void report() const {
        cout << left << setw(15) << "Last Name"
             << setw(15) << "First Name"
             << setw(10) << "Student ID";

        for (const auto& assignment : assignments) {
            cout << setw(10) << assignment.name;
        }
        cout << "\n";

        for (const auto& student : students) {
            cout << left << setw(15) << student.last_name
                 << setw(15) << student.first_name
                 << setw(10) << student.student_id;

            for (const auto& assignment : assignments) {
                auto it = student.grades.find(assignment.name);
                if (it != student.grades.end()) {
                    cout << setw(10) << it->second;
                } else {
                    cout << setw(10) << "none";
                }
            }
            cout << "\n";
        }
    }
};

int main() {
    Gradebook gradebook;

    gradebook.add_student("Bob", "Bobberson", "ABC123");
    gradebook.add_student("Sam", "Sammerson", "DEF456");
    gradebook.add_student("Jess", "Jesserson", "HIJ789");

    gradebook.add_assignment("Quiz 1", 100);
    gradebook.add_assignment("Lab 1", 50);

    gradebook.enter_grade("ABC123", "Quiz 1", 85);
    gradebook.enter_grade("DEF456", "Quiz 1", 95);
    gradebook.enter_grade("HIJ789", "Lab 1", 49);
    gradebook.enter_grade("HIJ789", "Quiz 1", 93);
    gradebook.enter_grade("ABC123", "Lab 1", 0);

    gradebook.report();

    return 0;
}