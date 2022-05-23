#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sys/stat.h>
#include <cstdlib>

using namespace std;

const int maxStudent = 30;
const string defaultPath = "/Users/truongnguyen/Documents/XCode/ProcessingStudentGrades/ProcessingStudentGrades/"; //in XCODE of MacOS

struct student {
    string id;
    string name;
    string surname;
    float progressMark;
    float finalMark;
    string grade;
};

struct scoreBoard {
    string subjectID;
    string subjectName;
    int progressPercentage;
    int finalPercentage;
    string semester;
    int studentCount;
    struct student students[maxStudent];
};

struct scoreBoard sb;
int currentStudent;

bool checkFileWithStat(string path) {
  struct stat buffer;
  return stat(path.c_str(), &buffer) == 0;
}

void addScoreBoard() {
    string data;
    
    cout << "Enter the subject ID: ";
    string subID; cin >> subID;
    cout << "Enter the subject's name: ";
    fflush(stdin); char subName[30]; fgets(subName, sizeof(subName)+1, stdin);
    cout << "Enter the percentage of progress exam marks (%): ";
    string progressPercentage; cin >> progressPercentage;
    cout << "Enter the percentage of final exam marks (%): ";
    string finalPercentage; cin >> finalPercentage;
    cout << "Enter the semester code: ";
    string semID; cin >> semID;
    cout << "Enter the total number of students in the class: ";
    string stuCount; cin >> stuCount;
    
    data = "SubjectID|" + subID + "\nSubject|" + subName + "F|" + progressPercentage + "|" + finalPercentage + "\nSemester|" + semID + "\nStudentCount|" + stuCount;
    
    string path = defaultPath + subID + "_" + semID + ".txt";
    if (checkFileWithStat(path)) {
        cout << "The score board already exists!\n";
    } else {
        fstream f;
        f.open(path, ios::out);
        f << data;
        f.close();
    }
}

void load(string path)
{
    fstream ff;
    ff.open(path, ios::in);
   
    char row[200];
    const char s[2] = "|";
    char *token;
    
    ff.getline(row, 200);
    token = strtok(row, s); token = strtok(NULL, s);
    sb.subjectID = token;
    
    ff.getline(row, 200);
    token = strtok(row, s); token = strtok(NULL, s);
    sb.subjectName = token;
    
    ff.getline(row, 200);
    token = strtok(row, s); token = strtok(NULL, s);
    sb.progressPercentage = atoi(token);
    token = strtok(NULL, s);
    sb.finalPercentage = atoi(token);
    
    ff.getline(row, 200);
    token = strtok(row, s); token = strtok(NULL, s);
    sb.semester = token;
    
    ff.getline(row, 200);
    token = strtok(row, s); token = strtok(NULL, s);
    sb.studentCount = atoi(token);
    
    currentStudent = 0;
    while (!ff.eof()){
        ff.getline(row, 200);
        token = strtok(row, s); token = strtok(NULL, s);
        sb.students[currentStudent].id = token;
        token = strtok(NULL, s); sb.students[currentStudent].surname = token;
        token = strtok(NULL, s); sb.students[currentStudent].name = token;
        token = strtok(NULL, s); sb.students[currentStudent].progressMark = atof(token);
        token = strtok(NULL, s); sb.students[currentStudent].finalMark = atof(token);
        token = strtok(NULL, s); sb.students[currentStudent].grade = token;
        currentStudent++;
    }
    ff.close();
}

void updateReportFile(string path)
{
    fstream f;
    f.open(path, ios::out);
    float maxMark = -1, minMark = 11, avgMark, sum = 0;
    string maxName, minName;
    for (int i=0; i<currentStudent; i++) {
        float mark = (sb.students[i].progressMark * sb.progressPercentage + sb.students[i].finalMark * sb.finalPercentage) / 100;
        sum += mark;
        if (maxMark < mark) {
            maxMark = mark;
            maxName = sb.students[i].surname + " " + sb.students[i].name;
        }
        if (minMark > mark) {
            minMark = mark;
            minName = sb.students[i].surname + " " + sb.students[i].name;
        }
    }
    avgMark = sum / currentStudent;
    
    string data = "The student with the highest mark is: " + maxName + "\nThe student with the lowest mark is: " + minName + "\nThe average mark is: " + to_string(avgMark) + "\n\nA histogram of the subject " + sb.subjectID + " is:\n";
    data += "A:";
    for (int i=0; i<currentStudent; i++) {
        if (sb.students[i].grade == "A") {
            data += "*";
        }
    }
    data += "\nB:";
    for (int i=0; i<currentStudent; i++) {
        if (sb.students[i].grade == "B") {
            data += "*";
        }
    }
    data += "\nC:";
    for (int i=0; i<currentStudent; i++) {
        if (sb.students[i].grade == "C") {
            data += "*";
        }
    }
    data += "\nD:";
    for (int i=0; i<currentStudent; i++) {
        if (sb.students[i].grade == "D") {
            data += "*";
        }
    }
    data += "\nF:";
    for (int i=0; i<currentStudent; i++) {
        if (sb.students[i].grade == "F") {
            data += "*";
        }
    }
    f << data;
    f.close();
}

void save(string path) {
    fstream f;
    f.open(path, ios::out);
    string data;
    
    data = "SubjectID|" + sb.subjectID + "\nSubject|" + sb.subjectName + "\nF|" + to_string(sb.progressPercentage) + "|" + to_string(sb.finalPercentage) + "\nSemester|" + sb.semester + "\nStudentCount|" + to_string(sb.studentCount);
    
    for (int i=0; i<currentStudent; i++) {
        data += "\nS|" + sb.students[i].id + "|" + sb.students[i].surname + "|" + sb.students[i].name + "|" + to_string(sb.students[i].progressMark) + "|" + to_string(sb.students[i].finalMark) + "|" + sb.students[i].grade + "|";
    }
    
    f << data;
    f.close();
    
    string pathRp = defaultPath + sb.subjectID + "_" + sb.semester + "_rp.txt";
    updateReportFile(pathRp);
}

void addScore() {
    cout << "Enter the subject ID: ";
    string subID; cin >> subID;
    cout << "Enter the semester code: ";
    string semID; cin >> semID;
    string path = defaultPath + subID + "_" + semID + ".txt";
    if (!checkFileWithStat(path)) {
        cout << "The score board does not exists!\n";
    } else {
        load(path);
        if (sb.studentCount == currentStudent) {
            cout << "The class is FULL!\n";
        } else {
            cout << "Enter the student ID: ";
            cin >> sb.students[currentStudent].id;
            
            cout << "Enter the surname: ";
            fflush(stdin); char subName[30]; fgets(subName, sizeof(subName)+1, stdin);
            sb.students[currentStudent].surname = "";
            for (int j=0; j<=strlen(subName); j++) {
                if (subName[j] == '\n') {
                    break;
                }
                sb.students[currentStudent].surname += subName[j];
            }
            cout << "Enter the name: ";
            cin >> sb.students[currentStudent].name;
            cout << "Enter the progress mark: ";
            cin >> sb.students[currentStudent].progressMark;
            cout << "Enter the final mark: ";
            cin >> sb.students[currentStudent].finalMark;
            fflush(stdin);
            float mark = (sb.students[currentStudent].progressMark * sb.progressPercentage + sb.students[currentStudent].finalMark * sb.finalPercentage) / 100;
            if (10 >= mark && mark >= 8.5) {
                sb.students[currentStudent].grade = "A";
            } else if (8.4 >= mark && mark >= 7) {
                sb.students[currentStudent].grade = "B";
            } else if (6.9 >= mark && mark >= 5.5) {
                sb.students[currentStudent].grade = "C";
            } else if (5.4 >= mark && mark >= 4) {
                sb.students[currentStudent].grade = "D";
            } else {
                sb.students[currentStudent].grade = "F";
            }
            currentStudent++;
            save(path);
            cout << "Add score DONE!\n";
        }
    }
}

void removeScore() {
    cout << "Enter the subject ID: ";
    string subID; cin >> subID;
    cout << "Enter the semester code: ";
    string semID; cin >> semID;
    string path = defaultPath + subID + "_" + semID + ".txt";
    if (!checkFileWithStat(path)) {
        cout << "The score board does not exists!\n";
    } else {
        load(path);
        string idRemove;
        cout << "Enter the student ID: ";
        cin >> idRemove;
        bool flag = false;
        for (int i=0; i<currentStudent; i++) {
            if (sb.students[i].id == idRemove) {
                for (int j=i; j<currentStudent-1; j++) {
                    sb.students[j] = sb.students[j+1];
                }
                currentStudent--;
                flag = true;
                break;
            }
        }
        if (!flag) {
            cout << "The student ID does not exists!\n";
        } else {
            save(path);
            cout << "Remove score DONE!\n";
        }
    }
}

void searchScore() {
    cout << "Enter the subject ID: ";
    string subID; cin >> subID;
    cout << "Enter the semester code: ";
    string semID; cin >> semID;
    string path = defaultPath + subID + "_" + semID + ".txt";
    if (!checkFileWithStat(path)) {
        cout << "The score board does not exists!\n";
    } else {
        load(path);
        string idSearch;
        cout << "Enter the student ID: ";
        cin >> idSearch;
        bool flag = false;
        for (int i=0; i<currentStudent; i++) {
            if (sb.students[i].id == idSearch) {
                cout << "\nStudent's name: " + sb.students[i].surname + " " + sb.students[i].name << endl;
                cout << "Student ID: " + sb.students[i].id << endl;
                cout << "Progress mark: " + to_string(sb.students[i].progressMark) << endl;
                cout << "Final mark: " + to_string(sb.students[i].finalMark) << endl;
                cout << "Grade: " + sb.students[i].grade << endl << endl;
                flag = true;
                break;
            }
        }
        if (!flag) {
            cout << "The student ID does not exists!\n";
        }
    }
}

void display() {
    cout << "Enter the subject ID: ";
    string subID; cin >> subID;
    cout << "Enter the semester code: ";
    string semID; cin >> semID;
    string path = defaultPath + subID + "_" + semID + ".txt";
    if (!checkFileWithStat(path)) {
        cout << "The score board does not exists!\n";
    } else {
        fstream f;
        f.open(path, ios::in);
        char row[200];
        cout << endl;
        while (!f.eof()){
            f.getline(row, 200);
            cout << row << endl;
        }
        f.close();
        
        string pathRp = defaultPath + subID + "_" + semID + "_rp.txt";
        f.open(pathRp, ios::in);
        cout << endl;
        while (!f.eof()){
            f.getline(row, 200);
            cout << row << endl;
        }
        cout << endl;
        f.close();
    }
}

int main(int argc, const char * argv[]) {
    tt:
        cout << "\nLearning Management System\n";
        cout << "-------------------------------------\n";
        cout << "    1. Add a new score board\n";
        cout << "    2. Add score\n";
        cout << "    3. Remove score\n";
        cout << "    4. Search score\n";
        cout << "    5. Display score board and score report\n";
        cout << "Your choice (1-5, other to quit): ";
        char c;
        string ip;
        fflush(stdin); cin >> c;
        switch(c) {
            case '1': {
                ip = "Y";
                while (ip == "Y" || ip == "y") {
                    addScoreBoard();
                    cout << "Do you want to continue? ";
                    cin >> ip;
                }
                goto tt;
            }
            case '2': {
                ip = "Y";
                while (ip == "Y" || ip == "y") {
                    addScore();
                    cout << "Do you want to continue? ";
                    cin >> ip;
                }
                goto tt;
            }
            case '3': {
                ip = "Y";
                while (ip == "Y" || ip == "y") {
                    removeScore();
                    cout << "Do you want to continue? ";
                    cin >> ip;
                }
                goto tt;
            }
            case '4': {
                ip = "Y";
                while (ip == "Y" || ip == "y") {
                    searchScore();
                    cout << "Do you want to continue? ";
                    cin >> ip;
                }
                goto tt;
            }
            case '5': {
                ip = "Y";
                while (ip == "Y" || ip == "y") {
                    display();
                    cout << "Do you want to continue? ";
                    cin >> ip;
                }
                goto tt;
            }
            default: {
                return 0;
            }
        }
}
