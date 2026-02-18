#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- CLASS 1: COURSE ---
class Course {
private:
    string code;
    string name;

public:
    Course(string c = "N/A", string n = "N/A") {
        code = c;
        name = n;
    }
    string getCourseInfo() {
        return code + " - " + name;
    }
};

// --- CLASS 2: PERSON (Abstract Base) ---
class Person {
protected:
    string name;

public:
    virtual void displayDetails() = 0; // Pure virtual function
    string getName() { return name; } // Helper to find students by name
    virtual ~Person() {} 
};

// --- CLASS 3: STUDENT ---
class Student : public Person {
private:
    int id;
    float marks;
    Course studentCourse;

public:
    Student(int sId, string sName, float sMarks, Course sCourse) {
        id = sId;
        name = sName;
        marks = sMarks;
        studentCourse = sCourse;
    }

    // Getter for ID to help with searching
    int getId() { return id; }

    // Encapsulation: Setter with validation
    void setMarks(float m) {
        if (m >= 0 && m <= 100) {
            marks = m;
            cout << "Marks updated successfully!" << endl;
        } else {
            cout << "Error: Marks must be between 0 and 100." << endl;
        }
    }

    string getGrade() {
        if (marks >= 70) return "A";
        else if (marks >= 60) return "B";
        else if (marks >= 50) return "C";
        else return "Fail";
    }

    void displayDetails() override {
        cout << "[ID: " << id << "] Name: " << name 
             << " | Course: " << studentCourse.getCourseInfo() 
             << " | Marks: " << marks << " | Grade: " << getGrade() << endl;
    }
};

// --- MAIN APPLICATION ---
int main() {
    vector<Student*> studentList; // Using Student* directly makes editing easier for now
    
    // Default Data
    studentList.push_back(new Student(101, "Alice Smith", 85, Course("CS101", "Programming")));
    studentList.push_back(new Student(102, "Bob Jones", 45, Course("MA101", "Maths")));

    int choice;
    do {
        cout << "\n--- STUDENT SYSTEM MENU ---" << endl;
        cout << "1. Add Student\n2. Display All\n3. Edit Student Grade\n4. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            int id; string n, cC, cN; float m;
            cout << "ID: "; cin >> id;
            cin.ignore();
            cout << "Name: "; getline(cin, n);
            cout << "Course Code: "; getline(cin, cC);
            cout << "Course Name: "; getline(cin, cN);
            cout << "Marks: "; cin >> m;
            studentList.push_back(new Student(id, n, m, Course(cC, cN)));
        } 
        else if (choice == 2) {
            for (auto s : studentList) s->displayDetails();
        } 
        else if (choice == 3) {
            int searchId;
            cout << "Enter Student ID to edit: ";
            cin >> searchId;
            
            bool found = false;
            for (auto s : studentList) {
                if (s->getId() == searchId) {
                    float newMarks;
                    cout << "Current Marks: " << " (Grade: " << s->getGrade() << ")" << endl;
                    cout << "Enter New Marks: ";
                    cin >> newMarks;
                    s->setMarks(newMarks); // Uses encapsulation
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Student ID not found." << endl;
        }
    } while (choice != 4);

    // Clean up
    for (auto s : studentList) delete s;

    return 0;
}
