#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#define FILE_NAME "students_data.txt"
#define USERNAME "sakshi"
#define PASSWORD "1717"

class Student {
public:
    int id;
    string name;
    int age;
    string gender;
    string caste;
    string area;
    string school;
    int grade;
    bool is_dropout;

    void input(int studentId) {
        id = studentId;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Gender (Male/Female): ";
        cin >> gender;
        cout << "Enter Caste: ";
        cin >> caste;
        cout << "Enter Area (Urban/Rural): ";
        cin >> area;
        cout << "Enter School Name: ";
        cin >> school;
        cout << "Enter Grade (1 to 12): ";
        cin >> grade;
        cout << "Is the student a dropout? (1 = Yes, 0 = No): ";
        cin >> is_dropout;
    }
};

class AnalysisSystem {
private:
    vector<Student> students;

public:
    bool login() {
        string username, password;
        int attempts = 0;

        while (attempts < 3) {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (username == USERNAME && password == PASSWORD) {
                cout << "Login successful!\n";
                return true;
            } else {
                cout << "Invalid username or password. Try again.\n";
                attempts++;
            }
        }
        return false;
    }

    void inputStudentData() {
        int n;
        cout << "Enter the number of students to add: ";
        cin >> n;

        for (int i = 0; i < n; ++i) {
            Student s;
            s.input(students.size() + 1);
            students.push_back(s);
        }

        cout << n << " student(s) added successfully!\n";
    }

    void displayDropoutAnalysis() {
        int choice;
        do {
            cout << "\n--- Dropout Analysis ---\n";
            cout << "1. School-wise Analysis\n";
            cout << "2. Gender-wise Analysis\n";
            cout << "3. Area-wise Analysis\n";
            cout << "4. Caste-wise Analysis\n";
            cout << "5. Age/Grade-wise Analysis\n";
            cout << "6. Go Back\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: displaySchoolWiseAnalysis(); break;
                case 2: displayGenderWiseAnalysis(); break;
                case 3: displayAreaWiseAnalysis(); break;
                case 4: displayCasteWiseAnalysis(); break;
                case 5: displayAgeGradeWiseAnalysis(); break;
                case 6: return;
                default: cout << "Invalid choice. Try again.\n";
            }
        } while (true);
    }

    void saveToFile() {
        ofstream file(FILE_NAME);
        if (!file) {
            cout << "Error opening file for saving data.\n";
            return;
        }

        for (const Student& s : students) {
            file << s.id << " " << s.name << " " << s.age << " "
                 << s.gender << " " << s.caste << " " << s.area << " "
                 << s.school << " " << s.grade << " " << s.is_dropout << "\n";
        }

        file.close();
        cout << "Data saved successfully!\n";
    }

    void loadFromFile() {
        ifstream file(FILE_NAME);
        if (!file) {
            cout << "No previous data found. Starting fresh.\n";
            return;
        }

        Student s;
        while (file >> s.id >> s.name >> s.age >> s.gender >> s.caste >> s.area >> s.school >> s.grade >> s.is_dropout) {
            students.push_back(s);
        }

        file.close();
    }

private:
    void displaySchoolWiseAnalysis() {
        cout << "\n--- School-wise Dropout Analysis ---\n";
        for (const Student& s : students) {
            if (s.is_dropout)
                cout << "Student " << s.name << " from School " << s.school << " dropped out.\n";
        }
    }

    void displayGenderWiseAnalysis() {
        int maleDropouts = 0, femaleDropouts = 0;
        for (const Student& s : students) {
            if (s.is_dropout) {
                if (s.gender == "Male") maleDropouts++;
                else if (s.gender == "Female") femaleDropouts++;
            }
        }
        cout << "\n--- Gender-wise Dropout Analysis ---\n";
        cout << "Male Dropouts: " << maleDropouts << "\n";
        cout << "Female Dropouts: " << femaleDropouts << "\n";
    }

    void displayAreaWiseAnalysis() {
        int urban = 0, rural = 0;
        for (const Student& s : students) {
            if (s.is_dropout) {
                if (s.area == "Urban") urban++;
                else if (s.area == "Rural") rural++;
            }
        }
        cout << "\n--- Area-wise Dropout Analysis ---\n";
        cout << "Urban Dropouts: " << urban << "\n";
        cout << "Rural Dropouts: " << rural << "\n";
    }

    void displayCasteWiseAnalysis() {
        cout << "\n--- Caste-wise Dropout Analysis ---\n";
        for (const Student& s : students) {
            if (s.is_dropout)
                cout << "Student " << s.name << " from Caste " << s.caste << " dropped out.\n";
        }
    }

    void displayAgeGradeWiseAnalysis() {
        cout << "\n--- Age/Grade-wise Dropout Analysis ---\n";
        for (const Student& s : students) {
            if (s.is_dropout)
                cout << "Student " << s.name << " aged " << s.age << " in Grade " << s.grade << " dropped out.\n";
        }
    }
};

int main() {
    cout << "\nProblem ID: PID048\n";
    cout << "Challenge Title: Student dropout analysis for school education\n";
    cout << "Department: Education Department\n";
    cout << "Challenge Context:\n";
    cout << "\tRight to education is a key concern. Dropout ratio is high due to various reasons.\n";
    cout << "\tGovernment needs analysis for policy making on:\n";
    cout << "\t\t* School wise\n\t\t* Area wise\n\t\t* Gender wise\n\t\t* Caste wise\n\t\t* Age/standard wise\n";
    cout << "Expected Outcome: Focused interventions and reduced dropout rates.\n\n";

    AnalysisSystem system;

    if (!system.login()) {
        cout << "Login failed. Exiting...\n";
        return 0;
    }

    system.loadFromFile();

    int choice;
    do {
        cout << "\n==== Student Dropout Analysis Menu ====\n";
        cout << "1. Input Student Data\n";
        cout << "2. View Dropout Analysis\n";
        cout << "3. Save Data\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: system.inputStudentData(); break;
            case 2: system.displayDropoutAnalysis(); break;
            case 3: system.saveToFile(); break;
            case 4: cout << "Exiting. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}

