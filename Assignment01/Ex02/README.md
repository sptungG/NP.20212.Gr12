## Exercise 2. Processing student grades

*Create a `Makefile` to make an executable file with the name **exercise2***

**Description:**
Grading information of a class is stored in a text file having the name of semester ID and subject ID. The file contains the following fields and information:

* One line is the subject ID (with the title “SubjectID”)
* One line is the subject’s name (with the title “Subject”)
* One “F” line provides the percentage of progress and final exam marks (%)
* Some line is the semester code (with the title “Semester”)
* One “StudentCount” line indicates the total number of students in the class (remaining lines in that file)
* After that, each line starts with “S” character and then contains information of student ID, full student name, component marks (progress and final exam, 10-point scale), and grades (according to the following table)
  ![image](https://user-images.githubusercontent.com/61298021/163710908-1604060c-592b-4493-af06-598b97a3e5af.png)

  Delimiter character between fields is “|”

  Example of a subject with the ID of IT4062 naming IT4062_20151.txt is as followed:
    ```sh
    SubjectID|IT4062
    Subject|Network Programming
    F|30|70
    Semester|20151
    StudentCount|4
    S|20101160|NGUYEN VAN |AN | 8.5 | 7.0 | B |
    S|20191182|TRAN QUOC |BO | 10.0 | 9.0 | A |
    S|20111191|LE BANG |CHAN | 5.5 | 4.5 | D |
    S|20101216|NGUYEN VAN |DUONG | 8.5 | 8.5 | A |
    ```
The grading summary was calculated and stored in a file having a name with the following format <Subject ID>_<semester ID>_rp.txt. Here is an example file

```sh
IT4062_20171_rp.txt

The student with the highest mark is: TRAN QUOC BO
The student with the lowest mark is: LE BANG CHAN
The average mark is: 7.51
A histogram of the subject IT4062 is:
A:**
B:*
C:
D:*
F:
```

Where number of * represents the number of students getting that grade.

If there are multiple students getting the highest/lowest grade, only show the name of the first student

Requirement: Write a problem to show a menu as followed and implement the according functions
```sh
Learning Management System
-------------------------------------
1. Add a new score board
2. Add score
3. Remove score
4. Search score
5. Display score board and score report
Your choice (1-5, other to quit)
```

Using link-list to store information of students read from text files.

* Function 1: Add a new score board of a subject in a semester. Information typed from keyboard should be subject information, semester ID, and the number of students
* Function 2: Add marks of a student of a specific subject. Users should provide subject ID and semester ID before adding student information and marks to the right text file
* Function 3: Delete the grade of a student of a subject. Again, users should provide correct subject ID, semester ID and student ID.
* Function 4: Find grade information of a student in a subject.
* Function 5: Show the score board and score report of a subject.

After each function, program needs to ask users whether they want to continue or not. If they type ‘y’ or ‘Y”, continue that function. If not, back to the main menu