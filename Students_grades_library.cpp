#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

class Subject {
private:
    string name;
    vector<int> grades;

public:
    Subject(string name) : name(name) {}

    void addGrades(const vector<int>& newGrades) {
        grades = newGrades;
    }

    string getName() const {
        return name;
    }

    vector<int> getGrades() const {
        return grades;
    }

    float getAverage() const {
        if (grades.empty()) return 0;
        float total = 0;
        for (int grade : grades) {
            total += grade;
        }
        return total / grades.size();
    }

    string getLetterGrade() const {
        float average = getAverage();
        if (average >= 90) return "A";
        if (average >= 80) return "B";
        if (average >= 70) return "C";
        if (average >= 60) return "D";
        return "F";
    }
};

class Student {
private:
    string name;
    int id;
    vector<Subject> subjects;

public:
    Student(string name, int id) : name(name), id(id) {}

    void addSubject(const string& subjectName, const vector<int>& grades) {
        subjects.push_back(Subject(subjectName));
        subjects.back().addGrades(grades);
    }

    string getName() const {
        return name;
    }

    int getId() const {
        return id;
    }

    vector<Subject> getSubjects() const {
        return subjects;
    }

    void printReport() const {
        cout << "Student Name: " << name << endl;
        cout << "Student ID: " << id << endl;
        for (const Subject& subject : subjects) {
            cout << "Subject: " << subject.getName() << endl;
            cout << "Grades: ";
            for (int grade : subject.getGrades()) {
                cout << grade << " ";
            }
            cout << endl;
            cout << "Average: " << fixed << setprecision(2) << subject.getAverage() << endl;
            cout << "Letter Grade: " << subject.getLetterGrade() << endl;
            cout << "--------------------" << endl;
        }
    }

    float calculateOverallAverage() const {
        if (subjects.empty()) return 0;
        float total = 0;
        for (const Subject& subject : subjects) {
            total += subject.getAverage();
        }
        return total / subjects.size();
    }
};

class StudentManager {
private:
    vector<Student> students;

    void saveToFile() {
        ofstream file("students_data.csv");
        if (!file) {
            cout << "Error opening the file." << endl;
            return;
        }
        for (const Student& student : students) {
            file << student.getId() << "," << student.getName();
            for (const Subject& subject : student.getSubjects()) {
                file << "," << subject.getName();
                for (int grade : subject.getGrades()) {
                    file << "," << grade;
                }
            }
            file << endl;
        }
    }

    void loadFromFile() {
        ifstream file("students_data.csv");
        if (!file) {
            cout << "No previous student data found." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> data;
            while (getline(ss, token, ',')) {
                data.push_back(token);
            }
            int id = stoi(data[0]);
            string name = data[1];
            Student student(name, id);
            for (size_t i = 2; i < data.size(); i++) {
                string subjectName = data[i++];
                vector<int> grades;
                while (i < data.size() && isdigit(data[i][0])) {
                    grades.push_back(stoi(data[i++]));
                }
                student.addSubject(subjectName, grades);
            }
            students.push_back(student);
        }
    }

public:
    StudentManager() {
        loadFromFile();  
    }

    ~StudentManager() {
        saveToFile();  
    }

    void addStudent(const string& name, int id) {
        students.push_back(Student(name, id));
    }

    void addGradesToStudent(int id, const string& subjectName, const vector<int>& grades) {
        for (Student& student : students) {
            if (student.getId() == id) {
                student.addSubject(subjectName, grades);
                return;
            }
        }
        cout << "Student with this ID not found." << endl;
    }

    void displayAllStudents() const {
        if (students.empty()) {
            cout << "No student data available." << endl;
            return;
        }
        for (const Student& student : students) {
            student.printReport();
            cout << "--------------------" << endl;
        }
    }

    void displayStudentById(int id) const {
        for (const Student& student : students) {
            if (student.getId() == id) {
                student.printReport();
                return;
            }
        }
        cout << "Student with this ID not found." << endl;
    }

    void showMenu() {
        while (true) {
            cout << "\n=== Student Management ===\n";
            cout << "1. Add Student\n";
            cout << "2. Add Grades to Student\n";
            cout << "3. Display Reports of All Students\n";
            cout << "4. Display Student Report by ID\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;

            switch (choice) {
                case 1: {
                    string name;
                    int id;
                    cout << "Enter student name: ";
                    cin >> name;
                    cout << "Enter student ID: ";
                    cin >> id;
                    addStudent(name, id);
                    break;
                }
                case 2: {
                    int id;
                    string subjectName;
                    cout << "Enter student ID: ";
                    cin >> id;
                    cout << "Enter subject name: ";
                    cin >> subjectName;
                    int numGrades;
                    cout << "Enter number of grades: ";
                    cin >> numGrades;
                    vector<int> grades(numGrades);
                    cout << "Enter the grades: ";
                    for (int i = 0; i < numGrades; i++) {
                        cin >> grades[i];
                    }
                    addGradesToStudent(id, subjectName, grades);
                    break;
                }
                case 3: {
                    displayAllStudents();
                    break;
                }
                case 4: {
                    int id;
                    cout << "Enter student ID: ";
                    cin >> id;
                    displayStudentById(id);
                    break;
                }
                case 5: {
                    cout << "Exiting the program...\n";
                    cout << "\n=== Credits ===\n";
                    cout << "Developed by: Georg Michelle\n";
                    cout << "Course: C++ Programming\n";
                    cout << "Version: 1.0\n";
                    
                    cout << "\n🇪🇬\n";
                    return;
                }
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        }
    }
};

int main() {
    StudentManager manager;
    manager.showMenu();
    return 0;
}